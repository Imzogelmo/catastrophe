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


EncounterData::EncounterData( int monsterPartyIndex, int encounterRate, int maxRate ) :
	troop_id(monsterPartyIndex),
	rate(encounterRate),
	max_rate(maxRate)
{
}


void EncounterData::Validate()
{
	if(rate < 0) rate = 0;
	if(max_rate < 0) max_rate = 0;
	if(max_rate < rate) max_rate = rate;
}


void EncounterData::SerializeXml( AttributeWriter* f )
{
	f->BeginNode("Encounter");
	f->SetInt("troop_id", troop_id);
	f->SetInt("rate", rate);
	f->SetInt("max_rate", max_rate);
	f->EndNode();
}


void EncounterData::DeserializeXml( AttributeReader* f )
{
	troop_id = f->GetInt("troop_id");
	rate = f->GetInt("rate");
	max_rate = f->GetInt("max_rate");
}




EncounterGroup::EncounterGroup() :
	name(),
	encounters()
{
}


void EncounterGroup::SerializeXml( AttributeWriter* f )
{
	f->BeginNode("Region");
	f->SetString("name", name.c_str());
	f->SetUInt("num_encounters", encounters.size());

	for( vec_type::iterator it = encounters.begin(); it != encounters.end(); ++it )
	{
		it->SerializeXml(f);
	}

	f->EndNode();
}


void EncounterGroup::DeserializeXml( AttributeReader* f )
{
	size_t numEncounters = f->GetUInt("num_encounters");
	encounters.resize(numEncounters);

	for( size_t i(0); i < numEncounters; ++i )
	{
		if( f->NextChild("Encounter") )
		{
			encounters[i].DeserializeXml(f);
		}
	}

	if( f->GetCurrentNodeName() == "Encounter" )
		f->SetToParent();
}




