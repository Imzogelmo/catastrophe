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


#include <Engine/IO/XmlWriter.h>
#include <Engine/IO/XmlReader.h>
#include "LevelData.h"
#include "Util/Serialization.h"



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//              LevelData
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void LevelData::SerializeXml( XmlWriter* xml )
{
	flags.SerializeXml(xml);
}


void LevelData::DeserializeXml( XmlReader* xml )
{
	flags.DeserializeXml(xml);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//               LevelInfo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void LevelInfo::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("LevelInfo");
	xml->SetUInt("count", levels.size());
	xml->SetInt("exp_table", exp_table_id);

	for( size_t i(0); i < levels.size(); ++i )
	{
		xml->BeginNode("LevelData");
		levels[i].SerializeXml(xml);
		xml->EndNode();
	}

	xml->EndNode();
}


void LevelInfo::DeserializeXml( XmlReader* xml )
{
	size_t n = xml->GetUInt("count");
	exp_table_id = xml->GetInt("exp_table");
	levels.clear();
	levels.reserve(n);

	while( xml->NextChild("LevelData") )
	{
		levels.push_back();
		levels.back().DeserializeXml(xml);
		xml->SetToParent();
	}
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//               LevelList
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool LevelList::SerializeXml( const fc::string& filename )
{
	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	xml.BeginNode("LevelList");
	xml.SetUInt("count", m_items.size());

	for( size_t i(0); i < m_items.size(); ++i )
	{
		xml.BeginNode("LevelInfo");
		m_items[i].SerializeXml(&xml);
		xml.EndNode();
	}

	xml.EndNode();
	xml.Close();

	return true;
}


bool LevelList::DeserializeXml( const fc::string& filename )
{
	XmlReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "LevelList" )
	{
		size_t n = xml.GetUInt("count");
		m_items.clear();
		m_items.reserve(n);

		while( xml.NextChild("LevelInfo") )
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
