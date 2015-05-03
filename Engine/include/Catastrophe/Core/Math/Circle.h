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
#include "Catastrophe/Core/Math/Vector4.h"
#include "Catastrophe/Core/Math/Rectf.h"

CE_NAMESPACE_BEGIN


class CE_API Circle
{
public:
	Vector2 position;
	float radius;

	Circle() {}
	Circle( float x, float y, float radius ) : position(x, y), radius(radius) {}
	Circle( const Vector2& position, float radius ) : position(position), radius(radius) {}
	Circle( const Rectf& r ) : position(r.Center()), radius(r.Extents().Max()) {}

	bool operator == ( const Circle &c ) const { return position == c.position && radius == c.radius; }
	bool operator != ( const Circle &c ) const { return !(*this == c); }
	bool Equals( const Circle &c, float epsilon = Math::Epsilon ) const
	{
		return (Math::EpsilonCompare(radius, c.radius, epsilon) && position == c.position);
	}

	void Set( float x, float y, float radius )
	{
		this->position.x = x;
		this->position.y = y;
		this->radius = radius;
	}

	void Set( const Vector2& position, float radius )
	{
		this->position = position;
		this->radius = radius;
	}

	void Scale( float scale )
	{
		radius *= scale;
	}

	void Translate( const Vector2& translation )
	{
		position += translation;
	}

	Rectf GetBoundingRect() const
	{
		return Rectf(
			position.x - radius,
			position.y - radius,
			position.x + radius,
			position.y + radius
			);
	}

	bool Intersects( const Circle& c ) const
	{
		float dx = position.x - c.position.x;
		float dy = position.y - c.position.y;
		return ((dx * dx + dy * dy) < (radius + c.radius) * (radius + c.radius));
	}

	bool Intersects( const Vector2& point ) const
	{
		return (position.DistanceSquared( point ) < (radius * radius));
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
		const float dx = fabsf(position.x - r.position.x + rx);
		const float dy = fabsf(position.y - r.position.y + ry);

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



