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
#include "ItemDrop.h"



struct RPG_API Monster
{
	fc::tiny_string32	name;
	fc::tiny_string32	script;
	fc::string			description;

	int					lv;
	int					exp;
	int					gold;
	int					spriteset_id;

	Attributes			attributes;
	ItemDropSet			item_dropset;

	Monster()
	{}

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};



