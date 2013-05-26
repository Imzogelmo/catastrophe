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

#include "Entity.h"
#include "Buff.h"
#include "BuffSet.h"
#include "Inventory.h"
#include "Equipment.h"



class Actor
{
public:
	fc::string	name;
	fc::string	script;
	int			id;
	int			data_id;
	int			portrait_id;
	int			map_spriteset_id;
	int			battle_spriteset_id;
	int			battle_row;

	enum ActorType
	{
		TypeCharacter,
		TypeMonster
	};

	Actor();

	bool InitializeFromCharacter( int character_id );
	bool InitializeFromMonster( int monster_id );

	// asset loading
	//void LoadPortaitSprite( AnimatedSprite& animatedSprite);
	bool LoadMapSpriteSet( AnimatedSpriteSet& animatedSpriteSetRef);
	bool LoadBattleSpriteSet( AnimatedSpriteSet& animatedSpriteSetRef);


	ActorType GetType() const { return m_type; }
	bool IsCharacter() const { return m_type == TypeCharacter; }
	bool IsMonster() const { return m_type == TypeMonster; }

	int GetLv() const;
	int GetExp() const;
	int GetGold() const;

	void SetLv( int val );
	void SetExp( int val );
	void SetGold( int val );

	void AddExp( int val );
	void AddGold( int val );
	void RemoveExp( int val );
	void RemoveGold( int val );

	int GetParam( int param ) const;
	int GetMaxParam( int param ) const;
	int GetBaseMaxParam( int param ) const;
	int GetBaseStat( int stat ) const;
	int GetStat( int stat ) const;
	int GetBaseElementalDef( int element ) const;
	int GetElementalDef( int element ) const;
	int GetBaseStatusAtk( int status ) const;
	int GetStatusAtk( int status ) const;
	int GetBaseStatusDef( int status ) const;
	int GetStatusDef( int status ) const;


	void SetParam( int param, int val );
	void SetBaseMaxParam( int param, int val );
	void SetBaseStat( int stat, int val );
	void SetBaseElementalDef( int element, int val );
	void SetBaseStatusAtk( int status, int val );
	void SetBaseStatusDef( int status, int val );


	Attributes& GetBaseAttributes() { return m_attributes; }
	Equipment& GetEquipment() { return m_equipment; }
	Inventory& GetInventory() { return m_inventory; }
	BuffSet& GetBuffs() { return m_buffs; }
	const Attributes& GetBaseAttributes() const { return m_attributes; }
	const Equipment& GetEquipment() const { return m_equipment; }
	const Inventory& GetInventory() const { return m_inventory; }
	const BuffSet& GetBuffs() const { return m_buffs; }

protected:
	ActorType			m_type;
	int					m_lv;
	int					m_exp;
	int					m_gold;
	ParamValueArrayType	m_params;
	Attributes			m_attributes;
	Equipment			m_equipment;
	Inventory			m_inventory;
	BuffSet				m_buffs;

};

