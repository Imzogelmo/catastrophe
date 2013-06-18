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

#include "Math/Quaternion.h"
#include "Math/Matrix.h"
#include "Math/Math.h"

CE_NAMESPACE_BEGIN



Quaternion::Quaternion( const Vector3 &axis, float angle )
{
	SetFromAxis(axis, angle);
}


Quaternion& Quaternion::SetFromAxis( const Vector3& axis, float angle )
{
	float d = axis.Length();
	if( d != 0.f )
	{
		d = 1.f / d;
		Vector2 v = Math::SinCos(angle);
		*this = Quaternion(d * axis.x * v.y, d * axis.y * v.y, d * axis.z * v.y, w = v.x).Normalize();
	}
	else
	{
		*this = Quaternion();
	}

	return *this;
}


Quaternion Quaternion::operator *( const Quaternion &q ) const
{
	return Quaternion 
	(	
		w * q.x + x * q.w + y * q.z - z * q.y,
		w * q.y + y * q.w + z * q.x - x * q.z,
		w * q.z + z * q.w + x * q.y - y * q.x,
		w * q.w - x * q.x - y * q.y - z * q.z
	);
}


Vector3 Quaternion::Transform( const Vector3& v )
{
	Quaternion t = Conjugate();
	t = (*this * (Quaternion(v.x, v.y, v.z, 0.f) * t));

	return Vector3( t.x, t.y, t.z );
}


Quaternion Quaternion::Concatenate( const Quaternion &q1, const Quaternion &q2 )
{
	Quaternion q;
	
	q.x = (q2.x * q1.w) + (q1.x * q2.w) + (q2.y * q1.z) - (q2.z * q1.y);
	q.y = (q2.y * q1.w) + (q1.y * q2.w) + (q2.z * q1.x) - (q2.x * q1.z);
	q.z = (q2.z * q1.w) + (q1.z * q2.w) + (q2.x * q1.y) - (q2.y * q1.x);
	q.w = (q2.w * q1.w) - (q2.x * q1.x) + (q2.y * q1.y) + (q2.z * q1.z);

	return q;
}


Quaternion Quaternion::CreateFromYawPitchRoll( const Vector3& rot )
{
	//rot *= 0.5f;
	Vector2 yaw = Math::SinCos(rot.x);
	Vector2 pitch = Math::SinCos(rot.y);
	Vector2 roll = Math::SinCos(rot.z);

	return Quaternion
	(
		((yaw.x * pitch.y) * roll.x) + ((yaw.y * pitch.x) * roll.y),
		((yaw.y * pitch.x) * roll.x) - ((yaw.x * pitch.y) * roll.y),
		((yaw.x * pitch.x) * roll.y) - ((yaw.y * pitch.y) * roll.x),
		((yaw.x * pitch.x) * roll.x) + ((yaw.y * pitch.y) * roll.y)
	);
}


Quaternion Quaternion::CreateFromRotationMatrix( const Matrix& matrix )
{
	Quaternion q;
	float trace = (matrix.m[0] + matrix.m[5] + matrix.m[10]);

	if( trace > 0.0f )
	{
		float s = 0.5f / sqrtf( trace+ 1.0f );
		q.w = 0.25f / s;
		q.x = (matrix.m[9] - matrix.m[6]) * s;
		q.y = (matrix.m[2] - matrix.m[8]) * s;
		q.z = (matrix.m[4] - matrix.m[1]) * s;
	} 
	else if( matrix.m[0] > matrix.m[5] && matrix.m[0] > matrix.m[10] )
	{
		float s = 2.0f * sqrtf( 1.0f + matrix.m[0] - matrix.m[5] - matrix.m[10] );
		q.w = (matrix.m[9] - matrix.m[6]) / s;
		q.x = 0.25f * s;
		q.y = (matrix.m[1] + matrix.m[4]) / s;
		q.z = (matrix.m[2] + matrix.m[8]) / s;
	}
	else if( matrix.m[5] > matrix.m[10] )
	{
		float s = 2.0f * sqrtf( 1.0f + matrix.m[5] - matrix.m[0] - matrix.m[10] );
		q.w = (matrix.m[2] - matrix.m[8]) / s;
		q.x = (matrix.m[1] + matrix.m[4]) / s;
		q.y = 0.25f * s;
		q.z = (matrix.m[6] + matrix.m[9]) / s;
	}
	else
	{
		float s = 2.0f * sqrtf( 1.0f + matrix.m[10] - matrix.m[0] - matrix.m[5] );
		q.w = (matrix.m[4] - matrix.m[1]) / s;
		q.x = (matrix.m[2] + matrix.m[8]) / s;
		q.y = (matrix.m[6] + matrix.m[9]) / s;
		q.z = 0.25f * s;
	}

	return q;
}




CE_NAMESPACE_END

