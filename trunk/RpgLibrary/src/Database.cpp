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

// these are not actually 'inlined'.

// data
#include "Attributes.inl"
#include "AttributeFlags.inl"
#include "Modifier.inl"
#include "BattleCommand.inl"
#include "Item.inl"
#include "EquipmentItem.inl"
#include "Buff.inl"
#include "Skill.inl"
#include "Spell.inl"
#include "MonsterData.inl"
#include "MonsterTroop.inl"
#include "Encounter.inl"
#include "Race.inl"
#include "CharacterData.inl"
#include "CharacterClass.inl"
#include "ItemDrop.inl"
#include "ItemDropSet.inl"
#include "Level.inl"
#include "ExpTable.inl"
#include "Shops.inl"
#include "Enhancement.inl"
#include "Synthesis.inl"

#include "StringAlias.inl"

#include "Database.h"
#include "ResourceDirectory.h"


Database::Database() :
	m_resourceDirectory(0)
{
	// these must always be called on init.
	SetAllDefaultDataArrayFilenames();
	SetAllDefaultDataArrayNodeNames();

}


Database::~Database()
{
}


void Database::Initialize()
{
	m_resourceDirectory = g_resourceDirectory;

	items.SetResourceDirectory(m_resourceDirectory);
	weapons.SetResourceDirectory(m_resourceDirectory);
	armor.SetResourceDirectory(m_resourceDirectory);
	accessories.SetResourceDirectory(m_resourceDirectory);

	monsters.SetResourceDirectory(m_resourceDirectory);
	monster_troops.SetResourceDirectory(m_resourceDirectory);
	characters.SetResourceDirectory(m_resourceDirectory);
	character_classes.SetResourceDirectory(m_resourceDirectory);
	races.SetResourceDirectory(m_resourceDirectory);

	character_map_sprites.SetResourceDirectory(m_resourceDirectory);
	character_battle_sprites.SetResourceDirectory(m_resourceDirectory);
	monster_map_sprites.SetResourceDirectory(m_resourceDirectory);
	monster_battle_sprites.SetResourceDirectory(m_resourceDirectory);
}


void Database::ClearAll()
{
	items.clear();
	weapons.clear();
	armor.clear();
	accessories.clear();

	monsters.clear();
	monster_troops.clear();
	characters.clear();
	character_classes.clear();
	races.clear();


	character_map_sprites.clear();
	character_battle_sprites.clear();
	monster_map_sprites.clear();
	monster_battle_sprites.clear();

}


void Database::SetAllDefaultDataArrayFilenames()
{
	items.SetFileame("items.xml");
	weapons.SetFileame("weapons.xml");
	armor.SetFileame("armor.xml");
	accessories.SetFileame("accessories.xml");

	monsters.SetFileame("monsters.xml");
	monster_troops.SetFileame("monster_troops.xml");
	characters.SetFileame("characters.xml");
	character_classes.SetFileame("character_classes.xml");
	races.SetFileame("races.xml");

	character_map_sprites.SetFileame("character_map_sprites.xml");
	character_battle_sprites.SetFileame("character_battle_sprites.xml");
	monster_map_sprites.SetFileame("monster_map_sprites.xml");
	monster_battle_sprites.SetFileame("monster_battle_sprites.xml");

}


void Database::SetAllDefaultDataArrayNodeNames()
{
	/*
	skills.SetNodeNames("SkillList", "Skill");
	spells.SetNodeNames("SpellList", "Spell");
	encounters.SetNodeNames("EncounterGroupList", "EncounterGroup");
	*/

	items.SetNodeNames("ItemList", "Item");
	weapons.SetNodeNames("ItemList", "Item");
	armor.SetNodeNames("ItemList", "Item");
	accessories.SetNodeNames("ItemList", "Item");

	monsters.SetNodeNames("MonsterList", "Monster");
	monster_troops.SetNodeNames("MonsterTroopList", "MonsterTroop");
	characters.SetNodeNames("CharacterList", "Character");
	character_classes.SetNodeNames("CharacterClassList", "CharacterClass");
	races.SetNodeNames("RaceList", "Race");

	character_map_sprites.SetNodeNames("AnimatedSpriteSetList", "AnimatedSpriteSet");
	character_battle_sprites.SetNodeNames("AnimatedSpriteSetList", "AnimatedSpriteSet");
	monster_map_sprites.SetNodeNames("AnimatedSpriteSetList", "AnimatedSpriteSet");
	monster_battle_sprites.SetNodeNames("AnimatedSpriteSetList", "AnimatedSpriteSet");

}


bool Database::SerializeAllDataXml()
{
	items.SerializeXml("");
	weapons.SerializeXml("");
	armor.SerializeXml("");
	accessories.SerializeXml("");

	monsters.SerializeXml("");
	monster_troops.SerializeXml("");
	characters.SerializeXml("");
	character_classes.SerializeXml("");
	races.SerializeXml("");


	character_map_sprites.SerializeXml("");
	character_battle_sprites.SerializeXml("");
	monster_map_sprites.SerializeXml("");
	monster_battle_sprites.SerializeXml("");

	return true;
}


bool Database::DeserializeAllDataXml()
{
	items.DeserializeXml("");
	weapons.DeserializeXml("");
	armor.DeserializeXml("");
	accessories.DeserializeXml("");

	monsters.DeserializeXml("");
	monster_troops.DeserializeXml("");
	characters.DeserializeXml("");
	character_classes.DeserializeXml("");
	races.DeserializeXml("");


	character_map_sprites.DeserializeXml("");
	character_battle_sprites.DeserializeXml("");
	monster_map_sprites.DeserializeXml("");
	monster_battle_sprites.DeserializeXml("");

	return true;
}


void Database::SetResourceDirectory( ResourceDirectory* resourceDirectory )
{
	m_resourceDirectory = resourceDirectory;
}


ResourceDirectory* Database::GetResourceDirectory() const
{
	return m_resourceDirectory;
}


template <class T>
void Database::GenerateIds( T& arr )
{
	int size = (int)arr.size();
	for( int i(0); i < size; ++i )
	{
		//id needs to match the indices.
		arr[i].id = i;
	}
}


template <class T>
bool Database::SerializeDataArray( T& arr, ResourceDirectory* resourceDirectory, const fc::string& filename, const char* root, const char* item )
{
	fc::string fn = resourceDirectory ? resourceDirectory->GetDataDirectory() : "";
	fn += filename;

	XmlWriter xml(fn);
	if( !xml.IsOpen() )
		return false;

	xml.BeginNode(root);
	xml.SetUInt("count", arr.size());
	for( size_t i(0); i < arr.size(); ++i )
	{
		xml.BeginNode(item);
		arr[i].SerializeXml(&xml);
		xml.EndNode();
	}

	xml.EndNode();
	xml.Close();

	return true;
}


template <class T>
bool Database::DeserializeDataArray( T& arr, ResourceDirectory* resourceDirectory, const fc::string& filename, const char* root, const char* item )
{
	fc::string fn = resourceDirectory ? resourceDirectory->GetDataDirectory() : "";
	fn += filename;

	XmlReader xml(fn);
	if( !xml.IsOpen() )
		return false;

	if( xml.GetCurrentNodeName() == root )
	{
		size_t i = 0;
		size_t n = xml.GetUInt("count");
		arr.resize(n);
		while( i < n && xml.NextChild(item) )
		{
			arr[i].DeserializeXml(&xml);
			i++;
		}
	}
	else
	{
		Log("Error parsing (%s). Root item not found", filename.c_str());
		return false;
	}

	xml.Close();

	return true;
}
