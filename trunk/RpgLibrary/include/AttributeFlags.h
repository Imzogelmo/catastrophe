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

#include "RpgCommon.h"


struct AttributeFlags
{
	typedef AttributeFlags this_type;

	enum : size_t
	{
		MaxInternalFlags = 8 //32 bytes
	};

	int	element_atk;
	int	element_absorb;
	int	element_nullify;
	int	element_resist;
	int	element_weak;
	int	family_flags;
	int	class_flags;
	int	misc_flags;

	//aggregate type

	int& operator [](size_t i) { return *((&element_atk) + i); }
	const int& operator [](size_t i) const { return *((&element_atk) + i); }

	this_type& operator |=(const this_type& rhs)
	{
		for( size_t i(0); i < MaxInternalFlags; ++i )
			operator [](i) |= rhs[i];
		return *this;
	}

	this_type& operator &=(const this_type& rhs)
	{
		for( size_t i(0); i < MaxInternalFlags; ++i )
			operator [](i) &= rhs[i];
		return *this;
	}

	this_type& operator ^=(const this_type& rhs)
	{
		for( size_t i(0); i < MaxInternalFlags; ++i )
			operator [](i) ^= rhs[i];
		return *this;
	}

	this_type& operator +=(const this_type& rhs)
	{
		// simply or them together.
		return operator |=(rhs);
	}

	this_type& operator -=(const this_type& rhs)
	{
		// special case:
		// if b[bit] and a[bit] then remove the bit (1 - 1 = 0),
		// otherwise there's no logical reason to remove a bit from lhs.
		for( size_t i(0); i < MaxInternalFlags; ++i )
		{
			int val = operator [](i) & rhs[i];
			operator [](i) &= ~val;
		}

		return *this;
	}

	this_type operator |(const this_type& rhs)
	{
		return this_type(*this).operator |=(rhs);
	}

	this_type operator &(const this_type& rhs)
	{
		return this_type(*this).operator &=(rhs);
	}

	this_type operator ^(const this_type& rhs)
	{
		return this_type(*this).operator ^=(rhs);
	}

	this_type operator +(const this_type& rhs)
	{
		return this_type(*this).operator +=(rhs);
	}

	this_type operator -(const this_type& rhs)
	{
		return this_type(*this).operator -=(rhs);
	}

	void Reset()
	{
		*this = this_type();
	}

	void SerializeXml( AttributeWriter* f );
	void DeserializeXml( AttributeReader* f );

};


