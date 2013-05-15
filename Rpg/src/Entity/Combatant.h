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

#include "ScriptEntity.h"


class Combatant : public ScriptEntity
{
public:
	Combatant( EntityType derivedType );

	virtual void Update() {}
	virtual void Render() {}

	virtual int GetParam( int param ) const = 0;
	virtual int GetMaxParam( int param ) const = 0;
	virtual int GetBaseMaxParam( int param ) const = 0;
	virtual int GetBaseStat( int stat ) const = 0;
	virtual int GetStat( int stat ) const = 0;
	virtual int GetBaseStatusAttackValue( int status ) const = 0;
	virtual int GetStatusAttackValue( int status ) const = 0;
	virtual int GetBaseStatusDefValue( int status ) const = 0;
	virtual int GetStatusDefValue( int status ) const = 0;


	virtual Attributes& GetAttributes() = 0;
	virtual Equipment& GetEquipment() = 0;
	virtual Inventory& GetInventory() = 0;
	virtual BuffSet& GetBuffs() = 0;
	virtual const Attributes& GetAttributes() const = 0;
	virtual const Equipment& GetEquipment() const = 0;
	virtual const Inventory& GetInventory() const = 0;
	virtual const BuffSet& GetBuffs() const = 0;

	AnimatedSpriteSet& GetAnimatedSpriteSet { return m_spriteset; }
	const AnimatedSpriteSet& GetAnimatedSpriteSet() const { return m_spriteset; }

protected:
	AnimatedSpriteSet	m_spriteset;

};
