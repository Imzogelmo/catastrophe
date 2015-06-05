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

CE_NAMESPACE_BEGIN


class CE_API PackedRect
{
public:
	union {
		struct { PackedPoint position, size; };
		s16 x, y, width, height;
	};

	PackedRect() {}
	PackedRect( const PackedPoint& position, const PackedPoint& size ) : position(position), size(size) {}
	PackedRect( s16 x, s16 y, s16 width, s16 height ) : position(x, y), size(width, height) {}
	PackedRect( const Rectf& rectf );
	PackedRect( const Rect& rect );

	PackedRect& operator =( const Rect &rect );
	PackedRect& operator =( const Rectf &rectf );

	s16			&operator [] ( int i )			{ return *( &x + i ); }
	const s16	&operator [] ( int i ) const	{ return *( &x + i ); }

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

	FORCEINLINE s16 Left()	const { return position.x; }
	FORCEINLINE s16 Right()	const { return position.x + size.x; }
	FORCEINLINE s16 Top()	const { return position.y; }
	FORCEINLINE s16 Bottom()	const { return position.y + size.y; }
	FORCEINLINE const PackedPoint& Size() const { return size; }

	FORCEINLINE PackedPoint TopLeft()		const { return position; }
	FORCEINLINE PackedPoint TopRight()		const { return PackedPoint( position.x + size.x, position.y ); }
	FORCEINLINE PackedPoint BottomLeft()	const { return PackedPoint( position.x, position.y + size.y ); }
	FORCEINLINE PackedPoint BottomRight()	const { return position + size; }
	FORCEINLINE PackedPoint Center()		const { return position + (size / 2); }

	FORCEINLINE void Translate( const PackedPoint& value ) { position += value; }
	FORCEINLINE void Offset( const PackedPoint& value ) { position += value; }
	FORCEINLINE void Set( const PackedPoint& Pos, const PackedPoint& Size ) { position = Pos; size = Size; }
	FORCEINLINE void Set( s16 x, s16 y, s16 w, s16 h ) { position.x = x; position.y = y; size.x = w; size.y = h; }

	FORCEINLINE s16 Width() const { return size.x; }
	FORCEINLINE s16 Height() const { return size.y; }
	FORCEINLINE s16 Area() const { return size.x * size.y;	}

	FORCEINLINE bool Empty() const { return size.IsZero(); }

	FORCEINLINE bool Intersects( const PackedRect& r ) const
	{
		return( r.position.x < Right() && position.x < r.Right() && r.position.y < Bottom() && position.y < r.Bottom() );
	}

	FORCEINLINE bool Contains( const PackedPoint& p ) const
	{
		return( p.x < Right() && position.x < p.x && p.y < Bottom() && position.y < p.y );
	}

	FORCEINLINE bool Contains( const PackedRect& r ) const
	{
		return( r.position.x > position.x && r.Right() <= Right() && r.position.y > position.y && r.Bottom() <= Bottom() );
	}

	static PackedRect Zero;
	static PackedRect One;

};



CE_NAMESPACE_END

