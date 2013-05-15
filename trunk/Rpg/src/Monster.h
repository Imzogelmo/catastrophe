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

#include <fc/string.h>

#include "Actor.h"
//#include "MonsterData.h"


class Monster : public Actor
{
public:
	fc::string	name;
	fc::string	script;

	int			monster_data_id;
	int			portait_id;
	int			map_spriteset_id;
	int			battle_spriteset_id;

	Monster();

	void InitializeFromData( int monsterDataId );

};


