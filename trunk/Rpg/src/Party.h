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
#include <fc/string.h>

#include "Common.h"
#include "Inventory.h"


class PlayerCharacter;



struct GameClock
{
	int elapsed;
	int hours;
	int minutes;
	int seconds;

	GameClock()
		: elapsed(0), hours(0), minutes(0), seconds(0)
	{}

	void Tick()
	{
		if( ++elapsed % 60 == 0 )
			if( ++seconds % 60 == 0 )
				if( ++minutes % 60 == 0 )
					++hours;
	}

	int GetTicks() const
	{
		return elapsed;
	}

	int GetHours() const { return hours; }
	int GetMinutes() const { return minutes; }
	int GetSeconds() const { return seconds; }

	fc::string GetFormattedText() const
	{
		return fc::string(); //todo 
	}

};



struct GameStatistics
{
	enum Statistics
	{
		Victory,
		Defeat,
		Run,
		Steps,
		// reserved

		EngineDefinedMax = 8,
		MaxStatistics = 32,
		UserDefinedMax = MaxStatistics - EngineDefinedMax,
		Max = MaxStatistics
	};

	int				data[Max];
	GameClock		game_clock;
	fc::vector<int> monsters_defeated;


	GameStatistics()
	{
		::memset(data, 0, sizeof(int) * Max);
	}

	int GetStat( int index )
	{
		if( index >= Max )
			return 0;

		return data[index];
	}

	GameClock GetGameClock() const
	{
		return game_clock;
	}
	
};



class Party
{
public:
	typedef fc::vector<int>			vec_type;

	Party();

	void AddMember( int id );
	void RemoveMember( int id );

	bool HasMember( int id );
	bool IsMemberInActiveParty( int id );
	bool IsMemberInReserve( int id );
	bool IsMemberInActiveParty( int id, vec_type::iterator& outIt );
	bool IsMemberInReserve( int id, vec_type::iterator& outIt );


	int GetGold() const;
	int GetPartySize() const;
	int GetMaxPartySize() const;
	int GetMaxActivePartySize() const;

	void SetGold( int val );
	void AddGold( int amount );
	void RemoveGold( int amount );

	//void AddItem( int id, int amount = 1 );
	//void RemoveItem( int id, int amount = 1 );


	Inventory&		GetInventory() { return m_inventory; }
	vec_type&		GetActiveMembers() { return m_activeMembers; }
	vec_type&		GetReserveMembers() { return m_reserveMembers; }
	vec_type		GetAllPartyMembers() const;

protected:
	vec_type		m_activeMembers;
	vec_type		m_reserveMembers;
	Inventory		m_inventory;

	int				m_gold;
	int				m_maxPartySize;
	int				m_maxActivePartySize;

};






