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
#include <fc/tiny_string.h>

#include "RpgCommon.h"
#include "Attributes.h"


struct RPG_API CharacterClass
{
	fc::tiny_string32	name;
	fc::tiny_string32	script;
	fc::string			description;

	int					id;
	int					portrait_id;
	int					map_spriteset_id;
	int					battle_spriteset_id;
	int					exp_table_id; //..levelup data..
	Attributes			attributes;

	CharacterClass();

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};

