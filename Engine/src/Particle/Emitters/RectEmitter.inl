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

#include "Particle/Emitters/RectEmitter.h"
#include "Math/Math.h"
#include "IO/AttributeWriter.h"
#include "IO/AttributeReader.h"


RectEmitter::RectEmitter() : ParticleEmitter()
{
}

RectEmitter::RectEmitter( const ParticleEmitter& emitterBaseValues, const Rectf& boundingRect, float rectAngle, bool wireFrame ) :
	ParticleEmitter(emitterBaseValues),
	m_boundingRect(boundingRect),
	m_boundingRectAngle(rectAngle),
	m_wireFrame(wireFrame)
{
	SetBoundingRectAngle(rectAngle);
}


void RectEmitter::SetBoundingRect( const Rectf& extentRect )
{
	m_boundingRect = extentRect;
}


void RectEmitter::SetBoundingRectAngle( float angle )
{
	m_boundingRectAngle = angle;
	fc::sincos(angle, m_angleSin, m_angleCos);
}


void RectEmitter::SetWireFrame( bool enable )
{
	m_wireFrame = enable;
}


void RectEmitter::Emit( const Vector2& pos, Particle* particles, size_t count )
{
	// This will initialize all basic particle values except emitter-specific values.
	GenerateInitialValues(particles, count);

	Particle* end = particles + count;
	for( Particle* p = particles; p != end; ++p )
	{
		Vector2 offset, emitPosition;

		if( m_wireFrame )
		{
			offset.x = fc::choose(m_boundingRect.min.x, m_boundingRect.max.x);
			offset.y = fc::choose(m_boundingRect.min.y, m_boundingRect.max.y);
		}
		else
		{
			offset.x = fc::randf(m_boundingRect.min.x, m_boundingRect.max.x);
			offset.y = fc::randf(m_boundingRect.min.y, m_boundingRect.max.y);
		}

		emitPosition = pos + offset;

		if( m_boundingRectAngle != 0.f )
		{
			Math::RotatePoint(Vector2(m_angleCos, m_angleSin), pos, emitPosition);
		}

		float angle = fc::randf(m_minAngle, m_maxAngle);
		float speed = fc::randf(m_minSpeed, m_maxSpeed);

		Vector2 force;
		fc::fast_sincos(angle, force.y, force.x);

		p->pos = emitPosition;
		p->velocity = force * speed;

		// first check if the particle needs a direction facing angle
		if( m_generateParticleAngle ) p->angle = angle;
		else p->angle = 0.f;

	}
}


void RectEmitter::Serialize( AttributeWriter* out )
{
	out->BeginNode("RectEmitter");

	out->SetRectfElement("BoundingRect", m_boundingRect);
	out->SetFloatElement("Angle", m_boundingRectAngle);
	out->SetBoolElement("WireFrame", m_wireFrame);
	ParticleEmitter::Serialize(out);

	out->EndNode();
}


void RectEmitter::Deserialize( AttributeReader* in )
{
	if( in->GetCurrentNodeName() != "RectEmitter" )
		return;

	m_boundingRect = in->GetRectfElement("BoundingRect", m_boundingRect);
	m_boundingRectAngle = in->GetFloatElement("Angle", m_boundingRectAngle);
	m_wireFrame = in->GetBoolElement("WireFrame", m_wireFrame);
	ParticleEmitter::Deserialize(in);

	SetBoundingRectAngle(m_boundingRectAngle);
}

