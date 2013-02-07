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
#include "Inventory.h"
#include "Equipment.h"
#include "Script/ScriptClass.h"


class Character : public Entity
{
public:
	Character( EntityType derivedType = TypeCharacter )
		: Entity(derivedType), m_scriptInstance()
	{}

	virtual void Update() {}
	virtual void Render() {}

	int GetBaseStat( int stat ) const;
	int GetStat( int stat );
	int GetBaseStatusAttackValue( int status ) const;
	int GetStatusAttackValue( int status );


	Attributes& GetAttributes() { return m_attributes; }
	Equipment& GetEquipment() { return m_equipment; }
	Inventory& GetInventory() { return m_inventory; }
	BuffSet& GetBuffs() { return m_buffs; }
	const Attributes& GetAttributes() const { return m_attributes; }
	const Equipment& GetEquipment() const { return m_equipment; }
	const Inventory& GetInventory() const { return m_inventory; }
	const BuffSet& GetBuffs() const { return m_buffs; }

protected:
	ScriptClass		m_scriptInstance;
	Attributes		m_attributes;
	Equipment		m_equipment;
	Inventory		m_inventory;
	BuffSet			m_buffs;

};

