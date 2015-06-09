// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// f the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included f
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
#include "Core/IO/AttributeWriter.h"
#include "Core/IO/AttributeReader.h"

#include "Catastrophe/Core/Random.h"



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
	if(m_emitter)
	{
		m_emitter->ReleaseRef();
		m_emitter = 0;
	}

	for(u32 i(0); i < m_modifiers.Size(); ++i)
	{
		m_modifiers[i]->ReleaseRef();
	}

	for(u32 i(0); i < m_destructors.Size(); ++i)
	{
		m_destructors[i]->ReleaseRef();
	}

	m_modifiers.Clear();
	m_destructors.Clear();
}


void ParticleGroup::SetParticleCapacity(u32 capacity)
{
	m_capacity = capacity;
	m_particles.SetCapacity(capacity);
}


void ParticleGroup::SetMinEmissionCount(u32 minEmission)
{
	m_minTriggerAmount = minEmission;
}


void ParticleGroup::SetMaxEmissionCount(u32 maxEmission)
{
	m_maxTriggerAmount = maxEmission;
}


void ParticleGroup::SetEmissionCount(u32 minEmission, u32 maxEmission)
{
	if(maxEmission < minEmission)
		Swap(minEmission, maxEmission);

	m_minTriggerAmount = minEmission;
	m_maxTriggerAmount = maxEmission;
}


u32 ParticleGroup::GetParticleCount() const
{
	return m_particles.Size();
}


void ParticleGroup::AddParticleModifier(ParticleModifier* modifier)
{
	if(modifier == null)
		return;

	modifier->AddRef();
	m_modifiers.Add(modifier);
}


void ParticleGroup::RemoveParticleModifier(ParticleModifier* modifier)
{
	if(modifier == null)
		return;

	modifier->ReleaseRef();
	m_modifiers.RemoveValue(modifier);
}


void ParticleGroup::AddParticleDestructor(ParticleDestructor* destructor)
{
	if(!destructor)
		return;

	destructor->AddRef();
	m_destructors.Add(destructor);
}


void ParticleGroup::RemoveParticleDestructor(ParticleDestructor* destructor)
{
	if(destructor != null)
	{
		destructor->ReleaseRef();
		m_destructors.RemoveValue(destructor);
	}
}


void ParticleGroup::SetParticleEmitter(ParticleEmitter* emitter)
{
	if(!emitter)
		return;

	if(m_emitter)
		m_emitter->ReleaseRef();

	emitter->AddRef();
	m_emitter = emitter;
}


void ParticleGroup::Emit(const Vector2& position)
{
	Emit(position, (u32)Random::Int(m_minTriggerAmount, m_maxTriggerAmount));
}


void ParticleGroup::Emit(const Vector2& position, u32 emitCount)
{
	CE_ASSERT(m_emitter != 0);

	emitCount = Math::Min(emitCount, m_particles.Unused());
	if(emitCount > 0)
	{
		Particle* p = m_particles.AddUninitialized(emitCount);
		m_emitter->Emit(position, p, emitCount);
	}
}


void ParticleGroup::Update()
{
	if(!IsEnabled())
		return;

	u32 particleCount = m_particles.Size();
	for(u32 i(0); i < particleCount; ++i)
	{
		Particle& p = m_particles[i];

		float particleAge = ++p.age / p.lifespan;
		if(particleAge > 1.f)
		{
			// add the particle index to the dead particle list.
			m_deadParticles.Add(i);
		}

		p.velocity *= p.friction;
		p.position += p.velocity;
		p.angle += p.rotationSpeed;
		p.size += p.growth;

		//p.endColor = Color::Red(255);
		//p.color = Color::Lerp(p.color,p.endColor,p.GetRemainingAgeDelta());

	}

	// This must be done in Update().
	RemoveDeadParticles();

	// Update modifiers
	for(u32 n(0); n < m_modifiers.Size(); ++n)
	{
		m_modifiers[n]->Update(m_particles.begin(), m_particles.Size());
	}
}


void ParticleGroup::Kill()
{
	m_particles.Clear();
	m_deadParticles.Clear();
}


void ParticleGroup::RemoveDeadParticles()
{
	u32 particleCount = m_particles.Size();
	u32 deadCount = m_deadParticles.Size();

	CE_ASSERT(deadCount <= particleCount);

	if(!m_destructors.Empty() && deadCount > 0)
	{
		for(u32 i(0); i < deadCount; ++i)
		{
			for(u32 j(0); j < m_destructors.Size(); ++j)
			{
				m_destructors[j]->OnDestroy(&m_particles[ m_deadParticles[i] ]);
			}
		}
	}

	if(m_keepParticleOrder)
	{
		// Much faster than erase; compact the entire array in O(n) time.
		m_particles.RemoveIndices(m_deadParticles.begin(), m_deadParticles.Size());
		m_deadParticles.Clear();
	}
	else
	{
		// Even faster method; simply fill removed gaps using particles from the back.
		for(u32 i(0); i < deadCount; ++i)
		{
			m_particles[ m_deadParticles[i] ] = m_particles[--particleCount];
		}

		m_particles.PopBackElements(deadCount);
		m_deadParticles.Clear();
	}
}


void ParticleGroup::Render(SpriteBatch* spriteBatch)
{
	u32 textureID = m_sprite.GetTextureID();
	Rectf uv = m_sprite.GetUVRect();

	spriteBatch->SetBlendMode(m_sprite.GetBlendMode());

	for(Particle* p = m_particles.begin(); p != m_particles.end(); ++p)
	{
		spriteBatch->DrawRotated(
		    textureID,
		    p->angle,
		    p->position,
		    Rectf(p->position - p->size, p->position + p->size),
		    uv,
		    p->color
		);
	}
}


void ParticleGroup::Serialize(AttributeWriter* f)
{
	f->SetAttribute("capacity", m_capacity);
	f->SetBoolElement("KeepParticleOrder", m_keepParticleOrder);

	f->BeginNode("TriggerAmount");
	f->SetAttribute("min", m_minTriggerAmount);
	f->SetAttribute("max", m_maxTriggerAmount);
	f->EndNode();

	f->BeginNode("ParticleEmitter");
	if(m_emitter)
		m_emitter->Serialize(f);
	f->EndNode();

	f->BeginNode("ParticleModifiers");
	for(u32 i(0); i < m_modifiers.Size(); ++i)
	{
		//f->BeginNode(m_modifiers[i]->GetTypeName());
		m_modifiers[i]->Serialize(f);
		//f->EndNode();
	}
	f->EndNode();

	f->BeginNode("ParticleDestructors");
	for(u32 i(0); i < m_destructors.Size(); ++i)
	{
		m_destructors[i]->Serialize(f);
	}
	f->EndNode();

}


void ParticleGroup::Deserialize(AttributeReader* f)
{
	m_capacity = f->GetAttribute("capacity", m_capacity);
	m_keepParticleOrder = f->GetBoolElement("keepParticleOrder", m_keepParticleOrder);

	if(f->SetToChild("TriggerAmount"))
	{
		f->GetAttribute("min", m_minTriggerAmount);
		f->GetAttribute("max", m_maxTriggerAmount);
		f->SetToParent();
	}

}



