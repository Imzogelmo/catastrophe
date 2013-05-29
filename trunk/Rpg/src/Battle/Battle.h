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
#include "BattleEvent.h"
#include "BattleGroup.h"
#include "BattleEvent.h"



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



class Battle
{
public:
	typedef fc::vector<BattleEvent*>								event_vec_type;
	typedef fc::fixed_vector<BattleGroupData, MAX_BATTLE_GROUPS>	vec_type;

	int		bgm_id;
	int		background_sprite_id;


	Battle();
	~Battle();

	void CreateFromMonsterTroop( const MonsterTroop& monsterTroop );
	void AddMonsterTroop( const MonsterTroop& monsterTroop );

	void AddEvent( BattleEvent* battleEvent );
	void AddOutroEvent( BattleEvent* battleEvent );

	void SetUseBattleGroups( bool enable );
	bool GetUseBattleGroups();
	int GetNumGroups() const { return (int)m_battlerGroups.size(); }
	int GetBattlerCount() const;

	BattleGroupData& GetBattleGroup( int index ) { return m_battlerGroups.at(index); }
	const BattleGroupData& GetBattleGroup( int index ) const { return m_battlerGroups.at(index); }

	BattlePolicy GetBattlePolicy() const { return m_battlePolicy; }

protected:
	vec_type			m_battlerGroups;

	BattlePolicy		m_battlePolicy; //todo: remove this

	event_vec_type		m_eventQueue;
	event_vec_type		m_outroEvents;

	bool				m_useGroups;

};


