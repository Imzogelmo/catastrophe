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

#include <Catastrophe/Graphics/AnimatedSpriteSet.h>
#include "ScriptEntity.h"
#include "Actor.h"


class Combatant : public ScriptEntity
{
public:
	Combatant( EntityType derivedType = EntityType_Combatant );
	virtual ~Combatant();

	void InitializeFromActor( Actor* actor );
	void InitializeFromActorId( int id );

	virtual void Update();
	virtual void Render();

	int GetParam( int param ) const { return m_actor->GetParam(param); }
	int GetMaxParam( int param ) const { return m_actor->GetMaxParam(param); }
	int GetBaseMaxParam( int param ) const { return m_actor->GetBaseMaxParam(param); }
	int GetBaseStat( int stat ) const { return m_actor->GetBaseStat(stat); }
	int GetStat( int stat ) const { return m_actor->GetStat(stat); }
	int GetBaseStatusAtk( int status ) const { return m_actor->GetBaseStatusAtk(status); }
	int GetStatusAtk( int status ) const { return m_actor->GetStatusAtk(status); }
	int GetBaseStatusDef( int status ) const { return m_actor->GetBaseStatusDef(status); }
	int GetStatusDef( int status ) const { return m_actor->GetStatusDef(status); }

	void SetParam( int param, int val ) { m_actor->SetParam(param, val); }
	void SetBaseMaxParam( int param, int val ) { m_actor->SetBaseMaxParam(param, val); }
	void SetBaseStat( int stat, int val ) { m_actor->SetBaseStat(stat, val); }
	void SetBaseStatusAtk( int status, int val ) { m_actor->SetBaseStatusAtk(status, val); }
	void SetBaseStatusDef( int status, int val ) { m_actor->SetBaseStatusDef(status, val); }

	Attributes& GetBaseAttributes() { return m_actor->GetBaseAttributes(); }
	Equipment& GetEquipment() { return m_actor->GetEquipment(); }
	Inventory& GetInventory() { return m_actor->GetInventory(); }
	BuffSet& GetBuffs() { return m_actor->GetBuffs(); }
	const Attributes& GetBaseAttributes() const { return m_actor->GetBaseAttributes(); }
	const Equipment& GetEquipment() const { return m_actor->GetEquipment(); }
	const Inventory& GetInventory() const { return m_actor->GetInventory(); }
	const BuffSet& GetBuffs() const { return m_actor->GetBuffs(); }

	Actor* GetActor() const { return m_actor; }
	AnimatedSpriteSet& GetAnimatedSpriteSet() { return m_spriteset; }
	const AnimatedSpriteSet& GetAnimatedSpriteSet() const { return m_spriteset; }

protected:
	Actor*				m_actor;
	AnimatedSpriteSet	m_spriteset;

};




/*
class Combatant : public ScriptEntity
{
public:
	Combatant( EntityType derivedType = EntityType_Combatant );

	virtual void Update() {}
	virtual void Render() {}

	virtual int GetParam( int param ) const = 0;
	virtual int GetMaxParam( int param ) const = 0;
	virtual int GetBaseMaxParam( int param ) const = 0;
	virtual int GetBaseStat( int stat ) const = 0;
	virtual int GetStat( int stat ) const = 0;
	virtual int GetBaseStatusAtk( int status ) const = 0;
	virtual int GetStatusAtk( int status ) const = 0;
	virtual int GetBaseStatusDef( int status ) const = 0;
	virtual int GetStatusDef( int status ) const = 0;


	virtual Attributes& GetBaseAttributes() = 0;
	virtual Equipment& GetEquipment() = 0;
	virtual Inventory& GetInventory() = 0;
	virtual BuffSet& GetBuffs() = 0;
	virtual const Attributes& GetBaseAttributes() const = 0;
	virtual const Equipment& GetEquipment() const = 0;
	virtual const Inventory& GetInventory() const = 0;
	virtual const BuffSet& GetBuffs() const = 0;

	AnimatedSpriteSet& GetAnimatedSpriteSet() { return m_spriteset; }
	const AnimatedSpriteSet& GetAnimatedSpriteSet() const { return m_spriteset; }

protected:
	AnimatedSpriteSet	m_spriteset;

};
*/

