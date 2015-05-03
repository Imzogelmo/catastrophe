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

#include "Catastrophe/Core/Math/Color.h"
#include "Catastrophe/Core/Math/Colorf.h"
#include "Catastrophe/Core/Math/HSLColor.h"
#include "Catastrophe/Core/PlatformMath.h"
#include "Catastrophe/Core/Math/MathUtil.h"

CE_NAMESPACE_BEGIN



HSLColor::HSLColor( const Color &c )
{
	*this = c.ToColorf();
}


HSLColor::HSLColor( const Colorf &c )
{
	*this = RgbToHsl(c.r, c.g, c.b, c.a);
}


HSLColor& HSLColor::operator = ( const Color &c )
{
	*this = c.ToColorf();
	return *this;
}


HSLColor& HSLColor::operator = ( const Colorf &c )
{
	*this = RgbToHsl(c.r, c.g, c.b, c.a);
	return *this;
}


Color HSLColor::ToColor() const
{
	return HslToRgb(h, s, l, a).ToColor();
}


Colorf HSLColor::ToColorf() const
{
	return HslToRgb(h, s, l, a);
}


HSLColor HSLColor::RgbToHsl( const Colorf& c )
{
	return RgbToHsl(c.r, c.g, c.b, c.a);
}


HSLColor HSLColor::RgbToHsl( float red, float green, float blue, float alpha )
{
	float hue(0), saturation(0), luminance(0);
	
	const float minColor = Math::Min( red, green, blue );
	const float maxColor = Math::Max( red, green, blue );
	const float d = maxColor - minColor;
	const float e = maxColor + minColor;

	luminance = e / 2.0f;

	if( d == 0.f )
		hue = 0.f, saturation = 0.f;

	else
	{
		if( luminance < 0.5f )
			saturation = d / e;
		else
			saturation = d / (2.f - d);


		if ( red == maxColor )
			hue = (blue - green) / d;

		else if ( green == maxColor )
			hue = 2.f + (red - blue) / d;

		else
			hue = 4.f + (red - green) / d;

		hue = Math::WrapDegrees( hue * 60.f );
	}

	return HSLColor( hue, saturation, luminance, alpha );
}


Colorf HSLColor::HslToRgb( const HSLColor& c )
{
	return HslToRgb(c.h, c.s, c.l, c.a);
}


Colorf HSLColor::HslToRgb( float hue, float saturation, float luminance, float alpha )
{
	Colorf rgb(0.f, alpha);
	
	if( saturation == 0.f )
	{
		rgb.r = luminance;
		rgb.g = luminance;
		rgb.b = luminance;
	}
	else
	{
		float p(0), k(0);
		
		if( luminance < 0.5f )
			p = luminance * (1.f + saturation);
		else
			p = (luminance + saturation) - (luminance * saturation);
			
		k = (luminance * 2.f) - p;
		hue = Math::ClampDegrees( hue ) / 360.f;
		
		const float q = 6.f * hue;
		const float t = 1.f / 3.f;
		hue = hue + t;

		for( int i(0); i < 3; ++i )
		{
			hue = Math::Clamp( hue, 0.f, 1.f );

			if( q < 1.f )
				rgb[ i ] = p + (k - p) * q;

			else if( 2.f * hue < 1.f )
				rgb[ i ] = k;

			else if( 3.f * hue < 2.f )
				rgb[ i ] = p + ((k - p) * ((2.f / 3.f) - hue) * 6.f);

			else rgb[ i ] = p;

			hue -= t;
		}
	}
	
	return rgb;
}


