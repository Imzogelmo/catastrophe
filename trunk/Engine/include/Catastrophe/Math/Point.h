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


class CE_API Point
{
public:
	int x, y;

	Point() {}
	Point( int x, int y )	: x(x), y(y) {}

	int			&operator [] ( const int i )		{ return *( &x + i ); }
	const int	&operator [] ( const int i ) const  { return *( &x + i ); }

	Point operator - () const { return Negate();	}
	Point operator + () const { return Abs();		}

	Point &operator ++ ()    { ++x;   ++y;   return *this; }
	Point &operator -- ()    { --x;   --y;   return *this; }
	Point  operator ++ (int) { Point tmp(*this); x++; y++; return tmp; }
	Point  operator -- (int) { Point tmp(*this); x--; y--; return tmp; }

	Point operator * ( const Point &p )	const { return Point ( x * p.x, y * p.y ); }
	Point operator / ( const Point &p )	const { return Point ( x / p.x, y / p.y ); }
	Point operator + ( const Point &p )	const { return Point ( x + p.x, y + p.y ); }
	Point operator - ( const Point &p )	const { return Point ( x - p.x, y - p.y ); }
	Point operator * ( int val ) const { return Point ( x * val, y * val ); }
	Point operator / ( int val ) const { return Point ( x / val, y / val ); }
	Point operator + ( int val ) const { return Point ( x + val, y + val ); }
	Point operator - ( int val ) const { return Point ( x - val, y - val ); }

	inline friend Point operator * ( int val, const Point &p ) { return Point( val * p.x, val * p.y ); }
	inline friend Point operator / ( int val, const Point &p ) { return Point( val / p.x, val / p.y ); }
	inline friend Point operator + ( int val, const Point &p ) { return Point( val + p.x, val + p.y ); }
	inline friend Point operator - ( int val, const Point &p ) { return Point( val - p.x, val - p.y ); }

	Point &operator *= ( const Point &p ) { x *= p.x; y *= p.y; return *this; }
	Point &operator /= ( const Point &p ) { x /= p.x; y /= p.y; return *this; }
	Point &operator += ( const Point &p ) { x += p.x; y += p.y; return *this; }
	Point &operator -= ( const Point &p ) { x -= p.x; y -= p.y; return *this; }
	Point &operator *= ( int val ) { x *= val; y *= val; return *this; }
	Point &operator /= ( int val ) { x /= val; y /= val; return *this; }
	Point &operator += ( int val ) { x += val; y += val; return *this; }
	Point &operator -= ( int val ) { x -= val; y -= val; return *this; }

	bool operator == ( const Point &p )	const { return ( x == p.x && y == p.y ); }
	bool operator != ( const Point &p )	const { return ( x != p.x && y != p.y ); }

	Point Abs() const { return Point( Math::Abs(x), Math::Abs(y) );	}
	Point Negate() const { return Point(-x, -y);	}

	bool IsZero() const { return (x == 0 && y == 0); }

	void Clamp( const Point &min, const Point &max )
	{
		Math::FastClamp(x, min.x, max.x);
		Math::FastClamp(y, min.y, max.y);
	}

	static Point Zero;
};



CE_NAMESPACE_END



