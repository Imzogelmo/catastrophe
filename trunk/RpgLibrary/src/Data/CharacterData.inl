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
#include "AttributeSerializer.h"



CharacterData::CharacterData() :
	name(),
	script(),
	description(),
	id(0),
	portrait_id(0),
	map_spriteset_id(0),
	battle_spriteset_id(0),
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
	REGISTER_ATTRIBUTE(CharacterData, VAR_TYPE_INT, "portrait_id", portrait_id);
	REGISTER_ATTRIBUTE(CharacterData, VAR_TYPE_INT, "map_spriteset_id", map_spriteset_id);
	REGISTER_ATTRIBUTE(CharacterData, VAR_TYPE_INT, "battle_spriteset_id", battle_spriteset_id);
	POP_ATTRIBUTE_NODE(CharacterData);
	*/
}


void CharacterData::SerializeXml( AttributeWriter* f )
{
	f->SetString("name", name.c_str());
	f->SetString("script", script.c_str());
	f->SetString("description", description.c_str());

	f->BeginNode("Data");
	f->SetInt("lv", lv);
	f->SetInt("exp", exp);
	f->SetInt("gold", gold);
	f->SetInt("class_id", class_id);
	f->SetInt("portrait_id", portrait_id);
	f->SetInt("map_spriteset_id", map_spriteset_id);
	f->SetInt("battle_spriteset_id", battle_spriteset_id);
	f->EndNode();

	attributes.SerializeXml(f);
}


void CharacterData::DeserializeXml( AttributeReader* f )
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
		portrait_id = f->GetInt("portrait_id", portrait_id);
		map_spriteset_id = f->GetInt("map_spriteset_id", map_spriteset_id);
		battle_spriteset_id = f->GetInt("battle_spriteset_id", battle_spriteset_id);
		f->SetToParent();
	}

	attributes.DeserializeXml(f);
}


int CharacterData::GetMemoryUsage() const
{
	return (int)(description.capacity());
}


