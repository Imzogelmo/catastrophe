
#pragma once

#include "Common.h"


/*
 * @database
 * 
 */
class Database
{
public:
	Database();
	~Database();

	ItemList*			GetItemList() const { return m_itemList; }
	MonsterList*		GetMonsterList() const { return m_monsterList; }
	EncounterGroupList*	GetEncounterGroupList() const { return m_encounterList; }

private:
	ItemList*			m_itemList;
	MonsterList*		m_monsterList;
	MonsterPartyList*	m_monsterPartyList;
	EncounterGroupList*	m_encounterList;

};

