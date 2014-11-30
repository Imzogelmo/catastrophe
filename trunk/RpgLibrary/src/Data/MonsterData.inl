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


#include <Catastrophe/IO/AttributeWriter.h>
#include <Catastrophe/IO/AttributeReader.h>
#include "MonsterData.h"
#include "Serialization.h"
#include "AttributeSerializer.h"


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
	f->SetString("name", name.c_str());
	f->SetString("script", script.c_str());
	f->SetString("description", description.c_str());

	f->BeginNode("Data");
	f->SetInt("lv", lv);
	f->SetInt("exp", exp);
	f->SetInt("gold", gold);
	f->SetUShort("portraitId", portraitId);
	f->SetUShort("mapSpritesetId", mapSpritesetId);
	f->SetUShort("battleSpritesetId", battleSpritesetId);
	f->SetUShort("terrain_id", backgroundId);
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
		lv = f->GetInt("lv", lv);
		exp = f->GetInt("exp", exp);
		gold = f->GetInt("gold", gold);
		portraitId = f->GetUShort("portraitId", portraitId);
		mapSpritesetId = f->GetUShort("mapSpritesetId", mapSpritesetId);
		battleSpritesetId = f->GetUShort("battleSpritesetId", battleSpritesetId);
		backgroundId = f->GetUShort("terrain_id", backgroundId);
		f->SetToParent();
	}

	attributes.Deserialize(f);
	factors.Deserialize(f);
	itemDropset.Deserialize(f);
}


int MonsterData::GetMemoryUsage() const
{
	return (int)description.capacity();
}


