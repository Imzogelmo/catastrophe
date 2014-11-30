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

#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4480 )
#endif


template <class T, u32 N>
struct FixedAttributeArray
{
	typedef FixedAttributeArray<T, N> this_type;

	enum : u32
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
		for( u32 i(0); i < N; ++i )
			attribute[i] = value;
	}

	void Set(T* values)
	{
		for( u32 i(0); i < N; ++i )
			attribute[i] = values[i];
	}

	T& operator [](u32 i) { return attribute[i]; }
	const T& operator [](u32 i) const { return attribute[i]; }

	this_type operator +(const this_type& rhs) const
	{
		this_type ret;
		for( u32 i(0); i < N; ++i )
			ret.attribute[i] = attribute[i] + rhs.attribute[i];

		return ret;
	}

	this_type operator -(const this_type& rhs) const
	{
		this_type ret;
		for( u32 i(0); i < N; ++i )
			ret.attribute[i] = attribute[i] - rhs.attribute[i];

		return ret;
	}

	this_type& operator +=(const this_type& rhs)
	{
		for( u32 i(0); i < N; ++i )
			attribute[i] += rhs.attribute[i];

		return *this;
	}

	this_type& operator -=(const this_type& rhs)
	{
		for( u32 i(0); i < N; ++i )
			attribute[i] -= rhs.attribute[i];

		return *this;
	}

	template <class I>
	this_type Add(const this_type& rhs, I min, I max) const
	{
		this_type ret;
		for( u32 i(0); i < N; ++i )
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
		for( u32 i(0); i < N; ++i )
		{
			I val = ((I)attribute[i] - (I)rhs.attribute[i]);
			if( val < min ) val = min;
			if( val > max ) val = min;
			ret.attribute[i] = (T)val;
		}

		return ret;
	}

	template <class I> inline
	void AddAssignIndex(u32 i, I value, I min, I max)
	{
		I val = ((I)attribute[i] + value);
		if( val < min ) val = min;
		if( val > max ) val = min;
		attribute[i] = (T)val;
	}

	template <class I>
	this_type& AddAssign(const this_type& rhs, I min, I max)
	{
		for( u32 i(0); i < N; ++i )
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
		for( u32 i(0); i < N; ++i )
		{
			I val = ((I)attribute[i] - (I)rhs.attribute[i]);
			if( val < min ) val = min;
			if( val > max ) val = min;
			attribute[i] = (T)val;
		}

		return *this;
	}

	template <class I> inline
	void ApplyPercentageModifierToIndex(u32 i, I value, I min, I max)
	{
		if( value != 0 )
		{
			float x = ((float)attribute[i] * (1.f + ((float)value / 100.f)));
			I val = I((x > 0.f) ? (x + 0.5f) : (x - 0.5f));
			if( val < min ) val = min;
			if( val > max ) val = min;
			attribute[i] = (T)val;
		}
	}

	template <class I>
	this_type& ApplyPercentageModifier(const this_type& rhs, I min, I max)
	{
		for( u32 i(0); i < N; ++i )
		{
			ApplyPercentageModifierToIndex(i, (I)rhs.attribute[i], min, max);
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
		for( u32 i(0); i < N; ++i )
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
		for( u32 i(0); i < N; ++i )
		{
			if( attribute[i] > max )
				attribute[i] = max;
			else
			if( attribute[i] < min )
				attribute[i] = min;
		}
	}

};



#ifdef _MSC_VER
	#pragma warning ( pop )
#endif
