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
#include <fc/fixed_tiny_vector.h>
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
#include "MonsterFormation.h"
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
#include "Switches.h"

#include "SpriteAsset.h"
#include "AnimatedSpriteAsset.h"
#include "AnimatedSpriteSetAsset.h"
#include "ShaderAsset.h"


// include last
#include "DataArray.h"



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
	DataArray<MonsterFormation>	monster_formations;
	DataArray<CharacterData>	characters;
	DataArray<CharacterClass>	character_classes;
	DataArray<Race>				races;

	DataArray<SpriteAsset>				character_portrait_sprites;
	DataArray<AnimatedSpriteSetAsset>	character_map_sprites;
	DataArray<AnimatedSpriteSetAsset>	character_battle_sprites;
	DataArray<AnimatedSpriteSetAsset>	monster_map_sprites;
	DataArray<AnimatedSpriteSetAsset>	monster_battle_sprites;
	DataArray<ShaderAsset>				shaders;


	//extra
	Switches	switches;
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

	/// Generate all applicable script headers.
	void GenerateScriptHeaders();


	/// Called internally by DataArray. (This also keep the header files clean) ;)
	template <class T> static bool SerializeDataArray
		( T& arr, ResourceDirectory* resourceDirectory, const fc::string& filename, const char* root, const char* item );

	template <class T> static bool DeserializeDataArray
		( T& arr, ResourceDirectory* resourceDirectory, const fc::string& filename, const char* root, const char* item );

	/// *Safe* lookup of data by id. If the id is invalid it will return null.
	template <class T> static inline T* GetArrayContent( DataArray<T>& arr, int id ) {
		return (size_t)id < arr.size() ? &arr[id] : (T*)0;
	}

	/// Linear lookup of data by name. If the name is not found it will return null.
	template <class T> static inline T* GetArrayContentByName( DataArray<T>& arr, const fc::string& name ) {
		for( size_t i(0); i < arr.size(); ++i )
			if( arr[i].GetName() == name )
				return &arr[i];

		return (T*)0;
	}

	/// Generate IDs from a DataArray. (Types must have an 'int id' property.)
	template <class T> static void GenerateIds( T& arr );

	/// Generate script header from array. (must contain T(item).name member).
	template <class Array> bool GenerateHeader
		( const Array& arr, ResourceDirectory* resourceDirectory, const fc::string& filename, const fc::string& prependStr );

	/*
	Skill*			GetSkill( int id ) { return GetArrayContent<Skill>(skills, id); }
	Spell*			GetSpell( int id ) { return GetArrayContent<Spell>(spells, id); }
	EncounterGroup*	GetEncounterGroup( int id ) { return GetArrayContent<EncounterGroup>(encounters, id); }
	*/

	// Lookup by id
	inline Item*				GetItem(int id) { return GetArrayContent<Item>(items, id); }
	inline Item*				GetWeapon(int id) { return GetArrayContent<EquipmentItem>(weapons, id); }
	inline Item*				GetArmor(int id) { return GetArrayContent<EquipmentItem>(armor, id); }
	inline Item*				GetAccessory(int id) { return GetArrayContent<EquipmentItem>(accessories, id); }

	inline MonsterData*			GetMonster(int id) { return GetArrayContent<MonsterData>(monsters, id); }
	inline MonsterTroop*		GetMonsterTroop(int id) { return GetArrayContent<MonsterTroop>(monster_troops, id); }
	inline MonsterFormation*	GetMonsterFormation(int id) { return GetArrayContent<MonsterFormation>(monster_formations, id); }

	inline CharacterData*		GetCharacter(int id) { return GetArrayContent<CharacterData>(characters, id); }
	inline CharacterClass*		GetCharacterClass(int id) { return GetArrayContent<CharacterClass>(character_classes, id); }
	inline Race*				GetRace(int id) { return GetArrayContent<Race>(races, id); }

	inline SpriteAsset*				GetCharacterPortraitSpriteAsset(int id) { return GetArrayContent<SpriteAsset>(character_portrait_sprites, id); }
	inline AnimatedSpriteSetAsset*	GetCharacterMapSpriteSetAsset(int id) { return GetArrayContent<AnimatedSpriteSetAsset>(character_map_sprites, id); }
	inline AnimatedSpriteSetAsset*	GetCharacterBattleSpriteSetAsset(int id) { return GetArrayContent<AnimatedSpriteSetAsset>(character_battle_sprites, id); }
	inline AnimatedSpriteSetAsset*	GetMonsterMapSpriteSetAsset(int id) { return GetArrayContent<AnimatedSpriteSetAsset>(monster_map_sprites, id); }
	inline AnimatedSpriteSetAsset*	GetMonsterBattleSpriteSetAsset(int id) { return GetArrayContent<AnimatedSpriteSetAsset>(monster_battle_sprites, id); }
	inline ShaderAsset*				GetShaderAsset(int id) { return GetArrayContent<ShaderAsset>(shaders, id); }

	// Lookup by name
	inline ShaderAsset*				GetShaderAsset(const fc::string& name) { return GetArrayContentByName<ShaderAsset>(shaders, name); }

private:
	ResourceDirectory*		m_resourceDirectory;
	DatabaseArrayAnyHolder	m_arrayAny;

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
		resource_directory(0)
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
DataArray<MonsterFormation>::DataArray() : base_type(), filename(), root_name(0), item_name(0), resource_directory(0) {
	SetNodeNames("MonsterFormationList", "Formation");
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
DataArray<SpriteAsset>::DataArray() : base_type(), filename(), root_name(0), item_name(0), resource_directory(0) {
	SetNodeNames("SpriteList", "Sprite");
}

template <> inline
DataArray<AnimatedSpriteAsset>::DataArray() : base_type(), filename(), root_name(0), item_name(0), resource_directory(0) {
	SetNodeNames("AnimatedSpriteList", "AnimatedSprite");
}

template <> inline
DataArray<AnimatedSpriteSetAsset>::DataArray() : base_type(), filename(), root_name(0), item_name(0), resource_directory(0) {
	SetNodeNames("AnimatedSpriteSetList", "AnimatedSpriteSet");
}

template <> inline
DataArray<ShaderAsset>::DataArray() : base_type(), filename(), root_name(0), item_name(0), resource_directory(0) {
	SetNodeNames("ShaderList", "Shader");
}



template <class T> inline
void DataArray<T>::GenerateIds()
{
	Database::GenerateIds(*this);
}


