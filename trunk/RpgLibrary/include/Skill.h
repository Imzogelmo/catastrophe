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


struct RPG_API Skill
{
	fc::string	name;
	fc::string	script;
	fc::string	description;
	//Attributes	attributes;
	int		id;
	int		type;
	int		gold;
	int		cost;

	//short	misc[16];

	//under construction...
	ubyte	usage_flags;
	ubyte	target_flags;
	ubyte	affect_flags;

	int		buff_id;
	int		animation_id;
	int		sfx;


	Skill();

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};

