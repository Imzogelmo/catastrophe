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
#include "Vector2.h"


CE_NAMESPACE_BEGIN



class Rectf
{
public:
	Vector2 min, max;

	Rectf() {}
	Rectf( const Vector2& min, const Vector2& max )	: min(min), max(max) {}
	Rectf( float x1, float y1, float x2, float y2 )	: min(x1,y1), max(x2,y2) {}

	float		&operator [] ( int i )			{ return *( &min.x + i ); }
	const float &operator [] ( int i ) const	{ return *( &min.x + i ); }

	bool operator == ( const Rectf &r ) const { return ( min == r.min && max == r.max ); }
	bool operator != ( const Rectf &r ) const { return ( min != r.min || max != r.max ); }

	Rectf operator + ( const Vector2 &v ) const { return Rectf( min + v, max + v ); }
	Rectf& operator += ( const Vector2 &v ) { min += v; max += v; return *this; }

	inline float Top()		const { return min.y; }
	inline float Bottom()	const { return max.y; }
	inline float Left()		const { return min.x; }
	inline float Right()	const { return max.x; }

	inline Vector2 TopLeft()		const { return min; }
	inline Vector2 TopRight()		const { return Vector2( max.x, min.y ); }
	inline Vector2 BottomLeft()		const { return Vector2( min.x, max.y ); }
	inline Vector2 BottomRight()	const { return max; }

	inline Vector2 Center()	const
	{
		return Vector2( 
			(min.x + max.x) * 0.5f,
			(min.y + max.y) * 0.5f
			);
	}

	Vector2 Size() const { return max - min; }
	Vector2 Extents() const { return (max - min) * 0.5f; }
	float Width() const { return fabs(max.x - min.x); }
	float Height() const { return fabs(max.y - min.y); }
	float Area() const { return Width() * Height();	}

	void Inflate( const Vector2& increase ) { min -= increase; max += increase; }
	void Deflate( const Vector2& decrease ) { min += decrease; max -= decrease; }
	void Offset( const Vector2& amount ) { min += amount; max += amount; }
	void Set( const Vector2& minPos, const Vector2& maxPos ) { min = minPos; max = maxPos; }
	void Set( float x1, float y1, float x2, float y2 ) { min.x = x1; min.y = y1; max.x = x2; max.y = y2; }
	void SetSize( const Vector2& s ) { max = min + s; }
	void SetWidth( float w ) { max.x = min.x + w; }
	void SetHeight( float h ) { max.y = min.y + h; }

	void Scale( const Vector2& scale )
	{
		const Vector2 radius = (Extents() * scale) * 0.5f;
		min -= radius;
		max += radius;
	}

	void GetSides( float* ptrTopBotLeftRight ) const
	{
		ptrTopBotLeftRight[0] = Top();
		ptrTopBotLeftRight[1] = Bottom();
		ptrTopBotLeftRight[2] = Left();
		ptrTopBotLeftRight[3] = Right();
	}

	void GetCorners( Vector2* ptrToplBotlBotrTopr ) const
	{
		ptrToplBotlBotrTopr[0] = TopLeft();
		ptrToplBotlBotrTopr[1] = BottomLeft();
		ptrToplBotlBotrTopr[2] = BottomRight();
		ptrToplBotlBotrTopr[3] = TopRight();
	}

	//Rect ToRect() const
	//{
	//	return Rectf( min, Size() );
	//}

	bool Empty() const
	{
		return min == max;
	}

	inline bool Intersects( const Rectf& r ) const
	{
		return( r.min.x < max.x && min.x < r.max.x && r.min.y < max.y && min.y < r.max.y );
	}

	inline bool Intersects( const Vector2& p ) const
	{
		return( p.x < max.x && min.x < p.x && p.y < max.y && min.y < p.y );
	}

	inline bool Contains( const Rectf& r ) const
	{
		return( r.min.x > min.x && r.max.x <= max.x && r.min.y > min.y && r.max.y <= max.y );
	}

	void Merge( const Rectf& r )
	{
		if(r.min.x < min.x) min.x = r.min.x;
		if(r.max.x > max.x) max.x = r.max.x;
		if(r.min.y < min.y) min.y = r.min.y;
		if(r.max.y > max.y) max.y = r.max.y;
	}

	void Merge( const Vector2& p )
	{
		if(p.x < min.x) min.x = p.x;
		if(p.x > max.x) max.x = p.x;
		if(p.y < min.y) min.y = p.y;
		if(p.y > max.y) max.y = p.y;
	}

	bool IntersectsCircle( const Vector2& point, float radius );

	static Rectf Zero;
	static Rectf One;

};


CE_NAMESPACE_END



