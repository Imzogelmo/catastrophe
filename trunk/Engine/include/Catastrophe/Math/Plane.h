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

CE_NAMESPACE_BEGIN


class Plane
{
public:
	Vector3 normal;
	float d;

	Plane() {}
	Plane( const Vector3& normal, float d ) : normal(normal), d(d) {}
	Plane( const Vector3& v0, const Vector3& v1, const Vector3& v2 )
	{
		normal = ((v1 - v0).Cross(v2 - v0)).Normal();
		d = normal.Dot(v0);
	}

	bool operator == ( const Plane &p ) const { return normal == p.normal && d == p.d; }
	bool operator != ( const Plane &p ) const { return !(*this == p); }
	bool Equals( const Plane &p, float epsilon = Math::Epsilon ) const
	{
		return (normal.Equals(p.normal) && Math::EpsilonCompare(d, p.d, epsilon));
	}

	void Normalize()
	{
		float length = normal.Length();
		if( length != 0.f )
		{
			const float inv = 1.f / length;
			normal *= inv;
		}
	}

	float Distance( const Vector3& point ) const
	{
		return normal.Dot(point) - d;
	}
 
	float Dot( const Vector3& v )
	{
		return normal.Dot(v) + d;
	}

	Vector3 AbsNormal() const
	{
		return normal.Abs();
	}

};


CE_NAMESPACE_END


