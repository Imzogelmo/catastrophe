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
	//todo: sanity check - verify that id is valid

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
		if( m_activeMembers.size() < (size_t)m_maxActivePartySize )
			m_activeMembers.push_back(id);

		else if( !IsFull() )
			m_reserveMembers.push_back(id);
	}
}


void Party::RemoveMember( int id )
{
	//todo: sanity check - verify that id is valid

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


bool Party::IsFull() const
{
	return GetPartySize() >= m_maxPartySize;
}


Party::vec_type Party::GetAllPartyMembers() const
{
	vec_type ret;
	ret.reserve(m_activeMembers.size() + m_reserveMembers.size());
	ret.insert(ret.end(), m_activeMembers.begin(), m_activeMembers.end());
	ret.insert(ret.end(), m_reserveMembers.begin(), m_reserveMembers.end());
	return ret;
}


int Party::GetGold() const
{
	return m_gold;
}


int Party::GetPartySize() const
{
	return GetActivePartySize() + GetReservePartySize();
}


int Party::GetActivePartySize() const
{
	return (int)m_activeMembers.size();
}


int Party::GetReservePartySize() const
{
	return (int)m_reserveMembers.size();
}


int Party::GetMaxPartySize() const
{
	return m_maxPartySize;
}


int Party::GetMaxActivePartySize() const
{
	return m_maxActivePartySize;
}



void Party::SetGold( int val )
{
	m_gold = fc::clamp(val, 0, MAX_GOLD);
}


void Party::AddGold( int amount )
{
	SetGold(m_gold + amount);
}


void Party::RemoveGold( int amount )
{
	SetGold(m_gold - amount);
}


void Party::SetMaxPartySize( int size )
{
	if( size < 0 )
		size = 0;

	// if size is less than all members we have to remove some.
	else if( size < GetPartySize() )
	{
		int diff = GetPartySize() - size;
		if( diff > GetReservePartySize() )
		{
			diff -= GetReservePartySize();
			m_reserveMembers.clear();
			m_activeMembers.erase(m_activeMembers.end() - diff, m_activeMembers.end());
		}
		else
		{
			m_reserveMembers.erase
				(m_reserveMembers.end() - diff, m_reserveMembers.end());
		}
	}

	m_maxPartySize = size;
}


void Party::SetMaxActivePartySize( int size )
{
	if( size < 0 )
		size = 0;

	// if size is less than active member size we put them in reserve.
	if( size < GetActivePartySize() )
	{
		int diff = GetActivePartySize() - size;
		vec_type::iterator first = m_activeMembers.end() - diff;
		vec_type::iterator last = m_activeMembers.end();

		m_reserveMembers.insert(m_reserveMembers.end(), first, last);
		m_activeMembers.erase(first, last);
	}

	m_maxActivePartySize = size;
}




