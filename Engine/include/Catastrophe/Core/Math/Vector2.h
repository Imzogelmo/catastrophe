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

CE_NAMESPACE_BEGIN


class CE_API Vector2
{
public:
	float x, y;

	Vector2() {}
	Vector2(float n) : x(n), y(n) {}
	Vector2(float x, float y) : x(x), y(y) {}
	Vector2(const float* p) : x(p[0]), y(p[1]) {}
	Vector2(const Vector3 &v);
	Vector2(const Vector4 &v);
	Vector2(const Point &p);

	Vector2 &operator = (float n) { x = n; y = n; return *this; }
	Vector2 &operator = (const Point &p) { *this = Vector2(p); return *this; }

	float&operator [](const int i) { return *(&x + i); }
	const float &operator [](const int i) const { return *(&x + i); }
	Vector2 operator - () const { return Vector2(-x, -y);}

	Vector2 &operator ++ () { ++x; ++y; return *this; }
	Vector2 &operator -- () { --x; --y; return *this; }
	Vector2 operator ++ (int) { Vector2 tmp(*this); x++; y++; return tmp; }
	Vector2 operator -- (int) { Vector2 tmp(*this); x--; y--; return tmp; }

	Vector2 operator * (const Vector2 &v)const { return Vector2(x * v.x, y * v.y); }
	Vector2 operator / (const Vector2 &v)const { return Vector2(x / v.x, y / v.y); }
	Vector2 operator + (const Vector2 &v)const { return Vector2(x + v.x, y + v.y); }
	Vector2 operator - (const Vector2 &v)const { return Vector2(x - v.x, y - v.y); }
	Vector2 operator * (const float val)const { return Vector2(x * val, y * val); }
	Vector2 operator / (const float val)const { return Vector2(x / val, y / val); }
	Vector2 operator + (const float val)const { return Vector2(x + val, y + val); }
	Vector2 operator - (const float val)const { return Vector2(x - val, y - val); }

	inline friend Vector2 operator * (const float val, const Vector2 &v) { return Vector2(val * v.x, val * v.y); }
	inline friend Vector2 operator / (const float val, const Vector2 &v) { return Vector2(val / v.x, val / v.y); }
	inline friend Vector2 operator + (const float val, const Vector2 &v) { return Vector2(val + v.x, val + v.y); }
	inline friend Vector2 operator - (const float val, const Vector2 &v) { return Vector2(val - v.x, val - v.y); }

	Vector2 &operator *= (const Vector2 &v) { x *= v.x; y *= v.y; return *this; }
	Vector2 &operator /= (const Vector2 &v) { x /= v.x; y /= v.y; return *this; }
	Vector2 &operator += (const Vector2 &v) { x += v.x; y += v.y; return *this; }
	Vector2 &operator -= (const Vector2 &v) { x -= v.x; y -= v.y; return *this; }
	Vector2 &operator *= (float val) { x *= val; y *= val; return *this; }
	Vector2 &operator /= (float val) { x /= val; y /= val; return *this; }
	Vector2 &operator += (float val) { x += val; y += val; return *this; }
	Vector2 &operator -= (float val) { x -= val; y -= val; return *this; }

	bool operator == (const Vector2 &v) const { return x == v.x && y == v.y; }
	bool operator != (const Vector2 &v) const { return !(*this == v); }
	bool Equals(const Vector2 &v, float epsilon = Math::Epsilon) const;

	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 One;

	float Dot(const Vector2 &v) const { return x * v.x + y * v.y; }
	float Cross(const Vector2 &v) const { return x * v.y - y * v.x; }
	float LengthSquared() const { return x * x + y * y;}
	float Length() const { return sqrtf(x * x + y * y);}
	float DistanceSquared(const Vector2 &v) const { return (*this - v).LengthSquared(); }
	float Distance(const Vector2 &v) const { return (*this - v).Length();}
	bool IsZero() const { return (*this == 0.0f); }

	float ApproxLength() const
	{
		float dx = fabs(x), dy = fabs(y);
		if(dy > dx) return 0.41f * dx + 0.941246f * dy;
		return 0.41f * dy + 0.941246f * dx;
	}

	float Angle() const { return atan2f(y, x); }
	float Angle(const Vector2& to) const
	{
		return atan2f(to.y - y, to.x - x);
	}

	Vector3 ToVector3() const;
	Vector2 Polar(const Vector2& dist, float theta) const;

	Vector2 Direction(const Vector2& other) const
	{
		const Vector2 distance = *this - other;
		return distance / distance.Length();
	}

	Vector2 Rotated(float a) const;
	Vector2 Rotated(float a, const Vector2& origin) const;
	void Rotate(float a);
	void Rotate(float a, const Vector2& origin);

	float Min() const { return (x < y ? x : y); }
	float Max() const { return (x > y ? x : y); }
	Vector2 Abs() const { return Vector2(fabsf(x), fabsf(y)); }
	Vector2 Ceil() const { return Vector2(ceilf(x), ceilf(y)); }
	Vector2 Floor() const { return Vector2(floorf(x), floorf(y)); }
	Vector2 Round() const { return Vector2(Math::Roundf(x), Math::Roundf(y)); }
	Vector2 Negate() const { return Vector2(-x, -y); }
	Vector2 Perpendicular() const { return Vector2(-y, x); }

	Vector2 Unit() const { return Normalized(); }
	Vector2 Normalized() const
	{
		const float length = 1.f / (Length() + 0.0000001f);
		return Vector2(x * length, y * length);
	}

	Vector2& Normalize()
	{
		const float length = 1.f / (Length() + 0.0000001f);
		x *= length;
		y *= length;
		return *this;
	}

	Vector2& Set(float X, float Y) { x = X; y = Y; return *this; }
	Vector2& Swap() { Math::Swap(x, y); return *this; }

	Vector2 Reflect(const Vector2& unit) const;
	Vector2 Refract(const Vector2& unit, float eta) const;

	Vector2& Clamp(const Vector2& min, const Vector2& max)
	{
		Math::FastClamp(x, min.x, max.x);
		Math::FastClamp(y, min.y, max.y);
		return *this;
	}

	Vector2 Clamped(const Vector2& min, const Vector2& max) const
	{
		return Vector2(*this).Clamp(min, max);
	}

	Vector2& Lerp(const Vector2& p2, float t)
	{
		x += (p2.x - x) * t;
		y += (p2.y - y) * t;
		return *this;
	}

	Vector2 Transform(const Matrix& mat) const;

};



CE_NAMESPACE_END



