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
#include <Catastrophe/Math/Vector2.h>

#include "Common.h"

#define MAX_BATTLE_GROUP_SIZE	256
#define MAX_BATTLE_GROUPS		16


struct BattleGroupEntityData
{
	int		id;
	int		flags;
	Vector2	pos;

	BattleGroupEntityData( int id = 0, const Vector2& pos = Vector2::Zero) :
		id(id), pos(pos)
	{}

};


struct BattleGroupData
{
	typedef fc::vector<BattleGroupEntityData>		vec_type;
	
	vec_type	battlers;

	/// Initialize from MonsterGroup. Returns the number of added monsters.
	int CreateFromMonsterGroup( const MonsterGroup& monsterGroup );

	/// Add a MonsterGroup to this group. Returns the number of added monsters.
	int AddMonsterGroup( const MonsterGroup& monsterGroup );

	void ForceAddSingleMonsterFromGroup( const MonsterGroup& monsterGroup );
	void AddBattler( const BattleGroupEntityData& data );
	void AddBattler( int id, const Vector2& pos = Vector2::Zero );
	void RemoveBattler( int id );

	int GetBattlerCount() const { return (int)battlers.size(); }

};

