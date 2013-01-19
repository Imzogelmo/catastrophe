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
#include "Script/ScriptClass.h"


class Character : public Entity
{
public:
	Character( EntityType derivedType = TypeCharacter )
		: Entity(derivedType), m_scriptInstance()
	{}

	virtual void Update() {}
	virtual void Render() {}


protected:
	ScriptClass	m_scriptInstance;
	BuffList	m_buffs;

};


