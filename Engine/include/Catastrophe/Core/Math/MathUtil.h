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
#include "Catastrophe/Core/PlatformMath.h"
#include "Catastrophe/Core/Math/Vector2.h"

CE_NAMESPACE_BEGIN



namespace Math
{

	// Note* Returns Vector2(cos, sin)!
	FORCEINLINE Vector2 SinCosf( float x )
	{
		Vector2 sc;
		SinCosf(x, sc.y, sc.x);
		return sc;
	}

	/* Rotates a point by polar coordinates 'rot' about an origin */
	constexpr FORCEINLINE void RotatePoint( const Vector2& rot, Vector2& outPoint )
	{
		outPoint.x = (rot.x * outPoint.x) - (rot.y * outPoint.y);
		outPoint.y = (rot.y * outPoint.x) + (rot.x * outPoint.y);
	}

	/* Rotates a point by polar coordinates 'rot' about an origin */
	constexpr FORCEINLINE void RotatePoint( const Vector2& rot, const Vector2& center, Vector2& outPoint )
	{
		const Vector2 v = (outPoint - center);

		outPoint.x = (rot.x * v.x) - (rot.y * v.y) + center.x;
		outPoint.y = (rot.y * v.x) + (rot.x * v.y) + center.y;
	}

	/* Scales a point by scale about an origin */
	constexpr FORCEINLINE void ScalePoint( const Vector2& scale, const Vector2& center, Vector2& outPoint )
	{
		outPoint = (scale * (outPoint - center)) + center;
	}

	/* Rotates and scales a point by polar coordinates about an origin */
	constexpr FORCEINLINE void RotateScalePoint( const Vector2& rot, const Vector2& scale, const Vector2& center, Vector2& outPoint )
	{
		const Vector2 v = (scale * (outPoint - center));

		outPoint.x = (rot.x * v.x) - (rot.y * v.y) + center.x;
		outPoint.y = (rot.y * v.x) + (rot.x * v.y) + center.y;
	}

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
	float Hermite(float value1, float tangent1, float value2, float tangent2, float t);
	float CatmullRom( float p1, float p2, float p3, float p4, float t );
	
	Vector2 Bezier( const Vector2& p1, const Vector2& t1, const Vector2& p2, float t );
	Vector2 Bezier( const Vector2& p1, const Vector2& t1, const Vector2& t2, const Vector2& p2, float t );
	Vector2 Bezier( const Vector2& p1, const Vector2& t1, const Vector2& t2, const Vector2& t3, const Vector2& p2, float t );
	Vector2 CatmullRom( const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, float t );
	
	Vector3 Bezier( const Vector3& p1, const Vector3& t1, const Vector3& p2, float t);
	Vector3 Bezier( const Vector3& p1, const Vector3& t1, const Vector3& t2, const Vector3& p2, float t);
	Vector3 Bezier( const Vector3& p1, const Vector3& t1, const Vector3& t2, const Vector3& t3, const Vector3& p2, float t);
	Vector3 CatmullRom( const Vector3& p1, const Vector3& p2, const Vector3& p3, const Vector3& p4, float t );


	/// Clamps radian value between -PI and PI
	inline float ClampAngle( float radians )
	{
		radians = fmodf( radians, TwoPi );
		return WrapAngle( radians );
	}

	/// Clamps degree value between 0 and 360
	inline float ClampDegrees( float degrees )
	{
		return fmodf( degrees, 360.f );
	}

	float DistancetoLineSegment( const Vector2 & a, const Vector2 & b, const Vector2 & point );
	float DistancetoLineSegment( const Vector3 & a, const Vector3 & b, const Vector3 & point );

	/* Returns true if a point is inside a triangle */
	inline bool PointIntersectsTriangle( const Vector2 &point, const Vector2 &t1, const Vector2 &t2, const Vector2 &t3 );


};




CE_NAMESPACE_END




