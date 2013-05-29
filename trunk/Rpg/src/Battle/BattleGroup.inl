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

#include <fc/rand.h>

#include "BattleGroup.h"
#include "MonsterTroop.h"


int BattleGroupData::CreateFromMonsterGroup( const MonsterGroup& monsterGroup )
{
	battlers.clear();
	return AddMonsterGroup(monsterGroup);
}


int BattleGroupData::AddMonsterGroup( const MonsterGroup& monsterGroup )
{
	int n = fc::min( fc::rand(monsterGroup.min, monsterGroup.max), MAX_BATTLE_GROUP_SIZE );
	for( int i(0); i < n; ++i )
	{
		ForceAddSingleMonsterFromGroup(monsterGroup);
	}

	return n;
}


void BattleGroupData::ForceAddSingleMonsterFromGroup( const MonsterGroup& monsterGroup )
{
	BattleGroupEntityData data;

	data.id = monsterGroup.monster_id;
	data.pos.x = (float)monsterGroup.x;
	data.pos.y = (float)monsterGroup.y;

	AddBattler(data);
}


void BattleGroupData::AddBattler( const BattleGroupEntityData& data )
{
	if( battlers.size() < MAX_BATTLE_GROUP_SIZE )
	{
		battlers.push_back(data);
	}
}


void BattleGroupData::AddBattler( int id, const Vector2& pos )
{
	AddBattler( BattleGroupEntityData(id, pos) );
}


void BattleGroupData::RemoveBattler( int id )
{
	for( vec_type::iterator it = battlers.begin(); it != battlers.end(); ++it )
	{
		if( it->id == id )
		{
			battlers.erase(it);
			break;
		}
	}
}


