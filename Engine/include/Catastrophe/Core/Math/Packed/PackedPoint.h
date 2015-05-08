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

#include "Catastrophe/Core/Common.h"

#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4201 ) // disable nameless struct/union warning
#endif


class CE_API PackedPoint
{
public:
	union {
		struct { s16 x, y; };
		int value;
	};

	PackedPoint() {}
	PackedPoint( s16 x, s16 y ) : x(x), y(y) {}
	PackedPoint( const Point &p );

	s16& operator [] ( const s16 i ) { return *( &x + i ); }
	const s16& operator [] ( const s16 i ) const { return *( &x + i ); }

	PackedPoint operator - () const { return Negate(); }
	PackedPoint operator + () const { return Abs(); }

	PackedPoint &operator ++ ()    { ++x;   ++y;   return *this; }
	PackedPoint &operator -- ()    { --x;   --y;   return *this; }
	PackedPoint  operator ++ (int) { PackedPoint tmp(*this); x++; y++; return tmp; }
	PackedPoint  operator -- (int) { PackedPoint tmp(*this); x--; y--; return tmp; }

	PackedPoint operator * ( const PackedPoint &p )	const { return PackedPoint ( x * p.x, y * p.y ); }
	PackedPoint operator / ( const PackedPoint &p )	const { return PackedPoint ( x / p.x, y / p.y ); }
	PackedPoint operator + ( const PackedPoint &p )	const { return PackedPoint ( x + p.x, y + p.y ); }
	PackedPoint operator - ( const PackedPoint &p )	const { return PackedPoint ( x - p.x, y - p.y ); }
	PackedPoint operator * ( s16 val ) const { return PackedPoint ( x * val, y * val ); }
	PackedPoint operator / ( s16 val ) const { return PackedPoint ( x / val, y / val ); }
	PackedPoint operator + ( s16 val ) const { return PackedPoint ( x + val, y + val ); }
	PackedPoint operator - ( s16 val ) const { return PackedPoint ( x - val, y - val ); }

	inline friend PackedPoint operator * ( s16 val, const PackedPoint &p ) { return PackedPoint( val * p.x, val * p.y ); }
	inline friend PackedPoint operator / ( s16 val, const PackedPoint &p ) { return PackedPoint( val / p.x, val / p.y ); }
	inline friend PackedPoint operator + ( s16 val, const PackedPoint &p ) { return PackedPoint( val + p.x, val + p.y ); }
	inline friend PackedPoint operator - ( s16 val, const PackedPoint &p ) { return PackedPoint( val - p.x, val - p.y ); }

	PackedPoint &operator *= ( const PackedPoint &p ) { x *= p.x; y *= p.y; return *this; }
	PackedPoint &operator /= ( const PackedPoint &p ) { x /= p.x; y /= p.y; return *this; }
	PackedPoint &operator += ( const PackedPoint &p ) { x += p.x; y += p.y; return *this; }
	PackedPoint &operator -= ( const PackedPoint &p ) { x -= p.x; y -= p.y; return *this; }
	PackedPoint &operator *= ( s16 val ) { x *= val; y *= val; return *this; }
	PackedPoint &operator /= ( s16 val ) { x /= val; y /= val; return *this; }
	PackedPoint &operator += ( s16 val ) { x += val; y += val; return *this; }
	PackedPoint &operator -= ( s16 val ) { x -= val; y -= val; return *this; }

	bool operator == ( const PackedPoint &p ) const { return (value == p.value); }
	bool operator != ( const PackedPoint &p ) const { return (value != p.value); }

	PackedPoint Abs() const { return PackedPoint( Math::Abs(x), Math::Abs(y) );	}
	PackedPoint Negate() const { return PackedPoint(-x, -y); }

	bool IsZero() const { return value == 0; }

	void Clamp( const PackedPoint &min, const PackedPoint &max )
	{
		Math::FastClamp(x, min.x, max.x);
		Math::FastClamp(y, min.y, max.y);
	}

	static PackedPoint Zero;
	static PackedPoint One;

};



CE_NAMESPACE_END


#ifdef _MSC_VER
	#pragma warning ( pop )
#endif
