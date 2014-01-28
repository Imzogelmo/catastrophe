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


#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/IO/XmlReader.h>
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
}


void CharacterData::SerializeXml( XmlWriter* xml )
{
	SERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);

	attributes.SerializeXml(xml);
}


void CharacterData::DeserializeXml( XmlReader* xml )
{
	DESERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);

	attributes.DeserializeXml(xml);
}


void CharacterData::Serialize( Serializer* f )
{
	SERIALIZE_OBJECT_ATTRIBUTES(this, f);
}


void CharacterData::Deserialize( Deserializer* f )
{
	DESERIALIZE_OBJECT_ATTRIBUTES(this, f);
}



