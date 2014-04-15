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
	portrait_id(0),
	map_spriteset_id(0),
	battle_spriteset_id(0),
	exp_table_id(0),
	attributes()
{
}


void CharacterClass::RegisterObject()
{
	REGISTER_ATTRIBUTE_FACTORY_TYPE(CharacterClass);
	REGISTER_ATTRIBUTE(CharacterClass, VAR_TYPE_STRING, "name", name);
	REGISTER_ATTRIBUTE(CharacterClass, VAR_TYPE_STRING, "script", script);
	REGISTER_ATTRIBUTE(CharacterClass, VAR_TYPE_STRING, "description", description);

	PUSH_ATTRIBUTE_NODE(CharacterClass, "Data");
	REGISTER_ATTRIBUTE(CharacterClass, VAR_TYPE_INT, "portrait_id", portrait_id);
	REGISTER_ATTRIBUTE(CharacterClass, VAR_TYPE_INT, "map_spriteset_id", map_spriteset_id);
	REGISTER_ATTRIBUTE(CharacterClass, VAR_TYPE_INT, "battle_spriteset_id", battle_spriteset_id);
	POP_ATTRIBUTE_NODE(CharacterClass);
}


void CharacterClass::SerializeXml( AttributeWriter* f )
{
	//SERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);

	f->SetString("name", name.c_str());
	f->SetString("script", script.c_str());
	f->SetString("description", description.c_str());

	f->BeginNode("Data");
	f->SetInt("portrait_id", portrait_id);
	f->SetInt("map_spriteset_id", portrait_id);
	f->SetInt("battle_spriteset_id", portrait_id);
	f->EndNode();

	attributes.SerializeXml(f);

}


void CharacterClass::DeserializeXml( AttributeReader* f )
{
	//DESERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);

	name = f->GetString("name");
	script = f->GetString("script");
	description = f->GetString("description");

	if( f->NextChild("Data") )
	{
		portrait_id = f->GetInt("portrait_id", portrait_id);
		map_spriteset_id = f->GetInt("map_spriteset_id", map_spriteset_id);
		battle_spriteset_id = f->GetInt("battle_spriteset_id", battle_spriteset_id);
		f->SetToParent();
	}

	attributes.DeserializeXml(f);

}


int CharacterClass::GetMemoryUsage() const
{
	return (int)(description.capacity());
}

