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

#include "Combatant.h"
#include "Character.h"


class PlayerCombatant : public Combatant
{
public:
	PlayerCombatant( EntityType derivedType = EntityType_PlayerCombatant );
	virtual ~PlayerCombatant()
	{}

	virtual void Update() {}
	virtual void Render() {}

	int GetParam( int param ) const { return m_character->GetParam(param); }
	int GetMaxParam( int param ) const { return m_character->GetMaxParam(param); }
	int GetBaseMaxParam( int param ) const { return m_character->GetBaseMaxParam(param); }
	int GetBaseStat( int stat ) const { return m_character->GetBaseStat(stat); }
	int GetStat( int stat ) const { return m_character->GetStat(stat); }
	int GetBaseStatusAttackValue( int status ) const { return m_character->GetBaseStatusAttackValue(status); }
	int GetStatusAttackValue( int status ) const { return m_character->GetStatusAttackValue(status); }

	Attributes& GetAttributes() { return m_character->GetAttributes(); }
	Equipment& GetEquipment() { return m_character->GetEquipment(); }
	Inventory& GetInventory() { return m_character->GetInventory(); }
	BuffSet& GetBuffs() { return m_character->GetBuffs(); }
	const Attributes& GetAttributes() const { return m_character->GetAttributes(); }
	const Equipment& GetEquipment() const { return m_character->GetEquipment(); }
	const Inventory& GetInventory() const { return m_character->GetInventory(); }
	const BuffSet& GetBuffs() const { return m_character->GetBuffs(); }

protected:
	Character*	m_character;

};


