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
#include "ParticleGroup.h"
#include "Renderers/ParticleRenderer.h"

#include <fc/vector.h>
#include <fc/string.h>

//emitters
#include "Emitters/ParticleEmitter.h"
#include "Emitters/PointEmitter.h"
#include "Emitters/CircleEmitter.h"
#include "Emitters/RectEmitter.h"

//modifiers
#include "Modifiers/ParticleModifier.h"
#include "Modifiers/GravityModifier.h"
#include "Modifiers/ColorModifier.h"
#include "Modifiers/ColorInterpolatorModifier.h"


class ParticleSystem : public ParticleSystemEntity
{
public:
	typedef fc::vector<ParticleGroup*> group_vec_type;

	ParticleSystem();
	~ParticleSystem();

	virtual void AddGroup( ParticleGroup* group );
	virtual void RemoveGroup( ParticleGroup* group );
	virtual void DestroyGroups();

	virtual void SetRenderer( ParticleRenderer* renderer );
	virtual void Create( const Vector2& pos );

	virtual void Update();
	virtual void Render();
	virtual void Render( SpriteBatch* spriteBatch );

	virtual size_t GetParticleCount() const;

	CE_NO_INLINE virtual bool Serialize( const fc::string& filename );
	CE_NO_INLINE virtual bool Deserialize( const fc::string& filename );

	void SetName( const fc::string& name ) { m_name = name; }
	const fc::string& GetName() const { return m_name; }

	group_vec_type&			GetGroups() { return m_groups; }
	const group_vec_type&	GetGroups() const { return m_groups; }

	ParticleRenderer*		GetRenderer() const { return m_renderer; }

protected:
	fc::string			m_name;
	group_vec_type		m_groups;
	ParticleRenderer*	m_renderer;

};

