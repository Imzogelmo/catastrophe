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

#include "BattleFaction.h"


BattleFaction::BattleFaction() :
	m_groups()
{
}


BattleGroup* BattleFaction::CreateBattleGroup()
{
	if( m_groups.full() )
		return null;

	BattleGroup* battleGroup = new BattleGroup();
	battleGroup->SetBattleFaction(this);
	//battleGroup->SetGroupNumber(m_groups.size());
	m_groups.push_back(battleGroup);

	return battleGroup;
}


void BattleFaction::RemoveBattleGroup( BattleGroup* battleGroup )
{
	for( vec_type::iterator it = m_groups.begin(); it != m_groups.end(); )
	{
		BattleGroup* group = *it;
		if( group == battleGroup )
		{
			//TODO: This is depricated:

			// set the next groups groupId accordingly
			for( vec_type::iterator next = it + 1; next != m_groups.end(); )
			{
				BattleGroup::vec_type& v = group->GetCombatants();
				for( BattleGroup::vec_type::iterator c = v.begin(); c != v.end(); ++c )
				{
					int currentGroup = (*c)->GetBattleGroup();
					(*c)->SetBattleGroup(currentGroup - 1);
				}
			}

			group->SetBattleFaction(null);
			m_groups.erase(it);

			break;
		}
		else
			++it;
	}
}


void BattleFaction::RemoveEmptyBattleGroups()
{
	for( vec_type::iterator it = m_groups.begin(); it != m_groups.end(); )
	{
		if( (*it)->GetNumCombatants() == 0 )
			RemoveBattleGroup(*it);
		else
			++it;
	}
}


void BattleFaction::RemoveCombatant( Combatant* combatant )
{
	if( combatant != null )
	{
		int battleGroup = combatant->GetBattleGroup();
		if( (u32)battleGroup < m_groups.size() )
			m_groups[battleGroup]->RemoveCombatant(combatant);
	}
}


void BattleFaction::RemoveIncapacitatedCombatants()
{
	for( vec_type::iterator it = m_groups.begin(); it != m_groups.end(); ++it )
		(*it)->RemoveIncapacitatedCombatants();
}


void BattleFaction::RemoveAllCombatants()
{
	for( vec_type::iterator it = m_groups.begin(); it != m_groups.end(); ++it )
		(*it)->RemoveAllCombatants();
}


bool BattleFaction::IsDefeated() const
{
	for( vec_type::const_iterator it = m_groups.begin(); it != m_groups.end(); ++it )
		if( !(*it)->IsDefeated() )
			return false;

	return true;
}


bool BattleFaction::ContainsActor( Actor* actor ) const
{
	for( vec_type::const_iterator it = m_groups.begin(); it != m_groups.end(); ++it )
		if( (*it)->ContainsActor(actor) )
			return true;

	return false;
}


bool BattleFaction::ContainsCombatant( Combatant* combatant ) const
{
	for( vec_type::const_iterator it = m_groups.begin(); it != m_groups.end(); ++it )
		if( (*it)->ContainsCombatant(combatant) )
			return true;

	return false;
}


void BattleFaction::GetActiveCombatants( BattleGroup::vec_type& outActiveCombatants ) const
{
	for( vec_type::const_iterator it = m_groups.begin(); it != m_groups.end(); ++it )
		(*it)->GetActiveCombatants(outActiveCombatants);
}


void BattleFaction::GetIncapacitatedCombatants( BattleGroup::vec_type& outIncapacitatedCombatants ) const
{
	for( vec_type::const_iterator it = m_groups.begin(); it != m_groups.end(); ++it )
		(*it)->GetIncapacitatedCombatants(outIncapacitatedCombatants);
}


void BattleFaction::GetCombatants( BattleGroup::vec_type& outCombatants ) const
{
	for( vec_type::const_iterator it = m_groups.begin(); it != m_groups.end(); ++it )
	{
		BattleGroup::vec_type& v = (*it)->GetCombatants();
		if( !v.empty() )
		{
			Combatant** p = outCombatants.push_back_uninitialized(v.size());
			fc::copy(v.begin(), v.end(), p);
		}
	}
}


u32 BattleFaction::GetNumActiveCombatants() const
{
	u32 totalActiveCombatants = 0;
	for( vec_type::const_iterator it = m_groups.begin(); it != m_groups.end(); ++it )
		totalActiveCombatants += (*it)->GetNumActiveCombatants();

	return totalActiveCombatants;
}


u32 BattleFaction::GetNumIncapacitatedCombatants() const
{
	u32 totalIncapacitatedCombatants = 0;
	for( vec_type::const_iterator it = m_groups.begin(); it != m_groups.end(); ++it )
		totalIncapacitatedCombatants += (*it)->GetNumIncapacitatedCombatants();

	return totalIncapacitatedCombatants;
}


u32 BattleFaction::GetNumCombatants() const
{
	u32 numCombatants = 0;
	for( vec_type::const_iterator it = m_groups.begin(); it != m_groups.end(); ++it )
		numCombatants += (*it)->GetNumCombatants();

	return numCombatants;
}


Combatant* BattleFaction::SelectRandomActiveCombatant() const
{
	if( m_groups.empty() )
		return null;

	// Return a random enomy from a random group.
	return m_groups[ fc::rand(m_groups.size()) ]->SelectRandomActiveCombatant();
}


Combatant* BattleFaction::SelectRandomIncapacitatedCombatant() const
{
	if( m_groups.empty() )
		return null;

	// Return a random enomy from a random group.
	return m_groups[ fc::rand(m_groups.size()) ]->SelectRandomIncapacitatedCombatant();
}


Combatant* BattleFaction::SelectRandomCombatant() const
{
	if( m_groups.empty() )
		return null;

	// Return a random enomy from a random group.
	return m_groups[ fc::rand(m_groups.size()) ]->SelectRandomCombatant();
}


Combatant* BattleFaction::GetClosestCombatantTo( Combatant* combatant ) const
{
	float closestDistance = 100000.f;
	Combatant* closestCombatant = null;

	if( combatant )
	{
		for( vec_type::const_iterator group = m_groups.begin(); group != m_groups.end(); ++group )
		{
			BattleGroup::vec_type& v = (*group)->GetCombatants();
			for( BattleGroup::vec_type::const_iterator it = v.begin(); it != v.end(); ++it )
			{
				const Combatant* p = *it;
				if( p != combatant )
				{
					float distanceSquared = combatant->position.DistanceSquared(p->position);
					if( distanceSquared < closestDistance )
					{
						closestDistance = distanceSquared;
						closestCombatant = const_cast<Combatant*>(p);
					}
				}
			}
		}
	}

	return closestCombatant;
}


Combatant* BattleFaction::GetClosestCombatantInDirection( Combatant* combatant, int direction ) const
{
	if( (size_t)direction > 4 )
		return 0;

	float closestDistance = 10000.f;
	Combatant* closestCombatant = null;

	if( combatant )
	{
		for( vec_type::const_iterator group = m_groups.begin(); group != m_groups.end(); ++group )
		{
			BattleGroup::vec_type& v = (*group)->GetCombatants();
			for( BattleGroup::vec_type::const_iterator it = v.begin(); it != v.end(); ++it )
			{
				const Combatant* p = *it;
				const Vector2& position = combatant->position;
				const Vector2& otherPosition = p->position;

				if( p == combatant )
					continue;
				if( direction == 1 && !(otherPosition.y < position.y) )
					continue;
				if( direction == 2 && !(otherPosition.y > position.y) )
					continue;
				if( direction == 3 && !(otherPosition.x < position.x) )
					continue;
				if( direction == 4 && !(otherPosition.x > position.x) )
					continue;

				const float distanceSquared = position.DistanceSquared(otherPosition);
				if( distanceSquared < closestDistance )
				{
					closestDistance = distanceSquared;
					closestCombatant = const_cast<Combatant*>(p);
				}
			}
		}
	}

	return closestCombatant;
}


int BattleFaction::GetCombinedExp() const
{
	int totalExp = 0;
	for( vec_type::const_iterator it = m_groups.begin(); it != m_groups.end(); ++it )
		totalExp += (*it)->GetCombinedExp();

	return totalExp;
}


int BattleFaction::GetCombinedGold() const
{
	int totalGold = 0;
	for( vec_type::const_iterator it = m_groups.begin(); it != m_groups.end(); ++it )
		totalGold += (*it)->GetCombinedGold();

	return totalGold;
}


void BattleFaction::Update()
{
	for( vec_type::iterator it = m_groups.begin(); it != m_groups.end(); ++it )
	{
		(*it)->Update();
	}
}


void BattleFaction::Render()
{
	for( vec_type::iterator it = m_groups.begin(); it != m_groups.end(); ++it )
	{
		(*it)->Render();
	}
}

