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

#include <fc/vector.h>
#include <fc/fixed_vector.h>

#include "Common.h"



struct BattlePolicy
{
	bool remove_dead_monsters;

	BattlePolicy() :
		remove_dead_monsters(true)
	{}

	bool ShouldRemoveDeadMonsters() const
	{
		return remove_dead_monsters;
	}

};

class BattleEvent
{
public:

};


class BattlerGroup
{
public:
	typedef fc::fixed_vector<int, 16>				vec_type;

	vec_type battlers;

	void AddBattler( int id );
	void RemoveBattler( int id );

};


class Battle
{
public:
	typedef fc::vector<BattleEvent*>	event_vec_type;
	typedef fc::vector<BattlerGroup>	battler_vec_type;
	typedef fc::vector<int>				vec_type;

	Battle();
	~Battle();

	void AddEvent( BattleEvent* battleEvent );
	void AddOutroEvent( BattleEvent* battleEvent );

	//void SetMusic( Sound* sound );
	//Sound* GetMusic() const { return m_bgm; }

	BattlerGroup& GetBattlerGroup( int index ) { return m_battlerGroups.at(index); }
	const BattlerGroup& GetBattlerGroup( int index ) const { return m_battlerGroups.at(index); }


	BattlePolicy GetBattlePolicy() const { return m_battlePolicy; }

protected:
	battler_vec_type	m_battlerGroups;

	//MonsterTroop	m_monsterParty;
	//Party			m_party;...?
	BattlePolicy		m_battlePolicy;

	event_vec_type		m_eventQueue;
	event_vec_type		m_outroEvents;

	//Sound*				m_bgm;
	//AnimatedSprite		m_background;
	//int		m_background_id;


};


