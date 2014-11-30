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
#include "Particle/Modifiers/ColorInterpolatorModifier.h"
#include "IO/AttributeWriter.h"
#include "IO/AttributeReader.h"



ColorInterpolatorModifier::ColorInterpolatorModifier( u32 maxNumColors ) :
	ParticleModifier(),
	m_colors()
{
	m_colors.reserve(maxNumColors);
}


void ColorInterpolatorModifier::AddColor( const Colorf& color )
{
	m_colors.push_back(color);
}


void ColorInterpolatorModifier::Update( Particle* particles, u32 count )
{
	const int size = (int)m_colors.size();
	if( size < 2 )
	{
		if( !m_colors.empty() )
		{
			Color c = m_colors[0];
			Particle* end = particles + count;
			for( Particle* p = particles; p < end; ++p )
				p->color = c;
		}

		return;
	}

	float numColors = (float)size;

	Particle* end = particles + count;
	for( Particle* p = particles; p < end; ++p )
	{
		float age = p->GetAgeDelta();

		float m;
		float remainder = modf( age * numColors, &m );
		u32 index = fc::clamp<u32>( (u32)m, 0, size - 2 );

		p->color = Colorf::Lerp( m_colors[index], m_colors[index + 1], remainder );
	}
}


void ColorInterpolatorModifier::Serialize( AttributeWriter* out )
{
	out->BeginNode("ColorInterpolatorModifier");

	u32 count = m_colors.size();
	out->SetUInt("count", count);
	for( u32 i(0); i < count; ++i )
		out->SetColorElement("Color", m_colors[i].ToColor());

	out->EndNode();
}


void ColorInterpolatorModifier::Deserialize( AttributeReader* in )
{
	if( in->GetCurrentNodeName() != "ColorInterpolatorModifier" )
		return;

	u32 count = in->GetUInt("count");
	m_colors.resize(count);
	for( u32 i(0); i < count; ++i )
		m_colors[i] = in->GetColorElement("Color");

}


