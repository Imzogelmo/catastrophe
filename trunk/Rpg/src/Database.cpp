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

#include "Database.h"
#include "ItemData.h"
#include "SpellData.h"
#include "MonsterData.h"
#include "MonsterPartyData.h"
#include "EncounterData.h"
#include "CharacterClass.h"
#include "ExpTable.h"


Database::Database()
{
	m_itemList = new ItemList();
	m_spellList = new SpellList();
	m_monsterList = new MonsterList();
	m_monsterPartyList = new MonsterPartyList();
	m_encounterList = new EncounterGroupList();
	m_characterClassList = new CharacterClassList();
	m_expTableList = new ExpTableList();

}


Database::~Database()
{
	delete m_itemList;
	delete m_spellList;
	delete m_monsterList;
	delete m_monsterPartyList;
	delete m_encounterList;
	delete m_characterClassList;
	delete m_expTableList;

}


void Database::Initialize()
{
	m_itemList->DeserializeXml("items.xml");
	m_monsterPartyList->DeserializeXml("monsters.xml");

}



