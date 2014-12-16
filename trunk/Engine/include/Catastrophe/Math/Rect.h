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
#include "Rectf.h"


CE_NAMESPACE_BEGIN


class CE_API Rect
{
public:
	Point pos, size;

	Rect() {}
	Rect( const Point& pos, const Point& size )	: pos(pos), size(size) {}
	Rect( int x, int y, int width, int height )	: pos(x,y), size(width,height) {}
	Rect( const PackedRect& r );
	Rect( const Rectf& r );

	Point		&operator [] ( const int i )		{ return *( &pos + i ); }
	const Point	&operator [] ( const int i ) const  { return *( &pos + i ); }

	bool operator ==( const Rect &r ) const { return ( pos == r.pos && size == r.size ); }
	bool operator !=( const Rect &r ) const { return ( pos != r.pos || size != r.size ); }

	Rect operator + ( const Point &p ) const { return Rect( pos + p, size ); }
	Rect& operator += ( const Point &p ) { pos += p; return *this; }

	inline int Left()	const { return pos.x; }
	inline int Right()	const { return pos.x + size.x; }
	inline int Top()	const { return pos.y; }
	inline int Bottom()	const { return pos.y + size.y; }

	Point TopLeft()		const { return pos; }
	Point TopRight()	const { return Point( pos.x + size.x, pos.y ); }
	Point BottomLeft()	const { return Point( pos.x, pos.y + size.y ); }
	Point BottomRight()	const { return pos + size; }
	Point Center()		const { return pos + (size / 2); }

	void Expand( const Point& amount ) { size += amount; }
	void Inflate( const Point& increase ) { pos -= increase; size += increase * 2; }
	void Deflate( const Point& decrease ) { pos += decrease; size -= decrease * 2; }
	void Offset( const Point& amount ) { pos += amount; }
	void Set( const Point& Pos, const Point& Size ) { pos = Pos; size = Size; }
	void Set( int x, int y, int w, int h ) { pos.x = x; pos.y = y; size.x = w; size.y = h; }

	int Width()		const { return size.x; }
	int Height()	const { return size.y; }
	int Area()		const { return size.x * size.y;	}

	bool Empty() const { return size.IsZero(); }

	inline bool Intersects( const Rect& r ) const
	{
		return( r.pos.x < Right() && pos.x < r.Right() && r.pos.y < Bottom() && pos.y < r.Bottom() );
	}

	inline bool Intersects( const Point& p ) const
	{
		return( p.x < Right() && pos.x < p.x && p.y < Bottom() && pos.y < p.y );
	}

	inline bool Contains( const Point& p ) const
	{
		return Intersects(p);
	}

	inline bool Contains( const Rect& r ) const
	{
		if( r.pos.x < pos.x || r.pos.y < pos.y ) return false;
		if( r.Right() > Right() || r.Bottom() > Bottom() ) return false;
		return true;
	}

	void Merge( const Rect& r );
	Rectf ToRectf() const; //todo...

	static Rect Zero;
	static Rect One;

};




CE_NAMESPACE_END

