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


void Item::Serialize( AttributeWriter* f )
{
	f->SetString("name", name.c_str());
	f->SetString("script", script.c_str());
	f->SetString("description", description);

	f->BeginNode("Data");
	f->SetShort("type", type);
	f->SetShort("subtype", subtype);
	f->SetInt("price", price);

	factors.Serialize(f);

	f->EndNode();
}


void Item::Deserialize( AttributeReader* f )
{
	name = f->GetString("name", name.c_str());
	script = f->GetString("script", script.c_str());
	description = f->GetString("description", description.c_str());

	if( f->NextChild("Data") )
	{
		type = f->GetShort("type");
		subtype = f->GetShort("subtype");
		price = f->GetInt("price");

		factors.Deserialize(f);

		f->SetToParent();
	}
}


int Item::GetMemoryUsage() const
{
	return (int)description.capacity();
}

