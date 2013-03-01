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

	this_type operator +(const this_type& rhs) const
	{
		this_type ret;
		for( size_t i(0); i < N; ++i )
			ret.attribute[i] = attribute[i] + rhs.attribute[i];

		return ret;
	}

	this_type operator -(const this_type& rhs) const
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

	template <class I>
	this_type Add(const this_type& rhs, I min, I max) const
	{
		this_type ret;
		for( size_t i(0); i < N; ++i )
		{
			I val = ((I)attribute[i] + (I)rhs.attribute[i]);
			if( val < min ) val = min;
			if( val > max ) val = min;
			ret.attribute[i] = (T)val;
		}

		return ret;
	}

	template <class I>
	this_type Subtract(const this_type& rhs, I min, I max) const
	{
		this_type ret;
		for( size_t i(0); i < N; ++i )
		{
			I val = ((I)attribute[i] - (I)rhs.attribute[i]);
			if( val < min ) val = min;
			if( val > max ) val = min;
			ret.attribute[i] = (T)val;
		}

		return ret;
	}

	template <class I>
	this_type& AddAssign(const this_type& rhs, I min, I max)
	{
		for( size_t i(0); i < N; ++i )
		{
			I val = ((I)attribute[i] + (I)rhs.attribute[i]);
			if( val < min ) val = min;
			if( val > max ) val = min;
			attribute[i] = (T)val;
		}

		return *this;
	}

	template <class I>
	this_type& SubtractAssign(const this_type& rhs, I min, I max)
	{
		for( size_t i(0); i < N; ++i )
		{
			I val = ((I)attribute[i] - (I)rhs.attribute[i]);
			if( val < min ) val = min;
			if( val > max ) val = min;
			attribute[i] = (T)val;
		}

		return *this;
	}

	template <class I>
	this_type& ApplyPercentageModifier(const this_type& rhs, I min, I max)
	{
		for( size_t i(0); i < N; ++i )
		{
			if( rhs.attribute[i] != 0 )
			{
				float x = ((float)attribute[i] * (1.f + ((float)rhs.attribute[i] / 100.f)));
				I val = I((x > 0.f) ? (x + 0.5f) : (x - 0.5f))
				if( val < min ) val = min;
				if( val > max ) val = min;
				attribute[i] = (T)val;
			}
		}

		return *this;
	}

	template <class I>
	void ApplyPercentageModifier(T modifier, I min, I max)
	{
		ApplyPercentageModifier<I>(this_type(modifier), min, max);
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

