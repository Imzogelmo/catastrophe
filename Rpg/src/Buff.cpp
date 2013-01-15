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


void BuffList::AddBuff( const Buff& buff )
{
	m_buffs.push_back(buff);
	m_is_dirty = true;
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
