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



class CE_API Colorf
{
public:
	float r, g, b, a;

	Colorf( float alpha = 1.f ) : r(0.0f), g(0.0f), b(0.0f), a(alpha) {}
	Colorf( float gray, float alpha ) : r(gray), g(gray), b(gray), a(alpha)	{}
	Colorf( float r, float g, float b, float a = 1.f ): r(r), g(g), b(b), a(a) {}
	Colorf( const float* p ) : r(p[0]), g(p[1]), b(p[2]), a(p[3]) {}
	Colorf( const Color &c );
	Colorf( const Vector3 &c );
	Colorf( const Vector4 &c );
	Colorf( const HSVColor &c );
	Colorf( const HSLColor &c );

	Colorf &operator = ( float f ) { r = f; g = f; b = f; a = f; return *this; }
	Colorf &operator = ( const Color &c );
	Colorf &operator = ( const HSVColor &c );
	Colorf &operator = ( const HSLColor &c );

	float		&operator [] ( int i )		 { return *( &r + i ); }
	const float &operator [] ( int i ) const { return *( &r + i ); }

	Colorf operator - () const { return Colorf( 1.f - r, 1.f - g, 1.f - b, a ); }
	Colorf operator + () const { return Colorf( +r, +g, +b, +a ); }
	Colorf operator * ( const Colorf &c ) const;

	Colorf &operator += ( const Colorf &c ) { r += c.r; g += c.g; b += c.b; a += c.a; return *this; }
	Colorf &operator -= ( const Colorf &c ) { r -= c.r; g -= c.g; b -= c.b; a -= c.a; return *this; }
	Colorf &operator *= ( const Colorf &c );

	bool operator == ( const Colorf &c ) const { return (r == c.r && g == c.g && b == c.b && a == c.a); }
	bool operator != ( const Colorf &c ) const { return !(*this == c); }
	
	bool Equals( const Colorf &c, float epsilon = Math::Epsilon ) const;

	Colorf Lerp( const Colorf& c, float t)
	{
		return Colorf( 
				r + (c.r - r) * t,
				g + (c.g - g) * t,
				b + (c.b - b) * t,
				a + (c.a - a) * t 
			);
	}

	static Colorf Lerp( const Colorf& c1, const Colorf& c2, float t)
	{
		return Colorf( 
				c1.r + (c2.r - c1.r) * t,
				c1.g + (c2.g - c1.g) * t,
				c1.b + (c2.b - c1.b) * t,
				c1.a + (c2.a - c1.a) * t 
			);
	}

	void Set( float red, float green, float blue, float alpha )
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	void Clamp()
	{
		Math::FastClamp(r, 0.0f, 1.0f);
		Math::FastClamp(g, 0.0f, 1.0f);
		Math::FastClamp(b, 0.0f, 1.0f);
		Math::FastClamp(a, 0.0f, 1.0f);
	}

	void Clamp( const Colorf &min, const Colorf &max )
	{
		Math::FastClamp(r, min.r, max.r);
		Math::FastClamp(g, min.g, max.g);
		Math::FastClamp(b, min.b, max.b);
		Math::FastClamp(a, min.a, max.a);
	}

	float Intensity() const;

	Colorf Negative() const
	{
		return Colorf( (1.f - r), (1.f - g), (1.f - b), a );
	}

	Colorf Grayscale( bool average = false ) const
	{
		if( average )
			return Colorf( (r + g + b) / 3.333333f, a );

		return Colorf( (0.299f * r) + (0.587f * g) + (0.114f * b), a );
	}

	Colorf CmykToRgb() const;
	Colorf RgbToCmyk() const;
	Colorf RgbToCmyk( float red, float green, float blue ) const;
	Colorf CmykToRgb( float cyan, float magenta, float yellow, float key ) const;

	Color	ToColor() const;
	Vector4 ToVector4() const;
	Vector3 ToVector3() const;

	static Colorf Black( float alpha = 1.f ) { return Colorf( 0.f, 0.f, 0.f, alpha); }
	static Colorf White( float alpha = 1.f ) { return Colorf( 1.f, 1.f, 1.f, alpha); }
	static Colorf Red( float alpha = 1.f ) { return Colorf( 1.f, 0.f, 0.f, alpha); }
	static Colorf Green( float alpha = 1.f ) { return Colorf( 0.f, 1.f, 0.f, alpha); }
	static Colorf Blue( float alpha = 1.f ) { return Colorf( 0.f, 0.f, 1.f, alpha); }
	static Colorf Magenta( float alpha = 1.f ) { return Colorf( 1.f, 0.f, 1.f, alpha); }
	static Colorf Teal( float alpha = 1.f ) { return Colorf( 0.f, 0.5f, 0.5f, alpha); }
	static Colorf Purple( float alpha = 1.f ) { return Colorf( 0.5f, 0.f, 0.5f, alpha); }
	static Colorf Gray( float alpha = 1.f ) { return Colorf( 0.5f, 0.5f, 0.5f, alpha); }
	static Colorf Cyan( float alpha = 1.f ) { return Colorf( 0.f, 1.f, 1.f, alpha); }
	static Colorf Aqua( float alpha = 1.f ) { return Colorf( 0.f, 1.f, 1.f, alpha); }

};



CE_NAMESPACE_END



