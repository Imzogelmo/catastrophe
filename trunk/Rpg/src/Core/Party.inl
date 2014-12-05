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
}


bool Party::AddMember( Actor* actor )
{
	if( actor )
		for( vec_type::iterator it = m_members.begin(); it != m_members.end(); ++it )
			if( (*it) == null )
			{
				(*it) = actor;
				return true;
			}

	return false;
}


bool Party::InsertMemberInSlot( int slot, Actor* actor )
{
	if( actor && (u32)slot < m_members.size() )
	{
		if( m_members[slot] == null )
		{
			// Simple case; add actor to the free slot
			m_members[slot] = actor;
		}
		else
		{
			int firstFreeSlot = GetFirstEmptySlot(slot + 1);
			if( firstFreeSlot == -1 )
				return false;

			// Move members back in order to free up the slot
			vec_type::iterator first = m_members.begin() + slot;
			vec_type::iterator last = m_members.begin() + firstFreeSlot;
			fc::copy_backward(first, last, last + 1);
			m_members[slot] = actor;
		}
	}

	return false;
}


void Party::RemoveMember( Actor* actor )
{
	vec_type::iterator it = fc::find(m_members.begin(), m_members.end(), actor);
	if( it != m_members.end() )
		*it = null;
}


void Party::RemoveMemberInSlot( int slot )
{
	if( (u32)slot < m_members.size() )
		m_members[slot] = null;
}


void Party::RemoveAllMembers()
{
	for( vec_type::iterator it = m_members.begin(); it != m_members.end(); ++it )
		(*it) = null;
}


int Party::GetFirstEmptySlot( int startSlot ) const
{
	return GetFirstEmptySlot(startSlot, (int)m_members.size() );
}


int Party::GetFirstEmptySlot( int startSlot, int endSlot ) const
{
	if( (u32)startSlot < (u32)endSlot && (u32)endSlot <= m_members.size() )
	{
		vec_type::const_iterator first = m_members.begin() + startSlot;
		vec_type::const_iterator last = m_members.begin() + endSlot;
		vec_type::const_iterator it = fc::find( first, last, (Actor*)null);
		if( it != last )
			return (int)(first - m_members.begin());
	}

	return -1;
}


bool Party::Contains( Actor* actor ) const
{
	return fc::contains(m_members.begin(), m_members.end(), actor);
}


bool Party::IsEmpty() const
{
	return GetPartySize() == 0;
}


bool Party::IsFull() const
{
	// The party is considered full if all the available slots
	// are occupied by actors.

	return (GetPartySize() == GetMaxPartySize());
}


bool Party::IsSlotOccupied( int slot ) const
{
	return (GetMember(slot) != null);
}


Actor* Party::GetMember( int slot ) const
{
	if( (u32)slot < m_members.size() )
		return const_cast<Actor*>(m_members[slot]);

	return null;
}


void Party::SetMember( int slot, Actor* actor )
{
	if( (u32)slot < m_members.size() )
		m_members[slot] = actor;
}


u32 Party::GetPartySize() const
{
	int numberOfPartyMembers = 0;
	for( vec_type::const_iterator it = m_members.begin(); it != m_members.end(); ++it )
		if( (*it) != null )
			numberOfPartyMembers++;

	return numberOfPartyMembers;
}


u32 Party::GetMaxPartySize() const
{
	return m_members.size();
}


void Party::SwapMembers( u32 firstSlot, u32 secondSlot)
{
	if( firstSlot < m_members.size() && secondSlot < m_members.size() )
		fc::swap(m_members[firstSlot], m_members[secondSlot]);
}


void Party::SetMaxPartySize( u32 size )
{
	size = fc::min(size, m_members.capacity());
	m_members.resize(size, null);
}


int Party::GetAverageExperienceLevel() const
{
	int numberOfMembers = 0;
	int totalExperienceLevels = 0;

	for( vec_type::const_iterator it = m_members.begin(); it != m_members.end(); ++it )
	{
		const Actor* actor = *it;
		if( actor )
		{
			numberOfMembers++;
			totalExperienceLevels += actor->GetLv();
		}
	}

	return (numberOfMembers > 0 ? totalExperienceLevels / numberOfMembers : 0);
}


int Party::GetGold() const
{
	return m_gold;
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

