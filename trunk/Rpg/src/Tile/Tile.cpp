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
#include "../Util/Serialization.h"
#include "Tile.h"


void Tile::SerializeXml( XmlWriter* xml )
{
	xml->SetInt("flags", flags);

	xml->BeginNode("Animation");
	Util::SerializeAnimation(xml, *this);
	xml->EndNode();
}


void Tile::DeserializeXml( XmlReader* xml )
{
	flags = xml->GetInt("flags");
	if( xml->NextChild("Animation") )
	{
		Util::DeserializeAnimation(xml, *this);
		xml->SetToParent();
	}
}

