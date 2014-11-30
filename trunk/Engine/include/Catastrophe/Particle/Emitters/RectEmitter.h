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
#include "Math/Rectf.h"


class RectEmitter : public ParticleEmitter
{
public:
	RectEmitter();
	RectEmitter( const ParticleEmitter& emitterBaseValues,
		const Rectf& boundingRect = Rectf::One,
		float rectAngle = 0.f,
		bool wireFrame = false
	);

	virtual void SetBoundingRect( const Rectf& extentRect );
	virtual void SetBoundingRectAngle( float angle );
	virtual void SetWireFrame( bool enable );

	virtual Rectf GetBoundingRect() const { return m_boundingRect; }
	virtual float GetBoundingRectAngle() const { return m_boundingRectAngle; }
	virtual bool GetWireFrame() const { return m_wireFrame; }

	virtual void Emit( const Vector2& pos, Particle* p, u32 count );

	virtual void Serialize( AttributeWriter* out );
	virtual void Deserialize( AttributeReader* in );

protected:
	Rectf	m_boundingRect;
	float	m_boundingRectAngle;
	float	m_angleCos;
	float	m_angleSin;
	bool	m_wireFrame;

};

