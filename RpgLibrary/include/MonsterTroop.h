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

#include <fc/static_vector.h>
#include <fc/string.h>

#include "RpgCommon.h"


/*
 * @MonsterGroup
 * class that represents data on how to instantiate
 * monsters.
 */
struct RPG_API MonsterGroup
{
	u16	monsterId;
	u8	min;
	u8	max;

	MonsterGroup();
	MonsterGroup(u16 monsterId, u8 minNum, u8 maxNum);

	void Validate();
	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

};



/*
 * @MonsterTroop
 * class that holds an array of monster groups.
 */
struct RPG_API MonsterTroop
{
	typedef fc::static_vector<MonsterGroup, 8> vec_type;

	String	name; //this is editor only....
	vec_type	groups;
	int			id;
	int			formation_id;
	int			max_monsters;

	MonsterTroop();

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

	int GetMemoryUsage() const;

};



