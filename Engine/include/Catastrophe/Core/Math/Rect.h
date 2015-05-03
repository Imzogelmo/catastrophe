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
#include "Catastrophe/Core/Math/Point.h"
#include "Catastrophe/Core/Math/Rectf.h"


CE_NAMESPACE_BEGIN


class CE_API Rect
{
public:
	Point position, size;

	Rect() {}
	Rect( const Point& position, const Point& size ) : position(position), size(size) {}
	Rect( int x, int y, int width, int height )	: position(x, y), size(width, height) {}
	Rect( const PackedRect& r );
	Rect( const Rectf& r );

	Point		&operator [] ( const int i )		{ return *( &position + i ); }
	const Point	&operator [] ( const int i ) const  { return *( &position + i ); }

	bool operator ==( const Rect &r ) const { return ( position == r.position && size == r.size ); }
	bool operator !=( const Rect &r ) const { return ( position != r.position || size != r.size ); }

	Rect operator + ( const Point &p ) const { return Rect( position + p, size ); }
	Rect& operator += ( const Point &p ) { position += p; return *this; }

	FORCEINLINE int Left() const { return position.x; }
	FORCEINLINE int Right() const { return position.x + size.x; }
	FORCEINLINE int Top() const { return position.y; }
	FORCEINLINE int Bottom() const { return position.y + size.y; }

	FORCEINLINE Point TopLeft()		const { return position; }
	FORCEINLINE Point TopRight()	const { return Point( position.x + size.x, position.y ); }
	FORCEINLINE Point BottomLeft()	const { return Point( position.x, position.y + size.y ); }
	FORCEINLINE Point BottomRight()	const { return position + size; }
	FORCEINLINE Point Center()		const { return position + (size / 2); }

	void Expand( const Point& amount ) { size += amount; }
	void Inflate( const Point& increase ) { position -= increase; size += increase * 2; }
	void Deflate( const Point& decrease ) { position += decrease; size -= decrease * 2; }
	void Offset( const Point& amount ) { position += amount; }
	void Set( const Point& Pos, const Point& Size ) { position = Pos; size = Size; }
	void Set( int x, int y, int w, int h ) { position.x = x; position.y = y; size.x = w; size.y = h; }

	FORCEINLINE const Point& Position() const { return position; }
	FORCEINLINE const Point& Size() const { return size; }

	FORCEINLINE int Width()		const { return size.x; }
	FORCEINLINE int Height()	const { return size.y; }
	FORCEINLINE int Area()		const { return size.x * size.y;	}

	FORCEINLINE bool Empty() const { return size.IsZero(); }

	FORCEINLINE bool Intersects( const Rect& r ) const
	{
		return( r.position.x < Right() && position.x < r.Right() && r.position.y < Bottom() && position.y < r.Bottom() );
	}

	FORCEINLINE bool Intersects( const Point& p ) const
	{
		return( p.x < Right() && position.x < p.x && p.y < Bottom() && position.y < p.y );
	}

	FORCEINLINE bool Contains( const Point& p ) const
	{
		return Intersects(p);
	}

	FORCEINLINE bool Contains( const Rect& r ) const
	{
		if( r.position.x < position.x || r.position.y < position.y ) return false;
		if( r.Right() > Right() || r.Bottom() > Bottom() ) return false;
		return true;
	}

	void Merge( const Rect& r );
	Rectf ToRectf() const;

	static Rect Zero;
	static Rect One;

};




CE_NAMESPACE_END

