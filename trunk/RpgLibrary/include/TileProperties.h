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



enum TileFlags
{
	TileFlag_FlipX = 0x0001,
	TileFlag_FlipY = x0002,
	TileFlag_Solid = x0004,
	//Blank			= 0x00000008,
	TileFlag_ImpassibleNorth = x0010,
	TileFlag_ImpassibleEast = x0020,
	TileFlag_ImpassibleSouth = x0040,
	TileFlag_ImpassibleWest = x0080,
	//Blank			= 0x00000100,
	//Blank			= 0x00000200,
	//Blank			= 0x00000400,
	//Blank			= 0x00000800,
	TileFlag_AnimationPingPong = 0x4000,
	TileFlag_InternalReverseDirection = 0x8000,

};


class TileProperties
{
public:


	u16	flags;
	u16	encounter;
	u8	terrain;

	TileProperties();

	inline bool GetFlagBit( int bit ) { return (flags & (1 << bit)) != 0; }
	inline void SetFlagBit( int bit, bool value )
	{
		if( value )
			flags |= (1 << bit);
		else
			flags &= ~(1 << bit);
	}

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

};
