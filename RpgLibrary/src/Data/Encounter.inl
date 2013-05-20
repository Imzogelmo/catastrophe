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


void EncounterData::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Encounter");
	xml->SetInt("troop_id", troop_id);
	xml->SetInt("rate", rate);
	xml->SetInt("max_rate", max_rate);
	xml->EndNode();
}


void EncounterData::DeserializeXml( XmlReader* xml )
{
	troop_id = xml->GetInt("troop_id");
	rate = xml->GetInt("rate");
	max_rate = xml->GetInt("max_rate");
}




EncounterGroup::EncounterGroup() :
	name(),
	encounters()
{
}


void EncounterGroup::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Region");
	xml->SetString("name", name.c_str());
	xml->SetUInt("num_encounters", encounters.size());

	for( vec_type::iterator it = encounters.begin(); it != encounters.end(); ++it )
	{
		it->SerializeXml(xml);
	}

	xml->EndNode();
}


void EncounterGroup::DeserializeXml( XmlReader* xml )
{
	size_t n = xml->GetUInt("num_encounters");
	encounters.resize(n);

	bool nested = false;
	for( size_t i(0); i < encounters.size(); ++i )
	{
		if( xml->NextChild("Encounter") )
		{
			encounters[i].DeserializeXml(xml);
			nested = true;
		}
		else
		{
		}
	}

	if( nested )
		xml->SetToParent();
}




