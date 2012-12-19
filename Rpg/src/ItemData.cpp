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

#pragma once

#include <Catastrophe/FileIO.h>
#include "ItemData.h"



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//               ItemData
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ItemData::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Item");

	base_type::SerializeXml(xml);
	//item usage...

	xml->EndNode();
}


void ItemData::DeserializeXml( XmlReader* xml )
{
	base_type::DeserializeXml(xml);
	//item usage...
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//               ItemList
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool ItemList::SerializeXml( const fc::string& filename )
{
	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	xml.BeginNode("ItemList");
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


bool ItemList::DeserializeXml( const fc::string& filename )
{
	XmlReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "ItemList" )
	{
		size_t n = xml.GetUInt("count");
		if( n == 0 )
			return false;

		m_items.clear();
		m_items.resize(n);

		for( size_t i(0); i < n; ++i )
		{
			m_items[i].DeserializeXml(&xml);
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
