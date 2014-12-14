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
#include "UsageInfo.inl"
#include "Attributes.inl"
#include "AttributeFlags.inl"
#include "Modifier.inl"
#include "BattleCommand.inl"
#include "Item.inl"
#include "EquipmentItem.inl"
#include "Buff.inl"
#include "Ability.inl"
#include "Skill.inl"
#include "Spell.inl"
#include "MonsterData.inl"
#include "MonsterTroop.inl"
#include "MonsterFormation.inl"
#include "Encounter.inl"
#include "Race.inl"
#include "Factor.inl"
#include "CharacterData.inl"
#include "CharacterClass.inl"
#include "ItemDrop.inl"
#include "ItemDropSet.inl"
#include "Level.inl"
#include "ExperienceTable.inl"
#include "Shops.inl"
#include "Enhancement.inl"
#include "Synthesis.inl"
#include "Switches.inl"

#include "DatabaseVariant.inl"
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

	skills.SetResourceDirectory(m_resourceDirectory);
	passiveSkills.SetResourceDirectory(m_resourceDirectory);
	spells.SetResourceDirectory(m_resourceDirectory);

	items.SetResourceDirectory(m_resourceDirectory);
	weapons.SetResourceDirectory(m_resourceDirectory);
	armor.SetResourceDirectory(m_resourceDirectory);
	accessories.SetResourceDirectory(m_resourceDirectory);

	monsters.SetResourceDirectory(m_resourceDirectory);
	monsterTroops.SetResourceDirectory(m_resourceDirectory);
	monsterFormations.SetResourceDirectory(m_resourceDirectory);
	characters.SetResourceDirectory(m_resourceDirectory);
	characterClasses.SetResourceDirectory(m_resourceDirectory);
	races.SetResourceDirectory(m_resourceDirectory);
	factors.SetResourceDirectory(m_resourceDirectory);
	experienceTables.SetResourceDirectory(m_resourceDirectory);

	battleBackgroundSprites.SetResourceDirectory(m_resourceDirectory);
	miscIconSprites.SetResourceDirectory(m_resourceDirectory);
	characterPortraitSprites.SetResourceDirectory(m_resourceDirectory);
	characterMapSprites.SetResourceDirectory(m_resourceDirectory);
	characterBattleSprites.SetResourceDirectory(m_resourceDirectory);
	monsterMapSprites.SetResourceDirectory(m_resourceDirectory);
	monsterBattleSprites.SetResourceDirectory(m_resourceDirectory);
	shaders.SetResourceDirectory(m_resourceDirectory);

	/*
	m_arrayAny.Add(items);
	m_arrayAny.Add(weapons);
	m_arrayAny.Add(armor);
	m_arrayAny.Add(accessories);

	m_arrayAny.Add(monsters);
	m_arrayAny.Add(monsterTroops);
	m_arrayAny.Add(monsterFormations);
	m_arrayAny.Add(characters);
	m_arrayAny.Add(characterClasses);
	m_arrayAny.Add(races);
	m_arrayAny.Add(factors);
	m_arrayAny.Add(experienceTables);

	m_arrayAny.Add(battleBackgroundSprites);
	m_arrayAny.Add(miscIconSprites);
	m_arrayAny.Add(characterPortraitSprites);
	m_arrayAny.Add(characterMapSprites);
	m_arrayAny.Add(characterBattleSprites);
	m_arrayAny.Add(monsterMapSprites);
	m_arrayAny.Add(monsterBattleSprites);
	m_arrayAny.Add(shaders);

	DatabaseArrayAnyHolder::vec_type & v = m_arrayAny.GetVector();
	for( u32 i(0); i < v.size(); ++i )
	{
		v[i]->SetResourceDirectory(m_resourceDirectory);
	}*/
}


void Database::GenerateScriptHeaders()
{
	//todo: cs now...
	GenerateHeader( items, m_resourceDirectory, "Items.cs", "Items" );
	GenerateHeader( weapons, m_resourceDirectory, "Weapons.cs", "Weapons" );
	GenerateHeader( armor, m_resourceDirectory, "Armor.cs", "Armor" );
	GenerateHeader( accessories, m_resourceDirectory, "Accessories.cs", "Accessories" );
	GenerateHeader( monsters, m_resourceDirectory, "Monsters.cs", "Monsters" );
	GenerateHeader( characters, m_resourceDirectory, "Characters.cs", "Characters" );
	GenerateHeader( characterClasses, m_resourceDirectory, "Classes.cs", "CharacterClasses" );
	GenerateHeader( races, m_resourceDirectory, "Races.cs", "Races" );
}


void Database::SetAllDefaultDataArrayFilenames()
{
	skills.SetFilename("Skills.xml");
	passiveSkills.SetFilename("PassiveSkills.xml");
	spells.SetFilename("Spells.xml");

	items.SetFilename("items.xml");
	weapons.SetFilename("weapons.xml");
	armor.SetFilename("armor.xml");
	accessories.SetFilename("accessories.xml");

	monsters.SetFilename("monsters.xml");
	monsterTroops.SetFilename("monster_troops.xml");
	monsterFormations.SetFilename("monster_formations.xml");
	characters.SetFilename("characters.xml");
	characterClasses.SetFilename("character_classes.xml");
	races.SetFilename("races.xml");
	factors.SetFilename("factors.xml");
	experienceTables.SetFilename("ExperienceTables.xml");

	battleBackgroundSprites.SetFilename("BattleBackgroundSprites.xml");
	miscIconSprites.SetFilename("misc_icon_sprites.xml");
	characterPortraitSprites.SetFilename("character_portrait_sprites.xml");
	characterMapSprites.SetFilename("character_map_sprites.xml");
	characterBattleSprites.SetFilename("character_battle_sprites.xml");
	monsterMapSprites.SetFilename("monster_map_sprites.xml");
	monsterBattleSprites.SetFilename("monster_battle_sprites.xml");
	shaders.SetFilename("shaders.xml");

}


void Database::ClearAll()
{
	skills.Clear();
	passiveSkills.Clear();
	spells.Clear();

	items.Clear();
	weapons.Clear();
	armor.Clear();
	accessories.Clear();

	monsters.Clear();
	monsterTroops.Clear();
	monsterFormations.Clear();
	characters.Clear();
	characterClasses.Clear();
	races.Clear();
	factors.Clear();
	experienceTables.Clear();

	battleBackgroundSprites.Clear();
	miscIconSprites.Clear();
	characterPortraitSprites.Clear();
	characterMapSprites.Clear();
	characterBattleSprites.Clear();
	monsterMapSprites.Clear();
	monsterBattleSprites.Clear();
	shaders.Clear();

	/*
	DatabaseArrayAnyHolder::vec_type & v = m_arrayAny.GetVector();
	for( u32 i(0); i < v.size(); ++i )
	{
		v[i]->Clear();
	}*/
}


void Database::SetAllDefaultDataArrayNodeNames()
{
	skills.SetDefaultNodeNames();
	passiveSkills.SetDefaultNodeNames();
	spells.SetDefaultNodeNames();

	items.SetDefaultNodeNames();
	weapons.SetDefaultNodeNames();
	armor.SetDefaultNodeNames();
	accessories.SetDefaultNodeNames();

	monsters.SetDefaultNodeNames();
	monsterTroops.SetDefaultNodeNames();
	monsterFormations.SetDefaultNodeNames();
	characters.SetDefaultNodeNames();
	characterClasses.SetDefaultNodeNames();
	races.SetDefaultNodeNames();
	factors.SetDefaultNodeNames();
	experienceTables.SetDefaultNodeNames();

	battleBackgroundSprites.SetDefaultNodeNames();
	miscIconSprites.SetDefaultNodeNames();
	characterPortraitSprites.SetDefaultNodeNames();
	characterMapSprites.SetDefaultNodeNames();
	characterBattleSprites.SetDefaultNodeNames();
	monsterMapSprites.SetDefaultNodeNames();
	monsterBattleSprites.SetDefaultNodeNames();
	shaders.SetDefaultNodeNames();

	/*
	DatabaseArrayAnyHolder::vec_type & v = m_arrayAny.GetVector();
	for( u32 i(0); i < v.size(); ++i )
	{
		v[i]->SetDefaultNodeNames();
	}*/
}


bool Database::SerializeAllDataXml()
{
	skills.Serialize();
	passiveSkills.Serialize();
	spells.Serialize();

	items.Serialize();
	weapons.Serialize();
	armor.Serialize();
	accessories.Serialize();

	monsters.Serialize();
	monsterTroops.Serialize();
	monsterFormations.Serialize();
	characters.Serialize();
	characterClasses.Serialize();
	races.Serialize();
	factors.Serialize();
	experienceTables.Serialize();

	battleBackgroundSprites.Serialize();
	miscIconSprites.Serialize();
	characterPortraitSprites.Serialize();
	characterMapSprites.Serialize();
	characterBattleSprites.Serialize();
	monsterMapSprites.Serialize();
	monsterBattleSprites.Serialize();
	shaders.Serialize();

	/*
	DatabaseArrayAnyHolder::vec_type & v = m_arrayAny.GetVector();
	for( u32 i(0); i < v.size(); ++i )
	{
		v[i]->Serialize("");
	}*/

	return true;
}


bool Database::DeserializeAllDataXml()
{
	skills.Deserialize();
	passiveSkills.Deserialize();
	spells.Deserialize();

	items.Deserialize();
	weapons.Deserialize();
	armor.Deserialize();
	accessories.Deserialize();

	monsters.Deserialize();
	monsterTroops.Deserialize();
	monsterFormations.Deserialize();
	characters.Deserialize();
	characterClasses.Deserialize();
	races.Deserialize();
	factors.Deserialize();
	experienceTables.Deserialize();

	battleBackgroundSprites.Deserialize();
	miscIconSprites.Deserialize();
	characterPortraitSprites.Deserialize();
	characterMapSprites.Deserialize();
	characterBattleSprites.Deserialize();
	monsterMapSprites.Deserialize();
	monsterBattleSprites.Deserialize();
	shaders.Deserialize();

	/*
	DatabaseArrayAnyHolder::vec_type & v = m_arrayAny.GetVector();
	for( u32 i(0); i < v.size(); ++i )
	{
		v[i]->Deserialize("");
	}*/

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
	u16 size = (u16)arr.size();
	for( u16 i(0); i < size; ++i )
	{
		//id needs to match the indices.
		arr[i].id = i;
	}
}


XmlWriter* SerializeDataArrayBeginImpl
( ResourceDirectory* resourceDirectory, const String& filename, const char* root, u32 size )
{
	String fn = resourceDirectory ? resourceDirectory->GetDataDirectory() : "";
	fn += filename;

	XmlWriter* xml = new XmlWriter(fn);
	if( !xml->IsOpen() )
	{
		delete xml;
		return 0;
	}

	//xml->CreateRoot(root);
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
bool Database::SerializeDataArray( T& arr, ResourceDirectory* resourceDirectory, const String& filename, const char* root, const char* item )
{
	XmlWriter* xml = SerializeDataArrayBeginImpl(resourceDirectory, filename, root, arr.size());
	if( xml )
	{
		for( u32 i(0); i < arr.size(); ++i )
		{
			xml->BeginNode(item);
			arr[i].Serialize(xml);
			xml->EndNode();
		}
	}

	SerializeDataArrayEndImpl(xml);
	return true;

	/*
	String fn = resourceDirectory ? resourceDirectory->GetDataDirectory() : "";
	fn += filename;

	XmlWriter xml(fn);
	if( !xml.IsOpen() )
		return false;

	xml.BeginNode(root);
	xml.SetInt("ver", 1);
	xml.SetUInt("count", arr.size());
	for( u32 i(0); i < arr.size(); ++i )
	{
		xml.BeginNode(item);
		arr[i].Serialize(&xml);
		xml.EndNode();
	}

	xml.EndNode();
	xml.Close();

	return true;
	*/
}


XmlReader* DeserializeDataArrayBeginImpl
( ResourceDirectory* resourceDirectory, const String& filename, const char* root, u32 size )
{
	String fn = resourceDirectory ? resourceDirectory->GetDataDirectory() : "";
	fn += filename;

	XmlReader* xml = new XmlReader(fn);
	if( xml->IsOpen() )
	{
		if( strcmp(xml->GetCurrentNodeNameCStr(), root) == 0 )
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
bool Database::DeserializeDataArray( T& arr, ResourceDirectory* resourceDirectory, const String& filename, const char* root, const char* item )
{
	XmlReader* xml = DeserializeDataArrayBeginImpl(resourceDirectory, filename, root, arr.size());
	if( xml )
	{
		u32 n = xml->GetUInt("count");
		arr.resize(n);
		for( u32 i(0); i < n && xml->NextChild(item); ++i )
		{
			arr[i].Deserialize(xml);
		}
	}

	DeserializeDataArrayEndImpl(xml);
		
	/*	
	String fn = resourceDirectory ? resourceDirectory->GetDataDirectory() : "";
	fn += filename;

	XmlReader xml(fn);
	if( !xml.IsOpen() )
		return false;

	if( xml.GetCurrentNodeName() == root )
	{
		u32 i = 0;
		u32 n = xml.GetUInt("count");
		arr.resize(n);
		while( i < n && xml.NextChild(item) )
		{
			arr[i].Deserialize(&xml);
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
bool Database::GenerateHeader( const Array& arr, ResourceDirectory* resourceDirectory, const String& filename, const String& prependStr )
{
	String fn = resourceDirectory ? resourceDirectory->GetScriptDefineDirectory() : "";
	fn += filename;

	File f;
	if( !f.Open(fn, FileWrite) )
	{
		return false;
	}

	f.WriteLine("");
	f.WriteLine("// !GENERATED FILE - DO NOT HAND EDIT!");
	f.WriteLine("namespace Catastrophe.Rpg");
	f.WriteLine("{");
	f.WriteLine("\tenum " + prependStr);
	f.WriteLine("\t{");

	String name;

	u32 i = 0;
	for( ; i < arr.size(); ++i )
	{
		name = "\t\t";
		name += arr[i].name.c_str();

		// TODO: just remove anything not a valid char
		name.erase( fc::remove(name.begin(), name.end(), '\''), name.end() );
		name.erase( fc::remove(name.begin(), name.end(), '\"'), name.end() );
		name.erase( fc::remove(name.begin(), name.end(), ' '), name.end() );

		//name += " = ";
		//name.append_int(i);
		name += ',';

		f.WriteLine(name);
	}

	// finish by writing the maximum valid indices to this array.
	f.WriteLine("\tMax");
	f.WriteLine("}");

	f.WriteLine("");
	f.Close();

	return true;
}

/*
template <class Array>
bool Database::GenerateHeader( const Array& arr, ResourceDirectory* resourceDirectory, const String& filename, const String& prependStr )
{
	String fn = resourceDirectory ? resourceDirectory->GetScriptDefineDirectory() : "";
	fn += filename;

	File f;
	if( !f.Open(fn, FileWrite) )
	{
		return false;
	}

	f.WriteLine("");
	f.WriteLine("// !GENERATED FILE - DO NOT HAND EDIT!");
	f.WriteLine("");
	f.WriteLine("#pragma once");
	f.WriteLine("");

	String str;
	String name;

	u32 i = 0;
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
*/

int Database::GetMemoryUsage() const
{
	return (int)
	(
		sizeof(Database) +

		skills.GetMemoryUsage() +
		passiveSkills.GetMemoryUsage() +
		spells.GetMemoryUsage() +

		items.GetMemoryUsage() +
		weapons.GetMemoryUsage() +
		armor.GetMemoryUsage() +
		accessories.GetMemoryUsage() +

		monsters.GetMemoryUsage() +
		monsterTroops.GetMemoryUsage() +
		monsterFormations.GetMemoryUsage() +
		characters.GetMemoryUsage() +
		characterClasses.GetMemoryUsage() +
		races.GetMemoryUsage() +
		factors.GetMemoryUsage() +
		experienceTables.GetMemoryUsage() +

		battleBackgroundSprites.GetMemoryUsage() +
		miscIconSprites.GetMemoryUsage() +
		characterPortraitSprites.GetMemoryUsage() +
		characterMapSprites.GetMemoryUsage() +
		characterBattleSprites.GetMemoryUsage() +
		monsterMapSprites.GetMemoryUsage() +
		monsterBattleSprites.GetMemoryUsage() +
		shaders.GetMemoryUsage()
	);

}


void Database::LogMemoryUsage() const
{
	LogInfo("[Database memory usage statistics (kilobytes)]");

	LogInfo("    Database total memory usage [%.2f]", GetMemoryUsage() / 1024.f);

	LogInfo("    Skills         [%.2f]", skills.GetMemoryUsage() / 1024.f);
	LogInfo("    Passive Skills [%.2f]", passiveSkills.GetMemoryUsage() / 1024.f);
	LogInfo("    Spells         [%.2f]", spells.GetMemoryUsage() / 1024.f);
	LogInfo("    Items          [%.2f]", items.GetMemoryUsage() / 1024.f);
	LogInfo("    Weapons        [%.2f]", weapons.GetMemoryUsage() / 1024.f);
	LogInfo("    Armor          [%.2f]", armor.GetMemoryUsage() / 1024.f);
	LogInfo("    Accessories    [%.2f]", accessories.GetMemoryUsage() / 1024.f);
	LogInfo("    Monsters       [%.2f]", monsters.GetMemoryUsage() / 1024.f);
	LogInfo("    Troops         [%.2f]", monsterTroops.GetMemoryUsage() / 1024.f);
	LogInfo("    Formations     [%.2f]", monsterFormations.GetMemoryUsage() / 1024.f);
	LogInfo("    Characters     [%.2f]", characters.GetMemoryUsage() / 1024.f);
	LogInfo("    Classes        [%.2f]", characterClasses.GetMemoryUsage() / 1024.f);
	LogInfo("    Races          [%.2f]", races.GetMemoryUsage() / 1024.f);
	LogInfo("    Factors        [%.2f]", factors.GetMemoryUsage() / 1024.f);
	LogInfo("    ExpTables      [%.2f]", experienceTables.GetMemoryUsage() / 1024.f);

	LogInfo("    Battle Background Sprites  [%.2f]", battleBackgroundSprites.GetMemoryUsage() / 1024.f);
	LogInfo("    Mmisc Icon Sprites         [%.2f]", miscIconSprites.GetMemoryUsage() / 1024.f);
	LogInfo("    Character portrait sprites [%.2f]", characterPortraitSprites.GetMemoryUsage() / 1024.f);
	LogInfo("    Character map sprites      [%.2f]", characterMapSprites.GetMemoryUsage() / 1024.f);
	LogInfo("    Character battle sprites   [%.2f]", characterBattleSprites.GetMemoryUsage() / 1024.f);
	//LogInfo("    Monster portrait sprites   [%.2f]", monsterPortraitSprites.GetMemoryUsage() / 1024.f);
	LogInfo("    Monster map sprites        [%.2f]", monsterMapSprites.GetMemoryUsage() / 1024.f);
	LogInfo("    Monster battle sprites     [%.2f]", monsterBattleSprites.GetMemoryUsage() / 1024.f);
	LogInfo("    Shader data [%.2f]", shaders.GetMemoryUsage() / 1024.f);

}
