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

#include <fc/string.h>
#include <fc/vector.h>
#include <fc/parallel.h>
#include <fc/fixed_vector.h>

#include "Battle.h"
#include "BattleActionQueue.h"
#include "Entity.h"
#include "EntitySorter.h"



class BattleCombatantGroup
{
public:
	typedef fc::vector<Combatant*>		vec_type;

	void CreateGroup( int monster_id, int n )
	{
	}


protected:
	vec_type	m_combatants;

};


class BattleEngine
{
public:
	typedef fc::fixed_vector<Battle*, 16>	battle_vec_type;
	typedef fc::vector<Entity*>				entity_vec_type;
	typedef fc::vector<Combatant*>			player_vec_type;
	typedef fc::vector<Combatant*>			monster_vec_type;
	typedef fc::vector<Actor*>				actor_vec_type;
	typedef fc::vector<BattleCombatantGroup>	group_vec_type;

	//So...
	//we need to,
	//push the game, script, camera, rendering state,
	//keep a list (queue) of battles,
	//update scripts, curent battle, and entities.

	//BattleScreen( const fc::string& script );

	BattleEngine();
	virtual ~BattleEngine();

	void Setup();
	void SetupMonsterCombatantsFromBattle( Battle* battle );
	void AddBattle( Battle* battle );
	//void RemoveBattle( Battle* battle );

	Battle* GetCurrentBattle();
	BattleActionQueue* GetBattleActionQueue() { return &m_actionQueue; }
	BattlePolicy GetCurrentBattlePolicy();


	void AddPlayerCombatantsFromParty( Party* party );
	//void AddMonsterCombatantsFromTroop( MonsterTroop* monsterTroop );
	void AddPlayerCombatant( Combatant* player );
	void AddMonsterCombatant( Combatant* monster );
	void AddEntity( Entity* e );
	void AddTextEntity( Entity* e );


	void Update();
	void Render();

protected:
	BattleActionQueue			m_actionQueue;
	battle_vec_type				m_battles;

	EntitySorter<EntitySortY>	m_sortedEntities;
	entity_vec_type				m_entityGarbageBin;
	entity_vec_type				m_textEntities;
	entity_vec_type				m_entities;
	player_vec_type				m_players;
	monster_vec_type			m_monsters;
	group_vec_type				m_groups;
	actor_vec_type				m_tempActors;

	monster_vec_type			m_deadMonsters;

};


