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


enum Gender ENUM_TYPE(u8)
{
	Sex_Male,
	Sex_Female,
	Sex_Unknown
};


enum Handedness ENUM_TYPE(u8)
{
	Handed_Right = 1,
	Handed_Left = 2,
	Handed_Ambidextrous = 3
};


enum Alignment ENUM_TYPE(u8)
{
	Alignment_Good,
	Alignment_Neutral,
	Alignment_Evil
};

//------------------------------------------------------------------------------------
// properties of potiential attack before it is input
//------------------------------------------------------------------------------------

enum TargetMode ENUM_TYPE(u8)
{
	TargetMode_None,			// Forced single-target to a selectable target
	TargetMode_Single,			// Forced single-target to a selectable target
	TargetMode_Group,			// Forced multi-target to a selectable group
	TargetMode_SingleOrGroup,	// Single or group, spreadable 
	TargetMode_Faction,			// Forced multi-target to selectable faction
	TargetMode_SingleOrFaction,	// Single or all of faction, spreadable
	TargetMode_GroupOrFaction,	// Group or all of faction, spreadable
	TargetMode_All				// Forced multi-target to both factions
};


enum Confirmation ENUM_TYPE(u8)
{
	Confirm_Manual,
	Confirm_Auto,
	Confirm_Randomize
};


enum CursorStart ENUM_TYPE(u8)
{
	CursorStart_None,
	CursorStart_Self,
	CursorStart_FirstAlly,
	CursorStart_FirstEnemy
};


enum CursorModeFlags ENUM_TYPE(u8)
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

enum Faction ENUM_TYPE(u8)
{
	Faction_Ally,
	Faction_Enemy
};


enum TargetScope ENUM_TYPE(u8)
{
	Scope_None,
	Scope_Single,
	Scope_Group,
	Scope_Faction,
	Scope_All
};


enum TargetInfo ENUM_TYPE(u8)
{
	Target_None, 
	Target_Enemy,
	Target_EnemyGroup,
	Target_EnemyFaction,
	Target_Ally,
	Target_AllyGroup,
	Target_AllyFaction, 
	Target_All
};

//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------

enum UsageFlags ENUM_TYPE(u8)
{
	UsageFlag_None = 0x00,
	UsageFlag_Camp = 0x01,
	UsageFlag_Field = 0x02,
	UsageFlag_Battle = 0x04,
	UsageFlag_Other = 0x08,
	UsageFlag_Any = 0x0F
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


enum BattleCondition ENUM_TYPE(u8)
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

enum ModifierType ENUM_TYPE(u8)
{
	ModifierType_BonusMalus,
	ModifierType_Multiplier
};


enum ItemFlags
{
	ItemFlag_KeyItem = 1,
	ItemFlag_Consumable = 2,
	ItemFlag_Equippable = 4,
	ItemFlag_Cursed = 8,
	ItemFlag_EquipOnlySpecialAbility = 0x10

};


// Details on how the item can be accessed within the database
enum ItemCategory ENUM_TYPE(u8)
{
	ItemCategory_Item,
	ItemCategory_Weapon,
	ItemCategory_Armor,
	ItemCategory_Accessory,
	ItemCategory_Material
};

