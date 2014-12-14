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
#include "CharacterClass.h"
#include "Serialization.h"



CharacterClass::CharacterClass() :
	name(),
	script(),
	description(),
	id(0),
	portraitId(0),
	mapSpritesetId(0),
	battleSpritesetId(0),
	exp_table_id(0),
	attributes()
{
}


void CharacterClass::RegisterObject()
{
	/*
	REGISTER_ATTRIBUTE_FACTORY_TYPE(CharacterClass);
	REGISTER_ATTRIBUTE(CharacterClass, VAR_TYPE_STRING, "name", name);
	REGISTER_ATTRIBUTE(CharacterClass, VAR_TYPE_STRING, "script", script);
	REGISTER_ATTRIBUTE(CharacterClass, VAR_TYPE_STRING, "description", description);

	PUSH_ATTRIBUTE_NODE(CharacterClass, "Data");
	REGISTER_ATTRIBUTE(CharacterClass, VAR_TYPE_INT, "portraitId", portraitId);
	REGISTER_ATTRIBUTE(CharacterClass, VAR_TYPE_INT, "mapSpritesetId", mapSpritesetId);
	REGISTER_ATTRIBUTE(CharacterClass, VAR_TYPE_INT, "battleSpritesetId", battleSpritesetId);
	POP_ATTRIBUTE_NODE(CharacterClass);
	*/
}


void CharacterClass::Serialize( AttributeWriter* f )
{
	//SERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);

	f->SetString("name", name.c_str());
	f->SetString("script", script.c_str());
	f->SetString("description", description.c_str());

	f->BeginNode("Data");
	f->SetInt("portraitId", portraitId);
	f->SetInt("mapSpritesetId", portraitId);
	f->SetInt("battleSpritesetId", portraitId);
	f->EndNode();

	attributes.Serialize(f);

}


void CharacterClass::Deserialize( AttributeReader* f )
{
	//DESERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);

	name = f->GetString("name");
	script = f->GetString("script");
	description = f->GetString("description");

	if( f->NextChild("Data") )
	{
		portraitId = f->GetInt("portraitId", portraitId);
		mapSpritesetId = f->GetInt("mapSpritesetId", mapSpritesetId);
		battleSpritesetId = f->GetInt("battleSpritesetId", battleSpritesetId);
		f->SetToParent();
	}

	attributes.Deserialize(f);

}


int CharacterClass::GetMemoryUsage() const
{
	return (int)(description.capacity());
}

