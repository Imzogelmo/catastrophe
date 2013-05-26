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

#include "GameData.h"
#include "Database.h"

//yep, sticking this here for now also.
GameData g_GameData;
GameData* GetGameData(){ return &g_GameData; }


GameData::GameData() :
	m_activeParty(0)
{
	CreateParty();
}


GameData::~GameData()
{
}


void GameData::Clear()
{
	//todo: free memory
	m_partyList.clear();
	m_characterActors.clear();
	m_monsterActors.clear();

	m_activeParty = 0;
}


void GameData::InitializeFromDatabase( Database* database )
{
	ASSERT(database != 0);

	m_database = database;

	Clear();
	CreateParty();

	size_t characterSize = database->characters.size();
	m_characterActors.reserve(characterSize * 2);

	for( size_t i(0); i < characterSize; ++i )
	{
		int actorId = database->characters[i].id;
		Actor* actor = new Actor();
		actor->InitializeFromCharacter(actorId);
		m_characterActors.push_back(actor);
	}
}


Actor* GameData::GetCharacterActor( int index )
{
	Actor* actor = 0;
	if( (size_t)index < m_characterActors.size() )
		actor = m_characterActors[index];

	return actor;
}


Actor* GameData::GetMonsterActor( int index )
{
	Actor* actor = 0;
	if( (size_t)index < m_monsterActors.size() )
		actor = m_monsterActors[index];

	return actor;
}


Actor* GameData::GetCharacterActorById( int id )
{
	actor_vec_type::const_iterator it;
	for( it = m_characterActors.begin(); it != m_characterActors.end(); ++it )
	{
		Actor* actor = *it;
		if( actor && actor->id == id )
			return actor;
	}

	return 0;
}


Actor* GameData::GetMonsterActorById( int id )
{
	actor_vec_type::const_iterator it;
	for( it = m_monsterActors.begin(); it != m_monsterActors.end(); ++it )
	{
		Actor* actor = *it;
		if( actor && actor->id == id )
			return actor;
	}

	return 0;
}



int GameData::CreateParty()
{
	int id = (int)m_partyList.size();
	m_partyList.push_back( new Party() );
	return id;
}


int GameData::RemoveParty( int id )
{
	if( m_partyList.empty() )
		return m_activeParty;

	if( (size_t)id < m_partyList.size() )
	{
		m_partyList.erase_at(id); //todo: free memory
		if( id <= m_activeParty )
			m_activeParty--;
	}

	return m_activeParty;
}


void GameData::SetActiveParty( int id )
{
	if( (size_t)id < m_partyList.size() )
		m_activeParty = id;
}


Party* GameData::GetParty( int id ) const
{
	Party* party = 0;
	if( (size_t)id < m_partyList.size() )
		party = m_partyList[id];

	return party;
}


Party* GameData::GetActiveParty() const
{
	return m_partyList.empty() ? 0 : m_partyList[m_activeParty];
}


