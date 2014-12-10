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

#include "Combatant.h"
#include "BattleGroup.h"


// BattleFaction
//
// The main purpose of this class is to encapsulate Combatants and Combatant Groups
// in a simple way, provide easy and straight-forward algorithms for managing them,
// and to eliminate code duplication for differing factions.

class BattleFaction
{
public:
	typedef fc::static_vector<BattleGroup*, MAX_BATTLEFACTION_GROUPS> vec_type;

	BattleFaction();

	/// Creates a BattleGroup and adds it to the list of active groups.
	BattleGroup* CreateBattleGroup();

	/// Removes a battle group from this faction.
	void RemoveBattleGroup( BattleGroup* battleGroup );

	/// Removes all empty battle group from this faction.
	void RemoveEmptyBattleGroups();

	/// Removes a combatant if it exists inside a group in this faction.
	void RemoveCombatant( Combatant* combatant );

	/// Removes all incapacitated combatantants from all groups in this faction.
	void RemoveIncapacitatedCombatants();

	/// Removes all combatants from all groups in this faction.
	void RemoveAllCombatants();

	/// Returns true if all Combatants are incapacitated.
	bool IsDefeated() const;

	/// Returns true if one of this factions groups contains actor.
	bool ContainsActor( Actor* actor ) const;

	/// Returns true if one of this factions groups contains combatant.
	bool ContainsCombatant( Combatant* combatant ) const;

	/// Gets all active combatants in this faction.
	void GetActiveCombatants( BattleGroup::vec_type& outActiveCombatants ) const;

	/// Gets all incapacitated combatants in this faction.
	void GetIncapacitatedCombatants( BattleGroup::vec_type& outIncapacitatedCombatants ) const;

	/// Gets all the combatants that are contained in this faction.
	void GetCombatants( BattleGroup::vec_type& outCombatants ) const;

	/// Gets the number of active combatants in this faction.
	u32 GetNumActiveCombatants() const;

	/// Gets the number of incapacitated combatants in this faction.
	u32 GetNumIncapacitatedCombatants() const;

	/// Gets the total number of combatants in this faction.
	u32 GetNumCombatants() const;

	/// Selects a combatant at random from all active combatants in this faction.
	Combatant* SelectRandomActiveCombatant() const;

	/// Selects a combatant at random from all incapacitated combatants in this faction.
	Combatant* SelectRandomIncapacitatedCombatant() const;

	/// Selects a combatant at random from this faction.
	Combatant* SelectRandomCombatant() const;

	Combatant* GetClosestCombatantTo( Combatant* combatant ) const;
	Combatant* GetClosestCombatantInDirection( Combatant* combatant, int direction ) const;

	/// Gets the combined exp value of all combatants in this faction.
	int GetCombinedExp() const;

	/// Gets the combined gold amount of all combatants in this faction.
	int GetCombinedGold() const;

	void Update();
	void Render();

	/// Gets battle group at index.
	BattleGroup* GetBattleGroup( u32 groupNumber ) const
	{
		return const_cast<BattleGroup*>(
			groupNumber < m_groups.size() ? m_groups[groupNumber] : 0);
	}

	vec_type& GetGroups() { return m_groups; }
	const vec_type& GetGroups() const { return m_groups; }

protected:
	vec_type		m_groups;

};

