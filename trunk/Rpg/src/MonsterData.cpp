
#pragma once

#include <Catastrophe/FileIO.h>
#include "MonsterData.h"



////////////////////////////////////////////
//             MonsterData
////////////////////////////////////////////

void MonsterData::SerializeXml(XmlWriter* xml)
{
	xml->BeginNode("Monster");

	xml->SetString("name", name.c_str());
	xml->SetString("script", script.c_str());
	xml->SetString("description", description.c_str());

	attributes.SerializeXml(xml);
	attribute_flags.SerializeXml(xml);
	item_dropset.SerializeXml(xml);

	xml->EndNode();
}


void MonsterData::DeserializeXml(XmlReader* xml)
{
	name = xml->GetString("name");
	script = xml->GetString("script");
	description = xml->GetString("description");

	attributes.DeserializeXml(xml);
	attribute_flags.DeserializeXml(xml);
	item_dropset.DeserializeXml(xml);
}



////////////////////////////////////////////
//             MonsterGroupData
////////////////////////////////////////////

void MonsterGroupData::Validate()
{
	if(min < 0) min = 0;
	if(max < 0) max = 0;
	if(max < min) max = min;
}


void MonsterGroupData::SerializeXml(XmlWriter* xml)
{
	xml->BeginNode("MonsterGroup");
	xml->SetInt("monster_index", monster_index);
	xml->SetInt("min", min);
	xml->SetInt("max", max);
	xml->EndNode();
}


void MonsterGroupData::DeserializeXml(XmlReader* xml)
{
	monster_index = xml->GetInt("monster_index");
	min = xml->GetInt("min");
	max = xml->GetInt("max");
}



////////////////////////////////////////////
//             MonsterPartyData
////////////////////////////////////////////

MonsterPartyData::MonsterPartyData() :
	m_groups()
{
}


void MonsterPartyData::AddGroup(const MonsterGroupData& group)
{
	m_groups.push_back(group);
}


void MonsterPartyData::RemoveGroup(size_t index)
{
	if( index < NumGroups() )
		m_groups.erase_at(index);
}


MonsterGroupData& MonsterPartyData::GetGroup(size_t index)
{
	ASSERT(index < NumGroups());
	return m_groups[index];
}


const MonsterGroupData& MonsterPartyData::GetGroup(size_t index) const
{
	ASSERT(index < NumGroups());
	return m_groups[index];
}


void MonsterPartyData::SerializeXml(XmlWriter* xml)
{
	xml->BeginNode("MonsterTroop");
	xml->SetUInt("num_groups", m_groups.size());

	for( vec_type::iterator it = m_groups.begin(); it < m_groups.end(); ++it )
	{
		it->SerializeXml(xml);
	}

	xml->EndNode();
}


void MonsterPartyData::DeserializeXml(XmlReader* xml)
{
	size_t numGroups = xml->GetUInt("num_groups");
	m_groups.resize(numGroups);

	xml->FirstChild("MonsterGroup");
	for( vec_type::iterator it = m_groups.begin(); it < m_groups.end(); ++it )
	{
		it->DeserializeXml(xml);
		if( !xml->NextChild("MonsterGroup") )
			break;
	}

	xml->SetToParent();
}


