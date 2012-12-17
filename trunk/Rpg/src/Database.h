
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
	SpellList*			GetSpellList() const { return m_spellList; }
	MonsterList*		GetMonsterList() const { return m_monsterList; }
	MonsterPartyList*	GetMonsterPartyList() const { return m_monsterPartyList; }
	EncounterGroupList*	GetEncounterGroupList() const { return m_encounterList; }
	CharacterClassList* GetCharacterClassList() const { return m_characterClassList; }

private:
	ItemList*			m_itemList;
	SpellList*			m_spellList;
	MonsterList*		m_monsterList;
	MonsterPartyList*	m_monsterPartyList;
	EncounterGroupList*	m_encounterList;
	CharacterClassList* m_characterClassList;

};

