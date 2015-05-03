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

#include "Catastrophe/Core/Math/Vector2.h"
#include "Catastrophe/Core/Math/Vector3.h"
#include "Catastrophe/Core/Math/Vector4.h"
#include "Catastrophe/Core/Math/Quaternion.h"
#include "Catastrophe/Core/Math/Matrix.h"
#include "Catastrophe/Core/Math/Color.h"
#include "Catastrophe/Core/Math/Colorf.h"

CE_NAMESPACE_BEGIN


const Vector3 Vector3::Zero		= Vector3( 0.0f, 0.0f, 0.0f );
const Vector3 Vector3::One		= Vector3( 1.0f, 1.0f, 1.0f );
const Vector3 Vector3::UnitX	= Vector3( 1.0f, 0.0f, 0.0f );
const Vector3 Vector3::UnitY	= Vector3( 0.0f, 1.0f, 0.0f );
const Vector3 Vector3::UnitZ	= Vector3( 0.0f, 0.0f, 1.0f );
const Vector3 Vector3::Up		= Vector3( 0.0f, 1.0f, 0.0f );
const Vector3 Vector3::Down		= Vector3( 0.0f, -1.0f, 0.0f );
const Vector3 Vector3::Left		= Vector3( -1.0f, 0.0f, 0.0f );
const Vector3 Vector3::Right	= Vector3( 1.0f, 0.0f, 0.0f );
const Vector3 Vector3::Forward	= Vector3( 0.0f, 0.0f, -1.0f );
const Vector3 Vector3::Backward	= Vector3( 0.0f, 0.0f, 1.0f );



Vector3::Vector3( const Vector4 &v )
	: x(v.x), y(v.y), z(v.z)
{
}


Vector3::Vector3( const Colorf &c )
	: x(c.r), y(c.g), z(c.b)
{
}


Vector3::Vector3( const Color &c )
{
	const float inv = 1.f / 255.f;
	x = c.r * inv;
	y = c.r * inv;
	z = c.r * inv;
}


Vector2 Vector3::ToVector2() const
{
	return Vector2( x, y );
}


Vector4 Vector3::ToVector4() const
{
	return Vector4( x, y, z, 1.0f );
}


Colorf Vector3::ToColorf( float alpha ) const
{
	return Colorf( x, y, z, alpha );
}


Color Vector3::ToColor( float alpha ) const
{
	return Color( Colorf( x, y, z, alpha ) );
}


bool Vector3::Equals( const Vector3 &v, float epsilon ) const
{
	if( !Math::EpsilonCompare( x, v.x, epsilon ) ) return false;
	if( !Math::EpsilonCompare( y, v.y, epsilon ) ) return false;
	if( !Math::EpsilonCompare( z, v.z, epsilon ) ) return false;

	return true;
}


Vector3 Vector3::Reflect( const Vector3& unit ) const
{
	return Vector3( unit * ( 2 * Dot( unit ) ) - *this );
}


Vector3 Vector3::Refract( const Vector3& unit, float const eta ) const
{
	const float dot = Dot( unit );
	const float k = 1.0f - eta * eta * (1.0f - dot * dot);
	if ( k < 0 )
		return Vector3::Zero;
	return Vector3( ( *this * eta ) - ( unit * ( eta * dot + sqrt(k) ) ) );
}


Vector3 Vector3::Transform( const Matrix& mat )
{
	return Vector3
		(
			(x * mat.m[0]) + (y * mat.m[4]) + (z * mat.m[ 8]) + mat.m[12],
			(x * mat.m[1]) + (y * mat.m[5]) + (z * mat.m[ 9]) + mat.m[13],
			(x * mat.m[2]) + (y * mat.m[6]) + (z * mat.m[10]) + mat.m[14]
		);
}



CE_NAMESPACE_END





