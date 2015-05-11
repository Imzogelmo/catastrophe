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


#include <Catastrophe/Core/IO/AttributeWriter.h>
#include <Catastrophe/Core/IO/AttributeReader.h>
#include "MonsterData.h"
#include "Serialization.h"


MonsterData::MonsterData() :
	name(),
	script(),
	description(),
	id(0),
	portraitId(0),
	mapSpritesetId(0),
	battleSpritesetId(0),
	lv(1),
	exp(0),
	gold(0),
	attributes(),
	factors()
{
}


void MonsterData::RegisterObject()
{
	/*
	REGISTER_ATTRIBUTE_FACTORY_TYPE(MonsterData);
	REGISTER_ATTRIBUTE(MonsterData, VAR_TYPE_STRING, "name", name);
	REGISTER_ATTRIBUTE(MonsterData, VAR_TYPE_STRING, "script", script);
	REGISTER_ATTRIBUTE(MonsterData, VAR_TYPE_STRING, "description", description);

	PUSH_ATTRIBUTE_NODE(MonsterData, "Data");
	REGISTER_ATTRIBUTE(MonsterData, VAR_TYPE_INT, "lv", lv);
	REGISTER_ATTRIBUTE(MonsterData, VAR_TYPE_INT, "exp", exp);
	REGISTER_ATTRIBUTE(MonsterData, VAR_TYPE_INT, "gold", gold);
	REGISTER_ATTRIBUTE(MonsterData, VAR_TYPE_INT, "portraitId", portraitId);
	REGISTER_ATTRIBUTE(MonsterData, VAR_TYPE_INT, "mapSpritesetId", mapSpritesetId);
	REGISTER_ATTRIBUTE(MonsterData, VAR_TYPE_INT, "battleSpritesetId", battleSpritesetId);
	POP_ATTRIBUTE_NODE(MonsterData);
	*/
}


void MonsterData::Serialize( AttributeWriter* f )
{
	//SERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);
	f->SetString("name", name.CString());
	f->SetString("script", script.CString());
	f->SetString("description", description.CString());

	f->BeginNode("Data");
	f->SetAttribute("lv", lv);
	f->SetAttribute("exp", exp);
	f->SetAttribute("gold", gold);
	f->SetAttribute("portraitId", portraitId);
	f->SetAttribute("mapSpritesetId", mapSpritesetId);
	f->SetAttribute("battleSpritesetId", battleSpritesetId);
	//f->SetAttribute("terrain_id", backgroundId);
	f->EndNode();

	attributes.Serialize(f);
	factors.Serialize(f);
	itemDropset.Serialize(f);
}


void MonsterData::Deserialize( AttributeReader* f )
{
	//DESERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);
	name = f->GetString("name");
	script = f->GetString("script");
	description = f->GetString("description");

	if( f->NextChild("Data") )
	{
		lv = f->GetAttribute("lv", lv);
		exp = f->GetAttribute("exp", exp);
		gold = f->GetAttribute("gold", gold);
		portraitId = f->GetAttribute("portraitId", portraitId);
		mapSpritesetId = f->GetAttribute("mapSpritesetId", mapSpritesetId);
		battleSpritesetId = f->GetAttribute("battleSpritesetId", battleSpritesetId);
		//backgroundId = f->GetAttribute("terrain_id", backgroundId);
		f->SetToParent();
	}

	attributes.Deserialize(f);
	factors.Deserialize(f);
	itemDropset.Deserialize(f);
}


int MonsterData::GetMemoryUsage() const
{
	return (int)description.Capacity();
}


