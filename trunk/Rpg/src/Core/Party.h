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

#include <fc/static_vector.h>
#include <fc/string.h>

#include "Common.h"
#include "../Inventory.h"


class Party
{
public:
	typedef fc::static_vector<Actor*, MAX_PARTY_SIZE>	vec_type;

	Party();

	/// Adds an actor to the party. (return true if the actor was added)
	bool AddMember( Actor* actor );

	/// Inserts an actor at position 'slot'. (return true if the actor was inserted)
	bool InsertMemberInSlot( int slot, Actor* actor );

	/// Removes an actor from the party.
	void RemoveMember( Actor* actor );

	/// Removes the actor specified by slot.
	void RemoveMemberInSlot( int slot );

	/// Clears the party of all members.
	void RemoveAllMembers();

	/// Returns the index of the first unused slot, or -1 if none exist.
	int GetFirstEmptySlot( int startSlot = 0 ) const;
	int GetFirstEmptySlot( int startSlot, int endSlot ) const;

	/// Returns true if actor is a member of this party.
	bool Contains( Actor* actor ) const;

	/// The party is empty if it contains no members.
	bool IsEmpty() const;

	/// The party is full if all slots are occupied.
	bool IsFull() const;

	/// Returns true if slot contains a party member.
	bool IsSlotOccupied( int slot ) const;

	/// Gets the actor in a given slot.
	Actor* GetMember( int slot ) const;

	/// Overrides the slot to contain the specified actor.
	void SetMember( int slot, Actor* actor );

	/// Gets the number of members this party contains.
	u32 GetPartySize() const;

	/// Gets the maximum number of members this party can hold.
	u32 GetMaxPartySize() const;

	/// Swaps two party members.
	void SwapMembers( u32 firstSlot, u32 secondSlot);

	/// Sets the maximum member capacity for this party.
	void SetMaxPartySize( u32 size );

	/// Gets the average experience level of all combined party members.
	int GetAverageExperienceLevel() const;

	int GetGold() const;
	void SetGold( int val );
	void AddGold( int amount );
	void RemoveGold( int amount );

	Inventory&			GetInventory() { return m_inventory; }
	vec_type&			GetMembers() { return m_members; }
	const Inventory&	GetInventory() const { return m_inventory; }
	const vec_type&		GetMembers() const { return m_members; }

protected:
	vec_type		m_members;
	Inventory		m_inventory;

	int				m_gold;
};






