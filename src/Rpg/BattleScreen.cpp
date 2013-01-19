
#include "BattleScreen.h"




Battle( ScreenManager* parent, const fc::string& script ) : Screen(parent)
{
}


void BattleScreen::AddAction( BattleAction* action, bool immediateAction )
{
	// Insert at either front or back.
	// "counterattack" is an example of an immediate action.
	size_t index = immediateAction ? (size_t)0 : m_actions.size();
	m_actions.insert_at(index);
}


void BattleScreen::ClearActions()
{
	m_actions.clear();
}



void BattleScreen::AddBattle( Battle* battle )
{
	if( battle )
		m_battles.push_back(battle);
}



Battle* GetCurrentBattle()
{
	if( !m_battles.empty() )
		return m_battles.front();

	return 0;
}


