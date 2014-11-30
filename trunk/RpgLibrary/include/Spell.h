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
#include "UsageInfo.h"


struct SpellLevelData
{
	s16 exp;
	s16 cost;
	s16 effectivity;
	SpellUsageInfo usageInfo;

	SpellLevelData()
	{
		::memset(this, 0, sizeof(SpellLevelData));
	}
};


struct RPG_API Spell
{
	StaticString<32>	name;
	StaticString<32>	script;
	String				description;
	Attributes			attributes;

	fc::vector<SpellLevelData> levelData;

	u16			id;
	int			cost;
	int			gold;
	int			flags;
	//s16		misc[16];
	u16			iconId;
	u16			animationId;
	u16			sfx;
	//Targeting	targeting;


	Spell();

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

	int Spell::GetMemoryUsage() const;

};

