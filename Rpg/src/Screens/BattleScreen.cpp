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

#include "BattleScreen.h"




//BattleScreen::BattleScreen( const fc::string& script ) : Screen()
BattleScreen::BattleScreen() :
	Screen()
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


BattlePolicy BattleScreen::GetCurrentBattlePolicy()
{
	BattlePolicy battlePolicy;
	Battle* b = GetCurrentBattle();
	if( b != 0 )
		battlePolicy = b->GetBattlePolicy();

	return battlePolicy;
}


void BattleScreen::Update()
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
		MonsterCombatant* m = *it;
		m->Update();
		if( !m->IsAlive() )
		{
			if( battlePolicy.ShouldRemoveDeadMonsters() )
			{
			}
		}
	}
}


void BattleScreen::Render()
{
	for( player_vec_type::iterator it = m_players.begin(); it != m_players.end(); ++it )
	{
		//(*it)->Render();
	}

	for( monster_vec_type::iterator it = m_monsters.begin(); it != m_monsters.end(); ++it )
	{
		//(*it)->Render();
	}

}

