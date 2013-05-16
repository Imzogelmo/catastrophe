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

#include "Screen.h"
#include "Battle.h"
#include "BattleActionQueue.h"
#include "Entity.h"
#include "PlayerCombatant.h"
#include "MonsterCombatant.h"



class BattleScreen : public Screen
{
public:
	typedef fc::fixed_vector<Battle*, 16>	battle_vec_type;
	typedef fc::vector<Entity*>				entity_vec_type;
	typedef fc::vector<PlayerCombatant*>	player_vec_type;
	typedef fc::vector<MonsterCombatant*>	monster_vec_type;

	//So...
	//we need to,
	//push the game, script, camera, rendering state,
	//keep a list (queue) of battles,
	//update scripts, curent battle, and entities.

	//BattleScreen( const fc::string& script );

	BattleScreen();
	virtual ~BattleScreen();

	void AddBattle( Battle* battle );
	//void RemoveBattle( Battle* battle );

	Battle* GetCurrentBattle();
	BattleActionQueue* GetBattleActionQueue() { return &m_actionQueue; }
	BattlePolicy GetCurrentBattlePolicy();

	void Update();
	void Render();

protected:
	BattleActionQueue			m_actionQueue;
	battle_vec_type				m_battles;

	entity_vec_type				m_textEntities;
	player_vec_type				m_players;
	monster_vec_type			m_monsters;


	//fc::vector<BattleAction*>	m_actions;
	//fc::vector<Actor*>		m_actors;

};


