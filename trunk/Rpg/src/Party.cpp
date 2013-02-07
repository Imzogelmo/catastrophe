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


Party::Party()
{
	m_gold = 0;
	m_maxPartySize = 32;
	m_maxActivePartySize = 4;
}


void Party::AddMember( int id )
{
	vec_type::iterator it;
	if( IsMemberInActiveParty(id, it) )
		return;

	if( IsMemberInReserve(id, it) )
	{
		if( m_activeMembers.size() < (size_t)m_maxActivePartySize )
		{
			m_reserveMembers.erase(it);
			m_activeMembers.push_back(id);
		}
	}
	else
	{
		//todo: sanity check
		if( m_activeMembers.size() < (size_t)m_maxActivePartySize )
			m_activeMembers.push_back(id);

		else if( GetPartySize() < (size_t)m_maxPartySize )
			m_reserveMembers.push_back(id);
	}
}


void Party::RemoveMember( int id )
{
	vec_type::iterator it;
	if( IsMemberInActiveParty(id, it) )
	{
		m_activeMembers.erase(it);
	}
	else if( IsMemberInActiveParty(id, it) )
	{
		m_reserveMembers.erase(it);
	}
}


bool Party::HasMember( int id )
{
	return (IsMemberInActiveParty(id) || IsMemberInReserve(id));
}


bool Party::IsMemberInActiveParty( int id )
{
	vec_type::iterator it = 0;
	return IsMemberInActiveParty(id, it);
}


bool Party::IsMemberInReserve( int id )
{
	vec_type::iterator it = 0;
	return IsMemberInReserve(id, it);
}


bool Party::IsMemberInActiveParty( int id, vec_type::iterator& outIt )
{
	outIt = fc::find(m_activeMembers.begin(), m_activeMembers.end(), id);
	return outIt != m_activeMembers.end();
}


bool Party::IsMemberInReserve( int id, vec_type::iterator& outIt )
{
	outIt = fc::find(m_reserveMembers.begin(), m_reserveMembers.end(), id);
	return outIt != m_reserveMembers.end();
}


Party::vec_type Party::GetAllPartyMembers() const
{
	vec_type ret;
	ret.reserve(m_activeMembers.size() + m_reserveMembers.size());
	ret.insert(ret.end(), m_activeMembers.begin(), m_activeMembers.end());
	ret.insert(ret.end(), m_reserveMembers.begin(), m_reserveMembers.end());
	return ret;
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


size_t Party::GetPartySize() const
{
	return m_activeMembers.size() + m_reserveMembers.size();
}




