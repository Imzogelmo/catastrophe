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

Attributes Item::m_staticAttributes = Attributes();


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


int Item::GetMemoryUsage() const
{
	return (int)description.capacity();
}

