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
#include "PackedPoint.h"
#include "Rect.h"

CE_NAMESPACE_BEGIN


class CE_API PackedRect
{
public:
	PackedPoint pos, size;

	PackedRect() {}
	PackedRect( const PackedPoint& pos, const PackedPoint& size ) : pos(pos), size(size) {}
	PackedRect( short x, short y, short width, short height ) : pos(x,y), size(width,height) {}

	PackedPoint			&operator [] ( int i )			{ return *( &pos + i ); }
	const PackedPoint	&operator [] ( int i ) const	{ return *( &pos + i ); }

	bool operator == ( const PackedRect &r ) const { return ( pos == r.pos && size == r.size ); }
	bool operator != ( const PackedRect &r ) const { return ( pos != r.pos || size != r.size ); }

	PackedRect operator * ( const PackedPoint &p )	const { return PackedRect ( pos * p, size ); }
	PackedRect operator / ( const PackedPoint &p )	const { return PackedRect ( pos / p, size ); }
	PackedRect operator + ( const PackedPoint &p )	const { return PackedRect ( pos + p, size ); }
	PackedRect operator - ( const PackedPoint &p )	const { return PackedRect ( pos - p, size ); }
	PackedRect operator * ( const PackedRect &r )	const { return PackedRect ( pos * r.pos, size * r.size ); }
	PackedRect operator / ( const PackedRect &r )	const { return PackedRect ( pos / r.pos, size / r.size ); }
	PackedRect operator + ( const PackedRect &r )	const { return PackedRect ( pos + r.pos, size + r.size ); }
	PackedRect operator - ( const PackedRect &r )	const { return PackedRect ( pos - r.pos, size - r.size ); }

	inline short Left()		const { return pos.x; }
	inline short Right()	const { return pos.x + size.x; }
	inline short Top()		const { return pos.y; }
	inline short Bottom()	const { return pos.y + size.y; }

	PackedPoint TopLeft()		const { return pos; }
	PackedPoint TopRight()		const { return PackedPoint( pos.x + size.x, pos.y ); }
	PackedPoint BottomLeft()	const { return PackedPoint( pos.x, pos.y + size.y ); }
	PackedPoint BottomRight()	const { return pos + size; }
	PackedPoint Center()		const { return pos + (size / 2); }

	void Expand( const PackedPoint& amount ) { size += amount; }
	void Inflate( const PackedPoint& increase ) { pos -= increase; size += increase * 2; }
	void Deflate( const PackedPoint& decrease ) { pos += decrease; size -= decrease * 2; }
	void Offset( const PackedPoint& amount ) { pos += amount; }
	void Set( const PackedPoint& Pos, const PackedPoint& Size ) { pos = Pos; size = Size; }
	void Set( short x, short y, short w, short h ) { pos.x = x; pos.y = y; size.x = w; size.y = h; }

	short Width()	const { return size.x; }
	short Height()	const { return size.y; }
	short Area()	const { return size.x * size.y;	}

	bool Empty() const { return size.IsZero(); }

	void GetSides( short* ptrTopBotLeftRight ) const
	{
		ptrTopBotLeftRight[0] = Top();
		ptrTopBotLeftRight[1] = Bottom();
		ptrTopBotLeftRight[2] = Left();
		ptrTopBotLeftRight[3] = Right();
	}

	void GetCorners( PackedPoint* ptrToplBotlBotrTopr ) const
	{
		ptrToplBotlBotrTopr[0] = TopLeft();
		ptrToplBotlBotrTopr[1] = BottomLeft();
		ptrToplBotlBotrTopr[2] = BottomRight();
		ptrToplBotlBotrTopr[3] = TopRight();
	}

	inline bool Intersects( const PackedRect& r ) const
	{
		return( r.pos.x < Right() && pos.x < r.Right() && r.pos.y < Bottom() && pos.y < r.Bottom() );
	}

	inline bool Contains( const PackedPoint& p ) const
	{
		return( p.x < Right() && pos.x < p.x && p.y < Bottom() && pos.y < p.y );
	}

	inline bool Contains( const PackedRect& r ) const
	{
		return( r.pos.x > pos.x && r.Right() <= Right() && r.pos.y > pos.y && r.Bottom() <= Bottom() );
	}

	Rect ToRect() const
	{
		return Rect( (int)pos.x, (int)pos.y, (int)size.x, (int)size.y );
	}

	static PackedRect Zero;

};



CE_NAMESPACE_END

