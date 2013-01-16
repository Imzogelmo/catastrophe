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

#include "Buff.h"


BuffList::BuffList() :
	m_buffs(),
	m_combinedBuffAttributes(),
	m_is_dirty(false)
{
}


bool BuffList::AddBuff( const Buff& buff )
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


void BuffList::RemoveBuff( size_t index )
{
	if( index < m_buffs.size() )
	{
		m_buffs.erase_at(index);
		m_is_dirty = true;
	}
}


void BuffList::Update()
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


void BuffList::CalculateModifiers()
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

	m_is_dirty = false;
}


const Attributes& BuffList::GetCombinedAttributes()
{
	if( m_is_dirty )
		CalculateModifiers();

	return m_combinedBuffAttributes;
}


Buff& BuffList::operator []( size_t index )
{
	ASSERT(index < m_buffs.size());
	return m_buffs[index];
}


const Buff& BuffList::operator []( size_t index ) const
{
	ASSERT(index < m_buffs.size());
	return m_buffs[index];
}

