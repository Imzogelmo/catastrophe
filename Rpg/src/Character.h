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


/*
class Character
{
int id;
int lv;
int exp;
int gold;
ParamValueArrayType	params;

};
*/


class Character
{
public:
	Character()
	{}

	//....should be non virtual class..?..
	//virtual void Update() {}
	//virtual void Render() {}

	int GetParam( int param ) const;
	int GetMaxParam( int param ) const;
	int GetBaseMaxParam( int param ) const;
	int GetBaseStat( int stat ) const;
	int GetStat( int stat ) const;
	int GetBaseStatusAttackValue( int status ) const;
	int GetStatusAttackValue( int status ) const;


	Attributes& GetAttributes() { return m_attributes; }
	Equipment& GetEquipment() { return m_equipment; }
	Inventory& GetInventory() { return m_inventory; }
	BuffSet& GetBuffs() { return m_buffs; }
	const Attributes& GetAttributes() const { return m_attributes; }
	const Equipment& GetEquipment() const { return m_equipment; }
	const Inventory& GetInventory() const { return m_inventory; }
	const BuffSet& GetBuffs() const { return m_buffs; }

protected:
	ParamValueArrayType	m_params;
	Attributes			m_attributes;
	Equipment			m_equipment;
	Inventory			m_inventory;
	BuffSet				m_buffs;

};

