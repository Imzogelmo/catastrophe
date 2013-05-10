
#include "BattleScreen.h"




BattleScreen::BattleScreen( ScreenManager* parent, const fc::string& script ) : Screen(parent)
{
}


BattleScreen::~BattleScreen()
{
}


void BattleScreen::AddBattle( Battle* battle )
{
	if( battle )
		m_battles.push_back(battle);
}


Battle* BattleScreen::GetCurrentBattle()
{
	if( !m_battles.empty() )
		return m_battles.front();

	return 0;
}


