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


void Item::SerializeXml( XmlWriter* xml )
{
	xml->SetString("name", name.c_str());
	xml->SetString("script", script.c_str());
	xml->SetString("description", description.c_str());

	xml->BeginNode("Data");
	xml->SetShort("type", type);
	xml->SetShort("subtype", subtype);
	xml->SetInt("price", price);
	xml->EndNode();

	//attributes.SerializeXml(xml);

}


void Item::DeserializeXml( XmlReader* xml )
{
	name = xml->GetString("name");
	script = xml->GetString("script");
	description = xml->GetString("description");

	if( xml->NextChild("Data") )
	{
		type = xml->GetShort("type");
		subtype = xml->GetShort("subtype");
		price = xml->GetInt("price");
		xml->SetToParent();
	}

	//attributes.DeserializeXml(xml);

}

