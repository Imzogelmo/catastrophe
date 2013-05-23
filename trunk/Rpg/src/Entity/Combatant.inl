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

#include "Combatant.h"



Combatant::Combatant( EntityType derivedType ) :
	ScriptEntity(derivedType),
	m_actor(0),
	m_spriteset()
{
}


Combatant::~Combatant()
{
}


void Combatant::InitializeFromActor( Actor* actor )
{
	ASSERT(actor != 0);

	m_actor = actor;
	m_actor->LoadBattleSpriteSet(m_spriteset);
	m_scriptInstance.Initialize(actor->script);
	m_scriptInstance.CreateScriptObject();
}


void Combatant::Update()
{
	ScriptEntity::Update();
}


void Combatant::Render()
{
}





