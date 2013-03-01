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

#include "RpgCommon.h"
#include "Attributes.h"


struct RPG_API Item
{
	fc::string	name;
	fc::string	script;
	fc::string	description;

	enum ItemFlags
	{
		Valuable = 0x0001,
		Consumable = 0x0002,
		Equippable = 0x0004,
		Cursed = 0x0008,
		//...
		UsableInMenu = 0x0040,
		UsableInBattle = 0x0080


	};

	//item types : item, weapon, armor, accessory, etc..
	//item subtypes : knife, katana, etc.

	Attributes	attributes;
	int			id;
	int			type;
	int			subtype;

	int			gold;
	int			spell_id;
	int			targeting;
	int		flags;
	int		usage_flags; //...
	//size_t		effect_id;
	int			sfx;
	int			icon_id;
	int			sprite_id;

	Item()
	{}

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};

