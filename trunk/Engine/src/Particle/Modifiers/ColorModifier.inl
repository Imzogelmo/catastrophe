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

#include "Math/Math.h"
#include "Particle/Modifiers/ColorModifier.h"
#include "IO/AttributeWriter.h"
#include "IO/AttributeReader.h"



ColorModifier::ColorModifier( const Color& endColor ) :
	ParticleModifier(),
	m_endColor(endColor)
{
}


void ColorModifier::Update( Particle* particles, u32 count )
{
	Color endColor = m_endColor;

	Particle* end = particles + count;
	for( Particle* p = particles; p != end; ++p )
	{
		float t = p->GetAgeDelta();
		p->color = Color::Lerp(p->startColor, endColor, t);
	}
}


void ColorModifier::Serialize( AttributeWriter* out )
{
	out->BeginNode("ColorModifier");
	out->SetColorElement("EndColor", m_endColor);
	out->EndNode();
}


void ColorModifier::Deserialize( AttributeReader* in )
{
	m_endColor = in->GetColorElement("EndColor", Color::White(0));
}


