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
#include <fc/dynamic_array.h>


#include <fc/dynamic_array.h>
//#include <fc/tiny_string.h>
#include <fc/string.h>

#include "RpgCommon.h"
#include "Serialization.h"

#include "Attributes.h"
#include "AttributeFlags.h"
#include "BattleCommand.h"
#include "Item.h"
#include "Skill.h"
#include "Spell.h"
#include "MonsterData.h"
#include "MonsterTroop.h"
#include "Encounter.h"
#include "Race.h"
#include "CharacterData.h"
#include "CharacterClass.h"
#include "ItemDrop.h"
#include "LevelData.h"
#include "ExpTable.h"
#include "Shops.h"
#include "Enhancement.h"
#include "Synthesis.h"


template <class T>
class DataArray : public fc::dynamic_array<T>
{
public:
	typedef fc::dynamic_array<T>	base_type;
	const char* root_name;
	const char* item_name;

	DataArray()
		: base_type(), root_name(0), item_name(0)
	{}

	void SetNodeNames( const char* root, const char* item )
	{
		root_name = root;
		item_name = item;
	}

	NO_INLINE bool SerializeXml( const fc::string& filename );
	NO_INLINE bool DeserializeXml( const fc::string& filename );
};


/*
 * @database
 * 
 */
class RPG_API Database
{
public:
	Database();
	~Database();

	DataArray<Item>				items;
	DataArray<Skill>			skills;
	DataArray<Spell>			spells;
	DataArray<CharacterData>	characters;
	DataArray<CharacterClass>	classes;
	DataArray<MonsterData>			monsters;
	DataArray<MonsterTroop>		troops;
	DataArray<EncounterGroup>	encounters;

	//todo:
	//monster sprites
	//battle sprites
	//player/npc sprites
	//icons (sprites)
	//backgrounds
	//tiles
	//tilesets
	//maps
	//fonts
	//music
	//sfx

	template <class T> static bool SerializeDataArray( T& arr, const fc::string& filename, const char* root, const char* item );
	template <class T> static bool DeserializeDataArray( T& arr, const fc::string& filename, const char* root, const char* item );
	template <class T> static inline T* GetArrayContent( DataArray<T>& arr, int id ) {
		return (size_t)id < arr.size() ? &arr[id] : (T*)0;
	}

	Item*			GetItem( int id ) { return GetArrayContent<Item>(items, id); }
	Skill*			GetSkill( int id ) { return GetArrayContent<Skill>(skills, id); }
	Spell*			GetSpell( int id ) { return GetArrayContent<Spell>(spells, id); }
	CharacterData*	GetCharacter( int id ) { return GetArrayContent<CharacterData>(characters, id); }
	CharacterClass*	GetCharacterClass( int id ) { return GetArrayContent<CharacterClass>(classes, id); }
	MonsterData*	GetMonster( int id ) { return GetArrayContent<MonsterData>(monsters, id); }
	MonsterTroop*	GetMonsterTroop( int id ) { return GetArrayContent<MonsterTroop>(troops, id); }
	EncounterGroup*	GetEncounterGroup( int id ) { return GetArrayContent<EncounterGroup>(encounters, id); }




private:

	//SpriteList*			m_portraitSprites;
	//AnimatedSpriteList*	m_weaponSprites;
	//AnimatedSpriteList*	m_miscSprites;

};



template <class T>
bool DataArray<T>::SerializeXml( const fc::string& filename ) {
	ASSERT(root_name != 0);
	ASSERT(item_name != 0);
	return Database::SerializeDataArray( *base_type, filename, root_name, item_name );
}


template <class T>
bool DataArray<T>::DeserializeXml( const fc::string& filename ) {
	ASSERT(root_name != 0);
	ASSERT(item_name != 0);
	return Database::DeserializeDataArray( *base_type, filename, root_name, item_name );
}

