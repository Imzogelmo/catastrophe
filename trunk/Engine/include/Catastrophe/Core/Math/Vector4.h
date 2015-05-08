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
#include "Catastrophe/Core/Math/Vector2.h"
#include "Catastrophe/Core/Math/Vector3.h"
#include "Catastrophe/Core/PlatformMath.h"

CE_NAMESPACE_BEGIN


class CE_API Vector4
{
public:
	float x, y, z, w;

	Vector4() {}
	Vector4(float n) : x(n), y(n), z(n), w(n) {}
	Vector4(float x , float y , float z , float w) : x(x), y(y), z(z), w(w) {}
	Vector4(const Vector3 &v, float w = 1.f) : x(v.x), y(v.y), z(v.z), w(w) {}
	Vector4(const float* p) : x(p[0]), y(p[1]), z(p[2]), w(p[3]) {}
	Vector4(const Color &c);
	Vector4(const Colorf &c);

	Vector4 &operator = (float n) { x = n; y = n; z = n; w = n; return *this; }
	Vector4 &operator = (const Vector3 &v) { x = v.x; y = v.y; z = v.z; w = 1.f; return *this; }

	float&operator [](const int i) { return *(&x + i);}
	const float &operator [](const int i) const { return *(&x + i);}

	Vector4 operator - () const { return Vector4(-x, -y, -z, -w);}

	Vector4 &operator ++ () { ++x; ++y; ++z; ++w; return *this; }
	Vector4 &operator -- () { --x; --y; ++z; ++w; return *this; }
	Vector4 operator ++ (int) { Vector4 tmp(*this); x++; y++; z++; w++; return tmp; }
	Vector4 operator -- (int) { Vector4 tmp(*this); x--; y--; z--; w--; return tmp; }

	Vector4 operator * (const Vector4 &v) const { return Vector4(x * v.x, y * v.y, z * v.z, w * v.w); }
	Vector4 operator / (const Vector4 &v) const { return Vector4(x / v.x, y / v.y, z / v.z, w / v.w); }
	Vector4 operator + (const Vector4 &v) const { return Vector4(x + v.x, y + v.y, z + v.z, w + v.w); }
	Vector4 operator - (const Vector4 &v) const { return Vector4(x - v.x, y - v.y, z - v.z, w - v.w); }
	Vector4 operator * (float val) const { return Vector4(x * val, y * val, z * val, w * val); }
	Vector4 operator / (float val) const { return Vector4(x / val, y / val, z / val, w / val); }
	Vector4 operator + (float val) const { return Vector4(x + val, y + val, z + val, w + val); }
	Vector4 operator - (float val) const { return Vector4(x - val, y - val, z - val, w - val); }

	Vector4 &operator *= (const Vector4 &v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	Vector4 &operator /= (const Vector4 &v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	Vector4 &operator += (const Vector4 &v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	Vector4 &operator -= (const Vector4 &v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	Vector4 &operator *= (float val) { x *= val; y *= val; z *= val; w *= val; return *this; }
	Vector4 &operator /= (float val) { x /= val; y /= val; z /= val; w /= val; return *this; }
	Vector4 &operator += (float val) { x += val; y += val; z += val; w += val; return *this; }
	Vector4 &operator -= (float val) { x -= val; y -= val; z -= val; w -= val; return *this; }

	inline friend Vector4 operator * (const float val, const Vector4 &v) { return Vector4(val * v.x, val * v.y, val * v.z, val * v.w); }
	inline friend Vector4 operator / (const float val, const Vector4 &v) { return Vector4(val / v.x, val / v.y, val / v.z, val / v.w); }
	inline friend Vector4 operator + (const float val, const Vector4 &v) { return Vector4(val + v.x, val + v.y, val + v.z, val + v.w); }
	inline friend Vector4 operator - (const float val, const Vector4 &v) { return Vector4(val - v.x, val - v.y, val - v.z, val - v.w); }

	bool operator == (const Vector4 &v) const { return Equals(v); }
	bool operator != (const Vector4 &v) const { return !Equals(v); }

	bool Equals(const Vector4 &v, float epsilon = Math::Epsilon) const;

	static const Vector4 Zero;
	static const Vector4 One;
	static const Vector4 UnitX;
	static const Vector4 UnitY;
	static const Vector4 UnitZ;
	static const Vector4 UnitW;

	float Dot(const Vector4 &v) const { return x * v.x + y * v.y + z * v.z + w * v.w;}
	float LengthSquared() const { return x * x + y * y + z * z + w * w;}
	float Length() const { return sqrtf(x * x + y * y + z * z + w * w);}
	float DistanceSquared(const Vector4 &v) const { return (*this - v).LengthSquared(); }
	float Distance(const Vector4 &v) const { return (*this - v).Length();}

	Vector2 ToVector2() const;
	Vector3 ToVector3() const;
	Colorf ToColorf() const;
	Color ToColor() const;

	Vector4 Abs() const { return Vector4(fabsf(x), fabsf(y), fabsf(z), fabsf(w));}
	Vector4 Ceil() const { return Vector4(ceilf(x), ceilf(y), ceilf(z), ceilf(w));}
	Vector4 Floor() const { return Vector4(floorf(x), floorf(y), floorf(z), floorf(w));}
	Vector4 Round() const { return Vector4(Math::Roundf(x), Math::Roundf(y), Math::Roundf(z), Math::Roundf(w)); }
	Vector4 Negate() const { return Vector4(-x, -y, -z, -w);}

	void Normalize();
	Vector4 Normalized() const;
	Vector4& Set(float X, float Y, float Z, float W) { x = X; y = Y; z = Z; w = W; return *this; }

	void Clamp(const Vector4& min, const Vector4& max);


};



CE_NAMESPACE_END



