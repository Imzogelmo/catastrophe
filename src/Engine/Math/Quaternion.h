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

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include <cmath>

CE_NAMESPACE_BEGIN


class CE_API Quaternion
{
public:
	float x, y, z, w;

	Quaternion()										: x(0.0f), y(0.0f), z(0.0f), w(1.0f)	{}
	Quaternion( float x, float y, float z, float w )	: x(x), y(y), z(z), w(w)				{}
	Quaternion( const Vector3 &q, float scalar )		{ x = q.x; y = q.y; z = q.z; w = scalar;	}
	Quaternion( const Vector4 &q )						{ x = q.x; y = q.y; z = q.z; w = q.w;		}

	Quaternion &operator = ( const Quaternion &q )	{ x = q.x; y = q.y; z = q.z; w = q.w;  return *this; }
	Quaternion &operator = ( const Vector4 &q )		{ x = q.x; y = q.y; z = q.z; w = q.w;	return *this; }

	Quaternion operator - () const { return Quaternion( -x, -y, -z, w ); }
	//Quaternion operator + () const { return Quaternion( +x, +y, +z, +w ); }
	
	Quaternion operator + ( const Quaternion &q ) const { return Quaternion ( x + q.x, y + q.y, z + q.z, w + q.w ); }
	Quaternion operator - ( const Quaternion &q ) const { return Quaternion ( x - q.x, y - q.y, z - q.z, w - q.w ); }
	Quaternion operator * ( const Quaternion &q ) const;
	Quaternion operator / ( const Quaternion &q ) const
	{
	  return Quaternion( *this * Quaternion( q ).Inverse() );
	}

	Quaternion Scale( float scale ) const
	{
		return Quaternion( x * scale, y * scale, z * scale, w * scale ); 
	}

	Quaternion Inverse() const
	{
	  return Quaternion( Conjugate() ).Scale( 1.0f / LengthSquared() );
	}

	Quaternion Conjugate() const
	{
		return Quaternion( -x, -y, -z, w );
	}

	static Quaternion Concatenate( const Quaternion &q1, const Quaternion &q2 );

	static Quaternion Add		( const Quaternion &q1, const Quaternion &q2 )  { return q1 + q2; }
	static Quaternion Subtract	( const Quaternion &q1, const Quaternion &q2 )  { return q1 - q2; }
	static Quaternion Multiply	( const Quaternion &q1, const Quaternion &q2 )  { return q1 * q2; }
	static Quaternion Divide	( const Quaternion &q1, const Quaternion &q2 )  { return q1 / q2; }

	float Length() const		{ return Vector4(x, y, z, w).Length(); }
	float LengthSquared() const	{ return Vector4(x, y, z, w).LengthSquared(); }
	Quaternion& Normalize()		{ Vector4(x, y, z, w).Normalize(); return *this;}
	Quaternion Normal()			{ return Vector4(x, y, z, w).Normal(); }

	Quaternion CreateFromYawPitchRoll( const Vector3& rot );
	static Quaternion CreateFromRotationMatrix( const Matrix& matrix );

};


CE_NAMESPACE_END







