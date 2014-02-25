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
	/*
	REGISTER_ATTRIBUTE_FACTORY_TYPE(Item);
	REGISTER_ATTRIBUTE(Item, VAR_TYPE_STRING, "name", name);
	REGISTER_ATTRIBUTE(Item, VAR_TYPE_STRING, "script", script);
	REGISTER_ATTRIBUTE(Item, VAR_TYPE_STRING, "description", description);

	PUSH_ATTRIBUTE_NODE(Item, "Data");
	REGISTER_ATTRIBUTE(Item, VAR_TYPE_INT, "type", type);
	REGISTER_ATTRIBUTE(Item, VAR_TYPE_INT, "subtype", subtype);
	REGISTER_ATTRIBUTE(Item, VAR_TYPE_INT, "price", price);
	POP_ATTRIBUTE_NODE(Item);
	*/
}


void Item::SerializeXml( AttributeWriter* f )
{
	f->SetString("name", name.c_str());
	f->SetString("script", script.c_str());
	f->SetString("description", description.c_str());

	f->BeginNode("Data");
	f->SetShort("type", type);
	f->SetShort("subtype", subtype);
	f->SetInt("price", price);
	f->EndNode();

	//SERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);
}


void Item::DeserializeXml( AttributeReader* f )
{
	name = f->GetString("name", name);
	script = f->GetString("script", script);
	description = f->GetString("description", description);

	if( f->NextChild("Data") )
	{
		type = f->GetShort("type");
		subtype = f->GetShort("subtype");
		price = f->GetInt("price");
		f->SetToParent();
	}

	//DESERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);
}



