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
#include "Race.h"
#include "Serialization.h"



Race::Race() :
	id(0)
{
}


void Race::SerializeXml( XmlWriter* xml )
{
	xml->SetString("name", name.c_str());
	xml->SetString("description", description.c_str());

	attributes.SerializeXml(xml);

}


void Race::DeserializeXml( XmlReader* xml )
{
	name = xml->GetString("name");
	description = xml->GetString("description");

	attributes.DeserializeXml(xml);

}


