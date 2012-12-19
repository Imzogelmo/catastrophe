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

#include <Catastrophe/FileIO.h>
#include "EncounterData.h"




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//               EncounterData
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void EncounterData::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Encounter");

	xml->SetInt("troop_index", troop_index);
	xml->SetInt("rate", rate);
	xml->SetInt("max_rate", max_rate);

	xml->EndNode();
}


void EncounterData::DeserializeXml( XmlReader* xml )
{
	troop_index = xml->GetInt("troop_index");
	rate = xml->GetInt("rate");
	max_rate = xml->GetInt("max_rate");
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//             EncounterGroupData
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

EncounterGroupData::EncounterGroupData( const fc::string& name ) :
	m_name(name),
	m_encounters()
{
}


void EncounterGroupData::AddEncounter( const EncounterData& data )
{
	m_encounters.push_back(data);
}


void EncounterGroupData::RemoveEncounter( size_t index )
{
	if( index < m_encounters.size() )
		m_encounters.erase_at(index);
}


EncounterData& EncounterGroupData::GetEncounter( size_t index )
{
	ASSERT(index < m_encounters.size());
	return m_encounters[index];
}


const EncounterData& EncounterGroupData::GetEncounter( size_t index ) const
{
	ASSERT(index < m_encounters.size());
	return m_encounters[index];
}


void EncounterGroupData::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Region");
	xml->SetString("name", m_name.c_str());
	xml->SetUInt("num_encounters", m_encounters.size());

	for( vec_type::iterator it = m_encounters.begin(); it != m_encounters.end(); ++it )
	{
		it->SerializeXml(xml);
	}

	xml->EndNode();
}


void EncounterGroupData::DeserializeXml( XmlReader* xml )
{
	size_t n = xml->GetUInt("num_encounters");
	m_encounters.clear();
	m_encounters.reserve(n);

	while( xml->NextChild("Encounter") )
	{
		m_encounters.push_back();
		m_encounters.back().DeserializeXml(xml);
	}

	if( m_encounters.size() != n )
	{
		LogWarning("Region: num_encounters does not match.");
	}
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//             EncounterGroupList
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool EncounterGroupList::SerializeXml( const fc::string& filename )
{
	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	xml.BeginNode("MonsterEncounters");
	xml.SetString("ver", "1.0");
	xml.SetUInt("count", m_items.size());

	for( size_t i(0); i < m_items.size(); ++i )
	{
		m_items[i].SerializeXml(&xml);
	}

	xml.EndNode();
	xml.Close();

	return true;
}


bool EncounterGroupList::DeserializeXml( const fc::string& filename )
{
	XmlReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "MonsterEncounters" )
	{
		size_t n = xml.GetUInt("count");
		m_items.clear();
		m_items.reserve(n);

		while( xml.NextChild("Region") )
		{
			m_items.push_back();
			m_items.back().DeserializeXml(&xml);
		}
	}
	else
	{
		Log("Error parsing (%s). Root item not found", filename.c_str());
		return false;
	}

	xml.Close();

	return true;
}



