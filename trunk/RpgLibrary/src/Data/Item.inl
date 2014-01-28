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
#include "Item.h"
#include "AttributeSerializer.h"

Attributes Item::m_static_attributes = Attributes();


Item::Item() :
	name(),
	script(),
	description(),
	type(0),
	subtype(0),
	id(0),
	price(1)
{
}


void Item::RegisterObject()
{
	REGISTER_ATTRIBUTE_FACTORY_TYPE(Item);
	REGISTER_ATTRIBUTE(Item, VAR_TYPE_STRING, "name", name);
	REGISTER_ATTRIBUTE(Item, VAR_TYPE_STRING, "script", script);
	REGISTER_ATTRIBUTE(Item, VAR_TYPE_STRING, "description", description);

	PUSH_ATTRIBUTE_NODE(Item, "Data");
	REGISTER_ATTRIBUTE(Item, VAR_TYPE_INT, "type", type);
	REGISTER_ATTRIBUTE(Item, VAR_TYPE_INT, "subtype", subtype);
	REGISTER_ATTRIBUTE(Item, VAR_TYPE_INT, "price", price);
	POP_ATTRIBUTE_NODE(Item);
}


void Item::SerializeXml( XmlWriter* xml )
{
	SERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);
}


void Item::DeserializeXml( XmlReader* xml )
{
	DESERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);
}


void Item::Serialize( Serializer* f )
{
	SERIALIZE_OBJECT_ATTRIBUTES(this, f);
}


void Item::Deserialize( Deserializer* f )
{
	DESERIALIZE_OBJECT_ATTRIBUTES(this, f);
}


