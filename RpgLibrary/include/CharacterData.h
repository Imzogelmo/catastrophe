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
//#include <fc/vector.h>

#include "RpgCommon.h"


struct RPG_API CharacterData
{
	fc::string		name;
	fc::string		script;
	fc::string		description;

	int				id;
	int				race_id;
	int					class_id;

	// these should be in CharacterClass only...?
	int				portrait_id;
	int				map_spriteset_id;
	int				battle_spriteset_id;

	int				lv;
	int				exp;
	int				gold;
	Attributes		attributes;

	//levelupLearning { id, lv } ..?
	//fc::vector<int>		spells;

	CharacterData();

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};

