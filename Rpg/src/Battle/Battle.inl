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

#include "Battle.h"
#include "MonsterTroop.h"
#include "Database.h"



Battle::Battle() :
	m_useGroups(false)
{
}


Battle::~Battle()
{
}


void Battle::CreateFromMonsterTroopId( int troop_id )
{
	MonsterTroop* troop = GetDatabase()->GetMonsterTroop(troop_id);
	if( troop )
		CreateFromMonsterTroop(*troop);
}


void Battle::AddMonsterTroopId( int troop_id )
{
	MonsterTroop* troop = GetDatabase()->GetMonsterTroop(troop_id);
	if( troop )
		AddMonsterTroop(*troop);
}


void Battle::CreateFromMonsterTroop( const MonsterTroop& monsterTroop )
{
	m_battlerGroups.reset();
	AddMonsterTroop(monsterTroop);
}


void Battle::AddMonsterTroop( const MonsterTroop& monsterTroop )
{
	int numGroups = fc::min<int>(monsterTroop.groups.size(), MAX_BATTLE_GROUPS);
	if( numGroups == 0 )
		return;

	if( m_useGroups )
	{
		m_battlerGroups.reserve(m_battlerGroups.size() + numGroups);

		// if we are empty or the last group already has monsters in it, start a new group.
		if( m_battlerGroups.empty() ||
			( !m_battlerGroups.empty() && !m_battlerGroups.back().battlers.empty() )
		)
		{
			m_battlerGroups.push_back();
		}

		for( int i(0); i < numGroups; ++i )
		{
			const MonsterGroup & monsterGroup = monsterTroop.groups[i];

			// It's possible to create zero monsters.
			int n = m_battlerGroups.back().CreateFromMonsterGroup(monsterGroup);
			if( n > 0 && i < numGroups - 1 )
				m_battlerGroups.push_back();
		}
	}
	else
	{
		if( m_battlerGroups.empty() )
			m_battlerGroups.push_back();

		for( int i(0); i < numGroups; ++i )
		{
			m_battlerGroups.back().AddMonsterGroup(monsterTroop.groups[i]);
		}
	}

	// If no monsters were added, and the total is zero, we force-add the leader.
	if( GetBattlerCount() == 0 )
	{
		if( m_battlerGroups.empty() )
			m_battlerGroups.push_back();

		m_battlerGroups.back().ForceAddSingleMonsterFromGroup(monsterTroop.groups[0]);
	}
}


void Battle::AddEvent( BattleEvent* battleEvent )
{
	m_eventQueue.push_back(battleEvent);
}


void Battle::AddOutroEvent( BattleEvent* battleEvent )
{
	m_outroEvents.push_back(battleEvent);
}


void Battle::SetUseBattleGroups( bool enable )
{
	m_useGroups = enable;
}


bool Battle::GetUseBattleGroups()
{
	return m_useGroups;
}


int Battle::GetBattlerCount() const
{
	int n = 0;
	for( vec_type::const_iterator it = m_battlerGroups.begin(); it != m_battlerGroups.end(); ++it )
	{
		n += it->GetBattlerCount();
	}

	return n;
}

