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

#include "Math/Matrix.h"

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


bool Matrix::operator == ( const Matrix& other ) const
{
	for( int i(0); i < 16; ++i )
		if( !Math::EpsilonCompare( m[ i ], other.m[ i ] ) )
			return false;
	return true;
}

Matrix Matrix::Negate( const Matrix& mat )
{
	Matrix ret;

	for( int i(0); i < 16; ++i )
		ret.m[i] = -mat.m[i];

	return ret;
}


Matrix Matrix::Add( const Matrix& m1, const Matrix& m2 )
{
	Matrix m;

	for( int i(0); i < 16; ++i ) 
		m.m[ i ] = m1.m[ i ] + m2.m[ i ];

	return m;
}


Matrix Matrix::Subtract( const Matrix& m1, const Matrix& m2 )
{
	Matrix m;

	for( int i(0); i < 16; ++i ) 
		m.m[ i ] = m1.m[ i ] - m2.m[ i ];

	return m;
}


Matrix Matrix::Multiply( const Matrix& m1, const Matrix& m2 )
{
	return Matrix
	(
		m1[0] * m2[0]	+ m1[4] * m2[1]	+ m1[8]  * m2[2]	+ m1[12] * m2[3],
		m1[1] * m2[0]	+ m1[5] * m2[1]	+ m1[9]  * m2[2]	+ m1[13] * m2[3],
		m1[2] * m2[0]	+ m1[6] * m2[1]	+ m1[10] * m2[2]	+ m1[14] * m2[3],
		m1[3] * m2[0]	+ m1[7] * m2[1]	+ m1[11] * m2[2]	+ m1[15] * m2[3],
		m1[0] * m2[4]	+ m1[4] * m2[5]	+ m1[8]  * m2[6]	+ m1[12] * m2[7],
		m1[1] * m2[4]	+ m1[5] * m2[5]	+ m1[9]  * m2[6]	+ m1[13] * m2[7],
		m1[2] * m2[4]	+ m1[6] * m2[5]	+ m1[10] * m2[6]	+ m1[14] * m2[7],
		m1[3] * m2[4]	+ m1[7] * m2[5]	+ m1[11] * m2[6]	+ m1[15] * m2[7],
		m1[0] * m2[8]	+ m1[4] * m2[9]	+ m1[8]  * m2[10]	+ m1[12] * m2[11],
		m1[1] * m2[8]	+ m1[5] * m2[9]	+ m1[9]  * m2[10]	+ m1[13] * m2[11],
		m1[2] * m2[8]	+ m1[6] * m2[9]	+ m1[10] * m2[10]	+ m1[14] * m2[11],
		m1[3] * m2[8]	+ m1[7] * m2[9]	+ m1[11] * m2[10]	+ m1[15] * m2[11],
		m1[0] * m2[12]	+ m1[4] * m2[13]+ m1[8]  * m2[14]	+ m1[12] * m2[15],
		m1[1] * m2[12]	+ m1[5] * m2[13]+ m1[9]  * m2[14]	+ m1[13] * m2[15],
		m1[2] * m2[12]	+ m1[6] * m2[13]+ m1[10] * m2[14]	+ m1[14] * m2[15],
		m1[3] * m2[12]	+ m1[7] * m2[13]+ m1[11] * m2[14]	+ m1[15] * m2[15]
	);
}


Matrix &Matrix::operator *=( const Matrix& m )
{
	*this = Matrix::Multiply( *this, m );
	return *this;
}


Matrix Matrix::Multiply( const Matrix& m1, float factor )
{
	Matrix m;

	for( int i(0); i < 16; ++i ) 
		m.m[ i ] = m1.m[ i ] * factor;

	return m;
}


Vector3 Matrix::Multiply( const Matrix& mat, const Vector3& v )
{
	const float* m = &mat.m[0];
	float inv = 1.0f / (m[12] * v.x + m[13] * v.y + m[14] * v.z + m[15]);

	return Vector3(
		(m[0] * v.x + m[1] * v.y + m[2] * v.z + m[3]) * inv,
		(m[4] * v.x + m[5] * v.y + m[6] * v.z + m[7]) * inv,
		(m[8] * v.x + m[9] * v.y + m[10] * v.z + m[11]) * inv
	);
}

/*
	Vector3 operator * ( const Vector3& v ) const
	{
		float inv = 1.0f / (m[12] * v.x + m[13] * v.y + m[14] * v.z + m[15]);

		return Vector3(
			(m[0] * v.x + m[1] * v.y + m[2] * v.z + m[3]) * inv,
			(m[4] * v.x + m[5] * v.y + m[6] * v.z + m[7]) * inv,
			(m[8] * v.x + m[9] * v.y + m[10] * v.z + m[11]) * inv
		);
	}
*/

Matrix Matrix::Divide( const Matrix& m1, const Matrix& m2 )
{
	Matrix m;

	for( int i(0); i < 16; ++i ) 
		m.m[ i ] = m1.m[ i ] / m2.m[ i ];

	return m;
}


Matrix Matrix::Divide( const Matrix& m1, float factor )
{
	Matrix m;

	for( int i(0); i < 16; ++i ) 
		m.m[ i ] = m1.m[ i ] / factor;

	return m;
}


Matrix Matrix::Lerp( const Matrix& m1, const Matrix& m2, float t )
{
	Matrix m;

	for( int i(0); i < 16; ++i )
		m[ i ] = m1[ i ] + ((m2[ i ] - m1[ i ]) * t);

	return m;
}


Matrix Matrix::Transpose( const Matrix& m )
{
	return Matrix
		(
			m[0], m[4], m[8],  m[12],
			m[1], m[5], m[9],  m[13],
			m[2], m[6], m[10], m[14],
			m[3], m[7], m[11], m[15]
		);
}


Matrix Matrix::CreateLookAt( const Vector3& camera, const Vector3& target, const Vector3& up )
{
	//TODO this is not entirely correct. use gluLookAt instead...

	const Vector3 v1 = ( camera - target ).Normal();
	//const Vector3 v1 = ( target - camera ).Normal();
	const Vector3 v2 = Vector3::Cross( up, v1 ).Normal();
	const Vector3 v3 = Vector3::Cross( v1, v2 );
	const float dot1 = -Vector3::Dot( v2, camera );
	const float dot2 = -Vector3::Dot( v3, camera );
	const float dot3 = -Vector3::Dot( v1, camera );

	return Matrix
		(
			v2.x, v3.x, v1.x, 0.0f,
			v2.y, v3.y, v1.y, 0.0f,
			v2.z, v3.z, v1.z, 0.0f,
			dot1, dot2, dot3, 1.0f
		);
}


Matrix Matrix::CreatePerspective( float fov, float aspect, float up, float zNear, float zFar )
{
	const float e = tanf(CE_TO_RADIANS * (fov / 2.f)) * zNear;	
	const float left = -e * aspect;
	const float right = e * aspect;
	const float top = e;
	const float bottom = -e;

	//flip the up vector
	float h = (2.f * zNear) / (top - bottom);
	if( up <= 0.f )
		h = -h;

	const float w = (2.f * zNear) / (right - left);
	const float q = -(zFar + zNear) / (zFar - zNear);
	const float z = -(2.f * zFar * zNear) / (zFar - zNear);

	return Matrix
		(
			w,		0.0f,	0.0f,   0.0f,  
			0.0f,	h,		0.0f,   0.0f,  
			0.0f,	0.0f,	q,		-1.0f,  
			0.0f,	0.0f,   z,		0.0f
		);
}


Matrix Matrix::CreateOrthographic( float left, float right, float bottom, float top, float zNear, float zFar )
{
	Matrix matrix;
	matrix[ 0] = 2.f / (right - left);
	matrix[ 5] = 2.f / (top - bottom);
	matrix[10] = -2.f / (zFar - zNear);
	matrix[12] = -((right + left) / (right - left));
	matrix[13] = -((top + bottom) / (top - bottom));
	matrix[14] = -((zFar + zNear) / (zFar - zNear));
	return matrix;
}


Matrix Matrix::CreateRotation( const Vector3& rotation )
{
	Matrix matrix;

	const Vector2 a( cosf(rotation.x), sinf(rotation.x) );
	const Vector2 b( cosf(rotation.y), sinf(rotation.y) );
	const Vector2 c( cosf(rotation.z), sinf(rotation.z) );

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


Matrix Matrix::CreateTransformation( const Vector3& pos, float rotation, const Vector3& scale, const Vector3& origin )
{
	//fixme: optimize.
	const Vector3 t = pos + origin;
	return Matrix(
		scale.x,	0.0f,		0.0f,		0.0f,
		0.0f,		scale.y,	0.0f,		0.0f,
		0.0f,		0.0f,		scale.z,	0.0f,
		t.x,		t.y,		t.z,		1.0f
	) *
	CreateRotationZ(rotation) *
	CreateTranslation(-origin);
}

Matrix Matrix::Create2DTransformation( const Vector2& pos, float rotation, const Vector2& scale, const Vector2& origin )
{
	//fixme: this is wrong..
	const Vector2 t = pos + origin;
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
}


CE_NAMESPACE_END


