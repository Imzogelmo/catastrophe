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
#include "Vector3.h"
#include "Rectf.h"


CE_NAMESPACE_BEGIN



class CE_API BoundingBox
{
public:
	Vector3 min, max;

	BoundingBox() {}
	BoundingBox( const Vector3& min, const Vector3& max )	: min(min), max(max) {}
	BoundingBox( const Rectf& r ) : min(r.min, 0.f), max(r.max, 0.f) {}
	BoundingBox( float x1, float y1, float z1, float x2, float y2, float z2 ) : min(x1, y1, z1), max(x2, y2, z2) {}
	BoundingBox( const Frustum& f ) : min(0.f), max(0.f)
	{
		*this = CreateFromFrustum(f);
	}

	float		&operator [] ( int i )			{ return *( &min.x + i ); }
	const float &operator [] ( int i ) const	{ return *( &min.x + i ); }

	bool operator == ( const BoundingBox &r ) const { return ( min == r.min && max == r.max ); }
	bool operator != ( const BoundingBox &r ) const { return ( min != r.min || max != r.max ); }

	bool Equals( const BoundingBox &box, float epsilon = Math::Epsilon ) const
	{
		return (min.Equals(box.min, epsilon) && max.Equals(box.max, epsilon));
	}

	inline float Top()		const { return min.y; }
	inline float Bottom()	const { return max.y; }
	inline float Left()		const { return min.x; }
	inline float Right()	const { return max.x; }
	inline float Front()	const { return min.z; }
	inline float Back()		const { return max.z; }

	Vector3 Center() const;

	Vector3 Size() const { return max - min; }
	Vector3 Extents() const { return (max - min) * 0.5f; }
	float Width() const { return fabsf(max.x - min.x); }
	float Height() const { return fabsf(max.y - min.y); }
	float Depth() const { return fabsf(max.z - min.z);	}
	float Volume() const { return Width() * Height() * Depth();	}

	void Inflate( const Vector3& increase ) { min -= increase; max += increase; }
	void Deflate( const Vector3& decrease ) { min += decrease; max -= decrease; }
	void Offset( const Vector3& amount ) { min += amount; max += amount; }
	void Set( const Vector3& minPos, const Vector3& maxPos ) { min = minPos; max = maxPos; }
	void SetSize( const Vector3& size ) { max = min + size; }

	Rectf ToRectf() const
	{
		return Rectf(min.x, min.y, max.x, max.y);
	}

	bool Empty() const
	{
		return min == max;
	}

	inline bool Intersects( const BoundingBox& b ) const
	{
		return( b.min.x < max.x && min.x < b.max.x && b.min.y < max.y && min.y < b.max.y && b.min.z < max.z && min.z < b.max.z );
	}

	inline bool Contains( const Vector3& b ) const
	{
		return( b.x < max.x && min.x < b.x && b.y < max.y && min.y < b.y && b.z < max.z && min.z < b.y );
	}

	void Merge( const BoundingBox& r );
	void Merge( const Vector3& p );

	static BoundingBox CreateFromFrustum( const Frustum& f );

	static BoundingBox Zero;
	static BoundingBox One;

};


CE_NAMESPACE_END



