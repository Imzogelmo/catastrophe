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
#include "MonsterFormation.h"



MonsterFormationCellData::MonsterFormationCellData() :
	x(0),
	y(0)
{
}


MonsterFormationCellData::MonsterFormationCellData( s16 x, s16 y ) :
	x(x),
	y(y)
{
}


void MonsterFormationCellData::RegisterObject()
{
	//REGISTER_ATTRIBUTE_FACTORY_TYPE(MonsterFormationCellData);
	//REGISTER_ATTRIBUTE(MonsterFormationCellData, VAR_TYPE_SHORT, "x", x);
	//REGISTER_ATTRIBUTE(MonsterFormationCellData, VAR_TYPE_SHORT, "y", y);
}


void MonsterFormationCellData::Serialize( AttributeWriter* f )
{
	f->SetShort("x", x);
	f->SetShort("y", y);
}


void MonsterFormationCellData::Deserialize( AttributeReader* f )
{
	x = f->GetShort("x", x);
	y = f->GetShort("y", y);
}





// MonsterFormation

MonsterFormation::MonsterFormation() :
	formations(),
	id(0)
{
}


void MonsterFormation::RegisterObject()
{
	//REGISTER_ATTRIBUTE_FACTORY_TYPE(MonsterFormation);
	//REGISTER_ATTRIBUTE_OBJECT_ARRAY(MonsterFormation, "Cell", "max", array_type, formations);
}


void MonsterFormation::Serialize( AttributeWriter* f )
{
	f->SetUInt( "max", formations.size() );
	for( array_type::iterator it = formations.begin(); it < formations.end(); ++it )
	{
		f->BeginNode("Cell");
		it->Serialize(f);
		f->EndNode();
	}
}


void MonsterFormation::Deserialize( AttributeReader* f )
{
	u32 numFormations = f->GetInt("max");
	formations.resize(numFormations);

	for( u32 i(0); i < numFormations; ++i )
	{
		if( f->NextChild("Cell") )
			formations[i].Deserialize(f);
	}

	if( f->GetCurrentNodeName() == "Cell" )
		f->SetToParent();
}


int MonsterFormation::GetMemoryUsage() const
{
	return (int)(formations.size() * sizeof(MonsterFormationCellData));
}



