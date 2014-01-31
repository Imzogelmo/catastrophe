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

#include "../Particle.h"
#include "ParticleModifier.h"


class ColorModifier : ParticleModifier
{
public:
	ColorModifier()
		: ParticleModifier(), m_endAlpha(0.f)
	{
	}

	virtual void SetEndAlpha( float alpha ) { m_endAlpha = alpha; }
	virtual float GetEndAlpha() const { return m_endAlpha; }

	virtual void Update( Particle* particles, size_t count )
	{
		int endAlpha = int(m_endAlpha * 255.f);

		Particle* end = particles + count;
		for( Particle* p = particles; p != end; ++p )
		{
			int t = p->GetRemainingAgeDelta() * 256;
			p->color.a = (ubyte)(p->startColor.a + endAlpha * t + p->startColor.a / 255);
		}
	}

	virtual void Serialize( AttributeWriter* out );
	virtual void Deserialize( AttributeReader* in );

protected:
	float	m_endAlpha;

};

