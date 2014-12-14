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
#include <fc/static_string.h>

#include "RpgCommon.h"
#include "UsageInfo.h"
#include "Ability.h"
#include "Factor.h"


/*
struct ItemType
{
	s16 type; // item, weapon, armor, accessory, etc..
	s16 subtype; // knife, katana, etc.. (used in inventory sorting)
};

struct ItemID
{
	u16 id;
	u16 type;

	ItemID() : id(0), type(0) {}
};
*/


struct ItemID
{
	/// ID of the item
	u16 id;

	/// Database category the item belongs to.
	u16 category;

	ItemID() : id(0), category(0) {}
};


struct RPG_API Item
{
	StaticString<32>	name;
	StaticString<32>	script;
	String				description;

	AbilityId	specialAbility;
	int			price;
	UsageInfo	usageInfo;

	u32			classFlags;
	u16			id;
	s16			type;
	s16			subtype;
	u16			sfx;
	u16			iconId;
	u16			spriteId;
	u8			itemFlags;

	
	//FactorSet factors;
	FixedFactorList factors;

	Item();

	virtual bool HasAttributes() const { return false; }
	virtual Attributes& GetAttributes() const { return m_staticAttributes; }

	virtual void Serialize( AttributeWriter* f );
	virtual void Deserialize( AttributeReader* f );

	virtual int GetMemoryUsage() const;

protected:
	static Attributes m_staticAttributes;

};

