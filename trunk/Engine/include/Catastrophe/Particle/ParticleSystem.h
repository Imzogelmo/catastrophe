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

#pragma once

#include "Particle.h"
#include "ParticleSystemEntity.h"
#include "ParticleGroup.h"
#include "Renderers/ParticleRenderer.h"

#include "Catastrophe/Core/Resource/Resource.h"
#include "Catastrophe/Core/Containers/Vector.h"
#include "Catastrophe/Core/Containers/String.h"

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

CE_NAMESPACE_BEGIN


class ParticleSystem : public Resource
{
public:
	//typedef Vector<ParticleGroup*> Vector<ParticleGroup*>;

	ParticleSystem();
	~ParticleSystem();

	virtual void AddGroup(ParticleGroup* group);
	virtual void RemoveGroup(ParticleGroup* group);
	virtual void DestroyGroups();

	virtual void SetRenderer(ParticleRenderer* renderer);
	virtual void Create(const Vector2& position);

	virtual void Update();
	virtual void Render();
	virtual void Render(SpriteBatch* spriteBatch);

	virtual u32 GetNumGroups() const { return m_particleGroups.Size(); }
	virtual u32 GetParticleCount() const;

	virtual bool Serialize(const String& filename);
	virtual bool Deserialize(const String& filename);

	void SetName(const String& name) { m_name = name; }
	const String& GetName() const { return m_name; }

	Vector<ParticleGroup*>& GetParticleGroups() { return m_particleGroups; }
	const Vector<ParticleGroup*>& GetParticleGroups() const { return m_particleGroups; }

	ParticleRenderer*		GetRenderer() const { return m_renderer; }

protected:
	String					m_name;
	Vector<ParticleGroup*>	m_particleGroups;
	ParticleRenderer*		m_renderer;

};

