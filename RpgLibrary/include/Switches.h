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
	typedef fc::static_bit_array<4096>	bit_array_type;
	bit_array_type bits;

	Switches();

	void Reset();
	void FlipBit( int bit );
	void SetBit( int bit, bool value );

	bool GetBit( int bit );

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};

