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
	enum
	{
		MaxFlags = 5
	};

	int elementAtk;
	int familyStrong;
	int familyWeak;
	int classFlags;
	int miscFlags;

	AttributeFlags() :
		elementAtk(0),
		familyStrong(0),
		familyWeak(0),
		classFlags(0),
		miscFlags(0)
	{}

	int& operator [](int i) { return *((&elementAtk) + i); }
	const int& operator [](int i) const { return *((&elementAtk) + i); }

	AttributeFlags& operator |=(const AttributeFlags& rhs)
	{
		for( int i(0); i < MaxFlags; ++i )
			operator [](i) |= rhs[i];
		return *this;
	}

	AttributeFlags& operator &=(const AttributeFlags& rhs)
	{
		for( int i(0); i < MaxFlags; ++i )
			operator [](i) &= rhs[i];
		return *this;
	}

	AttributeFlags& operator ^=(const AttributeFlags& rhs)
	{
		for( int i(0); i < MaxFlags; ++i )
			operator [](i) ^= rhs[i];
		return *this;
	}

	AttributeFlags& operator +=(const AttributeFlags& rhs)
	{
		// simply or them together.
		return operator |=(rhs);
	}

	AttributeFlags& operator -=(const AttributeFlags& rhs)
	{
		// special case:
		// if b[bit] and a[bit] then remove the bit (1 - 1 = 0),
		// otherwise there's no logical reason to remove a bit from lhs.
		for( int i(0); i < MaxFlags; ++i )
		{
			int val = operator [](i) & rhs[i];
			operator [](i) &= ~val;
		}

		return *this;
	}

	AttributeFlags operator |(const AttributeFlags& rhs)
	{
		return AttributeFlags(*this).operator |=(rhs);
	}

	AttributeFlags operator &(const AttributeFlags& rhs)
	{
		return AttributeFlags(*this).operator &=(rhs);
	}

	AttributeFlags operator ^(const AttributeFlags& rhs)
	{
		return AttributeFlags(*this).operator ^=(rhs);
	}

	AttributeFlags operator +(const AttributeFlags& rhs)
	{
		return AttributeFlags(*this).operator +=(rhs);
	}

	AttributeFlags operator -(const AttributeFlags& rhs)
	{
		return AttributeFlags(*this).operator -=(rhs);
	}

	void Reset()
	{
		*this = AttributeFlags();
	}

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

};


