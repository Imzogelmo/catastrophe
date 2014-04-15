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

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Quaternion.h"
#include "Math/Matrix.h"
#include "Math/Point.h"
#include "Math/Math.h"

CE_NAMESPACE_BEGIN


const Vector2 Vector2::Zero		= Vector2( 0.0f, 0.0f );
const Vector2 Vector2::UnitX	= Vector2( 1.0f, 0.0f );
const Vector2 Vector2::UnitY	= Vector2( 0.0f, 1.0f );
const Vector2 Vector2::One		= Vector2( 1.0f, 1.0f );



Vector2::Vector2( const Vector3 &v )
{
	x = v.x;
	y = v.y;
}


Vector2::Vector2( const Vector4 &v )
{
	x = v.x;
	y = v.y;
}


Vector2::Vector2( const Point &p )
{
	x = (float)p.x;
	y = (float)p.y;
}


Vector3 Vector2::ToVector3() const
{
	return Vector3( x, y, 0.0f );
}


bool Vector2::Equals( const Vector2 &v, float epsilon ) const
{
	return( Math::EpsilonCompare(x, v.x, epsilon) &&
			Math::EpsilonCompare(y, v.y, epsilon) );
}


Vector2 Vector2::Reflect( const Vector2& unit ) const
{ 
	return Vector2( unit * ( 2 * Dot( unit ) ) - *this );
}


Vector2 Vector2::Refract( const Vector2& unit, float eta ) const
{
	const float dot = Dot( unit );
	const float k = 1.0f - eta * eta * (1.0f - dot * dot);
	if ( k < 0 ) 
		return Vector2::Zero;

	return Vector2( ( *this * eta ) - ( unit * ( eta * dot + sqrt(k) ) ) );
}


Vector2 Vector2::Polar( const Vector2& distance, float theta ) const
{
	const Vector2 r = Math::SinCos(theta);
	return Vector2(
			x + distance.x * r.x,
			y + distance.y * r.y
		);
}


Vector2 Vector2::Rotated( float a ) const
{
	Vector2 value = *this;
	Math::RotatePoint( Math::SinCos(a), value );
	return value;
}


Vector2 Vector2::Rotated( float a, const Vector2& origin ) const
{
	Vector2 value = *this;
	Math::RotatePoint( Math::SinCos(a), origin, value );
	return value;
}


void Vector2::Rotate( float a )
{
	Math::RotatePoint( Math::SinCos(a), *this );
}


void Vector2::Rotate( float a, const Vector2& origin )
{
	Math::RotatePoint( Math::SinCos(a), origin, *this );
}


Vector2 Vector2::Transform( const Matrix& mat ) const
{
	return Vector2
		(
			(x * mat.m[0]) + (y * mat.m[4]) + mat.m[12],
			(x * mat.m[1]) + (y * mat.m[5]) + mat.m[13]
		);
}



CE_NAMESPACE_END

