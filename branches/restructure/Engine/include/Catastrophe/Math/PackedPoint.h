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
#include "Point.h"

//disable nameless struct/union warning
#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4201 )
#endif


class CE_API PackedPoint
{
public:
	union {
		struct { short x, y; };
		int value;
	};

	PackedPoint() {}
	PackedPoint( short x, short y )		: x(x), y(y) {}
	PackedPoint( const Point &p )		: x((short)p.x), y((short)p.y) {}

	short		&operator [] ( const short i ) { return *( &x + i ); }
	const short	&operator [] ( const short i ) const { return *( &x + i ); }

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
	PackedPoint operator * ( short val ) const { return PackedPoint ( x * val, y * val ); }
	PackedPoint operator / ( short val ) const { return PackedPoint ( x / val, y / val ); }
	PackedPoint operator + ( short val ) const { return PackedPoint ( x + val, y + val ); }
	PackedPoint operator - ( short val ) const { return PackedPoint ( x - val, y - val ); }

	inline friend PackedPoint operator * ( short val, const PackedPoint &p ) { return PackedPoint( val * p.x, val * p.y ); }
	inline friend PackedPoint operator / ( short val, const PackedPoint &p ) { return PackedPoint( val / p.x, val / p.y ); }
	inline friend PackedPoint operator + ( short val, const PackedPoint &p ) { return PackedPoint( val + p.x, val + p.y ); }
	inline friend PackedPoint operator - ( short val, const PackedPoint &p ) { return PackedPoint( val - p.x, val - p.y ); }

	PackedPoint &operator *= ( const PackedPoint &p ) { x *= p.x; y *= p.y; return *this; }
	PackedPoint &operator /= ( const PackedPoint &p ) { x /= p.x; y /= p.y; return *this; }
	PackedPoint &operator += ( const PackedPoint &p ) { x += p.x; y += p.y; return *this; }
	PackedPoint &operator -= ( const PackedPoint &p ) { x -= p.x; y -= p.y; return *this; }
	PackedPoint &operator *= ( short val ) { x *= val; y *= val; return *this; }
	PackedPoint &operator /= ( short val ) { x /= val; y /= val; return *this; }
	PackedPoint &operator += ( short val ) { x += val; y += val; return *this; }
	PackedPoint &operator -= ( short val ) { x -= val; y -= val; return *this; }

	bool operator == ( const PackedPoint &p ) const { return (value == p.value); }
	bool operator != ( const PackedPoint &p ) const { return !(*this == p); }

	PackedPoint Abs() const { return PackedPoint( Math::Abs(x), Math::Abs(y) );	}
	PackedPoint Negate() const { return PackedPoint(-x, -y); }

	bool IsZero() const { return value == 0; }

	void Clamp( const PackedPoint &min, const PackedPoint &max )
	{
		Math::FastClamp(x, min.x, max.x);
		Math::FastClamp(y, min.y, max.y);
	}

	Point ToPoint() const
	{
		return Point((int)x, (int)y);
	}

	static PackedPoint Zero;

};



CE_NAMESPACE_END


#ifdef _MSC_VER
	#pragma warning ( pop )
#endif
