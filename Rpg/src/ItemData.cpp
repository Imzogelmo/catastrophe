
#pragma once

#include <Catastrophe/FileIO.h>
#include "ItemData.h"



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//               ItemData
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ItemData::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Item");

	xml->SetString("name", name.c_str());
	xml->SetString("description", description.c_str());

	attributes.SerializeXml(xml);
	attribute_flags.SerializeXml(xml);
	//item usage...

	xml->EndNode();
}


void ItemData::DeserializeXml( XmlReader* xml )
{
	if( !xml->NextChild("Item") )
	{
		Log("----debug error---- ItemData::DeserializeXml()");
		return;
	}

	name = xml->GetString("name");
	description = xml->GetString("description");

	attributes.DeserializeXml(xml);
	attribute_flags.DeserializeXml(xml);
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
