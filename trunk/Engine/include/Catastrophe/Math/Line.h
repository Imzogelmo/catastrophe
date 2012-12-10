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


class Line
{
public:
	Vector2 p1, p2;

	Circle() {}
	Circle( const Vector2& p1, const Vector2& p2 ) : p1(p1), p2(p2) {}

	bool operator == ( const Line &l ) const { return p1 == l.p1 && p2 == l.p2; }
	bool operator != ( const Line &l ) const { return !(*this == l); }
	bool Equals( const Line &l, float epsilon = Math::Epsilon ) const
	{
		return (p1.Equals(l.p1) && p2.Equals(l.p2));
	}

	void Set( float x1, float y1, float x2, float y2 )
	{
		p1.x = x1;
		p1.y = y1;
		p2.x = x2;
		p2.y = y2;
	}

	void Set( const Vector2& point1, const Vector2& point2 )
	{
		p1 = point1;
		p2 = point2;
	}

	float Length() const
	{
		return p1.Distance(p2);
	}

	void Translate( const Vector2& translation )
	{
		p1 += translation;
		p2 += translation;
	}

	Rectf GetBoundingRect() const
	{
		return Rectf(
			Math::Min(p1.x, p2.x),
			Math::Min(p1.y, p2.y),
			Math::Max(p1.x, p2.x),
			Math::Max(p1.x, p2.x)
			);
	}

	bool Intersects( const Line& l ) const
	{
		return false;
	}

};


CE_NAMESPACE_END



