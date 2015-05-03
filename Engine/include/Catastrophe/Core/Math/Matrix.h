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
#include "Catastrophe/Core/Math/Vector3.h"

CE_NAMESPACE_BEGIN



class CE_API Matrix
{
public:
	float m[16];

	Matrix();
	Matrix( const float* ptr );
	Matrix(	float m0, float m1, float m2, float m3,
			float m4, float m5, float m6, float m7, 
			float m8, float m9, float m10, float m11,
			float m12, float m13, float m14, float m15 );

	float		&operator [] ( int i ) { return *( m + i ); }
	const float &operator [] ( int i ) const { return *( m + i ); }
	float		&operator () ( int y, int x ) { return m[ (y * 4) + x ]; }
	const float &operator () ( int y, int x ) const { return m[ (y * 4) + x ]; }

	Matrix operator + ( const Matrix &rhs ) const;
	Matrix operator - ( const Matrix &rhs ) const;
	Matrix operator * ( const Matrix &rhs ) const;
	Matrix operator * ( float scalar )	const;
	Matrix operator / ( float scalar )	const;
	Vector3 operator * ( const Vector3& v ) const;

	Matrix &operator +=( const Matrix& rhs );
	Matrix &operator -=( const Matrix& rhs );
	Matrix &operator *=( const Matrix& rhs );
	Matrix &operator *=( float scalar );
	Matrix &operator /=( float scalar );

	bool operator == ( const Matrix& rhs ) const;
	bool operator != ( const Matrix& rhs ) const;

	float Determinant() const;
	Matrix Transpose() const;
	Matrix Inverse() const;

	Vector3 GetTranslation() const;
	Vector3 GetScale() const;

	Matrix& Translate( const Vector3& translation );
	Matrix& Scale( const Vector3& scale );

	Matrix& SetFromAxes( const Vector3 &x, const Vector3 &y, const Vector3 &z );
	Matrix& SetFromAxisAngle( const Vector3 &axis, float angle );


	float* Data() { return &m[0]; }
	const float* Data() const { return &m[0]; }

	Vector3 Up() const { return Vector3( m[4], m[5], m[6] ); }
	Vector3 Down() const { return Vector3( -m[4], -m[5], -m[6] ); }
	Vector3 Left() const { return Vector3( -m[0], -m[1], -m[2] ); }
	Vector3 Right()	const { return Vector3( m[0], m[1], m[2] );	}
	Vector3 Forward() const { return Vector3( -m[8], -m[9], -m[10] ); }
	Vector3 Backward() const { return Vector3( m[8], m[9], m[10] );	}
	Vector3 Translation() const { return Vector3( m[12], m[13], m[14] ); }

	static Matrix Lerp( const Matrix& a, const Matrix& b, float t );
	static Matrix Multiply( const Matrix& a, const Matrix& b );
	static Matrix Multiply( const float* a, const float* b );

	static Matrix CreateLookAt( const Vector3& camera, const Vector3& target, const Vector3& up );
	static Matrix CreateOrthographic( float left, float right, float bottom, float top, float zNear = -1.f, float zFar = 1.f );
	static Matrix CreatePerspective( float fov, float aspect, float up, float zNear, float zFar );

	static Matrix CreateFromAxes( const Vector3 &x, const Vector3 &y, const Vector3 &z );
	static Matrix CreateFromAxisAngle( const Vector3 &axis, float angle );
	static Matrix CreateRotation( const Vector3& rotation );
	static Matrix CreateFromQuaternion( const Quaternion& q );
	static Matrix CreateTransformation( const Vector3& position, float rotation, const Vector3& scale, const Vector3& origin );
	static Matrix Create2DTransformation( const Vector2& position, float rotation, const Vector2& scale, const Vector2& origin );

	static Matrix CreateTranslation( const Vector3& position );
	static Matrix CreateScale( const Vector3& scale );
	static Matrix CreateRotationX( float radians );
	static Matrix CreateRotationY( float radians );
	static Matrix CreateRotationZ( float radians );

	static const Matrix Zero;
	static const Matrix Identity;

};



inline Matrix::Matrix()
{
	*this = Identity;
}


inline Matrix::Matrix( const float* ptr )
{
	m[0] = ptr[0]; m[1] = ptr[1]; m[2] = ptr[2]; m[3] = ptr[3];
	m[4] = ptr[4]; m[5] = ptr[5]; m[6] = ptr[6]; m[7] = ptr[7];
	m[8] = ptr[8]; m[9] = ptr[9]; m[10] = ptr[10]; m[11] = ptr[11];
	m[12] = ptr[12]; m[13] = ptr[13]; m[14] = ptr[14]; m[15] = ptr[15];
}


inline Matrix::Matrix(	float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, 
		float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15 )
{
	m[ 0] = m0;  m[ 1] = m1;  m[ 2] = m2;  m[ 3] = m3;  
	m[ 4] = m4;  m[ 5] = m5;  m[ 6] = m6;  m[ 7] = m7;  
	m[ 8] = m8;  m[ 9] = m9;  m[10] = m10; m[11] = m11;  
	m[12] = m12; m[13] = m13; m[14] = m14; m[15] = m15;
}



CE_NAMESPACE_END




