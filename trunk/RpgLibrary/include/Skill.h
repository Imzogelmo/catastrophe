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

#include "Catastrophe/Core/Containers/String.h"
#include "Catastrophe/Core/Containers/StaticString.h"

#include "RpgCommon.h"
#include "Attributes.h"
#include "UsageInfo.h"
#include "Ability.h"


// *SkillLevelData*
// Represents 
struct SkillLevelData
{
	s16 exp;
	s16 cost;
	s16 effectivity;
	AbilityId		unlockAbility;
	SkillUsageInfo	usageInfo;

	SkillLevelData()
	{
		::memset(this, 0, sizeof(SkillLevelData));
	}
};


struct RPG_API Skill : public Ability
{

	StaticString<32>	name;
	StaticString<32>	script;
	String				description;

	//Attributes	attributes;
	u16		id;
	int		type;
	int		gold;
	int		cost;

	//SkillLevelData levelData[MAX_SKILL_LV]; //should be dynamic
	Vector<SkillLevelData> levelData;

	//s16	misc[16];
	//u8 level;


	u16		buff_id;
	u16		animationId;
	u16		sfx;

	//Attributes	attributes;

	Skill();

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

	int GetMemoryUsage() const;

};


#define MAX_PASSIVE_SKILL_LV		16;

struct RPG_API PassiveSkill
{
	StaticString<32>	name;
	String	description;

	int		id;
	int		type;
	int		gold;
	int		cost;

	//char	sp_table[MAX_PASSIVE_SKILL_LV];

	//s16	misc[16];

	//under construction...
	u8	usage_flags;
	u8	target_flags;
	u8	affect_flags;

	int		buff_id;
	int		animationId;
	u16		sfx;


	PassiveSkill();

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

};
