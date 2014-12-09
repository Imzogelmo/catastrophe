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

#include "Common.h"
#include "Combatant.h"



// BattleGroup
//
// The main purpose of this class is to encapsulate Combatants
// in a simple way, provide easy and straight-forward algorithms for managing them,
// and to eliminate code duplication for differing factions.

class BattleGroup
{
public:
	typedef fc::static_vector<Combatant*, MAX_BATTLEGROUP_SIZE> vec_type;

	BattleGroup();

	/// Adds a combatant to this group.
	void AddCombatant( Combatant* combatant );

	/// Inserts a combatant into this group at position.
	void InsertCombatant( Combatant* combatant, u32 position );

	/// Removes a combatant in this group.
	void RemoveCombatant( Combatant* combatant );

	/// Removes all incapacitated combatantants from this group.
	void RemoveIncapacitatedCombatants();

	/// Removes a combatants from this group.
	void RemoveAllCombatants();

	/// Returns true if all Combatants are incapacitated.
	bool IsDefeated() const;

	/// Returns true if one of this groups combatants is actor.
	bool ContainsActor( Actor* actor ) const;

	/// Returns true if this group contains combatant.
	bool ContainsCombatant( Combatant* combatant ) const;

	/// Gets all active combatants in this group.
	void GetActiveCombatants( vec_type& outActiveCombatants ) const;
	
	/// Gets all incapacitated combatants in this group.
	void GetIncapacitatedCombatants( vec_type& outIncapacitatedCombatants ) const;

	/// Gets the number of active combatants this group contains.
	u32 GetNumActiveCombatants() const;

	/// Gets the number of incapacitated combatants this group contains.
	u32 GetNumIncapacitatedCombatants() const;

	/// Gets the number of combatants this group contains.
	u32 GetNumCombatants() const;

	/// Selects a combatant at random from all active combatants in this group.
	Combatant* SelectRandomActiveCombatant() const;

	/// Selects a combatant at random from all incapacitated combatants in this group.
	Combatant* SelectRandomIncapacitatedCombatant() const;

	/// Selects a combatant at random from this group.
	Combatant* SelectRandomCombatant() const;

	/// Gets the combined exp value of all combatants in this group.
	int GetCombinedExp() const;

	/// Gets the combined gold amount of all combatants in this group.
	int GetCombinedGold() const;

	void Update();
	void Render();

	BattleFaction* GetBattleFaction() const { return m_battleFaction; }
	void SetBattleFaction( BattleFaction* battleFaction );

	/// Gets the combatant at index.
	Combatant* GetCombatant( u32 index ) const
	{
		return const_cast<Combatant*>(
			index < m_combatants.size() ? m_combatants[index] : 0);
	}

	vec_type& GetCombatants() { return m_combatants; }
	const vec_type& GetCombatants() const { return m_combatants; }

protected:
	vec_type		m_combatants;
	BattleFaction*	m_battleFaction;
	//u32			m_groupId;

};

