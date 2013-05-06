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
#include "Buff.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 Buff
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Buff::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Attributes");
	attributes.SerializeXml(xml);
	xml->EndNode();
}


void Buff::DeserializeXml( XmlReader* xml )
{
	if( xml->NextChild("Attributes") )
	{
		attributes.DeserializeXml(xml);
		xml->SetToParent();
	}
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//              BuffSet
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BuffSet::BuffSet() :
	m_buffs(),
	m_combinedBuffAttributes(),
	m_is_dirty(false)
{
}


bool BuffSet::AddBuff( const Buff& buff )
{
	bool isAdded = false;
	int numFound = 0;
	for( vec_type::iterator it = m_buffs.begin(); it != m_buffs.end(); )
	{
		if( buff.id == it->id )
			++numFound;
	}

	// only add this buff if it is unique or it can stack.
	int stackCount = buff.GetStackCount();
	if( stackCount == 0 || stackCount > numFound )
	{
		m_buffs.push_back(buff);
		m_is_dirty = true;
		isAdded = true;
	}

	return isAdded;
}


void BuffSet::RemoveBuff( size_t index )
{
	if( index < m_buffs.size() )
	{
		m_buffs.erase_at(index);
		m_is_dirty = true;
	}
}


void BuffSet::Update()
{
	for( vec_type::iterator it = m_buffs.begin(); it != m_buffs.end(); )
	{
		if( it->IsTimedOut() )
		{
			m_buffs.erase(it);
			m_is_dirty = true;
		}
		else
		{
			++it;
		}
	}
}


void BuffSet::CalculateModifiers()
{
	// these have to be recalculated fully whenever the list changes.
	m_combinedBuffAttributes = Attributes();

	for( vec_type::iterator it = m_buffs.begin(); it != m_buffs.end(); ++it)
	{
		if( it->type == Buff::TypeModifier )
		{
			m_combinedBuffAttributes += it->attributes;
		}
	}

	for( vec_type::iterator it = m_buffs.begin(); it != m_buffs.end(); ++it)
	{
		if( it->type == Buff::TypeMultiplier )
		{
			//m_combinedBuffAttributes.ApplyPercentageModifier(it->attributes);
		}
	}

	m_is_dirty = false;
}


const Attributes& BuffSet::GetCombinedAttributes()
{
	if( m_is_dirty )
		CalculateModifiers();

	return m_combinedBuffAttributes;
}


Buff& BuffSet::operator []( size_t index )
{
	ASSERT(index < m_buffs.size());
	return m_buffs[index];
}


const Buff& BuffSet::operator []( size_t index ) const
{
	ASSERT(index < m_buffs.size());
	return m_buffs[index];
}


/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//               BuffList
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool BuffList::SerializeXml( const fc::string& filename )
{
	XmlWriter xml(filename);
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
	XmlReader xml(filename);
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

