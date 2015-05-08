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

#include "Catastrophe/Core/Math/Quaternion.h"
#include "Catastrophe/Core/Math/Matrix.h"
#include "Catastrophe/Core/PlatformMath.h"

CE_NAMESPACE_BEGIN


const Matrix Matrix::Zero = Matrix
(
	0.0f,  0.0f,  0.0f,  0.0f,  
	0.0f,  0.0f,  0.0f,  0.0f,  
	0.0f,  0.0f,  0.0f,  0.0f,  
	0.0f,  0.0f,  0.0f,  0.0f
);


const Matrix Matrix::Identity = Matrix
(
	1.0f,  0.0f,  0.0f,  0.0f,  
	0.0f,  1.0f,  0.0f,  0.0f,  
	0.0f,  0.0f,  1.0f,  0.0f,  
	0.0f,  0.0f,  0.0f,  1.0f
);


Matrix Matrix::operator +( const Matrix& rhs ) const
{
	return Matrix(
		m[0] + rhs.m[0], m[1] + rhs.m[1], m[2] + rhs.m[2], m[3] + rhs.m[3],
		m[4] + rhs.m[4], m[5] + rhs.m[5], m[6] + rhs.m[6], m[7] + rhs.m[7],
		m[8] + rhs.m[8], m[9] + rhs.m[9], m[10] + rhs.m[10], m[11] + rhs.m[11],
		m[12] + rhs.m[12], m[13] + rhs.m[13], m[14] + rhs.m[14], m[15] + rhs.m[15]
	);
}


Matrix Matrix::operator -( const Matrix& rhs ) const
{
	return Matrix(
		m[0] - rhs.m[0], m[1] - rhs.m[1], m[2] - rhs.m[2], m[3] - rhs.m[3],
		m[4] - rhs.m[4], m[5] - rhs.m[5], m[6] - rhs.m[6], m[7] - rhs.m[7],
		m[8] - rhs.m[8], m[9] - rhs.m[9], m[10] - rhs.m[10], m[11] - rhs.m[11],
		m[12] - rhs.m[12], m[13] - rhs.m[13], m[14] - rhs.m[14], m[15] - rhs.m[15]
	);
}


Matrix Matrix::operator *( const Matrix &rhs ) const
{
	return Multiply(&m[0], &rhs.m[0]);
}


Matrix Matrix::operator *( float scalar ) const
{
	return Matrix(
		m[0] * scalar, m[1] * scalar, m[2] * scalar, m[3] * scalar,
		m[4] * scalar, m[5] * scalar, m[6] * scalar, m[7] * scalar,
		m[8] * scalar, m[9] * scalar, m[10] * scalar, m[11] * scalar,
		m[12] * scalar, m[13] * scalar, m[14] * scalar, m[15] * scalar
	);
}


Matrix Matrix::operator /( float scalar ) const
{
	return operator *(1.f / scalar);
}


Vector3 Matrix::operator *( const Vector3& v ) const
{
	return Vector3(
		(m[0] * v.x + m[1] * v.y + m[2] * v.z + m[3]),
		(m[4] * v.x + m[5] * v.y + m[6] * v.z + m[7]),
		(m[8] * v.x + m[9] * v.y + m[10] * v.z + m[11])
	);
}


Matrix &Matrix::operator +=( const Matrix &rhs )
{
	m[0] += rhs.m[0], m[1] += rhs.m[1], m[2] += rhs.m[2], m[3] += rhs.m[3];
	m[4] += rhs.m[4], m[5] += rhs.m[5], m[6] += rhs.m[6], m[7] += rhs.m[7];
	m[8] += rhs.m[8], m[9] += rhs.m[9], m[10] += rhs.m[10], m[11] += rhs.m[11];
	m[12] += rhs.m[12], m[13] += rhs.m[13], m[14] += rhs.m[14], m[15] += rhs.m[15];
	return *this;
}


Matrix &Matrix::operator -=( const Matrix &rhs )
{
	m[0] -= rhs.m[0], m[1] -= rhs.m[1], m[2] -= rhs.m[2], m[3] -= rhs.m[3];
	m[4] -= rhs.m[4], m[5] -= rhs.m[5], m[6] -= rhs.m[6], m[7] -= rhs.m[7];
	m[8] -= rhs.m[8], m[9] -= rhs.m[9], m[10] -= rhs.m[10], m[11] -= rhs.m[11];
	m[12] -= rhs.m[12], m[13] -= rhs.m[13], m[14] -= rhs.m[14], m[15] -= rhs.m[15];
	return *this;
}


Matrix &Matrix::operator *=( const Matrix& rhs )
{
	float temp[16];
	temp[0] = m[0] * rhs.m[0] + m[1] * rhs.m[4] + m[2] * rhs.m[8] + m[3] * rhs.m[12];
	temp[1] = m[0] * rhs.m[1] + m[1] * rhs.m[5] + m[2] * rhs.m[9] + m[3] * rhs.m[13];
	temp[2] = m[0] * rhs.m[2] + m[1] * rhs.m[6] + m[2] * rhs.m[10] + m[3] * rhs.m[14];
	temp[3] = m[0] * rhs.m[3] + m[1] * rhs.m[7] + m[2] * rhs.m[11] + m[3] * rhs.m[15];
	temp[4] = m[4] * rhs.m[0] + m[5] * rhs.m[4] + m[6] * rhs.m[8] + m[7] * rhs.m[12];
	temp[5] = m[4] * rhs.m[1] + m[5] * rhs.m[5] + m[6] * rhs.m[9] + m[7] * rhs.m[13];
	temp[6] = m[4] * rhs.m[2] + m[5] * rhs.m[6] + m[6] * rhs.m[10] + m[7] * rhs.m[14];
	temp[7] = m[4] * rhs.m[3] + m[5] * rhs.m[7] + m[6] * rhs.m[11] + m[7] * rhs.m[15];
	temp[8] = m[8] * rhs.m[0] + m[9] * rhs.m[4] + m[10] * rhs.m[8] + m[11] * rhs.m[12];
	temp[9] = m[8] * rhs.m[1] + m[9] * rhs.m[5] + m[10] * rhs.m[9] + m[11] * rhs.m[13];
	temp[10] = m[8] * rhs.m[2] + m[9] * rhs.m[6] + m[10] * rhs.m[10] + m[11] * rhs.m[14];
	temp[11] = m[8] * rhs.m[3] + m[9] * rhs.m[7] + m[10] * rhs.m[11] + m[11] * rhs.m[15];
	temp[12] = m[12] * rhs.m[0] + m[13] * rhs.m[4] + m[14] * rhs.m[8] + m[15] * rhs.m[12];
	temp[13] = m[12] * rhs.m[1] + m[13] * rhs.m[5] + m[14] * rhs.m[9] + m[15] * rhs.m[13];
	temp[14] = m[12] * rhs.m[2] + m[13] * rhs.m[6] + m[14] * rhs.m[10] + m[15] * rhs.m[14];
	temp[15] = m[12] * rhs.m[3] + m[13] * rhs.m[7] + m[14] * rhs.m[11] + m[15] * rhs.m[15];

	*this = Matrix(temp);
	return *this;
}


Matrix &Matrix::operator *=( float scalar )
{
	m[0] *= scalar, m[1] *= scalar, m[2] *= scalar, m[3] *= scalar;
	m[4] *= scalar, m[5] *= scalar, m[6] *= scalar, m[7] *= scalar;
	m[8] *= scalar, m[9] *= scalar, m[10] *= scalar, m[11] *= scalar;
	m[12] *= scalar, m[13] *= scalar, m[14] *= scalar, m[15] *= scalar;
	return *this;
}


Matrix &Matrix::operator /=( float scalar )
{
	operator *=(1.f / scalar);
	return *this;
}


bool Matrix::operator ==( const Matrix& rhs ) const
{
	for( int i(0); i < 16; ++i )
		if( !Math::EpsilonCompare( m[i], rhs.m[i] ) )
			return false;
	return true;
}


bool Matrix::operator !=( const Matrix& rhs ) const
{
	return !(*this == rhs);
}


float Matrix::Determinant() const
{
	return(
		(m[0] * m[5] - m[4] * m[1]) * (m[10] * m[15] - m[14] * m[11]) -
		(m[0] * m[9] - m[8] * m[1]) * (m[6] * m[15] - m[14] * m[7]) +
		(m[0] * m[13] - m[12] * m[1]) * (m[6] * m[11] - m[10] * m[7]) +
		(m[4] * m[9] - m[8] * m[5]) * (m[2] * m[15] - m[14] * m[3]) -
		(m[4] * m[13] - m[12] * m[5]) * (m[2] * m[11] - m[10] * m[3]) +
		(m[8] * m[13] - m[12] * m[9]) * (m[2] * m[7] - m[6] * m[3])
	);

	/*
	return
		m[3] * m[6] * m[9] * m[12] -
		m[2] * m[7] * m[9] * m[12] -
		m[3] * m[5] * m[10] * m[12] +
		m[1] * m[7] * m[10] * m[12] +
		m[2] * m[5] * m[11] * m[12] -
		m[1] * m[6] * m[11] * m[12] -
		m[3] * m[6] * m[8] * m[13] +
		m[2] * m[7] * m[8] * m[13] +
		m[3] * m[4] * m[10] * m[13] -
		m[0] * m[7] * m[10] * m[13] -
		m[2] * m[4] * m[11] * m[13] +
		m[0] * m[6] * m[11] * m[13] +
		m[3] * m[5] * m[8] * m[14] -
		m[1] * m[7] * m[8] * m[14] -
		m[3] * m[4] * m[9] * m[14] +
		m[0] * m[7] * m[9] * m[14] +
		m[1] * m[4] * m[11] * m[14] -
		m[0] * m[5] * m[11] * m[14] -
		m[2] * m[5] * m[8] * m[15] +
		m[1] * m[6] * m[8] * m[15] +
		m[2] * m[4] * m[9] * m[15] -
		m[0] * m[6] * m[9] * m[15] -
		m[1] * m[4] * m[10] * m[15] +
		m[0] * m[5] * m[10] * m[15];
	*/
}


Matrix Matrix::Transpose() const
{
	return Matrix
		(
			m[0], m[4], m[8],  m[12],
			m[1], m[5], m[9],  m[13],
			m[2], m[6], m[10], m[14],
			m[3], m[7], m[11], m[15]
		);
}


Matrix Matrix::Inverse() const
{
	Matrix mat;

	float d = Determinant();
	if( d != 0.f )
	{
		d = (1.0f / d);

		mat[0] = d * (m[9] * m[14] * m[7] - m[13] * m[10] * m[7] + m[13] * m[6] * m[11] - m[5] * m[14] * m[11] - m[9] * m[6] * m[15] + m[5] * m[10] * m[15]);
		mat[1] = d * (m[13] * m[10] * m[3] - m[9] * m[14] * m[3] - m[13] * m[2] * m[11] + m[1] * m[14] * m[11] + m[9] * m[2] * m[15] - m[1] * m[10] * m[15]);
		mat[2] = d * (m[5] * m[14] * m[3] - m[13] * m[6] * m[3] + m[13] * m[2] * m[7] - m[1] * m[14] * m[7] - m[5] * m[2] * m[15] + m[1] * m[6] * m[15]);
		mat[3] = d * (m[9] * m[6] * m[3] - m[5] * m[10] * m[3] - m[9] * m[2] * m[7] + m[1] * m[10] * m[7] + m[5] * m[2] * m[11] - m[1] * m[6] * m[11]);
		mat[4] = d * (m[12] * m[10] * m[7] - m[8] * m[14] * m[7] - m[12] * m[6] * m[11] + m[4] * m[14] * m[11] + m[8] * m[6] * m[15] - m[4] * m[10] * m[15]);
		mat[5] = d * (m[8] * m[14] * m[3] - m[12] * m[10] * m[3] + m[12] * m[2] * m[11] - m[0] * m[14] * m[11] - m[8] * m[2] * m[15] + m[0] * m[10] * m[15]);
		mat[6] = d * (m[12] * m[6] * m[3] - m[4] * m[14] * m[3] - m[12] * m[2] * m[7] + m[0] * m[14] * m[7] + m[4] * m[2] * m[15] - m[0] * m[6] * m[15]);
		mat[7] = d * (m[4] * m[10] * m[3] - m[8] * m[6] * m[3] + m[8] * m[2] * m[7] - m[0] * m[10] * m[7] - m[4] * m[2] * m[11] + m[0] * m[6] * m[11]);
		mat[8] = d * (m[8] * m[13] * m[7] - m[12] * m[9] * m[7] + m[12] * m[5] * m[11] - m[4] * m[13] * m[11] - m[8] * m[5] * m[15] + m[4] * m[9] * m[15]);
		mat[9] = d * (m[12] * m[9] * m[3] - m[8] * m[13] * m[3] - m[12] * m[1] * m[11] + m[0] * m[13] * m[11] + m[8] * m[1] * m[15] - m[0] * m[9] * m[15]);
		mat[10] = d * (m[4] * m[13] * m[3] - m[12] * m[5] * m[3] + m[12] * m[1] * m[7] - m[0] * m[13] * m[7] - m[4] * m[1] * m[15] + m[0] * m[5] * m[15]);
		mat[11] = d * (m[8] * m[5] * m[3] - m[4] * m[9] * m[3] - m[8] * m[1] * m[7] + m[0] * m[9] * m[7] + m[4] * m[1] * m[11] - m[0] * m[5] * m[11]);
		mat[12] = d * (m[12] * m[9] * m[6] - m[8] * m[13] * m[6] - m[12] * m[5] * m[10] + m[4] * m[13] * m[10] + m[8] * m[5] * m[14] - m[4] * m[9] * m[14]);
		mat[13] = d * (m[8] * m[13] * m[2] - m[12] * m[9] * m[2] + m[12] * m[1] * m[10] - m[0] * m[13] * m[10] - m[8] * m[1] * m[14] + m[0] * m[9] * m[14]);
		mat[14] = d * (m[12] * m[5] * m[2] - m[4] * m[13] * m[2] - m[12] * m[1] * m[6] + m[0] * m[13] * m[6] + m[4] * m[1] * m[14] - m[0] * m[5] * m[14]);
		mat[15] = d * (m[4] * m[9] * m[2] - m[8] * m[5] * m[2] + m[8] * m[1] * m[6] - m[0] * m[9] * m[6] - m[4] * m[1] * m[10] + m[0] * m[5] * m[10]);
	}

	return mat;
}


Vector3 Matrix::GetTranslation() const
{
	return Vector3( m[12], m[13], m[14] );
}


Vector3 Matrix::GetScale() const
{
	return Vector3( m[0], m[5], m[10] );
}


Matrix& Matrix::Translate( const Vector3& translation )
{
	m[12] += translation.x;
	m[13] += translation.y;
	m[14] += translation.z;
	return *this;
}


Matrix& Matrix::Scale( const Vector3& scale )
{
	m[0] *= scale.x;
	m[5] *= scale.y;
	m[10] *= scale.z;
	return *this;
}


Matrix& Matrix::SetFromAxes( const Vector3 &x, const Vector3 &y, const Vector3 &z )
{
	m[0] = x.x,  m[1] = x.y,  m[2] = x.z,  m[3] = 0.0f;
	m[4] = y.x,  m[5] = y.y,  m[6] = y.z,  m[7] = 0.0f;
	m[8] = z.x,  m[9] = z.y,  m[10] = z.z,  m[11] = 0.0f;
	m[12] = 0.0f, m[13] = 0.0f, m[14] = 0.0f, m[15] = 1.0f;

	return *this;
}


Matrix& Matrix::SetFromAxisAngle( const Vector3 &axis, float angle )
{
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	float c, s;
	Math::SinCosf(angle, s, c);

	m[0] = (x * x) * (1.0f - c) + c;
	m[1] = (x * y) * (1.0f - c) + (z * s);
	m[2] = (x * z) * (1.0f - c) - (y * s);
	m[3] = 0.0f;

	m[4] = (y * x) * (1.0f - c) - (z * s);
	m[5] = (y * y) * (1.0f - c) + c;
	m[6] = (y * z) * (1.0f - c) + (x * s);
	m[7] = 0.0f;

	m[8] = (z * x) * (1.0f - c) + (y * s);
	m[9] = (z * y) * (1.0f - c) - (x * s);
	m[10] = (z * z) * (1.0f - c) + c;
	m[11] = 0.0f;

	m[12] = 0.0f;
	m[13] = 0.0f;
	m[14] = 0.0f;
	m[15] = 1.0f;

	return *this;
}


Matrix Matrix::Lerp( const Matrix& a, const Matrix& b, float t )
{
	return Matrix(
		a[0] + ((b[0] - a[0]) * t), a[1] + ((b[1] - a[1]) * t), a[2] + ((b[2] - a[2]) * t), a[3] + ((b[3] - a[3]) * t),
		a[4] + ((b[4] - a[4]) * t), a[5] + ((b[5] - a[5]) * t), a[6] + ((b[6] - a[6]) * t), a[7] + ((b[7] - a[7]) * t),
		a[8] + ((b[8] - a[8]) * t), a[9] + ((b[9] - a[9]) * t), a[10] + ((b[10] - a[10]) * t), a[11] + ((b[11] - a[11]) * t),
		a[12] + ((b[12] - a[12]) * t), a[13] + ((b[13] - a[13]) * t), a[14] + ((b[14] - a[14]) * t), a[15] + ((b[15] - a[15]) * t)
	);
}


Matrix Matrix::Multiply( const float* a, const float* b )
{
	/*
	return Matrix
	(
		a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12],
		a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13],
		a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14],
		a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15],
		a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12],
		a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13],
		a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14],
		a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15],
		a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12],
		a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13],
		a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14],
		a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15],
		a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12],
		a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13],
		a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14],
		a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15]
	);
	*/

	return Matrix(
		b[0] * a[0] + b[1] * a[4] + b[2] * a[8] + b[3] * a[12],
		b[0] * a[1] + b[1] * a[5] + b[2] * a[9] + b[3] * a[13],
		b[0] * a[2] + b[1] * a[6] + b[2] * a[10] + b[3] * a[14],
		b[0] * a[3] + b[1] * a[7] + b[2] * a[11] + b[3] * a[15],
		b[4] * a[0] + b[5] * a[4] + b[6] * a[8] + b[7] * a[12],
		b[4] * a[1] + b[5] * a[5] + b[6] * a[9] + b[7] * a[13],
		b[4] * a[2] + b[5] * a[6] + b[6] * a[10] + b[7] * a[14],
		b[4] * a[3] + b[5] * a[7] + b[6] * a[11] + b[7] * a[15],
		b[8] * a[0] + b[9] * a[4] + b[10] * a[8] + b[11] * a[12],
		b[8] * a[1] + b[9] * a[5] + b[10] * a[9] + b[11] * a[13],
		b[8] * a[2] + b[9] * a[6] + b[10] * a[10] + b[11] * a[14],
		b[8] * a[3] + b[9] * a[7] + b[10] * a[11] + b[11] * a[15],
		b[12] * a[0] + b[13] * a[4] + b[14] * a[8] + b[15] * a[12],
		b[12] * a[1] + b[13] * a[5] + b[14] * a[9] + b[15] * a[13],
		b[12] * a[2] + b[13] * a[6] + b[14] * a[10] + b[15] * a[14],
		b[12] * a[3] + b[13] * a[7] + b[14] * a[11] + b[15] * a[15]
	);
}


Matrix Matrix::Multiply( const Matrix& a, const Matrix& b )
{
	return Multiply(&a.m[0], &b.m[0]);
}


Matrix Matrix::CreateLookAt( const Vector3& camera, const Vector3& target, const Vector3& up )
{
	Vector3 z = (camera - target).Normalized();
	Vector3 x = Vector3::Cross(up, z).Normalized();
	Vector3 y = Vector3::Cross(z, x).Normalized();

	float tx = -Vector3::Dot(x, camera);
	float ty = -Vector3::Dot(y, camera);
	float tz = -Vector3::Dot(z, camera);

	return Matrix
		(
			x.x, y.x, z.x, 0.0f,
			x.y, y.y, z.y, 0.0f,
			x.z, y.z, z.z, 0.0f,
			tx,  ty,  tz,  1.0f
		);
}


Matrix Matrix::CreatePerspective( float fov, float aspect, float up, float near, float far )
{
	const float e = tanf(CE_TO_RADIANS * (fov / 2.f)) * near;	
	const float left = -e * aspect;
	const float right = e * aspect;
	const float top = e;
	const float bottom = -e;

	//flip the up vector
	float h = (2.f * near) / (top - bottom);
	if( up <= 0.f )
		h = -h;

	const float w = (2.f * near) / (right - left);
	const float q = -(far + near) / (far - near);
	const float z = -(2.f * far * near) / (far - near);

	return Matrix
		(
			w,		0.0f,	0.0f,   0.0f,  
			0.0f,	h,		0.0f,   0.0f,  
			0.0f,	0.0f,	q,		-1.0f,  
			0.0f,	0.0f,   z,		0.0f
		);
}


Matrix Matrix::CreateOrthographic( float left, float right, float bottom, float top, float near, float far )
{
	Matrix matrix;
	matrix[0] = 2.f / (right - left);
	matrix[5] = 2.f / (top - bottom);
	matrix[10] = -2.f / (far - near);
	matrix[12] = -((right + left) / (right - left));
	matrix[13] = -((top + bottom) / (top - bottom));
	matrix[14] = -((far + near) / (far - near));
	return matrix;
}


Matrix Matrix::CreateFromAxes( const Vector3 &x, const Vector3 &y, const Vector3 &z )
{
	Matrix mat;
	mat.SetFromAxes(x, y, z);
	return mat;
}

Matrix Matrix::CreateFromAxisAngle( const Vector3 &axis, float angle )
{
	Matrix mat;
	mat.SetFromAxisAngle(axis, angle);
	return mat;
}


Matrix Matrix::CreateRotation( const Vector3& rotation )
{
	Matrix matrix;

	const Vector2 a = Math::SinCosf(rotation.x);
	const Vector2 b = Math::SinCosf(rotation.y);
	const Vector2 c = Math::SinCosf(rotation.z);

	matrix[0] = b.x * c.x + a.y * b.y * c.y;
	matrix[1] = a.x * c.y;
	matrix[2] = c.x * b.y - b.x * a.y * c.y;

	matrix[4] = c.x * a.y * b.y - b.x * c.y;
	matrix[5] = a.x * c.x;
	matrix[6] = -b.x * c.x * a.y - b.y * c.y;

	matrix[8] = -a.x * b.y;
	matrix[9] = a.y;
	matrix[10] = a.x * b.x;

	return matrix;
}


Matrix Matrix::CreateFromQuaternion( const Quaternion& q )
{
	float xx = q.x * q.x;
	float xy = q.x * q.y;
	float xz = q.x * q.z;
	float xw = q.x * q.w;
	float yy = q.y * q.y;
	float yz = q.y * q.z;
	float yw = q.y * q.w;
	float zz = q.z * q.z;
	float zw = q.z * q.w;

	Matrix mat;
	mat.m[0] = 1.f - 2.f * (yy + zz);
	mat.m[1] = 2.f * (xy + zw);
	mat.m[2] = 2.f * (xz - yw);

	mat.m[4] = 2.f * (xy - zw);
	mat.m[5] = 1.f - 2.f * (xx + zz);
	mat.m[6] = 2.f * (yz + xw);

	mat.m[8] = 2.f * (xz + yw);
	mat.m[9] = 2.f * (yz - xw);
	mat.m[10] = 1.f - 2.f * (xx + yy);

	return mat;
}


Matrix Matrix::CreateTransformation( const Vector3& position, float rotation, const Vector3& scale, const Vector3& origin )
{
	//fixme: optimize.
	const Vector3 t = position + origin;
	return Matrix(
		scale.x,	0.0f,		0.0f,		0.0f,
		0.0f,		scale.y,	0.0f,		0.0f,
		0.0f,		0.0f,		scale.z,	0.0f,
		t.x,		t.y,		t.z,		1.0f
	) *
	CreateRotationZ(rotation) *
	CreateTranslation(-origin);
}


Matrix Matrix::Create2DTransformation( const Vector2& position, float rotation, const Vector2& scale, const Vector2& origin )
{
	Vector2 v = Math::SinCosf(rotation);
	float tx = origin.x * (1.f - v.x) + origin.y * v.x;
	float ty = origin.y * (1.f - v.x) - origin.x * v.y;
	float vx = v.x * scale.x;
	float vy = v.x * scale.y;

	//???
	tx += position.x;
	ty += position.y;

	return Matrix
	(
		vx,		v.y,	0.0f,	0.0f,
		-v.y,	vy,		0.0f,	0.0f,
		0.0f,	0.0f,	1.0f,	0.0f,
		tx,		ty,		0.0f,	1.0f
	);


	/*
	//fixme: this is wrong..
	const Vector2 t = position + origin;
	Matrix transform(
		scale.x,	0.0f,		0.0f,		0.0f,
		0.0f,		scale.y,	0.0f,		0.0f,
		0.0f,		0.0f,		1.0f,		0.0f,
		t.x,		t.y,		0.0f,		1.0f
	);

	if( rotation != 0.f )
	{
		float s, c;
		fc::sincos(rotation, s, c);

		transform[0] *= c - transform[1] * s;
		transform[1] *= s + transform[1] * c;
		transform[4] *= c - transform[5] * s;
		transform[5] *= s + transform[5] * c;
		transform[12] *= c - transform[13] * s;
		transform[13] *= s + transform[13] * c;
	}

	transform[12] -= origin.x;
	transform[13] -= origin.y;

	return transform;
	*/
}


Matrix Matrix::CreateTranslation( const Vector3& position )
{
	return Matrix
	(
		1.0f,	0.0f,	0.0f,	0.0f,
		0.0f,	1.0f,	0.0f,	0.0f,
		0.0f,	0.0f,	1.0f,	0.0f,
		position.x,	position.y,	position.z,	1.0f
	);
}


Matrix Matrix::CreateScale( const Vector3& scale )
{
	return Matrix
	(
		scale.x, 0.0f,	  0.0f,	   0.0f,
		0.0f,	 scale.y, 0.0f,	   0.0f,
		0.0f,	 0.0f,	  scale.z, 0.0f,
		0.0f,	 0.0f,	  0.0f,	   1.0f
	);
}


Matrix Matrix::CreateRotationX( float radians )
{
	Vector2 v = Math::SinCosf(radians);

	return Matrix
	(
		1.0f,	0.0f,	0.0f,	0.0f,
		0.0f,	v.x,	v.y,	0.0f,
		0.0f,	-v.y,	v.x,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f
	);
}


Matrix Matrix::CreateRotationY( float radians )
{
	Vector2 v = Math::SinCosf(radians);

	return Matrix
	(
		v.x,	0.0f,	-v.y,	0.0f,
		0.0f,	1.0f,	0.0f,	0.0f,
		v.y,	0.0f,	v.x,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f
	);
}


Matrix Matrix::CreateRotationZ( float radians )
{
	Vector2 v = Math::SinCosf(radians);

	return Matrix
	(
		v.x,	v.y,	0.0f,	0.0f,
		-v.y,	v.x,	0.0f,	0.0f,
		0.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f
	);
}




CE_NAMESPACE_END


