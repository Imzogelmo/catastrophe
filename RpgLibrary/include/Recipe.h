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


struct RPG_API Reagent
{
	short item_id;
	short amount;

	Reagent();

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );
};


struct RPG_API Recipe
{
	typedef fc::fixed_tiny_vector<Reagent, 4> vec_type;

	fc::string	name;
	int			id;
	vec_type	reagents;

	Recipe();

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );
};


