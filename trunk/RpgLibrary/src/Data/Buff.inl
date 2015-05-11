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

#include <Catastrophe/Core/IO/AttributeWriter.h>
#include <Catastrophe/Core/IO/AttributeReader.h>
#include "Buff.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 Buff
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Buff::Serialize( AttributeWriter* f )
{
	f->BeginNode("Attributes");
	attributes.Serialize(f);
	f->EndNode();
}


void Buff::Deserialize( AttributeReader* f )
{
	if( f->NextChild("Attributes") )
	{
		attributes.Deserialize(f);
		f->SetToParent();
	}
}



/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//               BuffList
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool BuffList::Serialize( const String& filename )
{
	AttributeWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.CString());
		return false;
	}

	xml.BeginNode("BuffList");
	xml.SetUInt("count", m_items.size());

	for( u32 i(0); i < m_items.size(); ++i )
	{
		xml.BeginNode("Buff");
		m_items[i].Serialize(&xml);
		xml.EndNode();
	}

	xml.EndNode();
	xml.Close();

	return true;
}


bool BuffList::Deserialize( const String& filename )
{
	AttributeReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.CString());
		return false;
	}

	if( xml.GetCurrentNodeName() == "BuffList" )
	{
		u32 n = xml.GetUInt("count");
		m_items.Clear();
		m_items.Reserve(n);

		while( xml.NextChild("Buff") )
		{
			m_items.Add();
			m_items.back().Deserialize(&xml);
		}
	}
	else
	{
		Log("Error parsing (%s). Root item not found", filename.CString());
		return false;
	}

	xml.Close();

	return true;
}
*/

