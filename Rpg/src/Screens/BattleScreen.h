
#pragma once

#include <fc/string.h>
#include <fc/vector.h>
#include <fc/fixed_vector.h>

#include "Screen.h"
#include "Battle.h"
#include "BattleActions.h"




class BattleScreen : public Screen
{
public:
	typedef fc::fixed_vector<Battle*, 16>	battle_vec_type;

	//So...
	//we need to,
	//push the game, script, camera, rendering state,
	//keep a list (queue) of battles,
	//update scripts, curent battle, and entities.

	BattleScreen( const fc::string& script );
	virtual ~BattleScreen();

	void AddBattle( Battle* battle );

	Battle* GetCurrentBattle();
	BattleActionQueue* GetActionQueue() { return &m_actionQueue; }

protected:
	//Script	m_script;
	BattleActionQueue			m_actionQueue;
	battle_vec_type				m_battles;
	//fc::vector<BattleAction*>	m_actions;
	//fc::vector<Actor*>		m_actors;

};


