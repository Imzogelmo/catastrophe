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
#include "Catastrophe/Core/Math/Packed/PackedPoint.h"
#include "Catastrophe/Core/Math/Rect.h"

CE_NAMESPACE_BEGIN


class CE_API PackedRect
{
public:
	PackedPoint position, size;

	PackedRect() {}
	PackedRect( const PackedPoint& position, const PackedPoint& size ) : position(position), size(size) {}
	PackedRect( s16 x, s16 y, s16 width, s16 height ) : position(x,y), size(width,height) {}
	PackedRect( const Rect& rect );

	// Implicit conversion to Rect.
	operator Rect() const { return Rect((int)position.x, (int)position.y, (int)size.x, (int)size.y); }

	s16			&operator [] ( int i )			{ return *( &position.x + i ); }
	const s16	&operator [] ( int i ) const	{ return *( &position.x + i ); }

	bool operator == ( const PackedRect &r ) const { return ( position == r.position && size == r.size ); }
	bool operator != ( const PackedRect &r ) const { return ( position != r.position || size != r.size ); }

	PackedRect operator * ( const PackedPoint &p )	const { return PackedRect ( position * p, size ); }
	PackedRect operator / ( const PackedPoint &p )	const { return PackedRect ( position / p, size ); }
	PackedRect operator + ( const PackedPoint &p )	const { return PackedRect ( position + p, size ); }
	PackedRect operator - ( const PackedPoint &p )	const { return PackedRect ( position - p, size ); }
	PackedRect operator * ( const PackedRect &r )	const { return PackedRect ( position * r.position, size * r.size ); }
	PackedRect operator / ( const PackedRect &r )	const { return PackedRect ( position / r.position, size / r.size ); }
	PackedRect operator + ( const PackedRect &r )	const { return PackedRect ( position + r.position, size + r.size ); }
	PackedRect operator - ( const PackedRect &r )	const { return PackedRect ( position - r.position, size - r.size ); }

	inline s16 Left()	const { return position.x; }
	inline s16 Right()	const { return position.x + size.x; }
	inline s16 Top()	const { return position.y; }
	inline s16 Bottom()	const { return position.y + size.y; }

	PackedPoint TopLeft()		const { return position; }
	PackedPoint TopRight()		const { return PackedPoint( position.x + size.x, position.y ); }
	PackedPoint BottomLeft()	const { return PackedPoint( position.x, position.y + size.y ); }
	PackedPoint BottomRight()	const { return position + size; }
	PackedPoint Center()		const { return position + (size / 2); }

	void Expand( const PackedPoint& amount ) { size += amount; }
	void Inflate( const PackedPoint& increase ) { position -= increase; size += increase * 2; }
	void Deflate( const PackedPoint& decrease ) { position += decrease; size -= decrease * 2; }
	void Offset( const PackedPoint& amount ) { position += amount; }
	void Set( const PackedPoint& Pos, const PackedPoint& Size ) { position = Pos; size = Size; }
	void Set( s16 x, s16 y, s16 w, s16 h ) { position.x = x; position.y = y; size.x = w; size.y = h; }

	s16 Width() const { return size.x; }
	s16 Height() const { return size.y; }
	s16 Area() const { return size.x * size.y;	}

	bool Empty() const { return size.IsZero(); }

	void GetSides( s16* ptrTopBotLeftRight ) const
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
		return( r.position.x < Right() && position.x < r.Right() && r.position.y < Bottom() && position.y < r.Bottom() );
	}

	inline bool Contains( const PackedPoint& p ) const
	{
		return( p.x < Right() && position.x < p.x && p.y < Bottom() && position.y < p.y );
	}

	inline bool Contains( const PackedRect& r ) const
	{
		return( r.position.x > position.x && r.Right() <= Right() && r.position.y > position.y && r.Bottom() <= Bottom() );
	}

	Rect ToRect() const
	{
		return Rect( (int)position.x, (int)position.y, (int)size.x, (int)size.y );
	}

	static PackedRect Zero;
	static PackedRect One;

};



CE_NAMESPACE_END

