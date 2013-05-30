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
#include "EquipmentItem.h"
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

	fc::string			filename;
	const char*			root_name;
	const char*			item_name;
	ResourceDirectory*	resource_directory;

	DataArray();

	/// Generate a unique id forr each item in array.
	void GenerateIds();

	void SetResourceDirectory( ResourceDirectory* resourceDirectory )
	{
		resource_directory = resourceDirectory;
	}

	void SetNodeNames( const char* root, const char* item )
	{
		root_name = root;
		item_name = item;
	}

	void SetFileame( const fc::string& name )
	{
		filename = name;
	}

	NO_INLINE bool SerializeXml( const fc::string& filename = "" );
	NO_INLINE bool DeserializeXml( const fc::string& filename = "" );
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

	//void Initialize();
	//void Shutdown();

	/*
	DataArray<Skill>			skills;
	DataArray<Spell>			spells;
	DataArray<EncounterGroup>	encounters;
	*/

	DataArray<Item>				items;
	DataArray<EquipmentItem>	weapons;
	DataArray<EquipmentItem>	armor;
	DataArray<EquipmentItem>	accessories;

	DataArray<MonsterData>		monsters;
	DataArray<MonsterTroop>		monster_troops;
	DataArray<CharacterData>	characters;
	DataArray<CharacterClass>	character_classes;
	DataArray<Race>				races;

	DataArray<AnimatedSpriteSetAsset>	character_map_sprites;
	DataArray<AnimatedSpriteSetAsset>	character_battle_sprites;
	DataArray<AnimatedSpriteSetAsset>	monster_map_sprites;
	DataArray<AnimatedSpriteSetAsset>	monster_battle_sprites;

	//todo:
	//player/npc sprites
	//icons (sprites)
	//backgrounds
	//tiles
	//tilesets
	//maps
	//fonts
	//music
	//sfx

	/// Initializes the database.
	void Initialize();

	/// Clears all data from all arrays and deallocated any memory used.
	void ClearAll();

	/// Sets all file names to default. (This is called from the constructor)
	void SetAllDefaultDataArrayFilenames();

	/// Sets all node names to default. (This should never need to be used)
	void SetAllDefaultDataArrayNodeNames();

	/// Sets the current resource directory.
	void SetResourceDirectory( ResourceDirectory* resourceDirectory );

	/// Gets the current resource directory.
	ResourceDirectory* GetResourceDirectory() const;

	/// Save the entire database to xml. This will override any existing files.
	bool SerializeAllDataXml();

	/// Load the entire database from xml files.
	bool DeserializeAllDataXml();


	/// Called internally by DataArray. (This also keep the header files clean) ;)
	template <class T> static bool SerializeDataArray
		( T& arr, ResourceDirectory* resourceDirectory, const fc::string& filename, const char* root, const char* item );

	template <class T> static bool DeserializeDataArray
		( T& arr, ResourceDirectory* resourceDirectory, const fc::string& filename, const char* root, const char* item );

	/// *Safe* lookup of data by id. If the id is invalid it will return null.
	template <class T> static inline T* GetArrayContent( DataArray<T>& arr, int id ) {
		return (size_t)id < arr.size() ? &arr[id] : (T*)0;
	}

	/// Generate IDs from a DataArray. (Types must have an 'int id' property.)
	template <class T> static void GenerateIds( T& arr );

	/*
	Skill*			GetSkill( int id ) { return GetArrayContent<Skill>(skills, id); }
	Spell*			GetSpell( int id ) { return GetArrayContent<Spell>(spells, id); }
	EncounterGroup*	GetEncounterGroup( int id ) { return GetArrayContent<EncounterGroup>(encounters, id); }
	*/

	inline Item*				GetItem(int id) { return GetArrayContent<Item>(items, id); }
	inline Item*				GetWeapon(int id) { return GetArrayContent<EquipmentItem>(weapons, id); }
	inline Item*				GetArmor(int id) { return GetArrayContent<EquipmentItem>(armor, id); }
	inline Item*				GetAccessory(int id) { return GetArrayContent<EquipmentItem>(accessories, id); }

	inline MonsterData*			GetMonster(int id) { return GetArrayContent<MonsterData>(monsters, id); }
	inline MonsterTroop*		GetMonsterTroop(int id) { return GetArrayContent<MonsterTroop>(monster_troops, id); }
	inline CharacterData*		GetCharacter(int id) { return GetArrayContent<CharacterData>(characters, id); }
	inline CharacterClass*		GetCharacterClass(int id) { return GetArrayContent<CharacterClass>(character_classes, id); }
	inline Race*				GetRace(int id) { return GetArrayContent<Race>(races, id); }

	inline AnimatedSpriteSetAsset* GetCharacterMapSpriteSetAsset(int id) { return GetArrayContent<AnimatedSpriteSetAsset>(character_map_sprites, id); }
	inline AnimatedSpriteSetAsset* GetCharacterBattleSpriteSetAsset(int id) { return GetArrayContent<AnimatedSpriteSetAsset>(character_battle_sprites, id); }
	inline AnimatedSpriteSetAsset* GetMonsterMapSpriteSetAsset(int id) { return GetArrayContent<AnimatedSpriteSetAsset>(monster_map_sprites, id); }
	inline AnimatedSpriteSetAsset* GetMonsterBattleSpriteSetAsset(int id) { return GetArrayContent<AnimatedSpriteSetAsset>(monster_battle_sprites, id); }

private:
	ResourceDirectory*	m_resourceDirectory;

};



template <class T>
bool DataArray<T>::SerializeXml( const fc::string& name ) {
	ASSERT(root_name != 0);
	ASSERT(item_name != 0);
	ASSERT(!(name.empty() && filename.empty()));

	bool ret = Database::SerializeDataArray(*this, resource_directory, name.empty() ? filename : name, root_name, item_name);
	return ret;
}


template <class T>
bool DataArray<T>::DeserializeXml( const fc::string& name ) {
	ASSERT(root_name != 0);
	ASSERT(item_name != 0);
	ASSERT(!(name.empty() && filename.empty()));

	bool ret = Database::DeserializeDataArray(*this, resource_directory, name.empty() ? filename : name, root_name, item_name);
	GenerateIds();

	return ret;
}


// DataArray constructor overloads
template <class T> inline
DataArray<T>::DataArray() : base_type(),
		filename(),
		root_name(0),
		item_name(0),
		resource_directory(0),
{
}

template <> inline
DataArray<Item>::DataArray() : base_type(), filename(), root_name(0), item_name(0), resource_directory(0) {
	SetNodeNames("ItemList", "Item");
}

template <> inline
DataArray<EquipmentItem>::DataArray() : base_type(), filename(), root_name(0), item_name(0), resource_directory(0) {
	SetNodeNames("ItemList", "Item");
}

template <> inline
DataArray<MonsterData>::DataArray() : base_type(), filename(), root_name(0), item_name(0), resource_directory(0) {
	SetNodeNames("MonsterList", "Monster");
}

template <> inline
DataArray<MonsterTroop>::DataArray() : base_type(), filename(), root_name(0), item_name(0), resource_directory(0) {
	SetNodeNames("MonsterTroopList", "Troop");
}

template <> inline
DataArray<CharacterData>::DataArray() : base_type(), filename(), root_name(0), item_name(0), resource_directory(0) {
	SetNodeNames("CharacterList", "Character");
}

template <> inline
DataArray<CharacterClass>::DataArray() : base_type(), filename(), root_name(0), item_name(0), resource_directory(0) {
	SetNodeNames("CharacterClassList", "CharacterClass");
}

template <> inline
DataArray<Race>::DataArray() : base_type(), filename(), root_name(0), item_name(0), resource_directory(0) {
	SetNodeNames("RaceList", "Race");
}

template <> inline
DataArray<AnimatedSpriteSetAsset>::DataArray() : base_type(), filename(), root_name(0), item_name(0), resource_directory(0) {
	SetNodeNames("AnimatedSpriteSetList", "AnimatedSpriteSet");
}


template <class T> inline
void DataArray<T>::GenerateIds()
{
	Database::GenerateIds(*this);
}


