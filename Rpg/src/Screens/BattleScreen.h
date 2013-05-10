
#pragma once

#include <fc/string.h>
#include <fc/vector.h>

#include "Screen.h"
#include "Battle.h"
#include "BattleActions.h"




class BattleScreen : public Screen
{
public:
	//So...
	//we need to,
	//push the game, script, camera, rendering state,
	//keep a list (queue) of battles,
	//update scripts, curent battle, and entities.

	Battle( ScreenManager* parent, const fc::string& script );
	virtual ~Battle();

	void AddAction( BattleAction* action, bool immediateAction = false );
	void ClearActions();

	void AddBattle( Battle* battle );

	Battle* GetCurrentBattle();
	BattleActionQueue* GetActionQueue() { return &m_actionQueue; }

protected:
	//Script	m_script;
	BattleActionQueue			m_actionQueue;
	fc::vector<Battle*>			m_battles;
	//fc::vector<BattleAction*>	m_actions;
	//fc::vector<Actor*>		m_actors;

};


