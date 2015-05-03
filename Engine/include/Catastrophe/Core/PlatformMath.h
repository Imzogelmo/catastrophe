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
#include <math.h>


#define CE_EPSILON		0.000001f
#define CE_PI			3.141592653589f
#define CE_TWOPI		6.28318530f
#define CE_TO_RADIANS	(CE_PI/180.0f)
#define CE_TO_DEGREES	(180.0f/CE_PI)
#define PI				3.141592653589f
#define PI_OVER_2		1.570796326794f

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

	template <class T> inline
	void Swap(T& first, T& second)
	{
		T tmp = first;
		first = second;
		second = tmp;
	}

	template <class T> inline
	T Clamp(T x, T min, T max)
	{
		if(x < min) return min;
		else if(x > max) return max;
		return x;
	}

	template <class T> inline
	void FastClamp(T& x, T min, T max)
	{
		if(x < min) x = min;
		else if(x > max) x = max;
	}

	template <class T> inline
	T Wrap(T x, T minVal, T maxVal, T amount)
	{
		if(x < minVal) x += amount;
		else if(x > maxVal) x -= amount;
		return x;
	}

	//Wraps radian value towards -PI and PI.
	inline float WrapAngle(float radians)
	{
		return Wrap(radians, -Pi, Pi, TwoPi);
	}

	//Wraps degree value towards 0 and 360.
	inline float WrapDegrees(float degrees)
	{
		return Wrap(degrees, 0.f, 360.f, 360.f);
	}

	inline bool IsNaN(float x)
	{
		return x != x;
	}

	inline u32 NextPowerOfTwo(u32 x)
	{
		u32 y(1);
		while(y < x) y <<= 1;
		return y;
	}



	constexpr FORCEINLINE int Truncate(float x) { return (int)x; }
	constexpr FORCEINLINE float Truncatef(float x) {return (float)((int)x); }
	constexpr FORCEINLINE int Round(float x) { return int((x > 0.f) ? (x + 0.5f) : (x - 0.5f)); }
	constexpr FORCEINLINE float Roundf(float x) { return (float)int((x > 0.f) ? (x + 0.5f) : (x - 0.5f)); }
	constexpr FORCEINLINE float Fractional(float x) { return x - Truncatef(x); }

	FORCEINLINE float Sqrtf(float x) { return sqrtf(x); }
	FORCEINLINE float InvSqrtf(float x) { return 1.0f / sqrtf(x); }
	FORCEINLINE float Expf(float x) { return expf(x); }
	FORCEINLINE float Powf(float x, float y) { return powf(x, y); }
	FORCEINLINE float Logf(float x) { return logf(x); }
	FORCEINLINE float Logx(float base, float x) { return logf(x) / logf(base); }
	FORCEINLINE float Fmodf(float x, float y) { return fmodf(x, y); }
	FORCEINLINE float Sinf(float x) { return sinf(x); }
	FORCEINLINE float Asinf(float x) { return asinf(x); }
	FORCEINLINE float Cosf(float x) { return cosf(x); }
	FORCEINLINE float Acosf(float x) { return acosf(x); }
	FORCEINLINE float Tanf(float x) { return tanf(x); }
	FORCEINLINE float Atanf(float x) { return atanf(x); }
	FORCEINLINE float Atan2f(float y, float x) { return atan2f(y, x); }

	FORCEINLINE int Floor(float x) { return (int)floorf(x); }
	FORCEINLINE float Floorf(float x) { return floorf(x); }
	FORCEINLINE int Ceil(float x) { return (int)ceilf(x); }
	FORCEINLINE float Ceilf(float x) { return ceilf(x); }

	template< class T >
	constexpr FORCEINLINE T Abs(const T x)
	{
		return x < T(0) ? -x : x;
	}

	template<>
	FORCEINLINE float Abs(const float x)
	{
		return fabsf(x);
	}

	constexpr FORCEINLINE bool EpsilonCompare(float x, float y, float epsilon = Epsilon)
	{
		return (Abs(x - y) < epsilon);
	}

	template<class T>
	constexpr FORCEINLINE T Min(const T a, const T b)
	{
		return (a < b) ? a : b;
	}

	template<class T>
	constexpr FORCEINLINE T Min(const T a, const T b, const T c)
	{
		return (a < b) ? Min(a, c) : Min(b, c);
	}

	template< class T >
	constexpr FORCEINLINE T Max(const T a, const T b)
	{
		return (a < b) ? b : a;
	}

	template<class T>
	constexpr FORCEINLINE T Max(const T a, const T b, const T c)
	{
		return (a > b) ? Max(a, c) : Max(b, c);
	}

	template<class T>
	constexpr FORCEINLINE T Sign(const T a)
	{
		return (a > (T)0) ? (T)1 : ((a < (T)0) ? (T)-1 : (T)0);
	}

	constexpr FORCEINLINE bool IsPowerOfTwo(int value)
	{
		return ((value & (value - 1)) == 0);
	}

	constexpr FORCEINLINE int SnapToGrid(int x, int grid)
	{
		if(grid == 0) return x;
		return (x / grid) * grid;
	}

	constexpr FORCEINLINE float SnapToGridf(float x, float grid)
	{
		if(grid == 0.f) return x;
		return Floorf(x / grid) * grid;
	}

	constexpr FORCEINLINE float ToDegrees(float radianValue)
	{
		return radianValue * (180.f / PI);
	}

	constexpr FORCEINLINE float ToRadians(float degreeValue)
	{
		return degreeValue * (PI / 180.f);
	}

	constexpr FORCEINLINE float DistanceSquared(float x1, float y1, float x2, float y2)
	{
		float a = x1 - x2;
		float b = y1 - y2;
		return a * a + b * b;
	}

	FORCEINLINE float Distance(float x1, float y1, float x2, float y2)
	{
		float a = x1 - x2;
		float b = y1 - y2;
		return sqrtf(float((a * a) + (b * b)));
	}

	constexpr FORCEINLINE float FastSqrtf(float x)
	{
		union
		{
			int i;
			float x;
		} u;

		u.x = x;
		u.i = (1 << 29) + (u.i >> 1) - (1 << 22);

		return u.x;
	}

	FORCEINLINE float FastAtan2f(float y, float x)
	{
		return Atan2f(y, x);
	}

	FORCEINLINE void SinCosf(float x, float& s, float& c)
	{
#if defined(_MSC_VER) || defined(__ICC)
		__asm
		{
			fld		x
			fsincos
			mov		eax, s
			mov		ecx, c
			fstp	dword ptr [ecx]
			fstp	dword ptr [eax]
		};
#elif defined(__GNUC__)
		__asm__
		(
		    "fsincos" :
		    "=t"(c) ,
		    "=u"(s) :
		    "0"(x)
		);
#else
		s = sinf(x);
		c = cosf(x);
#endif
	}

	FORCEINLINE void PolarToCartesian(float distance, float angle, float& outX, float& outY)
	{
		SinCosf(angle, outY, outX);
		outX *= distance;
		outY *= distance;
	}

	FORCEINLINE void CartesianToPolar(float x, float y, float& outDistance, float& outAngle)
	{
		outDistance = Sqrtf(x * x + y * y);
		outAngle = Atan2f(y, x);
	}


	constexpr FORCEINLINE float Lerp(float x, float y, float t)
	{
		return x + (y - x) * t;
	}

	constexpr FORCEINLINE float SmoothStep(float x, float y, float t)
	{
		t = (t * t) * (3.0f - (2.0f * t));
		return x + (y - x) * t;
	}

	constexpr FORCEINLINE float ApproximateSinf( const float x )
	{
		return x - ((x * x * x) / 6.f) + ((x * x * x * x * x) / 120.f) -
			((x * x * x * x * x * x * x) / 5040.f);
	}

	constexpr FORCEINLINE float ApproximateCosf( const float x )
	{
		return 1.f - (x * x * 0.5f) + (x * x * x * x * 0.0416666666f) -
			(x * x * x * x * x * x * 0.0013888888f);
	}

	constexpr FORCEINLINE void ApproximateSinCosf( const float x, float& s, float& c )
	{
		s = x - ((x * x * x) / 6.f) + ((x * x * x * x * x) / 120.f) - ((x * x * x * x * x * x * x) / 5040.f);
		c = 1.f - (x * x * 0.5f) + (x * x * x * x * 0.0416666666f) - (x * x * x * x * x * x * 0.0013888888f);
	}

	constexpr FORCEINLINE float ApproximateAtanf( const float x )
	{
		return x - (x * x * x * 0.33333333f) + (x * x * x * x * x * 0.2f) - 
			(x * x * x * x * x * x * x * 0.1428571429f) + (x * x * x * x * x * x * x * x * x * 0.11111111111f) - 
			(x * x * x * x * x * x * x * x * x * x * x * 0.09090909f);
	}

	constexpr inline float ApproximateAtan2f( float y, float x )
	{
		if( x > 0.f )
		{
			if( y == 0.f ) return 0.f;
			return ApproximateAtanf(y / x);
		}
		else if( x < 0.f )
		{
			if( y > 0.f ) return PI_OVER_2 + ApproximateAtanf(-x / y);
			if( y < 0.f ) return -PI_OVER_2 - ApproximateAtanf(x / y);
			return PI;
		}

		//else x equals 0/inf/nan
		if( y > 0.f ) return PI_OVER_2;
		if( y < 0.f ) return -PI_OVER_2;

		return 0.f;
	}

}


CE_NAMESPACE_END



/*
//  fast sin, cos, atan functions taken from glm.lib
//                (glm@g-truc.net)
//
//
// Copyright (c) 2005 - 2012 G-Truc Creation (www.g-truc.net)
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
*/
