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

#include "ParticleModifier.h"
#include "Catastrophe/Core/Math/Colorf.h"

#include "Catastrophe/Core/Containers/StaticVector.h"

/* 
 * Modifier that linearly interpolates between any amount
 * of colors during a particles lifetime.
 */
class ColorInterpolatorModifier : public ParticleModifier
{
public:
	enum {
		MaxColors = 8
	};

	ColorInterpolatorModifier();

	virtual void AddColor( const Colorf& color );
	virtual void Update( Particle* particles, u32 count );

	virtual void Serialize( AttributeWriter* f );
	virtual void Deserialize( AttributeReader* f );

protected:
	StaticVector<Colorf, MaxColors> m_colors;

};
