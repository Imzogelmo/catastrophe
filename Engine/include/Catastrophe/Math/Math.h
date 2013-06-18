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

#include <fc/math.h>

CE_NAMESPACE_BEGIN


namespace Math
{
	template <class T> inline
	T Distance( T x1, T y1, T x2, T y2 ) 
	{
		T a = x1 - x2;
		T b = y1 - y2;
		return (T) sqrtf( float((a * a) + (b * b)) );
	}

	template <class T> inline
	T DistanceSquared( T x1, T y1, T x2, T y2 ) 
	{
		T a = x1 - x2;
		T b = y1 - y2;
		return a * a + b * b;
	}

	inline float Dsin( float degrees ) { return sinf( (degrees) * 0.0174532925f ); }
	inline float Dcos( float degrees ) { return cosf( (degrees) * 0.0174532925f ); }

	inline void SinCos( float x, float& s, float& c )
	{
		fc::sincos(x, s, c);
	}

	/* Note* Returns Vector2(cos, sin)! */
	inline Vector2 SinCos( float x )
	{
		Vector2 sc;
		fc::sincos(x, sc.y, sc.x);
		return sc;
	}

	inline void Polar( Vector2& v, float distance, float theta )
	{
		v += SinCos(theta) * distance;
	}

	// Interpolation functions
	inline float Lerp( float x, float y, float t )
	{
		return x + (y - x) * t;
	}

	inline float SmoothStep( float x, float y, float t )
	{
		t = (t * t) * (3.0f - (2.0f * t));
		return x + (y - x) * t;
	}

	Vector2 CircularRand( float radius = 1.f );
	Vector2 ArcRand( float minAngle, float maxAngle, float radius = 1.f );

	Vector2 Clamp( const Vector2& vec, const Vector2& min, const Vector2& max );
	Vector3 Clamp ( const Vector3& vec, const Vector3& min, const Vector3& max );
	Vector4 Clamp( const Vector4& vec, const Vector4& min, const Vector4& max );

	Vector2 Lerp( const Vector2& p1, const Vector2& p2, float t );
	Vector2 SmoothStep( const Vector2& v1, const Vector2& v2, float t );
	
	Vector3 Lerp( const Vector3& p1, const Vector3& p2, float t );
	Vector3 SmoothStep( const Vector3& v1, const Vector3& v2, float t );
	
	Vector4 Lerp( const Vector4& p1, const Vector4& p2, float t );
	Vector4 SmoothStep( const Vector4& v1, const Vector4& v2, float t );

	float Bezier( float p1, float t1, float p2, float t );
	float Bezier( float p1, float t1, float t2, float p2, float t );
	float Bezier( float p1, float t1, float t2, float t3, float p2, float t );
	float CatmullRom( float p1, float p2, float p3, float p4, float t );
	
	Vector2 Bezier( const Vector2& p1, const Vector2& t1, const Vector2& p2, float t );
	Vector2 Bezier( const Vector2& p1, const Vector2& t1, const Vector2& t2, const Vector2& p2, float t );
	Vector2 Bezier( const Vector2& p1, const Vector2& t1, const Vector2& t2, const Vector2& t3, const Vector2& p2, float t );
	Vector2 CatmullRom( const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, float t );
	
	Vector3 Bezier( const Vector3& p1, const Vector3& t1, const Vector3& p2, float t);
	Vector3 Bezier( const Vector3& p1, const Vector3& t1, const Vector3& t2, const Vector3& p2, float t);
	Vector3 Bezier( const Vector3& p1, const Vector3& t1, const Vector3& t2, const Vector3& t3, const Vector3& p2, float t);
	Vector3 CatmullRom( const Vector3& p1, const Vector3& p2, const Vector3& p3, const Vector3& p4, float t );


	/* Clamps radian value between -PI and PI */
	inline float ClampAngle( float radians )
	{
		radians = fmodf( radians, TwoPi );
		return WrapAngle( radians );
	}

	/* Clamps degree value between 0 and 360 */
	inline float ClampDegrees( float degrees )
	{
		return fmodf( degrees, 360.f );
	}

	/* Rotates a point by polar coordinates 'rot' about an origin */
	inline void RotatePoint( const Vector2& rot, const Vector2& center, Vector2& point )
	{
		const Vector2 v = (point - center);

		point.x = (rot.x * v.x) - (rot.y * v.y) + center.x;
		point.y = (rot.y * v.x) + (rot.x * v.y) + center.y;
	}

	/* Scales a point by scale about an origin */
	inline void ScalePoint( const Vector2& scale, const Vector2& center, Vector2& point )
	{
		point = (scale * (point - center)) + center;
	}

	/* Rotates and scales a point by polar coordinates about an origin */
	inline void RotateScalePoint( const Vector2& rot, const Vector2& scale, const Vector2& center, Vector2& point )
	{
		const Vector2 v = (scale * (point - center));

		point.x = (rot.x * v.x) - (rot.y * v.y) + center.x;
		point.y = (rot.y * v.x) + (rot.x * v.y) + center.y;
	}

	//Returns a normal given a triangle surface
	/*
	inline Vector3 CalculateSurfaceNormal( const Vector3& p1, const Vector3& p2, const Vector3& p3 )
	{
		Vector3 normal = Vector3::Cross( p2 - p1, p3 - p1 );
		normal.Normalize();

		return normal;
	}
	*/

	float DistancetoLineSegment( const Vector2 & a, const Vector2 & b, const Vector2 & point );
	float DistancetoLineSegment( const Vector3 & a, const Vector3 & b, const Vector3 & point );

	/* Returns true if a point is inside a triangle */
	inline bool PointIntersectsTriangle( const Vector2 &point, const Vector2 &t1, const Vector2 &t2, const Vector2 &t3 );

	/* Up to 5x faster than sqrt */
	inline float FastSqrt( const float x )  
	{
		return fc::fast_sqrt(x);
	}

	/* Up to 3x faster than atan2f. Error < 0.005f */
	inline float FastAtan2( float y, float x )
	{
		return fc::fast_atan2(y, x);
	}


};




CE_NAMESPACE_END




