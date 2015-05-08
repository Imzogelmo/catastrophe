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


const Vector4 Vector4::Zero		= Vector4( 0.0f, 0.0f, 0.0f, 0.0f );
const Vector4 Vector4::One		= Vector4( 1.0f, 1.0f, 1.0f, 1.0f );
const Vector4 Vector4::UnitX	= Vector4( 1.0f, 0.0f, 0.0f, 0.0f );
const Vector4 Vector4::UnitY	= Vector4( 0.0f, 1.0f, 0.0f, 0.0f );
const Vector4 Vector4::UnitZ	= Vector4( 0.0f, 0.0f, 1.0f, 0.0f );
const Vector4 Vector4::UnitW	= Vector4( 0.0f, 0.0f, 0.0f, 1.0f );


Vector4::Vector4( const Colorf &c )
	: x(c.r), y(c.g), z(c.b), w(c.a)
{
}


Vector4::Vector4( const Color &c )
{
	const float inv = 1.f / 255.f;
	x = c.r * inv;
	y = c.r * inv;
	z = c.r * inv;
	w = c.a * inv;
}


Vector2 Vector4::ToVector2() const
{
	return Vector2( x, y );
}


Vector3 Vector4::ToVector3() const
{
	return Vector3( x, y, z );
}


Colorf Vector4::ToColorf() const
{
	return Colorf( x, y, z, w );
}


Color Vector4::ToColor() const
{
	return Color( Colorf( x, y, z, w ) );
}


bool Vector4::Equals( const Vector4 &v, float epsilon ) const
{
	if( !Math::EpsilonCompare( x, v.x, epsilon ) ) return false;
	if( !Math::EpsilonCompare( y, v.y, epsilon ) ) return false;
	if( !Math::EpsilonCompare( z, v.z, epsilon ) ) return false;
	if( !Math::EpsilonCompare( w, v.w, epsilon ) ) return false;

	return true;
}


void Vector4::Clamp( const Vector4& min, const Vector4& max )
{
	Math::FastClamp(x, min.x, max.x);
	Math::FastClamp(y, min.y, max.y);
	Math::FastClamp(z, min.z, max.z);
	Math::FastClamp(w, min.w, max.w);
}


void Vector4::Normalize()
{
	const float lengthSquared = LengthSquared();
	if(lengthSquared != 0.f)
	{
		const float inv = 1.f / sqrtf(lengthSquared);
		x *= inv;
		y *= inv;
		z *= inv;
		w *= inv;
	}
}


Vector4 Vector4::Normalized() const
{
	const float lengthSquared = LengthSquared();
	if(lengthSquared != 0.f)
	{
		const float inv = 1.f / sqrtf(lengthSquared);
		return Vector4(x * inv, y * inv, z * inv, w * inv);
	}

	return *this;
}



CE_NAMESPACE_END


