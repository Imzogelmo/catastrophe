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

#include <fc/string.h>
#include <fc/vector.h>
#include <fc/fixed_vector.h>

#include "Common.h"
#include "Actor.h"
#include "Party.h"


class GameData
{
public:
	// todo: Custom allocators for speed and fragmentation.
	typedef fc::vector<Actor*>				actor_vec_type;
	typedef fc::fixed_vector<Party*, 16>	party_vec_type;

	GameData();
	~GameData();

	//void SetDatabase( Database* database );
	void Clear();
	void InitializeFromDatabase( Database* database );

	Actor* GetCharacterActor( int index );
	Actor* GetMonsterActor( int index );
	Actor* GetCharacterActorById( int id );
	Actor* GetMonsterActorById( int id );

	int CreateParty();
	int RemoveParty( int id );
	void SetActiveParty( int id );

	Party* GetParty( int id ) const;
	Party* GetActiveParty() const;

	Database* GetDatabase() const { return m_database; }

private:
	Database*			m_database;
	party_vec_type		m_partyList;
	actor_vec_type		m_characterActors;
	actor_vec_type		m_monsterActors;

	int					m_activeParty;

};


