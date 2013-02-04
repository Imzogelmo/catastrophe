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

#include "SpellBook.h"



bool SpellBook::Contains( int id )
{
	for( vec_type::iterator it = m_spells.begin(); it != m_spells.end(); )
	{
		if( id == *it )
			return true;
	}

	return false;
}


void SpellBook::Learn( int id )
{
	if( !Contains(id) )
	{
		//todo check id
		m_spells.push_back(id);
	}
}


void SpellBook::Unlearn( int id )
{
	for( vec_type::iterator it = m_spells.begin(); it != m_spells.end(); )
	{
		if( id == *it )
		{
			m_spells.erase(it);
			break;
		}
	}
}


void SpellBook::UnlearnAll()
{
	m_spells.clear();
}





