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


enum Gender
{
	Sex_Male,
	Sex_Female,
	Sex_Unknown
};


enum Alignment
{
	Alignment_Good,
	Alignment_Neutral,
	Alignment_Evil
};


enum TargetModeFlags
{
	TargetMode_Single = 1,
	TargetMode_Many = 2,
	TargetMode_SingleOrMany = 3
};


enum TargetInfo
{
	Target_Self,
	Target_Enemy,
	Target_EnemyGroup,
	Target_AllEnemies,
	Target_Ally,
	Target_AllyGroup,
	Target_AllAllies,
	Target_All
};


enum TargetScope
{
	Scope_Single,
	Scope_Group,
	Scope_Faction,
	Scope_All
};


enum Faction
{
	Faction_Ally,
	Faction_Enemy
};


enum UsageFlags
{
	Usage_Camp = 1,
	Usage_Field = 2 | Usage_Camp,
	Usage_Battle = 4,
	Usage_Any = 0xff
};


enum AffectFlags
{
	Affect_Hp = 1,
	Affect_Mp = 2
	//should affect any stat?..
};


struct TargetData //saved in items/skills..
{
	byte some_flags;
	byte scope;
	byte padding[2]; //4 bytes
};


struct BattleTargetInfo //used in battle by actions.
{
	int target_id;
	byte info;

};


