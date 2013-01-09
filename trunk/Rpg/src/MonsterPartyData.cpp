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
#include "MonsterPartyData.h"


extern MonsterList gMonsterList; //temp for gererating data.
#include "MonsterData.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//             MonsterGroupData
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void MonsterGroupData::Validate()
{
	if(min < 0) min = 0;
	if(max < 0) max = 0;
	if(max < min) max = min;
}


void MonsterGroupData::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Monster");
	xml->SetInt("index", monster_index);
	xml->SetInt("min", min);
	xml->SetInt("max", max);
	xml->SetInt("x", x);
	xml->SetInt("y", y);
	xml->EndNode();
}


void MonsterGroupData::DeserializeXml( XmlReader* xml )
{
	monster_index = xml->GetInt("index");
	min = xml->GetInt("min");
	max = xml->GetInt("max");
	x = xml->GetInt("x");
	y = xml->GetInt("y");
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//             MonsterPartyData
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MonsterPartyData::MonsterPartyData() :
	m_groups()
{
}


void MonsterPartyData::AddGroup( const MonsterGroupData& group )
{
	m_groups.push_back(group);
}


void MonsterPartyData::RemoveGroup( size_t index )
{
	if( index < NumGroups() )
		m_groups.erase_at(index);
}


MonsterGroupData& MonsterPartyData::GetGroup( size_t index )
{
	ASSERT(index < NumGroups());
	return m_groups[index];
}


const MonsterGroupData& MonsterPartyData::GetGroup(size_t index) const
{
	ASSERT(index < NumGroups());
	return m_groups[index];
}


void MonsterPartyData::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Troop");
	xml->SetString("name", m_name);
	xml->SetUInt("num_groups", m_groups.size());

	for( vec_type::iterator it = m_groups.begin(); it < m_groups.end(); ++it )
	{
		it->SerializeXml(xml);
	}

	xml->EndNode();
}


void MonsterPartyData::DeserializeXml( XmlReader* xml )
{
	m_name = xml->GetString("name");
	size_t n = xml->GetUInt("num_groups");
	m_groups.reserve(n);

	while( xml->NextChild("Monster") )
	{
		m_groups.push_back();
		m_groups.back().DeserializeXml(xml);
	}

	xml->SetToParent(); //fixme
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//             MonsterPartyList
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool MonsterPartyList::SerializeXml( const fc::string& filename )
{
	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	xml.BeginNode("MonsterTroops");
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


bool MonsterPartyList::DeserializeXml( const fc::string& filename )
{
	XmlReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "MonsterTroops" )
	{
		size_t n = xml.GetUInt("count");
		m_items.clear();
		m_items.reserve(n);

		while( xml.NextChild("Troop") )
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

