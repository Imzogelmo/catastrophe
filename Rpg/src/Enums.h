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


enum Handedness
{
	Handed_Right,
	Handed_Left,
	Handed_Ambidextrous
};


enum Alignment
{
	Alignment_Good,
	Alignment_Neutral,
	Alignment_Evil
};

//------------------------------------------------------------------------------------
// properties of potiential attack before it is input
//------------------------------------------------------------------------------------

enum TargetModeFlags  
{
	TargetMode_Single = 1,         // Forced single-target to a selectable target
	TargetMode_Group = 2,          // Forced multi-target to a selectable group
	TargetMode_SingleOrGroup = 3,  // Single or group, spreadable 
	TargetMode_Faction = 4,        // Forced multi-target to selectable faction
	TargetMode_SingleOrFaction = 5 // Single or all of faction, spreadable
	TargetMode_All = 0xFF          // Forced multi-target to both factions
};


enum Confirmation  
{
	Confirm_Manual,
	Confirm_Auto,
	Confirm_Randomize
};


enum CursorStart
{
	Cursor_None,
	Cursor_Self,
	Cursor_FirstEnemy,
	Curosr_FirstAlly
};


enum CursorModeFlags
{
	CursorMode_Selectable = 1,       // Cam be moved off the starting target
	CursorMode_Spreadable = 2,       // Can be spread optionally
	CursorMode_FactionRestricted = 4 // Keep cursor within the faction it starts in
};


//------------------------------------------------------------------------------------
// properties of attack after it is input
//------------------------------------------------------------------------------------

enum Faction
{
	Faction_Ally,
	Faction_Enemy
};


enum TargetScope 
{
	Scope_Single,
	Scope_Group,
	Scope_Faction,
	Scope_All
};


enum TargetInfo 
{
	Target_None, 
	Target_Enemy,
	Target_EnemyGroup,
	Target_AllEnemies,
	Target_Ally,
	Target_AllyGroup,
	Target_AllAllies, 
	Target_All
};

//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------

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


