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

/*
struct ItemType
{
	short type; // item, weapon, armor, accessory, etc..
	short subtype; // knife, katana, etc.. (used in inventory sorting)
};
*/

struct RPG_API Item
{
	fc::string		name;
	fc::string		script;
	fc::string		description;

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


	//Attributes	attributes;

	short		type; // item, weapon, armor, accessory, etc..
	short		subtype; // knife, katana, etc.. (used in inventory sorting)

	int			id;
	int			price;
	int			spell_id;
	int			targeting;
	int			flags;
	int			usage_flags; //...
	//size_t		effect_id;

	int			sfx;
	int			icon_id;
	int			sprite_id;

	Item();

	virtual Attributes& GetAttributes() { return m_static_attributes; }
	virtual const Attributes& GetAttributes() const { return m_static_attributes; }

	static void RegisterObject();

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );
	void Serialize( Serializer* f );
	void Deserialize( Deserializer* f );

protected:
	static Attributes m_static_attributes;

};

