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
#include "Rectf.h"

CE_NAMESPACE_BEGIN


class CE_API Circle
{
public:
	Vector2 pos;
	float radius;

	Circle() {}
	Circle( float x, float y, float radius ) : pos(x, y), radius(radius) {}
	Circle( const Vector2& position, float radius ) : pos(position), radius(radius) {}
	Circle( const Rectf& r ) : pos(r.Center()), radius(r.Extents().Max()) {}

	bool operator == ( const Circle &c ) const { return pos == c.pos && radius == c.radius; }
	bool operator != ( const Circle &c ) const { return !(*this == c); }
	bool Equals( const Circle &c, float epsilon = Math::Epsilon ) const
	{
		return (Math::EpsilonCompare(radius, c.radius, epsilon) && pos == c.pos);
	}

	void Set( float x, float y, float rad )
	{
		pos.x = x;
		pos.y = y;
		radius = rad;
	}

	void Set( const Vector2& position, float rad )
	{
		pos = position;
		radius = rad;
	}

	void Scale( float scale )
	{
		radius *= scale;
	}

	void Translate( const Vector2& translation )
	{
		pos += translation;
	}

	Rectf GetBoundingRect() const
	{
		return Rectf(
			pos.x - radius,
			pos.y - radius,
			pos.x + radius,
			pos.y + radius
			);
	}

	bool Intersects( const Circle& c ) const
	{
		float dx = pos.x - c.pos.x;
		float dy = pos.y - c.pos.y;
		return ((dx * dx + dy * dy) < (radius + c.radius) * (radius + c.radius));
	}

	bool Intersects( const Vector2& point ) const
	{
		return (pos.DistanceSquared( point ) < (radius * radius));
	}

	float Circumference() const
	{
		return 2.0f * Math::Pi * radius;
	}

	float Diameter() const
	{
		return 2.0f * radius;
	}

/*
	bool IntersectsRect( const Rectf& r ) const
	{
		const float rx = r.size.x * 0.5f;
		const float ry = r.size.y * 0.5f;
		const float dx = fabsf(pos.x - r.pos.x + rx);
		const float dy = fabsf(pos.y - r.pos.y + ry);

		if( dx > (rx + radius) || dy > (ry + radius) )
			return false;

		if( dx <= rx || dy <= ry )
			return true;

		//special case for collision against corner
		const float ox = dx - rx;
		const float oy = dy - ry;
		const float distanceSquared = ox * ox + oy * oy;

		return (distanceSquared <= radius * radius);
	}
*/
};


CE_NAMESPACE_END



