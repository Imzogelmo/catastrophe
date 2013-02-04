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

#include "Common.h"


/*
 * @database
 * 
 */
class RPG_API Database
{
public:
	Database();
	~Database();

	void Initialize();

	ItemList*			GetItemList() const { return m_itemList; }
	SpellList*			GetSpellList() const { return m_spellList; }
	MonsterList*		GetMonsterList() const { return m_monsterList; }
	MonsterPartyList*	GetMonsterPartyList() const { return m_monsterPartyList; }
	EncounterGroupList*	GetEncounterGroupList() const { return m_encounterList; }
	CharacterClassList* GetCharacterClassList() const { return m_characterClassList; }

	//SpriteList* GetPortraits() const { return m_portraitSprites; }
	//AnimatedSpriteList* GetSpriteList() const { return m; }
	//AnimatedSpriteList* GetSpriteList() const { return m; }


	//typedef fc::vector<int>			sound_vec_type;


	//sound_vec_type		default_sfx;
	//sound_vec_type		default_music;

	//fc::string			title;
	//fc::string			currency;



	//template <class T>
	//bool SerializeXml( const fc::vector<T>& vec )
	//{
	//}

private:
	ItemList*			m_itemList;
	SpellList*			m_spellList;
	MonsterList*		m_monsterList;
	MonsterPartyList*	m_monsterPartyList;
	EncounterGroupList*	m_encounterList;
	CharacterClassList* m_characterClassList;
	ExpTableList*		m_expTableList; //hmmm... maybe go in character class?

	//SpriteList*			m_portraitSprites;
	//AnimatedSpriteList*	m_weaponSprites;
	//AnimatedSpriteList*	m_miscSprites;

};

