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
#include "MonsterFormation.h"
#include "Serialization.h"



MonsterFormationCellData::MonsterFormationCellData() :
	x(0),
	y(0)
{
}


MonsterFormationCellData::MonsterFormationCellData( short x, short y ) :
	x(x),
	y(y)
{
}


void MonsterFormationCellData::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Cell");
	xml->SetShort("x", x);
	xml->SetShort("y", y);
	xml->EndNode();
}


void MonsterFormationCellData::DeserializeXml( XmlReader* xml )
{
	x = xml->GetShort("x");
	y = xml->GetShort("y");
}




// MonsterFormation

MonsterFormation::MonsterFormation() :
	formations(),
	id(0)
{
}


void MonsterFormation::SerializeXml( XmlWriter* xml )
{
	xml->SetUInt("max", formations.size());
	for( array_type::iterator it = formations.begin(); it < formations.end(); ++it )
	{
		it->SerializeXml(xml);
	}
}


void MonsterFormation::DeserializeXml( XmlReader* xml )
{
	size_t n = xml->GetUInt("max");
	formations.resize(n);

	bool nested = false;
	for( size_t i(0); i < formations.size(); ++i )
	{
		if( xml->NextChild("Cell") )
		{
			formations[i].DeserializeXml(xml);
			nested = true;
		}
		else
		{
		}
	}

	if( nested )
		xml->SetToParent();
}


