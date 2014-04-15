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

#include <fc/rand.h>

#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

CE_NAMESPACE_BEGIN


namespace Math
{


Vector2 CircularRand( float radius )
{
	Vector2 v;
	fc::circular_rand(radius, v.x, v.y);
	return v;
}


Vector2 ArcRand( float minAngle, float maxAngle, float radius )
{
	Vector2 v;
	fc::arc_rand(minAngle, maxAngle, radius, v.x, v.y);
	return v;
}


Vector2 Clamp( const Vector2& vec, const Vector2& min, const Vector2& max )
{
	return Vector2(
		Math::Clamp(vec.x, min.x, max.x),
		Math::Clamp(vec.y, min.y, max.y)
	);
}


Vector3 Clamp( const Vector3& vec, const Vector3& min, const Vector3& max )
{
	return Vector3(
		Math::Clamp(vec.x, min.x, max.x),
		Math::Clamp(vec.y, min.y, max.y),
		Math::Clamp(vec.z, min.z, max.z)
	);
}


Vector4 Clamp( const Vector4& vec, const Vector4& min, const Vector4& max )
{
	Vector4 ret(vec);
	Math::FastClamp(ret.x, min.x, max.x);
	Math::FastClamp(ret.y, min.y, max.y);
	Math::FastClamp(ret.z, min.z, max.z);
	Math::FastClamp(ret.w, min.w, max.w);
	return ret;
}


Vector2 Lerp( const Vector2& p1, const Vector2& p2, float t )
{
	return Vector2 ( 
			p1.x + (p2.x - p1.x) * t,
			p1.y + (p2.y - p1.y) * t 
		);
}


Vector2 SmoothStep( const Vector2& v1, const Vector2& v2, float t )
{
	t = (t * t) * (3.0f - (2.0f * t));
	return Lerp( v1, v2, t );
}


Vector3 Lerp( const Vector3& p1, const Vector3& p2, float t )
{
	return Vector3(
		p1.x + (p2.x - p1.x) * t,
		p1.y + (p2.y - p1.y) * t,
		p1.z + (p2.z - p1.z) * t
	);
}


Vector3 SmoothStep( const Vector3& v1, const Vector3& v2, float t )
{
	t = t > 1.0f ? 1.0f : (t < 0.0f ? 0.0f : t);
	t = (t * t) * (3.0f - (2.0f * t));
	return Vector3(
		v1.x + ((v2.x - v1.x) * t),
		v1.y + ((v2.y - v1.y) * t),
		v1.z + ((v2.z - v1.z) * t)
	);
}


Vector4 Lerp( const Vector4& p1, const Vector4& p2, float t )
{
	return Vector4( 
			p1.x + (p2.x - p1.x) * t,
			p1.y + (p2.y - p1.y) * t,
			p1.z + (p2.z - p1.z) * t,
			p1.w + (p2.w - p1.w) * t 
		);
}


Vector4 SmoothStep( const Vector4& v1, const Vector4& v2, float t )
{
	t = (t * t) * (3.0f - (2.0f * t));
	return Vector4(
			v1.x + ((v2.x - v1.x) * t),
			v1.y + ((v2.y - v1.y) * t),
			v1.z + ((v2.z - v1.z) * t),
			v1.w + ((v2.w - v1.w) * t)
		);
}


float Bezier( float p1, float t1, float p2, float t )
{
	const float a = 1.0f - t;
	return ((p1 * a * a) + (t1 * 2.0f * a * t) + (p2 * t * t));
}


float Bezier( float p1, float t1, float t2, float p2, float t )
{
	const float a = 1.0f - t;
	const float A = a * a * a;
	const float B = 3.0f * a * a * t;
	const float C = 3.0f * a * t * t;
	const float D = t * t * t;
	return ((p1 * A) + (t1 * B) + (t2 * C) + (p2 * D));
}


float Bezier( float p1, float t1, float t2, float t3, float p2, float t )
{
	const float a = 1.0f - t, b = a * a, c = t * t, d = (1.0f - t) * t;
	const float A = b * b;
	const float B = 4.0f * b * d;
	const float C = 6.0f * b * c;
	const float D = 4.0f * d * c;
	const float E = c * c;
	return ((p1 * A) + (t1 * B) + (t2 * C) + (t3 * D) + (p2 * E));
}


float Hermite(float value1, float tangent1, float value2, float tangent2, float t)
{
	float part1 = ((2.0f * t * t * t) - (3.0f * t * t)) + 1.0f;
	float part2 = (-2.0f * t * t * t) + (3.0f * t * t);
	float part3 = (t * t * t - (2.0f * t * t)) + t;
	float part4 = (t * t * t) - (t * t);
	return (((value1 * part1) + (value2 * part2)) + (tangent1 * part3)) + (tangent2 * part4);
}


float CatmullRom( float p1, float p2, float p3, float p4, float t )
{
	return ( 0.5f * ( 
			(2.0f * p2) + p3 - (p1 * t) + (2.0f * p1) - (5.0f * p2) + 
			(4.0f * p3) - (p4 * t * t) + (3.0f * p2) + p4 - p1 - (3.0f * p3 * t * t * t) ) 
		);
}


Vector2 Bezier( const Vector2& p1, const Vector2& t1, const Vector2& p2, float t )
{
	const float a = 1.0f - t;
	const float A = a * a;
	const float B = 2.0f * a * t;
	const float C = t * t;
	return Vector2(
			(p1.x * A) + (t1.x * B) + (p2.x * C),
			(p1.y * A) + (t1.y * B) + (p2.y * C) 
		);
}


Vector2 Bezier( const Vector2& p1, const Vector2& t1, const Vector2& t2, const Vector2& p2, float t )
{
	const float a = 1.0f - t;
	const float A = a * a * a;
	const float B = 3.0f * a * a * t;
	const float C = 3.0f * a * t * t;
	const float D = t * t * t;
	return Vector2( 
			(p1.x * A) + (t1.x * B) + (t2.x * C) + (p2.x * D),
			(p1.y * A) + (t1.y * B) + (t2.y * C) + (p2.y * D)				
		);
}


Vector2 Bezier( const Vector2& p1, const Vector2& t1, const Vector2& t2, const Vector2& t3, const Vector2& p2, float t )
{
	const float a = 1.0f - t, b = a * a, c = t * t, d = (1.0f - t) * t;
	const float A = b * b;
	const float B = 4.0f * b * d;
	const float C = 6.0f * b * c;
	const float D = 4.0f * d * c;
	const float E = c * c;
	return Vector2( 
			(p1.x * A) + (t1.x * B) + (t2.x * C) + (t3.x * D) + (p2.x * E),
			(p1.y * A) + (t1.y * B) + (t2.y * C) + (t3.y * D) + (p2.y * E) 
		);
}


Vector2 CatmullRom( const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, float t )
{
	const float a = t * t;
	const float b = t * a;
	return Vector2(
		0.5f * ( (2.0f * p2.x) + p3.x - (p1.x * t) + (2.0f * p1.x) - (5.0f * p2.x) + (4.0f * p3.x) - (p4.x * a) + (3.0f * p2.x) + p4.x - p1.x - (3.0f * p3.x * b) ),
		0.5f * ( (2.0f * p2.y) + p3.y - (p1.y * t) + (2.0f * p1.y) - (5.0f * p2.y) + (4.0f * p3.y) - (p4.y * a) + (3.0f * p2.y) + p4.y - p1.y - (3.0f * p3.y * b) )
	);
}



Vector3 Bezier( const Vector3& p1, const Vector3& t1, const Vector3& p2, float t )
{
	const float a = 1.0f - t;
	const float A = a * a;
	const float B = 2.0f * a * t;
	const float C = t * t;
	return Vector3(
			(p1.x * A) + (t1.x * B) + (p2.x * C),
			(p1.y * A) + (t1.y * B) + (p2.y * C),
			(p1.z * A) + (t1.z * B) + (p2.z * C)
		);
}


Vector3 Bezier( const Vector3& p1, const Vector3& t1, const Vector3& t2, const Vector3& p2, float t )
{
	const float a = 1.0f - t;
	const float A = a * a * a;
	const float B = 3.0f * a * a * t;
	const float C = 3.0f * a * t * t;
	const float D = t * t * t;
	return Vector3(
			(p1.x * A) + (t1.x * B) + (t2.x * C) + (p2.x * D),
			(p1.y * A) + (t1.y * B) + (t2.y * C) + (p2.y * D),
			(p1.z * A) + (t1.z * B) + (t2.z * C) + (p2.z * D)
		);
}


Vector3 Bezier( const Vector3& p1, const Vector3& t1, const Vector3& t2, const Vector3& t3, const Vector3& p2, float t )
{
	const float a = 1.0f - t, b = a * a, c = t * t, d = (1.0f - t) * t;
	const float A = b * b;
	const float B = 4.0f * b * d;
	const float C = 6.0f * b * c;
	const float D = 4.0f * d * c;
	const float E = c * c;
	return Vector3(
			(p1.x * A) + (t1.x * B) + (t2.x * C) + (t3.x * D) + (p2.x * E),
			(p1.y * A) + (t1.y * B) + (t2.y * C) + (t3.y * D) + (p2.y * E),
			(p1.z * A) + (t1.z * B) + (t2.z * C) + (t3.z * D) + (p2.z * E)
		);
}


Vector3 CatmullRom( const Vector3& p1, const Vector3& p2, const Vector3& p3, const Vector3& p4, float t )
{
	const float a = t * t;
	const float b = t * a;
	return Vector3(
		0.5f * ( (2.0f * p2.x) + p3.x - (p1.x * t) + (2.0f * p1.x) - (5.0f * p2.x) + (4.0f * p3.x) - (p4.x * a) + (3.0f * p2.x) + p4.x - p1.x - (3.0f * p3.x * b) ),
		0.5f * ( (2.0f * p2.y) + p3.y - (p1.y * t) + (2.0f * p1.y) - (5.0f * p2.y) + (4.0f * p3.y) - (p4.y * a) + (3.0f * p2.y) + p4.y - p1.y - (3.0f * p3.y * b) ),
		0.5f * ( (2.0f * p2.z) + p3.z - (p1.z * t) + (2.0f * p1.z) - (5.0f * p2.z) + (4.0f * p3.z) - (p4.z * a) + (3.0f * p2.z) + p4.z - p1.z - (3.0f * p3.z * b) )
	);
}


Vector2 Barycentric( const Vector2& p1, const Vector2& p2, const Vector2& p3, float u, float v )
{
	return Vector2(
			p1.x + (u * (p3.x - p1.x)) + (v * (p2.x - p1.x)),
			p1.y + (u * (p3.y - p1.y)) + (v * (p2.y - p1.y))
		);
}


Vector3 Barycentric( const Vector3& p1, const Vector3& p2, const Vector3& p3, float u, float v )
{
	return Vector3(
			p1.x + (u * (p3.x - p1.x)) + (v * (p2.x - p1.x)),
			p1.y + (u * (p3.y - p1.y)) + (v * (p2.y - p1.y)),
			p1.z + (u * (p3.z - p1.z)) + (v * (p2.z - p1.z))
		);
}


float DistancetoLineSegment( const Vector3 & a, const Vector3 & b, const Vector3 & point )
{
	Vector3 dist = b - a;
	float length = dist.Length();
	if( dist == 0.0f )
		return (point - a).Length();

	dist.Normalize();
	float t = (point - a).Dot( dist );
	if( t < 0.0f )
		return (point - a).Length();
	if( t > length )
		return (point - b).Length();

	return (point - (a + dist * t)).Length();
}


float DistancetoLineSegment( const Vector2 & a, const Vector2 & b, const Vector2 & point )
{
	Vector2 dist = b - a;
	float length = dist.Length();
	if( dist == 0.0f )
		return (point - a).Length();

	dist.Normalize();
	float t = (point - a).Dot( dist );
	if( t < 0.0f )
		return (point - a).Length();
	if( t > length )
		return (point - b).Length();

	return (point - (a + dist * t)).Length();
}


bool PointIntersectsTriangle( const Vector2 &point, const Vector2 &t1, const Vector2 &t2, const Vector2 &t3 )
{
	const Vector2 d1 = t1 - point, d2 = t2 - point, d3 = t3 - point;
	const float c = (t1.x - t3.x) * (t2.y - t3.y) - (t2.x - t3.x) * (t1.y - t3.y);
	return
		(
			((( d3.x * d2.y - d2.x * d1.y ) / c) > 0.f) &&
			((( d3.x * d3.y - d3.x * d2.y ) / c) > 0.f) &&
			((( d3.x * d1.y - d1.x * d3.y ) / c) > 0.f)
		);
}




} //Math



CE_NAMESPACE_END
