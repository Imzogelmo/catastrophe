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

#include "BattleEngine.h"



BattleEngine::BattleEngine()
{
}


BattleEngine::~BattleEngine()
{
}


void BattleEngine::AddBattle( Battle* battle )
{
	if( battle )
		m_battles.push_back(battle);
}


Battle* BattleEngine::GetCurrentBattle()
{
	if( !m_battles.empty() )
		return m_battles.front();

	return 0;
}


BattlePolicy BattleEngine::GetCurrentBattlePolicy()
{
	BattlePolicy battlePolicy;
	Battle* b = GetCurrentBattle();
	if( b != 0 )
		battlePolicy = b->GetBattlePolicy();

	return battlePolicy;
}


void BattleEngine::AddPlayerCombatant( Combatant* player )
{
	m_players.push_back(player);
	//m_sortedEntities.push_back(player);
}


void BattleEngine::AddMonsterCombatant( Combatant* monster )
{
	m_monsters.push_back(monster);
	//m_sortedEntities.push_back(monster);
}


void BattleEngine::AddEntity( Entity* e )
{
	m_entities.push_back(e);
}


void BattleEngine::AddTextEntity( Entity* e )
{
	m_textEntities.push_back(e);
}


void BattleEngine::Update()
{
	BattlePolicy battlePolicy = GetCurrentBattlePolicy();

	// update players
	for( player_vec_type::iterator it = m_players.begin(); it != m_players.end(); ++it )
	{
		(*it)->Update();
	}

	// update monsters
	for( monster_vec_type::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it )
	{
		Combatant* m = *it;
		m->Update();
		if( !m->IsAlive() )
		{
			if( battlePolicy.ShouldRemoveDeadMonsters() )
			{
			}
		}
	}

	// update other entities
	for( entity_vec_type::iterator it = m_entities.begin(); it != m_entities.end(); ++it )
	{
		(*it)->Update();
	}

	// update battle texts
	for( entity_vec_type::iterator it = m_textEntities.begin(); it != m_textEntities.end(); ++it )
	{
		(*it)->Update();
	}

}


void BattleEngine::Render()
{
	// players
	for( player_vec_type::iterator it = m_players.begin(); it != m_players.end(); ++it )
	{
		//(*it)->Render();
	}

	// monsters
	for( monster_vec_type::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it )
	{
		//(*it)->Render();
	}

	// entities
	for( entity_vec_type::iterator it = m_entities.begin(); it != m_entities.end(); ++it )
	{
		//(*it)->Render();
	}

	// battle texts
	for( entity_vec_type::iterator it = m_textEntities.begin(); it != m_textEntities.end(); ++it )
	{
		//(*it)->Render();
	}

	//m_sortedEntities.RemoveDeadEntities();
	//m_sortedEntities.Sort();
	//todo:

}

