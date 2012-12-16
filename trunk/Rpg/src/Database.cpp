
#include "Database.h"
#include "ItemData.h"
#include "MonsterData.h"
#include "MonsterPartyData.h"
#include "EncounterData.h"


Database::Database()
{
	m_itemList = new ItemList();
	m_monsterList = new MonsterList();
	m_monsterPartyList = new MonsterPartyList();
	m_encounterList = new EncounterGroupList();
}


Database::~Database()
{
	delete m_itemList;
	delete m_monsterList;
	delete m_monsterPartyList;
	delete m_encounterList;
}


