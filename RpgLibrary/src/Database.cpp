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

#include <fc/search.h>
#include <fc/copy.h>

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
#include "MonsterFormation.inl"
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
#include "Switches.inl"

#include "StringAlias.inl"

#include "Database.h"
#include "ResourceDirectory.h"

#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/IO/XmlReader.h>


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

	m_arrayAny.Add(items);
	m_arrayAny.Add(weapons);
	m_arrayAny.Add(armor);
	m_arrayAny.Add(accessories);

	m_arrayAny.Add(monsters);
	m_arrayAny.Add(monster_troops);
	m_arrayAny.Add(monster_formations);
	m_arrayAny.Add(characters);
	m_arrayAny.Add(character_classes);
	m_arrayAny.Add(races);

	m_arrayAny.Add(character_portrait_sprites);
	m_arrayAny.Add(character_map_sprites);
	m_arrayAny.Add(character_battle_sprites);
	m_arrayAny.Add(monster_map_sprites);
	m_arrayAny.Add(monster_battle_sprites);
	m_arrayAny.Add(shaders);

	DatabaseArrayAnyHolder::vec_type & v = m_arrayAny.GetVector();
	for( size_t i(0); i < v.size(); ++i )
	{
		v[i]->SetResourceDirectory(m_resourceDirectory);
	}
}


void Database::GenerateScriptHeaders()
{
	GenerateHeader( items, m_resourceDirectory, "items.h", "ITEM_" );
	GenerateHeader( weapons, m_resourceDirectory, "weapons.h", "WEAPON_" );
	GenerateHeader( armor, m_resourceDirectory, "armor.h", "ARMOR_" );
	GenerateHeader( accessories, m_resourceDirectory, "accessories.h", "ACCESSORY_" );
	GenerateHeader( monsters, m_resourceDirectory, "monsters.h", "MONSTER_" );
	GenerateHeader( characters, m_resourceDirectory, "characters.h", "CHARACTER_" );
	GenerateHeader( character_classes, m_resourceDirectory, "classes.h", "CLASS_" );
	GenerateHeader( races, m_resourceDirectory, "races.h", "RACE_" );
}


void Database::SetAllDefaultDataArrayFilenames()
{
	items.SetFilename("items.xml");
	weapons.SetFilename("weapons.xml");
	armor.SetFilename("armor.xml");
	accessories.SetFilename("accessories.xml");

	monsters.SetFilename("monsters.xml");
	monster_troops.SetFilename("monster_troops.xml");
	monster_formations.SetFilename("monster_formations.xml");
	characters.SetFilename("characters.xml");
	character_classes.SetFilename("character_classes.xml");
	races.SetFilename("races.xml");

	character_portrait_sprites.SetFilename("character_portrait_sprites.xml");
	character_map_sprites.SetFilename("character_map_sprites.xml");
	character_battle_sprites.SetFilename("character_battle_sprites.xml");
	monster_map_sprites.SetFilename("monster_map_sprites.xml");
	monster_battle_sprites.SetFilename("monster_battle_sprites.xml");
	shaders.SetFilename("shaders.xml");

}


void Database::ClearAll()
{
	DatabaseArrayAnyHolder::vec_type & v = m_arrayAny.GetVector();
	for( size_t i(0); i < v.size(); ++i )
	{
		v[i]->Clear();
	}
}


void Database::SetAllDefaultDataArrayNodeNames()
{
	DatabaseArrayAnyHolder::vec_type & v = m_arrayAny.GetVector();
	for( size_t i(0); i < v.size(); ++i )
	{
		v[i]->SetDefaultNodeNames();
	}
}


bool Database::SerializeAllDataXml()
{
	DatabaseArrayAnyHolder::vec_type & v = m_arrayAny.GetVector();
	for( size_t i(0); i < v.size(); ++i )
	{
		v[i]->SerializeXml("");
	}

	return true;
}


bool Database::DeserializeAllDataXml()
{
	DatabaseArrayAnyHolder::vec_type & v = m_arrayAny.GetVector();
	for( size_t i(0); i < v.size(); ++i )
	{
		v[i]->DeserializeXml("");
	}

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


XmlWriter* SerializeDataArrayBeginImpl
( ResourceDirectory* resourceDirectory, const fc::string& filename, const char* root, size_t size )
{
	fc::string fn = resourceDirectory ? resourceDirectory->GetDataDirectory() : "";
	fn += filename;

	XmlWriter* xml = new XmlWriter(fn);
	if( !xml->IsOpen() )
	{
		delete xml;
		return 0;
	}

	xml->BeginNode(root);
	xml->SetInt("ver", 1);
	xml->SetUInt("count", size);

	return xml;
}


void SerializeDataArrayEndImpl( XmlWriter* xml )
{
	if( xml )
	{
		xml->EndNode();
		xml->Close();
		delete xml;
	}
}


template <class T>
bool Database::SerializeDataArray( T& arr, ResourceDirectory* resourceDirectory, const fc::string& filename, const char* root, const char* item )
{
	XmlWriter* xml = SerializeDataArrayBeginImpl(resourceDirectory, filename, root, arr.size());
	if( xml )
	{
		for( size_t i(0); i < arr.size(); ++i )
		{
			xml->BeginNode(item);
			arr[i].SerializeXml(xml);
			xml->EndNode();
		}
	}

	SerializeDataArrayEndImpl(xml);
	return true;

	/*
	fc::string fn = resourceDirectory ? resourceDirectory->GetDataDirectory() : "";
	fn += filename;

	XmlWriter xml(fn);
	if( !xml.IsOpen() )
		return false;

	xml.BeginNode(root);
	xml.SetInt("ver", 1);
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
	*/
}


XmlReader* DeserializeDataArrayBeginImpl
( ResourceDirectory* resourceDirectory, const fc::string& filename, const char* root, size_t size )
{
	fc::string fn = resourceDirectory ? resourceDirectory->GetDataDirectory() : "";
	fn += filename;

	XmlReader* xml = new XmlReader(fn);
	if( xml->IsOpen() )
	{
		if( xml->GetCurrentNodeName() == root )
			return xml;

		else
		{
			Log("Error parsing (%s). Root item not found", filename.c_str());
		}
	}

	// failure.
	delete xml;
	return 0;
}


void DeserializeDataArrayEndImpl( XmlReader* xml )
{
	if( xml )
	{
		xml->Close();
		delete xml;
	}
}


template <class T>
bool Database::DeserializeDataArray( T& arr, ResourceDirectory* resourceDirectory, const fc::string& filename, const char* root, const char* item )
{
	XmlReader* xml = DeserializeDataArrayBeginImpl(resourceDirectory, filename, root, arr.size());
	if( xml )
	{
		size_t n = xml->GetUInt("count");
		arr.resize(n);
		for( size_t i(0); i < n && xml->NextChild(item); ++i )
		{
			arr[i].DeserializeXml(xml);
		}
	}

	DeserializeDataArrayEndImpl(xml);
		
	/*	
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
	*/

	return true;
}


//
// this whole thing is a WIP.
//
template <class Array>
bool Database::GenerateHeader( const Array& arr, ResourceDirectory* resourceDirectory, const fc::string& filename, const fc::string& prependStr )
{
	fc::string fn = resourceDirectory ? resourceDirectory->GetScriptDefineDirectory() : "";
	fn += filename;

	File f;
	if( !f.Open(fn, FileWrite) )
	{
		return false;
	}

	f.WriteLine("");
	f.WriteLine("/* !GENERATED FILE - DO NOT HAND EDIT! */");
	f.WriteLine("");
	f.WriteLine("#pragma once");
	f.WriteLine("");

	fc::string str;
	fc::string name;

	size_t i = 0;
	for( ; i < arr.size(); ++i )
	{
		str = "#define " + prependStr;
		name = arr[i].name;

		// replace spaces with underscores.
		fc::replace(name.begin(), name.end(), ' ', '_');

		// TODO: just remove anything not a valid char
		name.erase( fc::remove(name.begin(), name.end(), '\''), name.end() );
		name.erase( fc::remove(name.begin(), name.end(), '\"'), name.end() );

		name.make_upper();
		str.append(name);

		// add whitespace and id.
		str.append(40 - str.size(), ' ');
		str.append_int(i);

		f.WriteLine(str);
	}

	// finish by writing the maximum valid indices to this array.
	str = "#define " + prependStr + "MAX";
	str.append(40 - str.size(), ' ');
	str.append_int(i);
	f.WriteLine(str);

	f.WriteLine("");
	f.Close();

	return true;
}

