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

#include "Catastrophe/Core/Math/Vector2.h"
#include "Catastrophe/Core/Math/Vector3.h"
#include "Catastrophe/Core/Math/Vector4.h"
#include "Catastrophe/Core/Math/Color.h"
#include "Catastrophe/Core/Math/Colorf.h"
#include "Catastrophe/Core/Math/HSVColor.h"
#include "Catastrophe/Core/Math/HSLColor.h"

CE_NAMESPACE_BEGIN



Colorf::Colorf( const Vector3 &v )
	: r(v.x), g(v.y), b(v.z), a(1.f)
{
}


Colorf::Colorf( const Vector4 &v )
	: r(v.x), g(v.y), b(v.z), a(v.w)
{
}


Colorf::Colorf( const Color &c )
{
	const float inv = 1.f / 255.f;
	r = (c.r * inv);
	g = (c.g * inv);
	b = (c.b * inv);
	a = (c.a * inv);
}


Colorf::Colorf( const HSVColor &c )
{
	*this = HSVColor::HsvToRgb(c);
}


Colorf::Colorf( const HSLColor &c )
{
	*this = HSLColor::HslToRgb(c);
}


Colorf& Colorf::operator = ( const Color &c )
{
	const float inv = 1.f / 255.f;
	r = (c.r * inv);
	g = (c.g * inv);
	b = (c.b * inv);
	a = (c.a * inv);

	return *this;
}


Colorf& Colorf::operator = ( const HSVColor &c )
{
	*this = HSVColor::HsvToRgb(c);
	return *this;
}


Colorf& Colorf::operator = ( const HSLColor &c )
{
	*this = HSLColor::HslToRgb(c);
	return *this;
}


bool Colorf::Equals( const Colorf &c, float epsilon ) const
{
	if( !Math::EpsilonCompare( r, c.r, epsilon ) ) return false;
	if( !Math::EpsilonCompare( g, c.g, epsilon ) ) return false;
	if( !Math::EpsilonCompare( b, c.b, epsilon ) ) return false;
	if( !Math::EpsilonCompare( a, c.a, epsilon ) ) return false;

	return true;
}


Colorf Colorf::operator * ( const Colorf &c ) const
{
	return Colorf(
		(r * c.r) / 2.f,
		(g * c.g) / 2.f,
		(b * c.b) / 2.f,
		(a * c.a) / 2.f );
}


Colorf& Colorf::operator *= ( const Colorf &c )
{
	r = (r * c.r) / 2.f;
	g = (g * c.g) / 2.f;
	b = (b * c.b) / 2.f;
	a = (a * c.a) / 2.f;
	return *this;
}


float Colorf::Intensity() const
{
	return Vector3(r, g, b).Dot( Vector3(0.3333333f) );
}


Colorf Colorf::CmykToRgb() const
{
	return CmykToRgb( r, g, b, a );
}


Colorf Colorf::CmykToRgb( float cyan, float magenta, float yellow, float key ) const
{
	const float K = (1.f - key);

	return Colorf
		(
			K - (K * cyan), K - (K * magenta), K - (K * yellow), 1.f
		);
}


Colorf Colorf::RgbToCmyk() const
{
	return RgbToCmyk( r, g, b );
}


Colorf Colorf::RgbToCmyk( float red, float green, float blue ) const
{
	const float maxColor = Math::Max( red, green, blue );

	return Colorf
		(
			(maxColor - red) / maxColor,
			(maxColor - green) / maxColor,
			(maxColor - blue) / maxColor,
			(1.f - maxColor)
		);
}


Color Colorf::ToColor() const
{
	return Color( *this );
}


Vector4 Colorf::ToVector4() const
{
	return Vector4( r, g, b, a );
}


Vector3 Colorf::ToVector3() const
{
	return Vector3( r, g, b );
}



CE_NAMESPACE_END




