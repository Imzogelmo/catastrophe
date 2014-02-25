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



struct RPG_API Race
{
	fc::string		name;
	fc::string		description;

	Attributes		attributes;

	int				id;
	//SpellBook		spells;

	Race();

	static void RegisterObject();

	void SerializeXml( AttributeWriter* f );
	void DeserializeXml( AttributeReader* f );

};


