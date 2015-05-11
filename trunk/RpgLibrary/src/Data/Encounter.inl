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
#include "Encounter.h"


EncounterData::EncounterData( u16 monsterTroopIndex, u8 encounterRate, u8 maxRate ) :
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
	f->SetAttribute("troop_id", troopId);
	f->SetAttribute("rate", rate);
	f->SetAttribute("max_rate", maxRate);
	f->EndNode();
}


void EncounterData::Deserialize( AttributeReader* f )
{
	f->GetAttribute("troop_id", troopId);
	f->GetAttribute("rate", rate);
	f->GetAttribute("max_rate", maxRate);
}




EncounterGroup::EncounterGroup() :
	name(),
	encounters()
{
}


void EncounterGroup::Serialize( AttributeWriter* f )
{
	f->BeginNode("Region");
	f->SetString("name", name.CString());
	f->SetAttribute("count", encounters.Size());

	for( VectorType::Iterator it = encounters.begin(); it != encounters.end(); ++it )
	{
		it->Serialize(f);
	}

	f->EndNode();
}


void EncounterGroup::Deserialize( AttributeReader* f )
{
	u32 numEncounters = 0;
	f->GetString("name", name);
	f->GetAttribute("count", numEncounters);
	encounters.Resize(numEncounters);

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


int EncounterGroup::GetMemoryUsage() const
{
	return (int)(encounters.Capacity() * sizeof(EncounterData));
}

