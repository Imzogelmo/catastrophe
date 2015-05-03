//////////////////////////////////////
// Fast Container Library           //
// MIT License - Copyright (c) 2012 //
//////////////////////////////////////

#pragma once

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/PlatformMath.h"
#include "Catastrophe/Core/Math/Vector2.h"

#define CE_RAND_MAX			0x7FFF
#define CE_INV_RAND_MAX		(1.0f / CE_RAND_MAX) //0.00003052f // 1/0x7fff

CE_NAMESPACE_BEGIN


namespace Random
{
	/// Generates a random number between 0 and RAND_MAX
	int CE_API Rand();

	/// Seeds the random number generator with the given seed.
	void CE_API SeedRand(int seed);

	inline int Int()
	{
		return Rand();
	}

	inline int Int(int upperBound)
	{
		return upperBound ? Rand() % upperBound : 0;
	}

	inline int Int(int low, int high)
	{
		return low + Int((1 + high) - low);
	}

	inline float Float()
	{
		return Rand() * CE_INV_RAND_MAX;
	}

	inline float Float(float n)
	{
		return (Rand() * CE_INV_RAND_MAX) * n;
	}

	inline float Float(float low, float high)
	{
		return (Rand() * CE_INV_RAND_MAX) * (high - low) + low;
	}

	inline int Variance(int variant)
	{
		return Int(-variant, variant);
	}

	inline int Variance(int n, int variant)
	{
		return n + Int(-variant, variant);
	}

	inline float Variance(float variant)
	{
		return Float(-variant, variant);
	}

	inline float Variance(float n, float variant)
	{
		return n + Float(-variant, variant);
	}

	inline bool Probability(int percent)
	{
		return (Int(100) < percent);
	}

	inline bool Probability(int percent, int total)
	{
		return (Int(total) < percent);
	}

	template <class T> inline
		const T& Choose( const T& a, const T& b )
		{
			int r = Int(2);
			if( r == 0 ) return a;
			return b;
		}

	template <class T> inline
		const T& Choose( const T& a, const T& b, const T& c )
		{
			int r = Int(3);
			if( r == 0 ) return a;
			if( r == 1 ) return b;
			return c;
		}

	template <class T> inline
		const T& Choose( const T& a, const T& b, const T& c, const T& d )
		{
			int r = Int(4);
			if( r == 0 ) return a;
			if( r == 1 ) return b;
			if( r == 2 ) return c;
			return d;
		}

	void CircularRand( float &x, float &y );
	void CircularRand( float radius, float &x, float &y );
	void ArcRand( float minAngle, float maxAngle, float &x, float &y );
	void ArcRand( float minAngle, float maxAngle, float radius, float &x, float &y );

	Vector2 CircularRand( float radius = 1.f );
	Vector2 ArcRand( float minAngle, float maxAngle, float radius = 1.f );

	template <class RandomAccessIterator, class RandomNumberGenerator> inline
	void Shuffle(RandomAccessIterator first, RandomAccessIterator last, RandomNumberGenerator r)
	{
		int distance = int(last - first);
		for(int i = distance - 1; i > 0; --i)
			Swap(first[i], first[r(i + 1)]);
	}

	template <class RandomAccessIterator> inline
	void Shuffle(RandomAccessIterator first, RandomAccessIterator last)
	{
		int distance = int(last - first);
		for(int i = distance - 1; i > 0; --i)
			Swap(first[i], first[Int(i + 1)]);
	}


} // Random



CE_NAMESPACE_END
