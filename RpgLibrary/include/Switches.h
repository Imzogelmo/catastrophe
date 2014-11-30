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

#include <fc/static_bit_array.h>
#include "RpgCommon.h"


struct Switches
{
	enum Properties {
		MaxBits = 4096,
		MaxWords = (((MaxBits - 1) / 32) + 1),
	};

	typedef fc::static_bit_array<MaxBits> bit_array_type;
	bit_array_type bits;

	Switches();

#ifdef EDITOR
	String strings[MaxBits];

	void SetString( int bit, const String& value )
	{
		if( bit < MaxBits )
			strings[bit] = value;
	}

	const String& GetString( int bit )
	{
		if( bit < MaxBits )
			return strings[bit];

		return String();
	}
#endif

	void Reset();
	void FlipBit( int bit );
	void SetBit( int bit, bool value );

	bool GetBit( int bit );

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

};

