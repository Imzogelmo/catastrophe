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

#include "Catastrophe/Core/Containers/Vector.h"

#include "RpgCommon.h"
#include "AttributeFlags.h"


/*
 * Stores information for a particular level.
 */
struct RPG_API LevelData
{
	AttributeFlags flags;

	LevelData() {}

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );
};


/*
 * Stores information for a range of levels.
 */
struct RPG_API LevelInfo
{
	typedef Vector<LevelData>	vec_type;

	vec_type levels;
	int exp_table_id;

	LevelInfo() : levels(), exp_table_id(-1)
	{}


	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );
};

