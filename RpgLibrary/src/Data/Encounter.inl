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
#include "Encounter.h"


EncounterData::EncounterData( u16 monsterTroopIndex, u16 encounterRate, u16 maxRate ) :
	troopId(monsterTroopIndex),
	rate(encounterRate),
	maxRate(maxRate)
{
}


void EncounterData::Validate()
{
	if(maxRate < rate)
		maxRate = rate;
}


void EncounterData::Serialize( AttributeWriter* f )
{
	f->BeginNode("Encounter");
	f->SetUShort("troopId", troopId);
	f->SetUShort("rate", rate);
	f->SetUShort("maxRate", maxRate);
	f->EndNode();
}


void EncounterData::Deserialize( AttributeReader* f )
{
	troopId = f->GetShort("troopId");
	rate = f->GetUShort("rate");
	maxRate = f->GetUShort("maxRate");
}




EncounterGroup::EncounterGroup() :
	name(),
	encounters()
{
}


void EncounterGroup::Serialize( AttributeWriter* f )
{
	f->BeginNode("Region");
	f->SetString("name", name.c_str());
	f->SetUInt("num_encounters", encounters.size());

	for( vec_type::iterator it = encounters.begin(); it != encounters.end(); ++it )
	{
		it->Serialize(f);
	}

	f->EndNode();
}


void EncounterGroup::Deserialize( AttributeReader* f )
{
	u32 numEncounters = f->GetUInt("num_encounters");
	encounters.resize(numEncounters);

	for( u32 i(0); i < numEncounters; ++i )
	{
		if( f->NextChild("Encounter") )
		{
			encounters[i].Deserialize(f);
		}
	}

	if( f->GetCurrentNodeName() == "Encounter" )
		f->SetToParent();
}




