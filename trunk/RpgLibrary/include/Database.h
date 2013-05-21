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

#include "AnimatedSpriteAsset.h"
#include "AnimatedSpriteSetAsset.h"



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

	/*
	DataArray<Item>				items;
	DataArray<Skill>			skills;
	DataArray<Spell>			spells;
	DataArray<CharacterData>	characters;
	DataArray<CharacterClass>	classes;
	DataArray<MonsterTroop>		troops;
	DataArray<EncounterGroup>	encounters;
	*/

	DataArray<MonsterData>		monsters;
	DataArray<MonsterTroop>		monster_troops;

	DataArray<AnimatedSpriteSetAsset>	character_battle_sprites;
	DataArray<AnimatedSpriteSetAsset>	monster_battle_sprites;

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

	/// Sets all node names to default. (This should never need to be used)
	void SetAllDefaultDataArrayNodeNames();

	/// Save the entire database to xml. This will override any existing files.
	bool SerializeAllDataXml();

	/// Load the entire database from xml files.
	bool DeserializeAllDataXml();

	/// Called internally by DataArray. (This also keep the header files clean) ;)
	template <class T> static bool SerializeDataArray( T& arr, const fc::string& filename, const char* root, const char* item );
	template <class T> static bool DeserializeDataArray( T& arr, const fc::string& filename, const char* root, const char* item );

	/// *Safe* lookup of data by id. If the id is invalid it will return null.
	template <class T> static inline T* GetArrayContent( DataArray<T>& arr, int id ) {
		return (size_t)id < arr.size() ? &arr[id] : (T*)0;
	}

	/*
	Item*			GetItem( int id ) { return GetArrayContent<Item>(items, id); }
	Skill*			GetSkill( int id ) { return GetArrayContent<Skill>(skills, id); }
	Spell*			GetSpell( int id ) { return GetArrayContent<Spell>(spells, id); }
	CharacterData*	GetCharacter( int id ) { return GetArrayContent<CharacterData>(characters, id); }
	CharacterClass*	GetCharacterClass( int id ) { return GetArrayContent<CharacterClass>(classes, id); }
	EncounterGroup*	GetEncounterGroup( int id ) { return GetArrayContent<EncounterGroup>(encounters, id); }
	*/


	MonsterData*			GetMonster(int id) { return GetArrayContent<MonsterData>(monsters, id); }
	MonsterTroop*			GetMonsterTroop(int id) { return GetArrayContent<MonsterTroop>(monster_troops, id); }

	AnimatedSpriteSetAsset* GetCharacterBattleSpriteSetAsset(int id) { return GetArrayContent<AnimatedSpriteSetAsset>(character_battle_sprites, id); }
	AnimatedSpriteSetAsset* GetMonsterBattleSpriteSetAsset(int id) { return GetArrayContent<AnimatedSpriteSetAsset>(monster_battle_sprites, id); }



	//template <> static bool SerializeDataArray< DataArray<AnimatedSpriteSetAsset> >
	//	( DataArray<AnimatedSpriteSetAsset>& arr, const fc::string& filename, const char* root, const char* item );


};



template <class T>
bool DataArray<T>::SerializeXml( const fc::string& filename ) {
	ASSERT(root_name != 0);
	ASSERT(item_name != 0);
	return Database::SerializeDataArray( *this, filename, root_name, item_name );
}


template <class T>
bool DataArray<T>::DeserializeXml( const fc::string& filename ) {
	ASSERT(root_name != 0);
	ASSERT(item_name != 0);
	return Database::DeserializeDataArray( *this, filename, root_name, item_name );
}

/*
template <>
bool DataArray<AnimatedSpriteSetAsset>::SerializeXml( const fc::string& filename ) {
	return Database::SerializeDataArray< DataArray<AnimatedSpriteSetAsset> >( *this, filename, root_name, item_name );
}
*/