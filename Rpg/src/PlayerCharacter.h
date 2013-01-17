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

#include "Character.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Buff.h"


class PlayerCharacter : public Character
{
public:
	Character( EntityType derivedType = TypePlayerCharacter ) : Character(derivedType) 
	{}

	virtual void Update() {}
	virtual void Render() {}

protected:
	Equipment	m_equipment;
	Inventory	m_inventory;
	BuffSet		m_buffs;

};


