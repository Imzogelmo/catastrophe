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

#include "Catastrophe/Core/Containers/Array.h"

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

MAKE_TRAIT(MonsterFormationCellData, is_pod);



/*
 * @MonsterFormation
 * class that holds an array of formation cells.
 */
struct RPG_API MonsterFormation
{
	typedef Array<MonsterFormationCellData> array_type;

	array_type	formations;
	u16			id;

	MonsterFormation();

	static void RegisterObject();

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

	int GetMemoryUsage() const;

};



