
#include "Database.h"
#include "ItemData.h"
#include "SpellData.h"
#include "MonsterData.h"
#include "MonsterPartyData.h"
#include "EncounterData.h"
#include "CharacterClass.h"


Database::Database()
{
	m_itemList = new ItemList();
	m_spellList = new SpellList();
	m_monsterList = new MonsterList();
	m_monsterPartyList = new MonsterPartyList();
	m_encounterList = new EncounterGroupList();
	m_characterClassList = new CharacterClassList();

}


Database::~Database()
{
	delete m_itemList;
	delete m_spellList;
	delete m_monsterList;
	delete m_monsterPartyList;
	delete m_encounterList;
	delete m_characterClassList;

}

