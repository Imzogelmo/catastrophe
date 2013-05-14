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
#include "Script/ScriptClass.h"


class ScriptEntity : public Entity
{
public:
	Character( EntityType derivedType = TypeCharacter )
		: Entity(derivedType), m_scriptInstance()
	{}

	virtual void Update() { m_scriptInstance.Update(); }
	virtual void Render() {}

	ScriptClass* GetScriptClass() { return &m_scriptInstance; }
	const ScriptClass* GetScriptClass() const { return &m_scriptInstance; }

protected:
	ScriptClass		m_scriptInstance;

};

