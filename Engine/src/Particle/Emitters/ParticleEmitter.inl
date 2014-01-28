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

#include "Particle/Emitters/ParticleEmitter.h"
#include "IO/AttributeWriter.h"
#include "IO/AttributeReader.h"


ParticleEmitter::ParticleEmitter() :
	ParticleSystemEntity(),
	m_minLife(120.f),
	m_maxLife(120.f),
	m_minSpeed(0.f),
	m_maxSpeed(0.f),
	m_minFriction(0.f),
	m_maxFriction(0.f),
	m_minAngle(-FC_PI),
	m_maxAngle(FC_PI),
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

	// angles must be in range -pi, pi.
	m_minAngle = fc::clamp(m_minAngle, -FC_PI, FC_PI);
	m_maxAngle = fc::clamp(m_maxAngle, -FC_PI, FC_PI);

	m_hasSizeVariation = !m_minSize.Equals(m_maxSize);
	m_hasScaleVariation = !m_minEndScale.Equals(m_maxEndScale);
	m_hasColorVariation = !m_minColor.Equals(m_maxColor);
}


void ParticleEmitter::SetMinLife( float minLife )
{
	m_minLife = minLife;
}


void ParticleEmitter::SetMaxLife( float maxLife )
{
	m_maxLife = maxLife;
}


void ParticleEmitter::SetMinSpeed( float minSpeed )
{
	m_minSpeed = minSpeed;
}


void ParticleEmitter::SetMaxSpeed( float maxSpeed )
{
	m_maxSpeed = maxSpeed;
}


void ParticleEmitter::SetMinFriction( float minFriction )
{
	m_minFriction = fc::clamp(minFriction, 0.f, 1.f);
}


void ParticleEmitter::SetMaxFriction( float maxFriction )
{
	m_maxFriction = fc::clamp(maxFriction, 0.f, 1.f);
}


void ParticleEmitter::SetMinAngle( float minAngle )
{
	m_minAngle = minAngle;
}


void ParticleEmitter::SetMaxAngle( float maxAngle )
{
	m_maxAngle = maxAngle;
}


void ParticleEmitter::SetMinRotationSpeed( float minRotationSpeed )
{
	m_minRotationSpeed = minRotationSpeed;
}


void ParticleEmitter::SetMaxRotationSpeed( float maxRotationSpeed )
{
	m_maxRotationSpeed = maxRotationSpeed;
}


void ParticleEmitter::SetMinSize( const Vector2& minSize )
{
	m_minSize = minSize;
	m_hasSizeVariation = !m_minSize.Equals(m_maxSize);
}


void ParticleEmitter::SetMaxSize( const Vector2& maxSize )
{
	m_maxSize = maxSize;
	m_hasSizeVariation = !m_minSize.Equals(m_maxSize);
}


void ParticleEmitter::SetMinEndScale( const Vector2& minScale )
{
	m_minEndScale = minScale;
	m_hasScaleFactor = !(m_minEndScale.Equals(Vector2::One) && m_minEndScale.Equals(Vector2::One));
	m_hasScaleVariation = !m_minEndScale.Equals(m_maxEndScale);
}


void ParticleEmitter::SetMaxEndScale( const Vector2& maxScale )
{
	m_maxEndScale = maxScale;
	m_hasScaleFactor = !(m_minEndScale.Equals(Vector2::One) && m_minEndScale.Equals(Vector2::One));
	m_hasScaleVariation = !m_minEndScale.Equals(m_maxEndScale);
}


void ParticleEmitter::SetMinColor( const Color& minColor )
{
	m_minColor = minColor;
	m_hasColorVariation = !m_minColor.Equals(m_maxColor);
}


void ParticleEmitter::SetMaxColor( const Color& maxColor )
{
	m_maxColor = maxColor;
	m_hasColorVariation = !m_minColor.Equals(m_maxColor);
}


void ParticleEmitter::SetGenerateParticleAngle( bool enable )
{
	m_generateParticleAngle = enable;
}


void ParticleEmitter::GenerateInitialValues( Particle* particles, size_t count )
{
	Particle* end = particles + count;
	for( Particle* p = particles; p != end; ++p )
	{
		// Life
		p->age = 0.f;
		p->lifespan = fc::randf(m_minLife, m_maxLife);
		p->rotationSpeed = fc::randf(m_minRotationSpeed, m_maxRotationSpeed);
		p->friction = 1.f - fc::randf(m_minFriction, m_maxFriction);

		// Size
		if( m_hasSizeVariation )
		{
			p->size.x = 0.5f * fc::randf(m_minSize.x, m_maxSize.x);
			p->size.y = 0.5f * fc::randf(m_minSize.y, m_maxSize.y);
		}
		else
		{
			p->size = m_minSize * 0.5f;
		}

		// Scale
		if( m_hasScaleFactor )
		{
			float x, y;
			if( m_hasScaleVariation )
			{
				x = fc::randf(m_minEndScale.x, m_maxEndScale.x);
				y = fc::randf(m_minEndScale.y, m_maxEndScale.y);
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
		if( m_hasColorVariation )
		{
			p->color = Color(
				(ubyte)fc::rand(m_minColor.r, m_maxColor.r),
				(ubyte)fc::rand(m_minColor.g, m_maxColor.g),
				(ubyte)fc::rand(m_minColor.b, m_maxColor.b),
				(ubyte)fc::rand(m_minColor.a, m_maxColor.a)
			);
		}
		else
		{
			p->color = m_minColor;
		}

		p->startColor = p->color;
	}
}


void ParticleEmitter::Emit( const Vector2& pos, Particle* particles, size_t count )
{
	// This will initialize all basic particle values except emitter-specific values.
	GenerateInitialValues(particles, count);

	Particle* end = particles + count;
	for( Particle* p = particles; p != end; ++p )
	{
		float angle = fc::wrap_radians( fc::randf(m_minAngle, m_maxAngle) );
		float speed = fc::randf(m_minSpeed, m_maxSpeed);

		Vector2 force;
		fc::fast_sincos( angle, force.y, force.x);

		p->pos = pos;
		p->velocity = force * speed;

		// first check if the particle needs a direction facing angle
		if( m_generateParticleAngle ) p->angle = angle;
		else p->angle = 0.f;
	}
}


void ParticleEmitter::Serialize( AttributeWriter* out )
{
	out->BeginNode("Life");
	out->SetFloat("min", m_minLife);
	out->SetFloat("max", m_maxLife);
	out->EndNode();

	out->BeginNode("Speed");
	out->SetFloat("min", m_minSpeed);
	out->SetFloat("max", m_maxSpeed);
	out->EndNode();

	out->BeginNode("Friction");
	out->SetFloat("min", m_minFriction);
	out->SetFloat("max", m_maxFriction);
	out->EndNode();

	out->BeginNode("Angle");
	out->SetFloat("min", m_minAngle);
	out->SetFloat("max", m_maxAngle);
	out->EndNode();

	out->BeginNode("RotationSpeed");
	out->SetFloat("min", m_minRotationSpeed);
	out->SetFloat("max", m_maxRotationSpeed);
	out->EndNode();

	out->BeginNode("Size");
	out->SetVector2("min", m_minSize);
	out->SetVector2("max", m_maxSize);
	out->EndNode();

	out->BeginNode("EndScale");
	out->SetVector2("min", m_minEndScale);
	out->SetVector2("max", m_maxEndScale);
	out->EndNode();

	out->BeginNode("Color");
	out->SetColor("min", m_minColor);
	out->SetColor("max", m_maxColor);
	out->EndNode();

	out->SetBoolElement("GenerateParticleAngle", m_generateParticleAngle);
}


void ParticleEmitter::Deserialize( AttributeReader* in )
{
	if( in->SetToChild("Life") )
	{
		m_minLife = in->GetFloat("min", m_minLife);
		m_maxLife = in->GetFloat("MaxLife", m_maxLife);
		in->SetToParent();
	}

	if( in->SetToChild("Speed") )
	{
		m_minSpeed = in->GetFloat("min", m_minSpeed);
		m_maxSpeed = in->GetFloat("MaxSpeed", m_maxSpeed);
		in->SetToParent();
	}

	if( in->SetToChild("Friction") )
	{
		m_minFriction = in->GetFloat("min", m_minFriction);
		m_maxFriction = in->GetFloat("MaxFriction", m_maxFriction);
		in->SetToParent();
	}

	if( in->SetToChild("Angle") )
	{
		m_minAngle = in->GetFloat("min", m_minAngle);
		m_maxAngle = in->GetFloat("MaxAngle", m_maxAngle);
		in->SetToParent();
	}

	if( in->SetToChild("RotationSpeed") )
	{
		m_minRotationSpeed = in->GetFloat("min", m_minRotationSpeed);
		m_maxRotationSpeed = in->GetFloat("MaxRotationSpeed", m_maxRotationSpeed);
		in->SetToParent();
	}

	if( in->SetToChild("Size") )
	{
		m_minSize = in->GetVector2("min", m_minSize);
		m_maxSize = in->GetVector2("MaxSize", m_maxSize);
		in->SetToParent();
	}

	if( in->SetToChild("EndScale") )
	{
		m_minEndScale = in->GetVector2("min", m_minEndScale);
		m_maxEndScale = in->GetVector2("MaxEndScale", m_maxEndScale);
		in->SetToParent();
	}

	if( in->SetToChild("Color") )
	{
		m_minColor = in->GetColor("min", m_minColor);
		m_maxColor = in->GetColor("MaxColor", m_maxColor);
		in->SetToParent();
	}

	m_generateParticleAngle = in->GetBoolElement("GenerateParticleAngle", m_generateParticleAngle);

	ValidateAttributes();
}
