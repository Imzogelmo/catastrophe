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

#include "Catastrophe/Core/PlatformMath.h"
#include "Particle/Modifiers/ColorInterpolatorModifier.h"
#include "Core/IO/AttributeWriter.h"
#include "Core/IO/AttributeReader.h"



ColorInterpolatorModifier::ColorInterpolatorModifier() :
	ParticleModifier(),
	m_colors()
{
}


void ColorInterpolatorModifier::AddColor( const Colorf& color )
{
	m_colors.Add(color);
}


void ColorInterpolatorModifier::Update( Particle* particles, u32 count )
{
	const int size = (int)m_colors.size();
	if( size < 2 )
	{
		if( !m_colors.Empty() )
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
	for( Particle* p = particles; p != end; ++p )
	{
		float age = p->GetAgeDelta();

		float m;
		float remainder = modf( age * numColors, &m );
		u32 index = Clamp<u32>( (u32)m, 0, size - 2 );

		p->color = Colorf::Lerp( m_colors[index], m_colors[index + 1], remainder );
	}
}


void ColorInterpolatorModifier::Serialize( AttributeWriter* f )
{
	f->BeginNode("ColorInterpolatorModifier");

	u32 count = m_colors.Size();
	f->SetAttribute("count", count);
	for( u32 i(0); i < count; ++i )
		f->SetColorElement("Color", m_colors[i].ToColor());

	f->EndNode();
}


void ColorInterpolatorModifier::Deserialize( AttributeReader* f )
{
	if( f->GetCurrentNodeName() != "ColorInterpolatorModifier" )
		return;

	u32 count = 0;
	f->GetAttribute("count", count);
	m_colors.Resize(count);

	for( u32 i(0); i < count; ++i )
	{
		Color color = Color::White();
		f->GetColorElement("Color", color);
		m_colors[i] = color;
	}

}


