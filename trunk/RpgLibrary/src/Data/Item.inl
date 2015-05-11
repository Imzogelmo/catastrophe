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

#include <Catastrophe/Core/IO/AttributeWriter.h>
#include <Catastrophe/Core/IO/AttributeReader.h>
#include "Item.h"

Attributes Item::m_staticAttributes = Attributes();


Item::Item() :
	name(),
	//script(),
	description(),
	type(0),
	subtype(0),
	id(0),
	price(1)
{
}


void Item::Serialize( AttributeWriter* f )
{
	f->SetString("name", name.CString());
	//f->SetString("script", script.CString());
	f->SetString("description", description);

	f->BeginNode("Data");
	{
		f->SetAttribute("type", type);
		f->SetAttribute("subtype", subtype);
		f->SetAttribute("price", price);

		factors.Serialize(f);
	}
	f->EndNode();
}


void Item::Deserialize( AttributeReader* f )
{
	name = f->GetString("name", name.CString());
	//script = f->GetString("script", script.CString());
	description = f->GetString("description", description.CString());

	if( f->NextChild("Data") )
	{
		f->GetAttribute("type", type);
		f->GetAttribute("subtype", subtype);
		f->GetAttribute("price", price);

		factors.Deserialize(f);

		f->SetToParent();
	}
}


int Item::GetMemoryUsage() const
{
	return (int)description.Capacity();
}

