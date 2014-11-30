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
	Handed_Right = 1,
	Handed_Left = 2,
	Handed_Ambidextrous = 3
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
	TargetMode_Single = 1,			// Forced single-target to a selectable target
	TargetMode_Group = 2,			// Forced multi-target to a selectable group
	TargetMode_SingleOrGroup = 3,	// Single or group, spreadable 
	TargetMode_Faction = 4,			// Forced multi-target to selectable faction
	TargetMode_SingleOrFaction = 5,	// Single or all of faction, spreadable
	TargetMode_All = 0xFF			// Forced multi-target to both factions
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
	Cursor_FirstAlly,
	Cursor_FirstEnemy,
};


enum CursorModeFlags
{
	CursorMode_None = 0	,				// User defined
	CursorMode_Selectable = 1,			// Cam be moved off the starting target
	CursorMode_Locked = 2,				// Keep cursor fixed in position.
	CursorMode_Spreadable = 4,			// Can be spread optionally
	CursorMode_FactionRestricted = 8	// Keep cursor within the faction it starts in
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
	Usage_Field = 2,
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
	u8 some_flags;
	u8 scope;
	u8 padding[2]; //4 bytes
};


struct BattleTargetInfo //used in battle by actions.
{
	int target_id;
	u8 info;

};


enum BattleCondition
{
	BattleCondition_None,
	BattleCondition_FirstStrike,
	BattleCondition_BackAttack,
	BattleCondition_Surrounded,
	BattleCondition_Pincer
};


//------------------------------------------------------------------------------------
// statistical data
//------------------------------------------------------------------------------------

enum ModifierType
{
	ModifierType_BonusMalus,
	ModifierType_Multiplier
};


enum ItemFlags
{
	ItemFlag_KeyItem = 1,
	ItemFlag_Eternal = 2,
	ItemFlag_Equippable = 4,
	ItemFlag_Cursed = 8,
	ItemFlag_EquipOnlySpecialAbility = 8

};


// Details on how the item can be accessed within the database
enum ItemCategory
{
	ItemCategory_Item,
	ItemCategory_Weapon,
	ItemCategory_Armor,
	ItemCategory_Accessory,
	ItemCategory_Material
};

