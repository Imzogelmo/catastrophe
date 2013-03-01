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
#include "Recipe.h"
#include "Serialization.h"



Recipe::Recipe() :
	id(0)
{
}


void Recipe::SerializeXml( XmlWriter* xml )
{
	xml->SetString("name", name.c_str());
	xml->SetUInt("count", reagents.size());

	for( size_t i(0); i < reagents.size(); ++i )
	{
		reagents[i].Serialize(xml);
	}
}


void Recipe::DeserializeXml( XmlReader* xml )
{
	name = xml->GetString("name");
	name = xml->GetUInt("count");


}


