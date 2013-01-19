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

#include "../Common.h"


#define CE_EPSILON		0.000001f
#define CE_PI			3.14159265f
#define CE_TWOPI		6.28318530f
#define CE_TO_RADIANS	(CE_PI/180.0f)
#define CE_TO_DEGREES	(180.0f/CE_PI)


CE_NAMESPACE_BEGIN


enum FlipFlags
{
	None			= 0,
	FlipHorizontal	= 1,
	FlipVertical	= 2,
	Rotate90		= 4,
	Rotate180		= 8,
	Rotate270		= 16
};


namespace Math
{
	// Math Constants
	const float TwoPi		= 6.28318530f;
	const float Pi			= 3.14159265f;
	const float HalfPi		= 1.57079632f;
	const float QuarterPi	= 0.78539816f;
	const float Epsilon		= 0.000001f;

	inline float ToDegrees( float radians ) { return (radians * 57.295780f ); }
	inline float ToRadians( float degrees ) { return (degrees * 0.0174533f); }

	template <class T> inline 
	T Abs( T x )
	{
		return x < T(0) ? -x : x;
	}

	template <class T> inline T Min( T a, T b ) { return (a < b ? a : b); }
	template <class T> inline T Max( T a, T b ) { return (a > b ? a : b); }
	template <class T> inline T Min( T a, T b, T c ) { return Min( a, Min( b, c ) ); }
	template <class T> inline T Max( T a, T b, T c ) { return Max( a, Max( b, c ) ); }
	template <class T> inline T Min( T a, T b, T c, T d ) { return Min( a, Min( b, Min( c, d ) ) ); }
	template <class T> inline T Max( T a, T b, T c, T d ) { return Max( a, Max( b, Max( c, d ) ) ); }
	
	inline float Round( float x )
	{
		if(x < 0.f) return float(int(x - 0.5f));
		return float(int(x + 0.5f));
 	}

	template <class T> inline
	void Swap( T& first, T& second )
	{
		T tmp = first;
		first = second;
		second = tmp;
	}

	template <class T> inline
	T Clamp( T x, T min, T max )
	{
		if(x < min) return min;
		else if(x > max) return max;
		return x;
	}

	template <class T> inline
	void FastClamp( T& x, T min, T max )
	{
		if( x < min ) x = min;
		else if( x > max ) x = max;
	}

	template <class T> inline
	T Wrap( T x, T minVal, T maxVal, T amount )
	{
		if( x < minVal ) x += amount;
		else if( x > maxVal ) x -= amount;
		return x;
	}

	//Wraps radian value towards -PI and PI.
	inline float WrapAngle( float radians )
	{
		return Wrap(radians, -Pi, Pi, TwoPi);
	}

	//Wraps degree value towards 0 and 360.
	inline float WrapDegrees( float degrees )
	{
		return Wrap(degrees, 0.f, 360.f, 360.f);
	}

	inline bool IsNaN( float x )
	{
		return x != x;
	}

	inline bool EpsilonCompare( float x, float y, float epsilon = Epsilon )
	{
		return (Abs(x - y) < epsilon);
	}

	inline bool IsPowerOfTwo( size_t x )
	{
		return !((x-1) & x);
	}

	inline size_t NextPowerOfTwo( size_t x )
	{
		size_t y(1);
		while( y < x ) y <<= 1;
		return y;
	}

}


CE_NAMESPACE_END
