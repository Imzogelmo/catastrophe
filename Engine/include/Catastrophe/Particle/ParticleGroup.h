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

#pragma once

#include "Particle.h"
#include "ParticleSystemEntity.h"
#include "Destructors/ParticleDestructor.h"
#include "Modifiers/ParticleModifier.h"
#include "Emitters/ParticleEmitter.h"

#include "../Graphics/Sprite.h"

#include <fc/vector.h>
#include <fc/parallel.h>
#include <fc/rand.h>
#include <fc/math.h>

#define CE_DEFAULT_PARTICLE_CAPACITY	1024


/*
 * @ParticleGroup
 * class that groups together particles with similar behaviors
 * such as blending, emission, capacity, and sprite, using the same types
 * of modifiers, emitters, destructors, and renderer.
 */
class ParticleGroup : public ParticleSystemEntity
{
public:
	typedef fc::parallel<Particle>				particle_vec_type;
	typedef fc::vector<ParticleModifier*>		modifier_vec_type;
	typedef fc::vector<ParticleDestructor*>		destructor_vec_type;

	ParticleGroup();
	virtual ~ParticleGroup();

	virtual void Dispose();
	virtual size_t GetParticleCount() const;

	virtual void SetParticleEmitter( ParticleEmitter* emitter );
	virtual void SetEnabled( bool enabled ) { m_enabled = enabled; }
	virtual void SetVisible( bool visible ) { m_visible = visible; }
	virtual void SetParticleCapacity( size_t cap );
	virtual void SetMinEmissionCount( size_t minEmission );
	virtual void SetMaxEmissionCount( size_t maxEmission );
	virtual void SetEmissionCount( size_t minEmission, size_t maxEmission );
	virtual void SetSprite( const AnimatedSprite& sprite ) { m_sprite = sprite; }

	virtual ParticleEmitter* GetParticleEmitter() const { return m_emitter; }
	virtual bool IsEnabled() const { return m_enabled; }
	virtual bool IsVisible() const { return m_visible; }
	virtual size_t GetParticleCapacity() const { return m_particles.capacity(); }
	virtual size_t GetMinEmissionCount() const { return m_minTriggerAmount; }
	virtual size_t GetMaxEmissionCount() const { return m_maxTriggerAmount; }
	virtual Texture* GetTexture() const { return 0; }

	virtual void AddParticleModifier( ParticleModifier* modifier );
	virtual void AddParticleDestructor( ParticleDestructor* destructor );
	virtual void RemoveParticleModifier( ParticleModifier* modifier );
	virtual void RemoveParticleDestructor( ParticleDestructor* destructor );

	virtual void Emit( const Vector2& pos );
	virtual void Emit( const Vector2& pos, size_t numParticles );

	virtual void Update();
	virtual void Render( SpriteBatch* spriteBatch );

	virtual void Kill();
	virtual void RemoveDeadParticles();

	modifier_vec_type& GetModifiers() { return m_modifiers; }
	const modifier_vec_type& GetModifiers() const { return m_modifiers; }

	destructor_vec_type& GetDestructors() { return m_destructors; }
	const destructor_vec_type& GetDestructors() const { return m_destructors; }

	particle_vec_type& GetParticles() { return m_particles; }
	const particle_vec_type& GetParticles() const { return m_particles; }

	CE_NO_INLINE virtual void Serialize( AttributeWriter* out );
	CE_NO_INLINE virtual void Deserialize( AttributeReader* in );

protected:
	ParticleEmitter*		m_emitter;
	particle_vec_type		m_particles;
	modifier_vec_type		m_modifiers;
	destructor_vec_type		m_destructors;

	//sprite
	AnimatedSprite			m_sprite;
	//Texture*		m_texture;
	//BlendMode		m_blendmode;

	//amount of particles emitted on each trigger
	int				m_minTriggerAmount;
	int				m_maxTriggerAmount;

	size_t			m_capacity;
	bool			m_enabled;
	bool			m_visible;
	bool			m_keepParticleOrder;

};

