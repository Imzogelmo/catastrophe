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


class TileProperties
{
public:

	enum TilePropertyFlags
	{
		Solid			= 0x00000004,
		//Blank			= 0x00000008,
		ImpassibleNorth	= 0x00000010,
		ImpassibleEast	= 0x00000020,
		ImpassibleSouth	= 0x00000040,
		ImpassibleWest	= 0x00000080
		//Blank			= 0x00000100,
		//Blank			= 0x00000200,
		//Blank			= 0x00000400,
		//Blank			= 0x00000800,

	};

	int		flags;
	short	encounter;
	byte	terrain;

	TileProperties();

	inline bool GetFlagBit( int bit ) { return (flags & (1 << bit)) != 0; }
	inline void SetFlagBit( int bit, bool value )
	{
		if( value )
			flags |= (1 << bit);
		else
			flags &= ~(1 << bit);
	}

	void SerializeXml( AttributeWriter* f );
	void DeserializeXml( AttributeReader* f );

};
