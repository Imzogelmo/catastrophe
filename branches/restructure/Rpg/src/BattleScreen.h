
#pragma once

#include <fc/string.h>
#include <fc/vector.h>

#include "Screen.h"
#include "Battle.h"




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

protected:
	//Script	m_script;
	fc::vector<Battle*>			m_battles;
	fc::vector<BattleAction*>	m_actions;
	//fc::vector<Actor*>		m_actors;

};


