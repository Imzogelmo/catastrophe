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
#include "Vector3.h"
#include "../Math/Math.h"
//#include "Vector4.h"
//#include "Quaternion.h"

CE_NAMESPACE_BEGIN



class Matrix
{
public:
	float m[16];

	Matrix()
	{
		*this = Identity;
	}

	Matrix( const float matrix[] )
	{
		for( int i(0); i < 16; ++i )
			m[ i ] = matrix[ i ];
	}

	Matrix(	float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, 
			float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15 )
	{
		m[ 0] = m0;  m[ 1] = m1;  m[ 2] = m2;  m[ 3] = m3;  
		m[ 4] = m4;  m[ 5] = m5;  m[ 6] = m6;  m[ 7] = m7;  
		m[ 8] = m8;  m[ 9] = m9;  m[10] = m10; m[11] = m11;  
		m[12] = m12; m[13] = m13; m[14] = m14; m[15] = m15;
	}

	float		&operator [] ( int i ) { return *( m + i ); }
	const float &operator [] ( int i ) const { return *( m + i ); }
	float		&operator () ( int i ) { return m[ i ]; }
	const float &operator () ( int i ) const { return m[ i ]; }
	float		&operator () ( int y, int x ) { return m[ (y * 4) + x ]; }
	const float &operator () ( int y, int x ) const { return m[ (y * 4) + x ]; }

	float &At( int i ) { return m[ i ]; }
	float &At( int y, int x ) { return m[ (y * 4) + x ]; }

	Matrix operator * ( const Matrix &m ) const { return Multiply( *this, m ); }
	Matrix operator / ( const Matrix &m ) const { return Divide( *this, m ); }
	Matrix operator + ( const Matrix &m ) const { return Add( *this, m ); }
	Matrix operator - ( const Matrix &m ) const { return Subtract( *this, m ); }
	Matrix operator * ( float val )	const { return Multiply( *this, val ); }
	Matrix operator / ( float val )	const { return Divide( *this, val ); }
	Vector3 operator * ( const Vector3& v ) const { return Multiply( *this, v ); }

	Matrix &operator *=( const Matrix& m );

	Matrix &operator = ( const Matrix& mat )
	{
		if( this == &mat )
			return *this;

		for( int i(0); i < 16; ++i )
			m[ i ] = mat.m[ i ];

		return *this;
	}

	bool operator == ( const Matrix& other ) const;
	bool operator != ( const Matrix& other ) const
	{
		return !(*this == other);
	}

	Vector3 Up() const { return Vector3( m[4], m[5], m[6] ); }
	Vector3 Down() const { return Vector3( -m[4], -m[5], -m[6] ); }
	Vector3 Left() const { return Vector3( -m[0], -m[1], -m[2] ); }
	Vector3 Right()	const { return Vector3( m[0], m[1], m[2] );	}
	Vector3 Forward() const { return Vector3( -m[8], -m[9], -m[10] ); }
	Vector3 Backward() const { return Vector3( m[8], m[9], m[10] );	}
	Vector3 Translation() const { return Vector3( m[12], m[13], m[14] ); }

	static Matrix Negate( const Matrix& mat );
	static Matrix Add( const Matrix& m1, const Matrix& m2 );
	static Matrix Subtract( const Matrix& m1, const Matrix& m2 );
	static Matrix Multiply( const Matrix& m1, const Matrix& m2 );
	static Matrix Multiply( const Matrix& m1, float factor );
	static Vector3 Multiply( const Matrix& mat, const Vector3& v );

	static Matrix Divide( const Matrix& m1, const Matrix& m2 );
	static Matrix Divide( const Matrix& m1, float factor );
	static Matrix Lerp( const Matrix& m1, const Matrix& m2, float t );
	static Matrix Transpose( const Matrix& m );

	static Matrix CreateLookAt( const Vector3& camera, const Vector3& target, const Vector3& up );
	static Matrix CreateOrthographic( float left, float right, float bottom, float top, float zNear = -1.f, float zFar = 1.f );
	static Matrix CreatePerspective( float fov, float aspect, float up, float zNear, float zFar );
	static Matrix CreateRotation( const Vector3& rotation );
	static Matrix CreateTransformation( const Vector3& pos, float rotation, const Vector3& scale, const Vector3& origin );
	static Matrix Create2DTransformation( const Vector2& pos, float rotation, const Vector2& scale, const Vector2& origin );

	Matrix Negate() const
	{
		return Negate( *this );
	}

	float* Data() { return &m[0]; }
	const float* Data() const { return &m[0]; }

	static const Matrix Zero;
	static const Matrix Identity;

	static Matrix CreateTranslation( const Vector3& pos )
	{
		return Matrix
		(
			1.0f,	0.0f,	0.0f,	0.0f,
			0.0f,	1.0f,	0.0f,	0.0f,
			0.0f,	0.0f,	1.0f,	0.0f,
			pos.x,	pos.y,	pos.z,	1.0f
		);
	}

	static Matrix CreateScale( const Vector3& scale )
	{
		return Matrix
		(
			scale.x, 0.0f,	  0.0f,	   0.0f,
			0.0f,	 scale.y, 0.0f,	   0.0f,
			0.0f,	 0.0f,	  scale.z, 0.0f,
			0.0f,	 0.0f,	  0.0f,	   1.0f
		);
	}

	static Matrix CreateRotationX( float radians )
	{
		Vector2 v( cosf(radians), sinf(radians) );

		return Matrix
		(
			1.0f,	0.0f,	0.0f,	0.0f,
			0.0f,	v.x,	-v.y,	0.0f,
			0.0f,	v.y,	v.x,	0.0f,
			0.0f,	0.0f,	0.0f,	1.0f
		);
	}

	static Matrix CreateRotationY( float radians )
	{
		Vector2 v( cosf(radians), sinf(radians) );

		return Matrix
		(
			v.x,	0.0f,	v.y,	0.0f,
			0.0f,	1.0f,	0.0f,	0.0f,
			-v.y,	0.0f,	v.x,	0.0f,
			0.0f,	0.0f,	0.0f,	1.0f
		);
	}

	static Matrix CreateRotationZ( float radians )
	{
		Vector2 v = Math::SinCos(radians);

		return Matrix
		(
			v.x,	v.y,	0.0f,	0.0f,
			-v.y,	v.x,	0.0f,	0.0f,
			0.0f,	0.0f,	1.0f,	0.0f,
			0.0f,	0.0f,	0.0f,	1.0f
		);
	}


};


CE_NAMESPACE_END




