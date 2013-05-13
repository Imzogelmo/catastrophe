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
#include "BattleCommand.inl"
#include "Item.inl"
#include "Buff.inl"
#include "Skill.inl"
#include "Spell.inl"
#include "Monster.inl"
#include "MonsterTroop.inl"
#include "Encounter.inl"
#include "Race.inl"
#include "CharacterData.inl"
#include "CharacterClass.inl"
#include "ItemDrop.inl"
#include "Level.inl"
#include "ExpTable.inl"
#include "Shops.inl"
#include "Enhancement.inl"
#include "Synthesis.inl"


#include "Database.h"


Database::Database()
{
	items.SetNodeNames("ItemList", "Item");
	skills.SetNodeNames("SkillList", "Skill");
	spells.SetNodeNames("SpellList", "Spell");
	characters.SetNodeNames("CharacterList", "CharacterData");
	classes.SetNodeNames("CharacterClassList", "CharacterClass");
	monsters.SetNodeNames("MonsterList", "Monster");
	troops.SetNodeNames("MonsterTroopList", "MonsterTroop");
	encounters.SetNodeNames("EncounterGroupList", "EncounterGroup");
}


Database::~Database()
{
}


template <class T>
bool Database::SerializeDataArray( T& arr, const fc::string& filename, const char* root, const char* item )
{
	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

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
bool Database::DeserializeDataArray( T& arr, const fc::string& filename, const char* root, const char* item )
{
	XmlReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

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
