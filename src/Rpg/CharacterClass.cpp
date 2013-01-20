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
#include "CharacterClass.h"
#include "Util/Serialization.h"



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//             CharacterClass
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


CharacterClass::CharacterClass() :
	base_type(),
	exp_table_index(0)
{
}


void CharacterClass::SerializeXml( XmlWriter* xml )
{
	base_type::SerializeXml(xml);

	xml->BeginNode("AnimationSet");
	Util::SerializeAnimationSet(xml, animation_set);
	xml->EndNode();
}


void CharacterClass::DeserializeXml( XmlReader* xml )
{
	base_type::DeserializeXml(xml);

	if( xml->NextChild("AnimationSet") )
	{
		Util::DeserializeAnimationSet(xml, animation_set);
		xml->SetToParent();
	}
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//             CharacterClassList
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool CharacterClassList::SerializeXml( const fc::string& filename )
{
	XmlWriter xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	xml.BeginNode("CharacterList");
	xml.SetUInt("count", m_items.size());

	for( size_t i(0); i < m_items.size(); ++i )
	{
		xml.BeginNode("Character");
		m_items[i].SerializeXml(&xml);
		xml.EndNode();
	}

	xml.EndNode();
	xml.Close();

	return true;
}


bool CharacterClassList::DeserializeXml( const fc::string& filename )
{
	XmlReader xml(filename);
	if( !xml.IsOpen() )
	{
		Log("Could not open file (%s)", filename.c_str());
		return false;
	}

	if( xml.GetCurrentNodeName() == "CharacterList" )
	{
		size_t n = xml.GetUInt("count");
		m_items.clear();
		m_items.reserve(n);

		while( xml.NextChild("Character") )
		{
			m_items.push_back();
			m_items.back().DeserializeXml(&xml);
			xml.SetToParent();
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
