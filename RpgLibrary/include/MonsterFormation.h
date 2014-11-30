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

#include <fc/dynamic_array.h>

#include "RpgCommon.h"


/*
 * @MonsterFormationCellData
 * class that represents data on where to instantiate
 * monsters.
 */
struct RPG_API MonsterFormationCellData
{
	s16	x;
	s16	y;

	MonsterFormationCellData();
	MonsterFormationCellData( s16 x, s16 y );

	static void RegisterObject();

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );
};



/*
 * @MonsterFormation
 * class that holds an array of formation cells.
 */
struct RPG_API MonsterFormation
{
	typedef fc::dynamic_array<MonsterFormationCellData> array_type;

	array_type	formations;
	u16			id;

	MonsterFormation();

	static void RegisterObject();

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

	int GetMemoryUsage() const;

};



