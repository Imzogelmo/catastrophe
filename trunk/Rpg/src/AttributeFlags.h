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

#include "Common.h"
#include "Flags.h"


struct AttributeFlags
{
	typedef AttributeFlags this_type;

	enum : size_t
	{
		MaxInternalFlags = 8 //32 bytes
	};

	Flags32	element;
	Flags32	element_absorb;
	Flags32	element_nullify;
	Flags32	element_resist;
	Flags32	element_weak;
	Flags32	family_flags;
	Flags32	class_flags;
	Flags32	misc_flags;

	//aggregate type

	Flags32& operator [](size_t i) { return *((&element) + i); }
	const Flags32& operator [](size_t i) const { return *((&element) + i); }

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

	void Reset()
	{
		*this = this_type();
	}

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};


