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

#include <fc/fixed_vector.h>
#include <fc/string.h>

#include "RpgCommon.h"


/*
 * @MonsterGroup
 * class that represents data on how to instantiate
 * monsters.
 */
struct RPG_API MonsterGroup
{
	int		monster_id;
	int		min;
	int		max;

	MonsterGroup(int monsterIndex = 0, int minNum = 1, int maxNum = 1);

	//simply to ensure data is sane before saving.
	void Validate();

	static void RegisterObject();

	void SerializeXml( AttributeWriter* f );
	void DeserializeXml( AttributeReader* f );

};



/*
 * @MonsterTroop
 * class that holds an array of monster groups.
 */
struct RPG_API MonsterTroop
{
	typedef fc::fixed_vector<MonsterGroup, 4> vec_type;

	fc::string	name; //this is editor only....
	vec_type	groups;
	int			id;
	int			formation_id;
	int			max_monsters;

	MonsterTroop();

	static void RegisterObject();

	NO_INLINE void SerializeXml( AttributeWriter* f );
	NO_INLINE void DeserializeXml( AttributeReader* f );

};



