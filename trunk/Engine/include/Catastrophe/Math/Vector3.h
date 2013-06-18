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
#include <cmath>

CE_NAMESPACE_BEGIN


class CE_API Vector3 
{
public:
	float x, y, z;

	Vector3() {}
	Vector3( float n ) : x(n), y(n), z(n) {}
	Vector3( float x, float y, float z ) : x(x), y(y), z(z) {}
	Vector3( const Vector2 &v, float z = 0.f ) : x(v.x), y(v.y), z(z) {}
	Vector3( const float* p ) : x(p[0]), y(p[1]), z(p[2]) {}
	Vector3( const Vector4 &v );
	Vector3( const Color &c );
	Vector3( const Colorf &c );

	Vector3 &operator = ( float n ) { x = n; y = n; z = n; return *this; }
	Vector3 &operator = ( const Vector2 &v ) { x = v.x; y = v.y; z = 0.0f; return *this; }

	const float &operator [] ( const int i ) const	{ return *( &x + i );	}
	float		&operator [] ( const int i )		{ return *( &x + i );	}
	Vector3 operator - () const { return Vector3( -x, -y, -z );		}

	Vector3 &operator ++ ()    { ++x;   ++y;   ++z;		return *this; }
	Vector3 &operator -- ()    { --x;   --y;   ++z;		return *this; }
	Vector3  operator ++ (int) { Vector3 tmp(*this); x++; y++; z++; return tmp; }
	Vector3  operator -- (int) { Vector3 tmp(*this); x--; y--; z--; return tmp; }

	Vector3 operator * ( const Vector3 &v )	const { return Vector3 ( x * v.x, y * v.y, z * v.z ); }
	Vector3 operator / ( const Vector3 &v )	const { return Vector3 ( x / v.x, y / v.y, z / v.z ); }
	Vector3 operator + ( const Vector3 &v )	const { return Vector3 ( x + v.x, y + v.y, z + v.z ); }
	Vector3 operator - ( const Vector3 &v ) const { return Vector3 ( x - v.x, y - v.y, z - v.z ); }
	Vector3 operator * ( float val )		const { return Vector3 ( x * val, y * val, z * val ); }
	Vector3 operator / ( float val )		const { return Vector3 ( x / val, y / val, z / val ); }
	Vector3 operator + ( float val )	    const { return Vector3 ( x + val, y + val, z + val ); }
	Vector3 operator - ( float val )	    const { return Vector3 ( x - val, y - val, z - val ); }

	inline friend Vector3 operator * ( const float val,  const Vector3 &v ) { return Vector3 ( val * v.x, val * v.y, val * v.z ); }
	inline friend Vector3 operator / ( const float val,  const Vector3 &v ) { return Vector3 ( val / v.x, val / v.y, val / v.z ); }
	inline friend Vector3 operator + ( const float val,  const Vector3 &v ) { return Vector3 ( val + v.x, val + v.y, val + v.z ); }
	inline friend Vector3 operator - ( const float val,  const Vector3 &v ) { return Vector3 ( val - v.x, val - v.y, val - v.z ); }

	Vector3 &operator *= ( const Vector3 &v ) { x *= v.x; y *= v.y; z *= v.z; return *this; }
	Vector3 &operator /= ( const Vector3 &v ) { x /= v.x; y /= v.y; z /= v.z; return *this; }
	Vector3 &operator += ( const Vector3 &v ) { x += v.x; y += v.y; z += v.z; return *this; }
	Vector3 &operator -= ( const Vector3 &v ) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	Vector3 &operator *= ( float val )		  { x *= val; y *= val; z *= val; return *this; }
	Vector3 &operator /= ( float val )        { x /= val; y /= val; z /= val; return *this; }
	Vector3 &operator += ( float val )		  { x += val; y += val; z += val; return *this; }
	Vector3 &operator -= ( float val )		  { x -= val; y -= val; z -= val; return *this; }

	bool operator == ( const Vector3 &v ) const { return Equals( v ); }
	bool operator != ( const Vector3 &v ) const { return !Equals( v ); }

	bool Equals( const Vector3 &v, float epsilon = 0.000001f ) const;
	bool IsZero() const { return ( *this == 0.0f ); }

	static const Vector3 Zero;
	static const Vector3 One;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 Up;
	static const Vector3 Down;
	static const Vector3 Left;
	static const Vector3 Right;
	static const Vector3 Forward;
	static const Vector3 Backward;

	float Dot( const Vector3 &v ) const		{ return x * v.x + y * v.y + z * v.z;		}
	float LengthSquared() const				{ return x * x + y * y + z * z;				}
	float Length() const					{ return sqrtf( x * x + y * y + z * z );	}
	float DistanceSquared( const Vector3 &v ) const	{ return ( *this - v ).LengthSquared(); }
	float Distance		 ( const Vector3 &v ) const	{ return ( *this - v ).Length();		}

	Vector2 ToVector2() const;
	Vector4 ToVector4() const;
	Colorf ToColorf( float alpha = 1.0f ) const;
	Color ToColor( float alpha = 1.0f ) const;

	float Min() const { return Math::Min(x, y, z); }
	float Max() const { return Math::Max(x, y, z); }
	Vector3 Abs ()   const { return Vector3( fabsf(x),  fabsf(y),  fabsf(z)  ); }
	Vector3 Ceil()   const { return Vector3( ceilf(x),  ceilf(y),  ceilf(z)  ); }
	Vector3 Floor()  const { return Vector3( floorf(x), floorf(y), floorf(z) ); }
	Vector3 Round()	 const { return Vector3( Math::Round(x), Math::Round(y), Math::Round(z) );	}
	Vector3 Negate() const { return Vector3( -x, -y, -z ); }

	Vector3 Normal() const
	{
		const float length = Length();
		if( length == 0.f )
			return Vector3::Zero;

		const float inv = 1.f / length;
		return Vector3(
				x * inv,
				y * inv,
				z * inv
			);
	}

	Vector3& Normalize()
	{
		const float length = Length();
		if( length != 0.f )
		{
			const float inv = 1.f / length;
			x *= inv;
			y *= inv;
			z *= inv;
		}
		return *this;
	}

	Vector3 Cross( const Vector3 &v ) const
	{
		return Cross( *this, v );
	}

	Vector3 Reflect( const Vector3& unit ) const;
	Vector3 Refract( const Vector3& unit, float const eta ) const;

	Vector3& Set( float x_, float y_, float z_ ) { x = x_; y = y_; z = z_; return *this; }
	Vector3& Clamp( const Vector3& min, const Vector3& max )
	{
		Math::FastClamp(x, min.x, max.x);
		Math::FastClamp(y, min.y, max.y);
		Math::FastClamp(z, min.z, max.z);
		return *this;
	}

	Vector3& Lerp( const Vector3& p2, float t)
	{
		x += (p2.x - x) * t;
		y += (p2.y - y) * t;
		z += (p2.z - z) * t;
		return *this;
	}

	Vector3 Transform( const Matrix& mat );

	static float Dot( const Vector3 &u, const Vector3 &v )
	{
		return u.x * v.x + u.y * v.y + u.z * v.z;
	}

	static Vector3 Cross ( const Vector3 &u, const Vector3 &v )
	{
		return Vector3(
			u.y * v.z - u.z * v.y,
			u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x
		);
	}

};



CE_NAMESPACE_END



