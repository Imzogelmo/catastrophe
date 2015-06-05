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
#include "Catastrophe/Core/Math/Vector2.h"


CE_NAMESPACE_BEGIN



class CE_API Rectf
{
public:
	Vector2 min, max;

	Rectf() {}
	Rectf( const Vector2& min, const Vector2& max )	: min(min), max(max) {}
	Rectf( float x1, float y1, float x2, float y2 )	: min(x1,y1), max(x2,y2) {}
	Rectf( const Rect& r );

	Rectf &operator = ( const Rect &r ) { *this = Rectf(r); }

	float		&operator [] ( int i )			{ return *( &min.x + i ); }
	const float &operator [] ( int i ) const	{ return *( &min.x + i ); }

	bool operator == ( const Rectf &r ) const { return ( min == r.min && max == r.max ); }
	bool operator != ( const Rectf &r ) const { return ( min != r.min || max != r.max ); }

	Rectf operator + ( const Vector2 &v ) const { return Rectf( min + v, max + v ); }
	Rectf& operator += ( const Vector2 &v ) { min += v; max += v; return *this; }

	FORCEINLINE float Top() const { return min.y; }
	FORCEINLINE float Bottom() const { return max.y; }
	FORCEINLINE float Left() const { return min.x; }
	FORCEINLINE float Right() const { return max.x; }

	FORCEINLINE Vector2 TopLeft() const { return min; }
	FORCEINLINE Vector2 TopRight() const { return Vector2( max.x, min.y ); }
	FORCEINLINE Vector2 BottomLeft() const { return Vector2( min.x, max.y ); }
	FORCEINLINE Vector2 BottomRight() const { return max; }

	FORCEINLINE Vector2 Center()	const
	{
		return Vector2( 
			(min.x + max.x) * 0.5f,
			(min.y + max.y) * 0.5f
			);
	}

	FORCEINLINE Vector2 Size() const { return max - min; }
	FORCEINLINE Vector2 Extents() const { return (max - min) * 0.5f; }
	FORCEINLINE float Width() const { return fabs(max.x - min.x); }
	FORCEINLINE float Height() const { return fabs(max.y - min.y); }
	FORCEINLINE float Area() const { return Width() * Height();	}

	void Offset( const Vector2& amount ) { min += amount; max += amount; }
	void Set( const Vector2& minPos, const Vector2& maxPos ) { min = minPos; max = maxPos; }
	void Set( float x1, float y1, float x2, float y2 ) { min.x = x1; min.y = y1; max.x = x2; max.y = y2; }
	void SetSize( const Vector2& s ) { max = min + s; }
	void SetWidth( float w ) { max.x = min.x + w; }
	void SetHeight( float h ) { max.y = min.y + h; }
	void Scale( const Vector2& scale );

	FORCEINLINE void FlipX()
	{
		float temp = min.x;
		min.x = max.x;
		max.x = temp;
	}

	FORCEINLINE void FlipY()
	{
		float temp = min.y;
		min.y = max.y;
		max.y = temp;
	}

	FORCEINLINE bool Empty() const
	{
		return min == max;
	}

	FORCEINLINE bool Intersects( const Rectf& r ) const
	{
		return( r.min.x < max.x && min.x < r.max.x && r.min.y < max.y && min.y < r.max.y );
	}

	FORCEINLINE bool Intersects( const Vector2& p ) const
	{
		return( p.x < max.x && min.x < p.x && p.y < max.y && min.y < p.y );
	}

	FORCEINLINE bool Contains( const Rectf& r ) const
	{
		return( r.min.x > min.x && r.max.x <= max.x && r.min.y > min.y && r.max.y <= max.y );
	}

	FORCEINLINE bool Contains( const Vector2& p ) const
	{
		return Intersects(p);
	}

	void Merge( const Rectf& r );
	void Merge( const Vector2& p );
	bool IntersectsCircle( const Vector2& point, float radius );

	static Rectf Zero;
	static Rectf One;

};


CE_NAMESPACE_END



