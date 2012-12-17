// catastrophe rpg engine
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#pragma once

#include <fc/math.h>


template <class T, size_t N>
struct FixedAttributeArray
{
	typedef FixedAttributeArray<T, N> this_type;

	enum : size_t
	{
		MaxSize = N,
		MaxAttributes = N
	};

	T attribute[MaxAttributes];

	FixedAttributeArray()
	{
		memset(this, 0, sizeof(this_type));
	}

	void Set(T value)
	{
		for( size_t i(0); i < N; ++i )
			attribute[i] = value;
	}

	void Set(T* values)
	{
		for( size_t i(0); i < N; ++i )
			attribute[i] = values[i];
	}

	T& operator [](size_t i) { return attribute[i]; }
	const T& operator [](size_t i) const { return attribute[i]; }

	this_type operator +(T value)
	{
		this_type ret;
		for( size_t i(0); i < N; ++i )
			ret.attribute[i] = attribute[i] + value;

		return ret;
	}

	this_type operator +(const this_type& rhs)
	{
		this_type ret;
		for( size_t i(0); i < N; ++i )
			ret.attribute[i] = attribute[i] + rhs.attribute[i];

		return ret;
	}

	this_type operator -(T value)
	{
		this_type ret;
		for( size_t i(0); i < N; ++i )
			ret.attribute[i] = attribute[i] - value;

		return ret;
	}

	this_type operator -(const this_type& rhs)
	{
		this_type ret;
		for( size_t i(0); i < N; ++i )
			ret.attribute[i] = attribute[i] - rhs.attribute[i];

		return ret;
	}

	this_type& operator +=(const this_type& rhs)
	{
		for( size_t i(0); i < N; ++i )
			attribute[i] += rhs.attribute[i];

		return *this;
	}

	this_type& operator -=(const this_type& rhs)
	{
		for( size_t i(0); i < N; ++i )
			attribute[i] -= rhs.attribute[i];

		return *this;
	}

	this_type Add(T value)
	{
		return *this + value;
	}

	this_type Add(const this_type& rhs)
	{
		return *this + rhs;
	}

	this_type Subtract(T value)
	{
		return *this - value;
	}

	this_type Subtract(const this_type& rhs)
	{
		return *this - rhs;
	}

	void ApplyModifier(float modifier)
	{
		for( size_t i(0); i < N; ++i )
			attribute[i] = T( fc::round((float)attribute[i] * modifier) );
	}

	void ApplyPercentageModifier(T modifier)
	{
		ApplyModifier((float)modifier / 100.f);
	}

	void ApplyPercentageModifier(const this_type& modifier)
	{
		for( size_t i(0); i < N; ++i )
		{
			if( modifier.attribute[i] != 0 )
			{
				float n = ((float)modifier.attribute[i] / 100.f);
				attribute[i] = T( fc::round((float)attribute[i] * n) );
			}
		}
	}

	void ApplyMin(const this_type& value)
	{
		for( size_t i(0); i < N; ++i )
			if( attribute[i] < value.attribute[i] )
				attribute[i] = value.attribute[i];
	}

	void ApplyMin(T value)
	{
		for( size_t i(0); i < N; ++i )
			if( attribute[i] < value )
				attribute[i] = value;
	}

	void ApplyMax(const this_type& value)
	{
		for( size_t i(0); i < N; ++i )
			if( attribute[i] > value.attribute[i] )
				attribute[i] = value.attribute[i];
	}

	void ApplyMax(T value)
	{
		for( size_t i(0); i < N; ++i )
			if( attribute[i] > value )
				attribute[i] = value;
	}

	void Clamp(const this_type& min, const this_type& max)
	{
		for( size_t i(0); i < N; ++i )
		{
			if( attribute[i] > max.attribute[i] )
				attribute[i] = max.attribute[i];
			else
			if( attribute[i] < min.attribute[i] )
				attribute[i] = min.attribute[i];
		}
	}

	void Clamp(T min, T max)
	{
		for( size_t i(0); i < N; ++i )
		{
			if( attribute[i] > max )
				attribute[i] = max;
			else
			if( attribute[i] < min )
				attribute[i] = min;
		}
	}

};

