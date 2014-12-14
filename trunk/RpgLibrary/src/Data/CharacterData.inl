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
#include "CharacterData.h"



CharacterData::CharacterData() :
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
	attributes()
{
}


void CharacterData::RegisterObject()
{
	/*
	REGISTER_ATTRIBUTE_FACTORY_TYPE(CharacterData);
	REGISTER_ATTRIBUTE(CharacterData, VAR_TYPE_STRING, "name", name);
	REGISTER_ATTRIBUTE(CharacterData, VAR_TYPE_STRING, "script", script);
	REGISTER_ATTRIBUTE(CharacterData, VAR_TYPE_STRING, "description", description);

	PUSH_ATTRIBUTE_NODE(CharacterData, "Data");
	REGISTER_ATTRIBUTE(CharacterData, VAR_TYPE_INT, "lv", lv);
	REGISTER_ATTRIBUTE(CharacterData, VAR_TYPE_INT, "exp", exp);
	REGISTER_ATTRIBUTE(CharacterData, VAR_TYPE_INT, "gold", gold);
	REGISTER_ATTRIBUTE(CharacterData, VAR_TYPE_INT, "class_id", class_id);
	REGISTER_ATTRIBUTE(CharacterData, VAR_TYPE_INT, "portraitId", portraitId);
	REGISTER_ATTRIBUTE(CharacterData, VAR_TYPE_INT, "mapSpritesetId", mapSpritesetId);
	REGISTER_ATTRIBUTE(CharacterData, VAR_TYPE_INT, "battleSpritesetId", battleSpritesetId);
	POP_ATTRIBUTE_NODE(CharacterData);
	*/
}


void CharacterData::Serialize( AttributeWriter* f )
{
	f->SetString("name", name.c_str());
	f->SetString("script", script.c_str());
	f->SetString("description", description.c_str());

	f->BeginNode("Data");
	f->SetInt("lv", lv);
	f->SetInt("exp", exp);
	f->SetInt("gold", gold);
	f->SetInt("class_id", class_id);
	f->SetInt("portraitId", portraitId);
	f->SetInt("mapSpritesetId", mapSpritesetId);
	f->SetInt("battleSpritesetId", battleSpritesetId);
	f->EndNode();

	attributes.Serialize(f);
}


void CharacterData::Deserialize( AttributeReader* f )
{
	name = f->GetString("name");
	script = f->GetString("script");
	description = f->GetString("description");
	
	if( f->NextChild("Data") )
	{
		lv = f->GetInt("lv", lv);
		exp = f->GetInt("exp", exp);
		gold = f->GetInt("gold", gold);
		class_id = f->GetInt("class_id", class_id);
		portraitId = f->GetInt("portraitId", portraitId);
		mapSpritesetId = f->GetInt("mapSpritesetId", mapSpritesetId);
		battleSpritesetId = f->GetInt("battleSpritesetId", battleSpritesetId);
		f->SetToParent();
	}

	attributes.Deserialize(f);
}


int CharacterData::GetMemoryUsage() const
{
	return (int)(description.capacity());
}


