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


Color Color::Lerp( const Color& c1, const Color& c2, float t)
{
	return Color
	(
		(ubyte)Math::Clamp<int>( (int)(c1.r + (c2.r - c1.r) * t), 0, 255 ),
		(ubyte)Math::Clamp<int>( (int)(c1.g + (c2.g - c1.g) * t), 0, 255 ),
		(ubyte)Math::Clamp<int>( (int)(c1.b + (c2.b - c1.b) * t), 0, 255 ),
		(ubyte)Math::Clamp<int>( (int)(c1.a + (c2.a - c1.a) * t), 0, 255 )
	);
}


Colorf Color::ToColorf() const
{
	return Colorf( *this );
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



