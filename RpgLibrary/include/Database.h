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
#include <fc/fixed_vector.h>
#include <fc/string.h>

#include "RpgCommon.h"
#include "Enums.h"
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
#include "Factor.h"
#include "CharacterData.h"
#include "CharacterClass.h"
#include "ItemDrop.h"
#include "LevelData.h"
#include "ExperienceTable.h"
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


	DataArray<Skill>			skills;
	DataArray<Skill>			passiveSkills;
	DataArray<Spell>			spells;
	//DataArray<EncounterGroup>	encounters;

	DataArray<Item>				items;
	DataArray<EquipmentItem>	weapons;
	DataArray<EquipmentItem>	armor;
	DataArray<EquipmentItem>	accessories;

	DataArray<MonsterData>		monsters;
	DataArray<MonsterTroop>		monsterTroops;
	DataArray<MonsterFormation>	monsterFormations;
	DataArray<CharacterData>	characters;
	DataArray<CharacterClass>	characterClasses;
	DataArray<Race>				races;
	DataArray<Factor>			factors;
	DataArray<ExperienceTable>	experienceTables;


	//DataArray<SpriteAsset>				characterPortraitSprites;
	DataArray<SpriteAsset>				battleBackgroundSprites;
	DataArray<SpriteAsset>				miscIconSprites;
	DataArray<SpriteAsset>				characterPortraitSprites;
	DataArray<AnimatedSpriteSetAsset>	characterMapSprites;
	DataArray<AnimatedSpriteSetAsset>	characterBattleSprites;
	DataArray<AnimatedSpriteSetAsset>	monsterMapSprites;
	DataArray<AnimatedSpriteSetAsset>	monsterBattleSprites;
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
		( T& arr, ResourceDirectory* resourceDirectory, const String& filename, const char* root, const char* item );

	template <class T> static bool DeserializeDataArray
		( T& arr, ResourceDirectory* resourceDirectory, const String& filename, const char* root, const char* item );

	/// *Safe* lookup of data by id. If the id is invalid it will return null.
	template <class T> static inline T* GetArrayContent( DataArray<T>& arr, int id ) {
		return (u32)id < arr.size() ? &arr[id] : (T*)0;
	}

	/// Linear lookup of data by name. If the name is not found it will return null.
	template <class T> static inline T* GetArrayContentByName( DataArray<T>& arr, const String& name ) {
		for( u32 i(0); i < arr.size(); ++i )
			if( arr[i].GetName() == name )
				return &arr[i];

		return (T*)0;
	}

	/// Generate IDs from a DataArray. (Types must have an 'int id' property.)
	template <class T> static void GenerateIds( T& arr );

	/// Generate script header from array. (must contain T(item).name member).
	template <class Array> bool GenerateHeader
		( const Array& arr, ResourceDirectory* resourceDirectory, const String& filename, const String& prependStr );

	/*
	Skill*			GetSkill( int id ) { return GetArrayContent<Skill>(skills, id); }
	Spell*			GetSpell( int id ) { return GetArrayContent<Spell>(spells, id); }
	EncounterGroup*	GetEncounterGroup( int id ) { return GetArrayContent<EncounterGroup>(encounters, id); }
	*/

	// Lookup by id
	inline Item*				GetItem(ItemID itemId)
	{
		const u16 id = itemId.id;
		switch( itemId.category )
		{
			case ItemCategory_Item: return GetArrayContent<Item>(items, id);
			case ItemCategory_Weapon: return GetArrayContent<EquipmentItem>(weapons, id);
			case ItemCategory_Armor: return GetArrayContent<EquipmentItem>(armor, id);
			case ItemCategory_Accessory: return GetArrayContent<EquipmentItem>(accessories, id);
			break;
		}

		return (Item*)0;
	}


	inline Skill*				GetSkill(int id) { return GetArrayContent<Skill>(skills, id); }
	inline Skill*				GetPassiveSkill(int id) { return GetArrayContent<Skill>(passiveSkills, id); }
	inline Spell*				GetSpell(int id) { return GetArrayContent<Spell>(spells, id); }

	inline Item*				GetItem(int id) { return GetArrayContent<Item>(items, id); }
	inline Item*				GetWeapon(int id) { return GetArrayContent<EquipmentItem>(weapons, id); }
	inline Item*				GetArmor(int id) { return GetArrayContent<EquipmentItem>(armor, id); }
	inline Item*				GetAccessory(int id) { return GetArrayContent<EquipmentItem>(accessories, id); }

	inline MonsterData*			GetMonster(int id) { return GetArrayContent<MonsterData>(monsters, id); }
	inline MonsterTroop*		GetMonsterTroop(int id) { return GetArrayContent<MonsterTroop>(monsterTroops, id); }
	inline MonsterFormation*	GetMonsterFormation(int id) { return GetArrayContent<MonsterFormation>(monsterFormations, id); }

	inline CharacterData*		GetCharacter(int id) { return GetArrayContent<CharacterData>(characters, id); }
	inline CharacterClass*		GetCharacterClass(int id) { return GetArrayContent<CharacterClass>(characterClasses, id); }
	inline Race*				GetRace(int id) { return GetArrayContent<Race>(races, id); }
	inline ExperienceTable*		GetExperienceTable(int id) { return GetArrayContent<ExperienceTable>(experienceTables, id); }

	inline SpriteAsset*				GetBattleBackgroundSpritesAsset(int id) { return GetArrayContent<SpriteAsset>(battleBackgroundSprites, id); }
	inline SpriteAsset*				GetMiscIconSpriteAsset(int id) { return GetArrayContent<SpriteAsset>(miscIconSprites, id); }
	inline SpriteAsset*				GetCharacterPortraitSpriteAsset(int id) { return GetArrayContent<SpriteAsset>(characterPortraitSprites, id); }
	inline AnimatedSpriteSetAsset*	GetCharacterMapSpriteSetAsset(int id) { return GetArrayContent<AnimatedSpriteSetAsset>(characterMapSprites, id); }
	inline AnimatedSpriteSetAsset*	GetCharacterBattleSpriteSetAsset(int id) { return GetArrayContent<AnimatedSpriteSetAsset>(characterBattleSprites, id); }
	inline AnimatedSpriteSetAsset*	GetMonsterMapSpriteSetAsset(int id) { return GetArrayContent<AnimatedSpriteSetAsset>(monsterMapSprites, id); }
	inline AnimatedSpriteSetAsset*	GetMonsterBattleSpriteSetAsset(int id) { return GetArrayContent<AnimatedSpriteSetAsset>(monsterBattleSprites, id); }
	inline ShaderAsset*				GetShaderAsset(int id) { return GetArrayContent<ShaderAsset>(shaders, id); }

	// Lookup by name
	inline ShaderAsset*				GetShaderAsset(const String& name) { return GetArrayContentByName<ShaderAsset>(shaders, name); }

	/// Gets the combined memory usage (in bytes) of every object inside the database,
	/// including the database object itself.
	int GetMemoryUsage() const;

	/// Logs detailed memory usage information for each object inside the database.
	void LogMemoryUsage() const;

private:
	ResourceDirectory*		m_resourceDirectory;
	//DatabaseArrayAnyHolder	m_arrayAny;

};



template <class T>
bool DataArray<T>::Serialize( const String& name ) {
	ASSERT(rootName != 0);
	ASSERT(itemName != 0);
	ASSERT(!(name.empty() && filename.empty()));

	bool ret = Database::SerializeDataArray(*this, resourceDirectory, name.empty() ? filename : name, rootName, itemName);
	return ret;
}


template <class T>
bool DataArray<T>::Deserialize( const String& name ) {
	ASSERT(rootName != 0);
	ASSERT(itemName != 0);
	ASSERT(!(name.empty() && filename.empty()));

	bool ret = Database::DeserializeDataArray(*this, resourceDirectory, name.empty() ? filename : name, rootName, itemName);
	GenerateIds();

	return ret;
}


// DataArray constructor overloads
template <class T> inline
DataArray<T>::DataArray() : base_type(),
		filename(),
		rootName(0),
		itemName(0),
		resourceDirectory(0)
{
	InitializeType();
}


template <class T> inline void DataArray<T>::InitializeType() {}
template <> inline void DataArray<Skill>::InitializeType() { SetNodeNames("SkillList", "Skill"); }
template <> inline void DataArray<Spell>::InitializeType() { SetNodeNames("SpellList", "Spell"); }
template <> inline void DataArray<Item>::InitializeType() { SetNodeNames("ItemList", "Item"); }
template <> inline void DataArray<EquipmentItem>::InitializeType() { SetNodeNames("ItemList", "Item"); }
template <> inline void DataArray<MonsterData>::InitializeType() { SetNodeNames("MonsterList", "Monster"); }
template <> inline void DataArray<MonsterTroop>::InitializeType() { SetNodeNames("MonsterTroopList", "Troop"); }
template <> inline void DataArray<MonsterFormation>::InitializeType() { SetNodeNames("MonsterFormationList", "Formation"); }
template <> inline void DataArray<CharacterData>::InitializeType() { SetNodeNames("CharacterList", "Character"); }
template <> inline void DataArray<CharacterClass>::InitializeType() { SetNodeNames("CharacterClassList", "CharacterClass"); }
template <> inline void DataArray<Race>::InitializeType() { SetNodeNames("RaceList", "Race"); }
template <> inline void DataArray<Factor>::InitializeType() { SetNodeNames("FactorList", "Factor"); }
template <> inline void DataArray<ExperienceTable>::InitializeType() { SetNodeNames("ExpTableList", "ExpTable"); }
template <> inline void DataArray<SpriteAsset>::InitializeType() { SetNodeNames("SpriteList", "Sprite"); }
template <> inline void DataArray<AnimatedSpriteAsset>::InitializeType() { SetNodeNames("AnimatedSpriteList", "AnimatedSprite"); }
template <> inline void DataArray<AnimatedSpriteSetAsset>::InitializeType() { SetNodeNames("AnimatedSpriteSetList", "AnimatedSpriteSet"); }
template <> inline void DataArray<ShaderAsset>::InitializeType() { SetNodeNames("ShaderList", "Shader"); }



template <class T>
inline void DataArray<T>::GenerateIds()
{
	Database::GenerateIds(*this);
}


