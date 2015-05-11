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

#include <Catastrophe/Core/Containers/StaticBitset.h>


struct Switches
{
	enum Properties {
		MaxBits = 4096,
		MaxWords = (((MaxBits - 1) / 32) + 1),
	};

	typedef StaticBitset<MaxBits> bit_array_type;
	bit_array_type bits;

	Switches();

#ifdef EDITOR
	String strings[MaxBits];

	void SetString( u32 position, const String& value )
	{
		if( position < MaxBits )
			strings[position] = value;
	}

	String GetString( u32 position )
	{
		if( position < MaxBits )
			return strings[position];

		return String();
	}
#endif

	void Reset();
	void ToggleBit( u32 position );
	void SetBit( u32 position, bool value );
	bool GetBit( u32 position );

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

};

