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


struct RPG_API MonsterGroup
{
	int		monster_id;
	int		min;
	int		max;
	int		x;
	int		y;

	MonsterGroup(int monsterIndex = 0, int minNum = 1, int maxNum = 1, int x = 0, int y = 0);

	//simply to ensure data is sane before saving.
	void Validate();

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );
};


struct RPG_API MonsterTroop
{
	typedef fc::fixed_vector<MonsterGroup, 4> vec_type;

	fc::fixed_string128 name; //this is editor only....
	vec_type	groups;
	int			id;

	MonsterTroop();

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );
};

