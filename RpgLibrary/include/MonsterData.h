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

#include "RpgCommon.h"
#include "Attributes.h"
#include "ItemDropSet.h"



struct RPG_API MonsterData
{
	fc::string		name;
	fc::string		script;
	fc::string		description;

	int				id;
	short			portrait_id;
	short			map_spriteset_id;
	short			battle_spriteset_id;
	short			default_background_id;

	int				lv;
	int				exp;
	int				gold;
	Attributes		attributes;
	ItemDropSet		item_dropset;

	MonsterData();

	static void RegisterObject();

	void SerializeXml( AttributeWriter* f );
	void DeserializeXml( AttributeReader* f );

};



