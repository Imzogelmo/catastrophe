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

	size_t index = 0;
	if( IsMemberInActiveParty(id, index) )
		return;

	if( IsMemberInReserve(id, index) )
	{
		// add to active party if there is room.
		if( m_activeMembers.size() < (size_t)m_maxActivePartySize )
		{
			m_reserveMembers.erase_at(index);
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

	size_t index = 0;
	if( IsMemberInActiveParty(id, index) )
	{
		m_activeMembers.erase_at(index);
	}
	else if( IsMemberInActiveParty(id, index) )
	{
		m_reserveMembers.erase_at(index);
	}
}


bool Party::HasMember( int id ) const
{
	return (IsMemberInActiveParty(id) || IsMemberInReserve(id));
}


bool Party::IsMemberInActiveParty( int id ) const
{
	size_t i = 0;
	return IsMemberInActiveParty(id, i);
}


bool Party::IsMemberInReserve( int id ) const
{
	size_t i = 0;
	return IsMemberInReserve(id, i);
}


bool Party::IsMemberInActiveParty( int id, size_t& outIndex ) const
{
	vec_type::const_iterator it = fc::find(m_activeMembers.begin(), m_activeMembers.end(), id);
	if( it != m_activeMembers.end() )
		outIndex = size_t(m_activeMembers.end() - it);

	return it != m_activeMembers.end();
}


bool Party::IsMemberInReserve( int id, size_t& outIndex ) const
{
	vec_type::const_iterator it = fc::find(m_reserveMembers.begin(), m_reserveMembers.end(), id);
	if( it != m_reserveMembers.end() )
		outIndex = size_t(m_reserveMembers.end() - it);

	return it != m_reserveMembers.end();
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


int Party::GetActiveMemberId( int index )
{
	int ret = -1;
	if( (size_t)index < m_activeMembers.size() )
		ret = m_activeMembers[index];

	return ret;
}


int Party::GetReserveMemberId( int index )
{
	int ret = -1;
	if( (size_t)index < m_reserveMembers.size() )
		ret = m_reserveMembers[index];

	return ret;
}


