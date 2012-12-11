
#include <Catastrophe/FileIO.h>
#include "EncounterData.h"




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




EncounterGroupData::EncounterGroupData() :
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
	xml->BeginNode("EncounterGroup");
	xml->SetString("name", m_name.c_str());

	for( vec_type::iterator it = m_encounters.begin(); it != m_encounters.end(); ++it )
	{
		it->SerializeXml(xml);
	}

	xml->EndNode();
}


void EncounterGroupData::DeserializeXml( XmlReader* xml )
{
	//size_t numGroups = xml->GetUInt("num_groups");
	//m_encounters.resize(numGroups);

	for( vec_type::iterator it = m_encounters.begin(); it < m_encounters.end(); ++it )
	{
		//it->DeserializeXml(xml);
	}
}
