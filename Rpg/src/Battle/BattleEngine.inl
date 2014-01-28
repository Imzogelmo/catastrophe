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
#include "Combatant.h"
#include "Actor.h"
#include "Party.h"
#include "Game.h"
#include "GameData.h"



BattleEngine::BattleEngine()
{
}


BattleEngine::~BattleEngine()
{
}


void BattleEngine::Setup()
{
	Battle* battle = GetCurrentBattle();
	if( !battle )
		return;

	// for each monster in each group of the battle class,
	// we have to create an instance Combatant, and if
	// need be, a base Actor class as well.
	int n = battle->GetNumGroups();

	for( int j(0); j < n; ++j )
	{
		BattleGroupData & group = battle->GetBattleGroup(j);

		for( size_t i(0); i < group.battlers.size(); ++i )
		{
			Actor* actor = new Actor(); //todo: We can actually pool these.
			actor->InitializeFromMonster(group.battlers[i].id);
			m_tempActors.push_back(actor);

			Combatant* enemy = new Combatant();
			enemy->InitializeFromActor(actor);
			AddMonsterCombatant(enemy);
		}
	}
}


void BattleEngine::SetupMonsterCombatantsFromBattle( Battle* battle )
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


void BattleEngine::AddPlayerCombatantsFromParty( Party* party )
{
	ASSERT(party != 0);

	Party::vec_type& partyMembers = party->GetActiveMembers();
	if( partyMembers.empty() )
	{
		//what to do???
	}

	for( size_t i(0); i < partyMembers.size(); ++i )
	{
		int actor_id = partyMembers[i];
		//Actor* actor = GetGameData()->GetCharacterActorById(actor_id);
		Actor* actor = GetGameData()->GetCharacterActor(actor_id);

		if( actor )
		{
			Combatant* playerCombatant = new Combatant();
			playerCombatant->InitializeFromActor(actor);
			AddPlayerCombatant(playerCombatant);
		}
	}
}


void BattleEngine::AddPlayerCombatant( Combatant* player )
{
	m_players.push_back(player);
	m_sortedEntities.AddEntity(player);
}


void BattleEngine::AddMonsterCombatant( Combatant* monster )
{
	m_monsters.push_back(monster);
	m_sortedEntities.AddEntity(monster);
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
				//todo: should it be stored inside object?
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
		(*it)->Render();
	}

	// battle texts
	for( entity_vec_type::iterator it = m_textEntities.begin(); it != m_textEntities.end(); ++it )
	{
		(*it)->Render();
	}

	// battle texts
	for( entity_vec_type::iterator it = m_sortedEntities.m_entities.begin(); it != m_sortedEntities.m_entities.end(); ++it )
	{
		(*it)->Render();
	}

	//m_sortedEntities.RemoveDeadEntities();
	m_sortedEntities.Sort();
	//for( int i(m_sortedEntities.m_entities.size()); i > 0 ; )
	//{
	//	m_sortedEntities.m_entities[--i]->Render();
	//}
	for( size_t i(0); i < m_sortedEntities.m_entities.size(); ++i )
	{
		m_sortedEntities.m_entities[i]->Render();
	}
	//todo:

}

