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

#include "Catastrophe/Core/PlatformMath.h"
#include "Catastrophe/Core/Math/Color.h"
#include "Catastrophe/Core/Math/Colorf.h"
#include "Catastrophe/Core/Math/HSVColor.h"
#include "Catastrophe/Core/PlatformMath.h"

CE_NAMESPACE_BEGIN



HSVColor::HSVColor( const Color &c )
{
	*this = c.ToColorf();
}


HSVColor::HSVColor( const Colorf &c )
{
	*this = RgbToHsv(c.r, c.g, c.b, c.a);
}


HSVColor& HSVColor::operator = ( const Color &c )
{
	*this = c.ToColorf();
	return *this;
}


HSVColor& HSVColor::operator = ( const Colorf &c )
{
	*this = RgbToHsv(c.r, c.g, c.b, c.a);
	return *this;
}


Color HSVColor::ToColor() const
{
	return HsvToRgb(h, s, v, a).ToColor();
}


Colorf HSVColor::ToColorf() const
{
	return HsvToRgb(h, s, v, a);
}


HSVColor HSVColor::RgbToHsv( const Colorf& c )
{
	return RgbToHsv(c.r, c.g, c.b, c.a);
}


HSVColor HSVColor::RgbToHsv( float red, float green, float blue, float alpha )
{
	float minColor = Math::Min( red, green, blue );
	float maxColor = Math::Max( red, green, blue );
	float d = maxColor - minColor;

	if( d == 0.f )
		return Colorf( 0.f, alpha );

	HSVColor c( 0.f, (d / maxColor), maxColor, alpha );

	if( red == maxColor )
		c.h = ( green - blue ) / d;

	else if( green == maxColor )
		c.h = 2.f + ( blue - red ) / d;

	else
		c.h = 4.f + ( red - green ) / d;

	c.h = Math::WrapDegrees( c.h * 60.f );

	return c;
}


Colorf HSVColor::HsvToRgb( const HSVColor& c )
{
	return HsvToRgb(c.h, c.s, c.v, c.a);
}


Colorf HSVColor::HsvToRgb( float hue, float saturation, float value, float alpha )
{
	hue = Math::ClampDegrees( hue ) / 60.f;

	const int i = (int)hue;
	const float f = hue - (float)i;
	const float p = value * ( 1.f - saturation );
	const float q = value * ( 1.f - saturation * f );
	const float t = value * ( 1.f - saturation * ( 1.f - f ) );

	Colorf c( 0.f, 0.f, 0.f, alpha );

	switch( i )
	{
		default:
		case 0:	c.r = value, c.g = t, c.b = p; break;
		case 1:	c.r = q, c.g = value, c.b = p; break;
		case 2:	c.r = p, c.g = value, c.b = t; break;
		case 3:	c.r = p, c.g = q, c.b = value; break;
		case 4:	c.r = t, c.g = p, c.b = value; break;
		case 5:	c.r = value, c.g = p, c.b = q; break;
	}

	return c;
}


