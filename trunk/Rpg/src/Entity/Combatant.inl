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

#include <Catastrophe/Graphics/SpriteBatch.h>
#include "Combatant.h"
#include "GameData.h"



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
	actor->LoadBattleSpriteSet(m_spriteset);

	// load script data
	ScriptClassDeclarations scd;
	scd.class_decl = actor->script;

	if( actor->IsCharacter() )
		scd = ScriptClassCharacterDeclarations();

	else if( actor->IsMonster() )
		scd = ScriptClassMonsterDeclarations();

	// always initialize the script first.
	ScriptEntity::InitializeScript(scd);

	// finaly create the script object which links back to us.
	ScriptEntity::CreateScriptObject();
}


void Combatant::InitializeFromActorId( int id )
{
	Actor* actor = GetGameData()->GetCharacterActorById(id);
	if( actor )
	{
		InitializeFromActor(actor);
	}
}


void Combatant::Update()
{
	ScriptEntity::Update();
}


void Combatant::Render()
{
	gGetSpriteBatch()->DrawAnimatedSpriteSet(m_spriteset, pos);
}





