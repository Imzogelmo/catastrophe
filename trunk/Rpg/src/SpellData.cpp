
#include <Catastrophe/FileIO.h>
#include "SpellData.h"



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//               SpellData
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SpellData::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Spell");
	base_type::SerializeXml(xml);
	xml->EndNode();
}


void SpellData::DeserializeXml( XmlReader* xml )
{
	base_type::DeserializeXml(xml);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//               SpellList
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool SpellList::SerializeXml( const fc::string& filename )
{
	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	xml.BeginNode("SpellList");
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


bool SpellList::DeserializeXml( const fc::string& filename )
{
	XmlReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "SpellList" )
	{
		size_t n = xml.GetUInt("count");
		m_items.clear();
		m_items.reserve(n);

		while( xml.NextChild("Spell") )
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
