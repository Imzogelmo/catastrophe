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

#include "Party.h"


void Party::AddMember( int id )
{
	vec_type::iterator it = fc::find(m_characters.begin(), m_characters.end(), id);
	if( it != m_characters.end() )
	{
		//todo: sanity check
		m_characters.push_back(id);
	}
}


void Party::RemoveMember( int id )
{
	vec_type::iterator it = fc::find(m_characters.begin(), m_characters.end(), id);
	if( it != m_characters.end() )
	{
		m_characters.erase(it);
	}
}


bool HasMember( int id )
{
	vec_type::iterator it = fc::find(m_characters.begin(), m_characters.end(), id);
	return it != m_characters.end();
}


void Party::AddGold( int amount )
{
	m_gold += amount;
	m_gold = fc::clamp(m_gold, 0, 999999999);
}


void Party::RemoveGold( int amount )
{
	m_gold -= amount;
	m_gold = fc::clamp(m_gold, 0, 999999999);
}






