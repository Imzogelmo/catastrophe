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

#include "Catastrophe/Core/Math/Vector3.h"
#include "Catastrophe/Core/Math/Vector4.h"
#include "Catastrophe/Core/Math/Matrix.h"
#include "Catastrophe/Core/PlatformMath.h"

CE_NAMESPACE_BEGIN


class CE_API Quaternion
{
public:
	float x, y, z, w;

	Quaternion(): x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
	Quaternion(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}
	Quaternion(const Vector4 &q): x(q.x), y(q.y), z(q.z), w(q.w) {}
	Quaternion(const Vector3 &axis, float angle);

	Quaternion& Set(float X, float Y, float Z, float W) { x = X; y = Y; z = Z; w = W; return *this; }
	Quaternion& Scale(float scale) { x *= scale, y *= scale, z *= scale, w *= scale; return *this; }
	Quaternion& SetFromAxis(const Vector3& axis, float angle);

	Quaternion &operator = (const Vector4 &q) { x = q.x; y = q.y; z = q.z; w = q.w; return *this; }

	Quaternion operator - () const { return Quaternion(-x, -y, -z, w); }
	Quaternion operator + (const Quaternion &q) const { return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w); }
	Quaternion operator - (const Quaternion &q) const { return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w); }
	Quaternion operator * (const Quaternion &q) const;
	Quaternion operator / (const Quaternion &q) const { return Quaternion(*this * Quaternion(q).Inverse()); }

	Quaternion Scaled(float scale) const { return Quaternion(x * scale, y * scale, z * scale, w * scale); }
	Quaternion Inverse() const { return Quaternion(Conjugate()).Scaled(1.0f / LengthSquared()); }
	Quaternion Conjugate() const { return Quaternion(-x, -y, -z, w); }

	float Length() const { return (*((Vector4*)this)).Length(); }
	float LengthSquared() const { return (*((Vector4*)this)).LengthSquared(); }
	Quaternion& Normalize() { (*((Vector4*)this)).Normalize(); return *this;}
	Quaternion Normalized() { return (*((Vector4*)this)).Normalized(); }
	Vector3 Transform(const Vector3& v);

	static Quaternion Concatenate(const Quaternion &q1, const Quaternion &q2);
	static Quaternion Add(const Quaternion &q1, const Quaternion &q2)  { return q1 + q2; }
	static Quaternion Subtract(const Quaternion &q1, const Quaternion &q2)  { return q1 - q2; }
	static Quaternion Multiply(const Quaternion &q1, const Quaternion &q2)  { return q1 * q2; }
	static Quaternion Divide(const Quaternion &q1, const Quaternion &q2)  { return q1 / q2; }

	static Quaternion CreateFromYawPitchRoll(const Vector3& rot);
	static Quaternion CreateFromRotationMatrix(const Matrix& matrix);

};


CE_NAMESPACE_END







