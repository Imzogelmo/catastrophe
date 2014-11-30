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

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Color.h"
#include "Math/Colorf.h"
#include "Math/HSVColor.h"
#include "Math/HSLColor.h"


CE_NAMESPACE_BEGIN



Color::Color( const HSVColor &c )
{
	*this = HSVColor::HsvToRgb(c);
}


Color::Color( const HSLColor &c )
{
	*this = HSLColor::HslToRgb(c);
}


Color& Color::operator = ( const HSVColor &c )
{
	*this = HSVColor::HsvToRgb(c);
	return *this;
}


Color& Color::operator = ( const HSLColor &c )
{
	*this = HSLColor::HslToRgb(c);
	return *this;
}


Color Color::operator *( const Color &c ) const
{
	return Color(
		(u8)(((int)r * c.r) / 255),
		(u8)(((int)g * c.g) / 255),
		(u8)(((int)b * c.b) / 255),
		(u8)(((int)a * c.a) / 255) );
	//return Color( (r + c.r) / 2, (g + c.g) / 2, (b + c.b) / 2, (a + c.a) / 2 );
}


Color Color::Lerp( const Color& c1, const Color& c2, float t )
{
	int x = int(t * 256.f);
	return Color
	(
		u8((c1.r * (255 - x) + c2.r * x) / 255),
		u8((c1.g * (255 - x) + c2.g * x) / 255),
		u8((c1.b * (255 - x) + c2.b * x) / 255),
		u8((c1.a * (255 - x) + c2.a * x) / 255)
	);
}


Colorf Color::ToColorf() const
{
	return Colorf(*this);
}


Vector4 Color::ToVector4() const
{
	return Vector4( _ToFloat(r), _ToFloat(g), _ToFloat(b), _ToFloat(a) );
}


Vector3 Color::ToVector3() const
{
	return Vector3( _ToFloat(r), _ToFloat(g), _ToFloat(b) );
}



CE_NAMESPACE_END




