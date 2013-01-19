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



class CE_API HSVColor
{
public:
	float h, s, v, a;

	HSVColor( float h = 0.f, float s = 0.f, float v = 0.f, float a = 1.f ): h(h), s(s), v(v), a(a) {}
	HSVColor( const Colorf &c );
	HSVColor( const Color &c );

	HSVColor &operator = ( const Color &c );
	HSVColor &operator = ( const Colorf &c );

	float		&operator [] ( int i )		 { return *( &h + i ); }
	const float &operator [] ( int i ) const { return *( &h + i ); }

	bool operator == ( const HSVColor &c ) const { return (h == c.h && s == c.s && v == c.v && a == c.a); }
	bool operator != ( const HSVColor &c ) const { return !(*this == c); }

	void Set( float hue, float saturation, float value, float alpha )
	{
		h = hue;
		s = saturation;
		v = value;
		a = alpha;
	}

	void Clamp( const HSVColor &min, const HSVColor &max )
	{
		Math::FastClamp(h, min.h, max.h);
		Math::FastClamp(s, min.s, max.s);
		Math::FastClamp(v, min.v, max.v);
		Math::FastClamp(a, min.a, max.a);
	}

	HSVColor Lerp( const HSVColor& c, float t)
	{
		return Lerp(*this, c, t);
	}

	static HSVColor Lerp( const HSVColor& c1, const HSVColor& c2, float t)
	{
		return HSVColor( 
				c1.h + (c2.h - c1.h) * t,
				c1.s + (c2.s - c1.s) * t,
				c1.v + (c2.v - c1.v) * t,
				c1.a + (c2.a - c1.a) * t 
			);
	}

	Color ToColor() const;
	Colorf ToColorf() const;

	static HSVColor RgbToHsv( const Colorf& c );
	static Colorf HsvToRgb( const HSVColor& c );
	static HSVColor RgbToHsv( float red, float green, float blue, float alpha );
	static Colorf HsvToRgb( float hue, float saturation, float value, float alpha );

};


CE_NAMESPACE_END

