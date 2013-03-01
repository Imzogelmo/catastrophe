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
#include "TileProperties.h"
#include "Serialization.h"



TileProperties::TileProperties() :
	flags(0),
	terrain(0),
	encounter(0)
{
}


void TileProperties::SerializeXml( XmlWriter* xml )
{
	xml->SetInt("flags", flags);
	xml->SetShort("terrain", terrain);
	xml->SetShort("encounter", encounter);

}


void TileProperties::DeserializeXml( XmlReader* xml )
{
	flags = xml->GetInt("flags");
	terrain = xml->GetShort("terrain");
	encounter = xml->GetShort("encounter");

}


