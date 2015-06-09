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

#include "Particle/Emitters/ParticleEmitter.h"
#include "Core/IO/AttributeWriter.h"
#include "Core/IO/AttributeReader.h"


ParticleEmitter::ParticleEmitter() :
	ParticleSystemEntity(),
	m_minLife(120.f),
	m_maxLife(120.f),
	m_minSpeed(0.f),
	m_maxSpeed(0.f),
	m_minFriction(0.f),
	m_maxFriction(0.f),
	m_minAngle(-PI),
	m_maxAngle(PI),
	m_minRotationSpeed(0.f),
	m_maxRotationSpeed(0.f),
	m_minSize(Vector2::One),
	m_maxSize(Vector2::One),
	m_minEndScale(Vector2::One),
	m_maxEndScale(Vector2::One),
	m_minColor(Color::White()),
	m_maxColor(Color::White()),
	m_generateParticleAngle(true),
	m_hasScaleFactor(false),
	m_hasSizeVariation(false),
	m_hasScaleVariation(false),
	m_hasColorVariation(false)
{
}


ParticleEmitter::ParticleEmitter(
    float minLife,
    float maxLife,
    float minSpeed,
    float maxSpeed,
    float minFriction,
    float maxFriction,
    float minAngle,
    float maxAngle,
    float minRotationSpeed,
    float maxRotationSpeed,
    const Vector2& minSize,
    const Vector2& maxSize,
    const Vector2& minEndScale,
    const Vector2& maxEndScale,
    const Color& minColor,
    const Color& maxColor
) :
	ParticleSystemEntity(),
	m_minLife(minLife),
	m_maxLife(maxLife),
	m_minSpeed(minSpeed),
	m_maxSpeed(maxSpeed),
	m_minFriction(minFriction),
	m_maxFriction(maxFriction),
	m_minAngle(minAngle),
	m_maxAngle(maxAngle),
	m_minRotationSpeed(minRotationSpeed),
	m_maxRotationSpeed(maxRotationSpeed),
	m_minSize(minSize),
	m_maxSize(maxSize),
	m_minEndScale(minEndScale),
	m_maxEndScale(maxEndScale),
	m_minColor(minColor),
	m_maxColor(maxColor)
{
	m_generateParticleAngle = true;
	ValidateAttributes();
}


void ParticleEmitter::ValidateAttributes()
{
	m_hasScaleFactor = !(m_minEndScale.Equals(Vector2::One) && m_minEndScale.Equals(Vector2::One));

	// angles must be f range -pi, pi.
	m_minAngle = Clamp(m_minAngle, -PI, PI);
	m_maxAngle = Clamp(m_maxAngle, -PI, PI);

	m_hasSizeVariation = !m_minSize.Equals(m_maxSize);
	m_hasScaleVariation = !m_minEndScale.Equals(m_maxEndScale);
	m_hasColorVariation = !m_minColor.Equals(m_maxColor);
}


void ParticleEmitter::SetMinLife(float minLife)
{
	m_minLife = minLife;
}


void ParticleEmitter::SetMaxLife(float maxLife)
{
	m_maxLife = maxLife;
}


void ParticleEmitter::SetMinSpeed(float minSpeed)
{
	m_minSpeed = minSpeed;
}


void ParticleEmitter::SetMaxSpeed(float maxSpeed)
{
	m_maxSpeed = maxSpeed;
}


void ParticleEmitter::SetMinFriction(float minFriction)
{
	m_minFriction = Clamp(minFriction, 0.f, 1.f);
}


void ParticleEmitter::SetMaxFriction(float maxFriction)
{
	m_maxFriction = Clamp(maxFriction, 0.f, 1.f);
}


void ParticleEmitter::SetMinAngle(float minAngle)
{
	m_minAngle = minAngle;
}


void ParticleEmitter::SetMaxAngle(float maxAngle)
{
	m_maxAngle = maxAngle;
}


void ParticleEmitter::SetMinRotationSpeed(float minRotationSpeed)
{
	m_minRotationSpeed = minRotationSpeed;
}


void ParticleEmitter::SetMaxRotationSpeed(float maxRotationSpeed)
{
	m_maxRotationSpeed = maxRotationSpeed;
}


void ParticleEmitter::SetMinSize(const Vector2& minSize)
{
	m_minSize = minSize;
	m_hasSizeVariation = !m_minSize.Equals(m_maxSize);
}


void ParticleEmitter::SetMaxSize(const Vector2& maxSize)
{
	m_maxSize = maxSize;
	m_hasSizeVariation = !m_minSize.Equals(m_maxSize);
}


void ParticleEmitter::SetMinEndScale(const Vector2& minScale)
{
	m_minEndScale = minScale;
	m_hasScaleFactor = !(m_minEndScale.Equals(Vector2::One) && m_minEndScale.Equals(Vector2::One));
	m_hasScaleVariation = !m_minEndScale.Equals(m_maxEndScale);
}


void ParticleEmitter::SetMaxEndScale(const Vector2& maxScale)
{
	m_maxEndScale = maxScale;
	m_hasScaleFactor = !(m_minEndScale.Equals(Vector2::One) && m_minEndScale.Equals(Vector2::One));
	m_hasScaleVariation = !m_minEndScale.Equals(m_maxEndScale);
}


void ParticleEmitter::SetMinColor(const Color& minColor)
{
	m_minColor = minColor;
	m_hasColorVariation = !m_minColor.Equals(m_maxColor);
}


void ParticleEmitter::SetMaxColor(const Color& maxColor)
{
	m_maxColor = maxColor;
	m_hasColorVariation = !m_minColor.Equals(m_maxColor);
}


void ParticleEmitter::SetGenerateParticleAngle(bool enable)
{
	m_generateParticleAngle = enable;
}


void ParticleEmitter::GenerateInitialValues(Particle* particles, u32 count)
{
	Particle* end = particles + count;
	for(Particle* p = particles; p != end; ++p)
	{
		// Life
		p->age = 0.f;
		p->lifespan = Random::Float(m_minLife, m_maxLife);
		p->rotationSpeed = Random::Float(m_minRotationSpeed, m_maxRotationSpeed);
		p->friction = 1.f - Random::Float(m_minFriction, m_maxFriction);

		// Size
		if(m_hasSizeVariation)
		{
			p->size.x = 0.5f * Random::Float(m_minSize.x, m_maxSize.x);
			p->size.y = 0.5f * Random::Float(m_minSize.y, m_maxSize.y);
		}
		else
		{
			p->size = m_minSize * 0.5f;
		}

		// Scale
		if(m_hasScaleFactor)
		{
			float x, y;
			if(m_hasScaleVariation)
			{
				x = Random::Float(m_minEndScale.x, m_maxEndScale.x);
				y = Random::Float(m_minEndScale.y, m_maxEndScale.y);
			}
			else
			{
				x = m_minEndScale.x;
				y = m_minEndScale.y;
			}

			float invLife = -1.f / p->lifespan;
			float sx = (p->size.x - (p->size.x * x)) * invLife;
			float sy = (p->size.y - (p->size.y * y)) * invLife;

			p->growth.x = sx;
			p->growth.y = sy;
		}
		else
		{
			p->growth = 0.f;
		}

		// Color
		if(m_hasColorVariation)
		{
			p->color = Color(
			               (u8)Random::Int(m_minColor.r, m_maxColor.r),
			               (u8)Random::Int(m_minColor.g, m_maxColor.g),
			               (u8)Random::Int(m_minColor.b, m_maxColor.b),
			               (u8)Random::Int(m_minColor.a, m_maxColor.a)
			           );
		}
		else
		{
			p->color = m_minColor;
		}

		p->startColor = p->color;
	}
}


void ParticleEmitter::Emit(const Vector2& position, Particle* particles, u32 count)
{
	// This will initialize all basic particle values except emitter-specific values.
	GenerateInitialValues(particles, count);

	Particle* end = particles + count;
	for(Particle* p = particles; p != end; ++p)
	{
		float angle = Math::WrapAngle(Random::Float(m_minAngle, m_maxAngle));
		float speed = Random::Float(m_minSpeed, m_maxSpeed);

		Vector2 force;
		Math::ApproximateSinCosf(angle, force.y, force.x);

		p->position = position;
		p->velocity = force * speed;

		// first check if the particle needs a direction facing angle
		if(m_generateParticleAngle) p->angle = angle;
		else p->angle = 0.f;
	}
}


void ParticleEmitter::Serialize(AttributeWriter* f)
{
	f->BeginNode("Life");
	f->SetAttribute("min", m_minLife);
	f->SetAttribute("max", m_maxLife);
	f->EndNode();

	f->BeginNode("Speed");
	f->SetAttribute("min", m_minSpeed);
	f->SetAttribute("max", m_maxSpeed);
	f->EndNode();

	f->BeginNode("Friction");
	f->SetAttribute("min", m_minFriction);
	f->SetAttribute("max", m_maxFriction);
	f->EndNode();

	f->BeginNode("Angle");
	f->SetAttribute("min", m_minAngle);
	f->SetAttribute("max", m_maxAngle);
	f->EndNode();

	f->BeginNode("RotationSpeed");
	f->SetAttribute("min", m_minRotationSpeed);
	f->SetAttribute("max", m_maxRotationSpeed);
	f->EndNode();

	f->BeginNode("Size");
	f->SetAttribute("min", m_minSize);
	f->SetAttribute("max", m_maxSize);
	f->EndNode();

	f->BeginNode("EndScale");
	f->SetAttribute("min", m_minEndScale);
	f->SetAttribute("max", m_maxEndScale);
	f->EndNode();

	f->BeginNode("Color");
	f->SetAttribute("min", m_minColor);
	f->SetAttribute("max", m_maxColor);
	f->EndNode();

	f->SetBoolElement("GenerateParticleAngle", m_generateParticleAngle);
}


void ParticleEmitter::Deserialize(AttributeReader* f)
{
	if(f->SetToChild("Life"))
	{
		m_minLife = f->GetAttribute("min", m_minLife);
		m_maxLife = f->GetAttribute("MaxLife", m_maxLife);
		f->SetToParent();
	}

	if(f->SetToChild("Speed"))
	{
		m_minSpeed = f->GetAttribute("min", m_minSpeed);
		m_maxSpeed = f->GetAttribute("MaxSpeed", m_maxSpeed);
		f->SetToParent();
	}

	if(f->SetToChild("Friction"))
	{
		m_minFriction = f->GetAttribute("min", m_minFriction);
		m_maxFriction = f->GetAttribute("MaxFriction", m_maxFriction);
		f->SetToParent();
	}

	if(f->SetToChild("Angle"))
	{
		m_minAngle = f->GetAttribute("min", m_minAngle);
		m_maxAngle = f->GetAttribute("MaxAngle", m_maxAngle);
		f->SetToParent();
	}

	if(f->SetToChild("RotationSpeed"))
	{
		m_minRotationSpeed = f->GetAttribute("min", m_minRotationSpeed);
		m_maxRotationSpeed = f->GetAttribute("MaxRotationSpeed", m_maxRotationSpeed);
		f->SetToParent();
	}

	if(f->SetToChild("Size"))
	{
		m_minSize = f->GetAttribute("min", m_minSize);
		m_maxSize = f->GetAttribute("MaxSize", m_maxSize);
		f->SetToParent();
	}

	if(f->SetToChild("EndScale"))
	{
		m_minEndScale = f->GetAttribute("min", m_minEndScale);
		m_maxEndScale = f->GetAttribute("MaxEndScale", m_maxEndScale);
		f->SetToParent();
	}

	if(f->SetToChild("Color"))
	{
		m_minColor = f->GetAttribute("min", m_minColor);
		m_maxColor = f->GetAttribute("MaxColor", m_maxColor);
		f->SetToParent();
	}

	m_generateParticleAngle = f->GetBoolElement("GenerateParticleAngle", m_generateParticleAngle);

	ValidateAttributes();
}
