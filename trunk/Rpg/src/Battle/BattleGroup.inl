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

#include <fc/rand.h>

#include "BattleGroup.h"


BattleGroup::BattleGroup() :
	m_combatants(),
	m_battleFaction(null)
{
}


void BattleGroup::AddCombatant( Combatant* combatant )
{
	if( combatant != 0 )
		m_combatants.push_back(combatant);
}


void BattleGroup::InsertCombatant( Combatant* combatant, u32 position )
{
	if( combatant != 0 && position <= m_combatants.size() )
		m_combatants.insert_at(position, combatant);
}


void BattleGroup::RemoveCombatant( Combatant* combatant )
{
	for( vec_type::iterator it = m_combatants.begin(); it != m_combatants.end(); )
		if( *it == combatant )
		{
			m_combatants.erase(it);
			break;
		}
}


void BattleGroup::RemoveAllCombatants()
{
	m_combatants.clear(); //todo: manage memory
}


void BattleGroup::RemoveIncapacitatedCombatants()
{
	for( vec_type::iterator it = m_combatants.begin(); it != m_combatants.end(); )
	{
		if( (*it)->IsIncapacitated() )
			m_combatants.erase(it);

		else ++it;
	}
}


bool BattleGroup::IsDefeated() const
{
	for( vec_type::const_iterator it = m_combatants.begin(); it != m_combatants.end(); ++it )
		if( !(*it)->IsIncapacitated() )
			return false;

	return true;
}


bool BattleGroup::ContainsActor( Actor* actor ) const
{
	for( vec_type::const_iterator it = m_combatants.begin(); it != m_combatants.end(); ++it )
		if( (*it)->GetActor() == actor )
			return true;

	return false;
}


bool BattleGroup::ContainsCombatant( Combatant* combatant ) const
{
	for( vec_type::const_iterator it = m_combatants.begin(); it != m_combatants.end(); ++it )
		if( (*it) == combatant )
			return true;

	return false;
}


void BattleGroup::GetActiveCombatants( vec_type& outActiveCombatants ) const
{
	for( vec_type::const_iterator it = m_combatants.begin(); it != m_combatants.end(); ++it )
	{
		if( !(*it)->IsIncapacitated() )
			outActiveCombatants.push_back( const_cast<Combatant*>(*it) );
	}
}


void BattleGroup::GetIncapacitatedCombatants( vec_type& outIncapacitatedCombatants ) const
{
	for( vec_type::const_iterator it = m_combatants.begin(); it != m_combatants.end(); ++it )
	{
		if( (*it)->IsIncapacitated() )
			outIncapacitatedCombatants.push_back( const_cast<Combatant*>(*it) );
	}
}


u32 BattleGroup::GetNumActiveCombatants() const
{
	u32 totalActiveCombatants = 0;
	for( vec_type::const_iterator it = m_combatants.begin(); it != m_combatants.end(); ++it )
	{
		if( !(*it)->IsIncapacitated() )
			++totalActiveCombatants;
	}

	return totalActiveCombatants;
}


u32 BattleGroup::GetNumIncapacitatedCombatants() const
{
	u32 totalIncapacitatedCombatants = 0;
	for( vec_type::const_iterator it = m_combatants.begin(); it != m_combatants.end(); ++it )
	{
		if( (*it)->IsIncapacitated() )
			++totalIncapacitatedCombatants;
	}

	return totalIncapacitatedCombatants;
}


u32 BattleGroup::GetNumCombatants() const
{
	return m_combatants.size();
}


Combatant* BattleGroup::SelectRandomActiveCombatant() const
{
	vec_type activeCombatants;
	GetActiveCombatants(activeCombatants);
	if( activeCombatants.empty() )
		return null;

	return activeCombatants[ fc::rand(activeCombatants.size()) ];
}


Combatant* BattleGroup::SelectRandomIncapacitatedCombatant() const
{
	vec_type incapacitatedCombatants;
	GetIncapacitatedCombatants(incapacitatedCombatants);
	if( incapacitatedCombatants.empty() )
		return null;

	return incapacitatedCombatants[ fc::rand(incapacitatedCombatants.size()) ];
}


Combatant* BattleGroup::SelectRandomCombatant() const
{
	if( m_combatants.empty() )
		return null;

	return m_combatants[ fc::rand(m_combatants.size()) ];
}


int BattleGroup::GetCombinedExp() const
{
	int totalExp = 0;
	for( vec_type::const_iterator it = m_combatants.begin(); it != m_combatants.end(); ++it )
	{
		const Actor* actor = (*it)->GetActor();
		if( actor )
			totalExp += actor->GetExp();
	}

	return totalExp;
}


int BattleGroup::GetCombinedGold() const
{
	int totalGold = 0;
	for( vec_type::const_iterator it = m_combatants.begin(); it != m_combatants.end(); ++it )
	{
		const Actor* actor = (*it)->GetActor();
		if( actor )
			totalGold += actor->GetGold();
	}

	return totalGold;
}


void BattleGroup::Update()
{
	for( vec_type::iterator it = m_combatants.begin(); it != m_combatants.end(); ++it )
	{
		Combatant* combatant = *it;
		combatant->Update();
	}
}


void BattleGroup::Render()
{
	for( vec_type::iterator it = m_combatants.begin(); it != m_combatants.end(); ++it )
	{
		Combatant* combatant = *it;
		combatant->Render();
	}
}


void BattleGroup::SetBattleFaction( BattleFaction* battleFaction )
{
	if( m_battleFaction != null )
		m_battleFaction->RemoveBattleGroup(this);

	m_battleFaction = battleFaction;
}

