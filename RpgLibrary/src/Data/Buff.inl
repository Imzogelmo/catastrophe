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
#include "Buff.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 Buff
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Buff::SerializeXml( AttributeWriter* f )
{
	f->BeginNode("Attributes");
	attributes.SerializeXml(f);
	f->EndNode();
}


void Buff::DeserializeXml( AttributeReader* f )
{
	if( f->NextChild("Attributes") )
	{
		attributes.DeserializeXml(f);
		f->SetToParent();
	}
}



/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//               BuffList
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool BuffList::SerializeXml( const fc::string& filename )
{
	AttributeWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	xml.BeginNode("BuffList");
	xml.SetUInt("count", m_items.size());

	for( size_t i(0); i < m_items.size(); ++i )
	{
		xml.BeginNode("Buff");
		m_items[i].SerializeXml(&xml);
		xml.EndNode();
	}

	xml.EndNode();
	xml.Close();

	return true;
}


bool BuffList::DeserializeXml( const fc::string& filename )
{
	AttributeReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "BuffList" )
	{
		size_t n = xml.GetUInt("count");
		m_items.clear();
		m_items.reserve(n);

		while( xml.NextChild("Buff") )
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
*/

