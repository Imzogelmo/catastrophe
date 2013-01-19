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

#include "Common.h"

CE_NAMESPACE_BEGIN



class CE_API HSLColor
{
public:
	float h, s, l, a;

	HSLColor( float h = 0.f, float s = 0.f, float l = 0.f, float a = 1.f ): h(h), s(s), l(l), a(a) {}
	HSLColor( const Colorf &c );
	HSLColor( const Color &c );

	HSLColor &operator = ( const Color &c );
	HSLColor &operator = ( const Colorf &c );

	float		&operator [] ( int i )		 { return *( &h + i ); }
	const float &operator [] ( int i ) const { return *( &h + i ); }

	bool operator == ( const HSLColor &c ) const { return (h == c.h && s == c.s && l == c.l && a == c.a); }
	bool operator != ( const HSLColor &c ) const { return !(*this == c); }

	void Set( float hue, float saturation, float luminance, float alpha )
	{
		h = hue;
		s = saturation;
		l = luminance;
		a = alpha;
	}

	void Clamp( const HSLColor &min, const HSLColor &max )
	{
		Math::FastClamp(h, min.h, max.h);
		Math::FastClamp(s, min.s, max.s);
		Math::FastClamp(l, min.l, max.l);
		Math::FastClamp(a, min.a, max.a);
	}

	HSLColor Lerp( const HSLColor& c, float t)
	{
		return Lerp(*this, c, t);
	}

	static HSLColor Lerp( const HSLColor& c1, const HSLColor& c2, float t)
	{
		return HSLColor( 
				c1.h + (c2.h - c1.h) * t,
				c1.s + (c2.s - c1.s) * t,
				c1.l + (c2.l - c1.l) * t,
				c1.a + (c2.a - c1.a) * t 
			);
	}

	Color ToColor() const;
	Colorf ToColorf() const;

	static HSLColor RgbToHsl( const Colorf& c );
	static Colorf HslToRgb( const HSLColor& c );
	static HSLColor RgbToHsl( float red, float green, float blue, float alpha );
	static Colorf HslToRgb( float hue, float saturation, float luminance, float alpha );

};


CE_NAMESPACE_END

