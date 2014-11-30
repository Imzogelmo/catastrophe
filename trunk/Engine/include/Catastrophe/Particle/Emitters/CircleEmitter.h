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

#include "ParticleEmitter.h"


class CircleEmitter : public ParticleEmitter
{
public:
	enum EmitDirection
	{
		Default,
		Outward,
		Inward
	};

	CircleEmitter();
	CircleEmitter( const ParticleEmitter& emitterBaseValues,
		float radius = 64.f,
		bool outline = false
		//EmitDirection dir = Default

	);

	virtual void SetRadius( float radius );
	virtual void SetOutline( bool enable );
	virtual void SetOutwardForce( bool enable );
	virtual void SetInwardForce( bool enable );

	virtual float GetRadius() const { return m_radius; }
	virtual bool GetOutline() const { return m_outline; }
	virtual bool GetOutwardForce() const { return m_outwardForce; }
	virtual bool GetInwardForce() const { return m_inwardForce; }

	virtual void Emit( const Vector2& pos, Particle* particles, u32 count );

	virtual void Serialize( AttributeWriter* out );
	virtual void Deserialize( AttributeReader* in );

protected:
	float	m_radius;
	bool	m_outline;
	bool	m_outwardForce;
	bool	m_inwardForce;
	//EmitDirection 

};

