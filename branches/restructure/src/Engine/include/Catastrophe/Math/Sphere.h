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
#include "BoundingBox.h"

CE_NAMESPACE_BEGIN


class Sphere
{
public:
	Vector3 pos;
	float radius;

	Sphere() {}
	Sphere( float x, float y, float z, float radius ) : pos(x, y, z), radius(radius) {}
	Sphere( const Vector3& pos, float radius ) : pos(pos), radius(radius) {}
	Sphere( const BoundingBox& r ) : pos(r.Center()), radius(r.Extents().Max()) {}

	bool operator == ( const Sphere &s ) const { return pos == s.pos && radius == s.radius; }
	bool operator != ( const Sphere &s ) const { return !(*this == s); }
	bool Equals( const Sphere &s, float epsilon = Math::Epsilon ) const
	{
		return (Math::EpsilonCompare(radius, s.radius, epsilon) && pos == s.pos);
	}

	void Set( float x, float y, float z, float rad )
	{
		pos.x = x;
		pos.y = y;
		pos.z = z;
		radius = rad;
	}

	void Set( const Vector3& position, float rad )
	{
		pos = position;
		radius = rad;
	}

	void Scale( float scale )
	{
		radius *= scale;
	}

	void Translate( const Vector3& translation )
	{
		pos += translation;
	}

	BoundingBox GetBoundingBox() const
	{
		return BoundingBox(
			pos.x - radius,
			pos.y - radius,
			pos.z - radius,
			pos.x + radius,
			pos.y + radius,
			pos.z + radius
			);
	}

	bool Intersects( const Sphere& s ) const
	{
		return (pos.DistanceSquared(s.pos) < (radius + s.radius) * (radius + s.radius));
	}

	bool Contains( const Vector3& point ) const
	{
		return (pos.DistanceSquared(point) < (radius * radius));
	}

};


CE_NAMESPACE_END



