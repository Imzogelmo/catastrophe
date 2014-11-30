// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "Particle/ParticleGroup.h"
#include "Graphics/SpriteBatch.h"
#include "IO/AttributeWriter.h"
#include "IO/AttributeReader.h"

#include <fc/rand.h>
#include <fc/math.h>



ParticleGroup::ParticleGroup() :
	m_particles(),
	m_modifiers(), 
	m_minTriggerAmount(1),
	m_maxTriggerAmount(1),
	m_capacity(0),
	m_enabled(true),
	m_visible(true),
	m_keepParticleOrder(true)
{
	SetParticleCapacity(CE_DEFAULT_PARTICLE_CAPACITY);
}


ParticleGroup::~ParticleGroup()
{
	Dispose();
}


void ParticleGroup::Dispose()
{
	if( m_emitter )
	{
		m_emitter->ReleaseRef();
		m_emitter = 0;
	}

	for( u32 i(0); i < m_modifiers.size(); ++i )
	{
		m_modifiers[i]->ReleaseRef();
	}

	for( u32 i(0); i < m_destructors.size(); ++i )
	{
		m_destructors[i]->ReleaseRef();
	}

	m_modifiers.clear();
	m_destructors.clear();
}


void ParticleGroup::SetParticleCapacity( u32 cap )
{
	m_capacity = cap;
	m_particles.set_capacity(cap);
}


void ParticleGroup::SetMinEmissionCount( u32 minEmission )
{
	m_minTriggerAmount = minEmission;
}


void ParticleGroup::SetMaxEmissionCount( u32 maxEmission )
{
	m_maxTriggerAmount = maxEmission;
}


void ParticleGroup::SetEmissionCount( u32 minEmission, u32 maxEmission )
{
	if( maxEmission < minEmission )
		fc::swap( minEmission, maxEmission );

	m_minTriggerAmount = minEmission;
	m_maxTriggerAmount = maxEmission;
}


u32 ParticleGroup::GetParticleCount() const
{
	return m_particles.size();
}


void ParticleGroup::AddParticleModifier( ParticleModifier* modifier )
{
	if( !modifier )
		return;

	modifier->AddRef();
	m_modifiers.push_back(modifier);
}


void ParticleGroup::RemoveParticleModifier( ParticleModifier* modifier )
{
	if( !modifier )
		return;

	modifier_vec_type::iterator it = fc::find( m_modifiers.begin(), m_modifiers.end(), modifier );
	if( it != m_modifiers.end() )
	{
		(*it)->ReleaseRef();
		m_modifiers.erase(it);
	}
}


void ParticleGroup::AddParticleDestructor( ParticleDestructor* destructor )
{
	if( !destructor )
		return;

	destructor->AddRef();
	m_destructors.push_back(destructor);
}


void ParticleGroup::RemoveParticleDestructor( ParticleDestructor* destructor )
{
	if(!destructor)
		return;

	destructor_vec_type::iterator it = fc::find( m_destructors.begin(), m_destructors.end(), destructor );
	if( it != m_destructors.end() )
	{
		(*it)->ReleaseRef();
		m_destructors.erase(it);
	}
}


void ParticleGroup::SetParticleEmitter( ParticleEmitter* emitter )
{
	if( !emitter )
		return;

	if( m_emitter )
		m_emitter->ReleaseRef();

	emitter->AddRef();
	m_emitter = emitter;
}


void ParticleGroup::Emit( const Vector2& pos )
{
	Emit(pos, (u32)fc::rand(m_minTriggerAmount, m_maxTriggerAmount));
}


void ParticleGroup::Emit( const Vector2& pos, u32 emitCount )
{
	CE_ASSERT(m_emitter != 0);

	emitCount = fc::min( emitCount, m_particles.unused() );

	if( emitCount > 0 )
	{
		Particle* p = m_particles.push_back_uninitialized(emitCount);
		m_emitter->Emit( pos, p, emitCount );
	}
}


void ParticleGroup::Update()
{
	if( !IsEnabled() )
		return;

	u32 particleCount = m_particles.size();
	for( u32 i(0); i < particleCount; ++i )
	{
		Particle& p = m_particles[i];

		float particleAge = ++p.age / p.lifespan;
		if( particleAge > 1.f )
			m_particles.bind(i);

		p.velocity *= p.friction;
		p.pos += p.velocity;
		p.angle += p.rotationSpeed;
		p.size += p.growth;

		//p.endColor = Color::Red(255);
		//p.color = Color::Lerp(p.color,p.endColor,p.GetRemainingAgeDelta());

	}

	RemoveDeadParticles();

	particleCount = m_particles.size();
	u32 modifierCount = m_modifiers.size();

	for( u32 n (0); n < modifierCount; ++n )
	{
		m_modifiers[n]->Update( m_particles.begin(), particleCount );
	}	
}


void ParticleGroup::Kill()
{
	m_particles.clear();
	m_particles.vacate();	
}


void ParticleGroup::RemoveDeadParticles()
{
	particle_vec_type::cell_type & deadParticlePool = m_particles.get_cells();

	u32 particleCount = m_particles.size();
	u32 deadCount = deadParticlePool.size();

	if( !m_destructors.empty() && deadCount > 0 )
	{
		for( u32 i(0); i < deadCount; ++i )
		{
			for( u32 j(0); j < m_destructors.size(); ++j )
			{
				m_destructors[j]->OnDestroy( &m_particles[ deadParticlePool[i] ] );
			}
		}
	}

	if( m_keepParticleOrder )
	{
		// much faster than erase.
		m_particles.execute();
	}
	else
	{
		// even faster method - simply fill gaps using particles from the back.
		for( u32 i(0); i < deadCount; ++i )
		{
			m_particles[ deadParticlePool[i] ] = m_particles[--particleCount];
		}

		m_particles.resize(particleCount);
		m_particles.vacate();
	}
}


void ParticleGroup::Render( SpriteBatch* spriteBatch )
{
	gluint textureID = m_sprite.GetTextureID();
	Rectf uv = m_sprite.GetUVRect();

	spriteBatch->SetBlendMode(m_sprite.GetBlendMode());

	for( particle_vec_type::const_iterator p = m_particles.begin(); p != m_particles.end(); ++p )
	{
		spriteBatch->DrawRotated(
			textureID,
			p->angle,
			p->pos,
			Rectf(p->pos - p->size, p->pos + p->size),
			uv,
			p->color
		);
	}
}


void ParticleGroup::Serialize( AttributeWriter* out )
{
	out->SetUInt("capacity", m_capacity);
	out->SetBoolElement("KeepParticleOrder", m_keepParticleOrder);

	out->BeginNode("TriggerAmount");
	out->SetInt("min", m_minTriggerAmount);
	out->SetInt("max", m_maxTriggerAmount);
	out->EndNode();

	out->BeginNode("ParticleEmitter");
	if( m_emitter )
		m_emitter->Serialize(out);
	out->EndNode();

	out->BeginNode("ParticleModifiers");
	for( u32 i(0); i < m_modifiers.size(); ++i )
	{
		//out->BeginNode(m_modifiers[i]->GetTypeName());
		m_modifiers[i]->Serialize(out);
		//out->EndNode();
	}
	out->EndNode();

	out->BeginNode("ParticleDestructors");
	for( u32 i(0); i < m_destructors.size(); ++i )
	{
		m_destructors[i]->Serialize(out);
	}
	out->EndNode();

}


void ParticleGroup::Deserialize( AttributeReader* in )
{
	m_capacity = in->GetUInt("capacity", m_capacity);
	m_keepParticleOrder = in->GetBoolElement("keepParticleOrder", m_keepParticleOrder);

	if( in->SetToChild("TriggerAmount") )
	{
		m_minTriggerAmount = in->GetInt("min", m_minTriggerAmount);
		m_minTriggerAmount = in->GetInt("max", m_maxTriggerAmount);
		in->SetToParent();
	}

}



