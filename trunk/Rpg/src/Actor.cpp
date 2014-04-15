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

#include "Actor.h"
#include "Database.h"


Actor::Actor() :
	name(),
	script(),
	id(0),
	portrait_id(0),
	map_spriteset_id(0),
	battle_spriteset_id(0)
{
}


bool Actor::InitializeFromCharacter( int character_id )
{
	CharacterData* character = GetDatabase()->GetCharacter(character_id);
	if( !character )
	{
		Log("Actor::InitializeFromCharacter : invalid id (%i)", character_id);
		return false;
	}

	m_type = TypeCharacter;

	// initialize base attribute data and modify it according to race and class.
	Attributes compiledAttributes = character->attributes;

	Race* race = GetDatabase()->GetRace(character->race_id);
	if( race )
		compiledAttributes += race->attributes;

	CharacterClass* character_class = GetDatabase()->GetCharacterClass(character->class_id);
	if( character_class )
		compiledAttributes += character_class->attributes;

	name = character->name;
	script = character->script;

	data_id = character_id;
	portrait_id = character->portrait_id;
	map_spriteset_id = character->map_spriteset_id;
	battle_spriteset_id = character->battle_spriteset_id;

	SetLv(character->lv);
	SetExp(character->exp);
	SetGold(character->gold);

	m_attributes = compiledAttributes;
	m_params = compiledAttributes.max_params;

	return true;
}


bool Actor::InitializeFromMonster( int monster_id )
{
	MonsterData* monster = GetDatabase()->GetMonster(monster_id);
	if( !monster )
	{
		Log("Actor::InitializeFromMonster : invalid id (%i)", monster_id);
		return false;
	}

	m_type = TypeMonster;

	data_id = monster_id;
	portrait_id = monster->portrait_id;
	map_spriteset_id = monster->map_spriteset_id;
	battle_spriteset_id = monster->battle_spriteset_id;

	SetLv(monster->lv);
	SetExp(monster->exp);
	SetGold(monster->gold);

	m_attributes = monster->attributes;
	m_params = monster->attributes.max_params;

	return true;
}


bool Actor::LoadMapSpriteSet( AnimatedSpriteSet& animatedSpriteSetRef )
{
	Database* database = GetDatabase();
	AnimatedSpriteSetAsset* animatedSpriteSetAsset = 0;

	if( IsCharacter() )
		animatedSpriteSetAsset = database->GetCharacterMapSpriteSetAsset(map_spriteset_id);

	else if( IsMonster() )
		animatedSpriteSetAsset = database->GetMonsterMapSpriteSetAsset(map_spriteset_id);

	if( !animatedSpriteSetAsset )
	{
		LogDebug("Actor::LoadSpriteSet : invalid type (%i) or asset_id (%i)", m_type, map_spriteset_id);
		return false;
	}

	return animatedSpriteSetAsset->LoadAnimatedSpriteSet(animatedSpriteSetRef);
}


bool Actor::LoadBattleSpriteSet( AnimatedSpriteSet& animatedSpriteSetRef )
{
	Database* database = GetDatabase();
	AnimatedSpriteSetAsset* animatedSpriteSetAsset = 0;

	if( IsCharacter() )
		animatedSpriteSetAsset = database->GetCharacterBattleSpriteSetAsset(battle_spriteset_id);

	else if( IsMonster() )
		animatedSpriteSetAsset = database->GetMonsterBattleSpriteSetAsset(battle_spriteset_id);

	if( !animatedSpriteSetAsset )
	{
		LogDebug("Actor::LoadSpriteSet : invalid type (%i) or asset_id (%i)", m_type, battle_spriteset_id);
		return false;
	}

	return animatedSpriteSetAsset->LoadAnimatedSpriteSet(animatedSpriteSetRef);
}


int Actor::GetLv() const
{
	return m_lv;
}


int Actor::GetExp() const
{
	return m_exp;
}


int Actor::GetGold() const
{
	return m_gold;
}


void Actor::SetLv( int value )
{
	m_lv = value;
}


void Actor::SetExp( int value )
{
	m_exp = fc::clamp(value, 0, MAX_EXP);
}


void Actor::SetGold( int value )
{
	m_gold = fc::clamp(value, 0, MAX_GOLD);
}


void Actor::AddExp( int value )
{
	SetExp(m_exp + value);
}


void Actor::AddGold( int value )
{
	SetGold(m_gold + value);
}


void Actor::RemoveExp( int value )
{
	SetExp(m_exp - value);
}


void Actor::RemoveGold( int value )
{
	SetGold(m_gold - value);
}


int Actor::GetParam( int param ) const
{
	return m_params[param];
}


int Actor::GetMaxParam( int param ) const
{
	int value = m_attributes.max_params[param] +
		CalculateModifiedMaxParamValue(param);

	return fc::clamp(value, 0, MAX_PARAM_VALUE);
}


int Actor::GetBaseMaxParam( int param ) const
{
	return m_attributes.max_params[param];
}


int Actor::GetBaseStat( int stat ) const
{
	return m_attributes.stats[stat];
}


int Actor::GetStat( int stat ) const
{
	int value = m_attributes.stats[stat] +
		CalculateModifiedStatValue(stat);

	return fc::clamp(value, 0, MAX_STAT_VALUE);
}


int Actor::GetBaseElementalDef( int element ) const
{
	return m_attributes.elemental_def[element];
}


int Actor::GetElementalDef( int element ) const
{
	return m_attributes.elemental_def[element] +
		m_equipment.GetCombinedAttributes().elemental_def[element] +
		m_buffs.GetCombinedAttributes().elemental_def[element];
}


int Actor::GetBaseStatusAtk( int status ) const
{
	return m_attributes.status_atk[status];
}


int Actor::GetStatusAtk( int status ) const
{
	return m_attributes.status_atk[status] +
		m_equipment.GetCombinedAttributes().status_atk[status] +
		m_buffs.GetCombinedAttributes().status_atk[status];
}


int Actor::GetBaseStatusDef( int status ) const
{
	return m_attributes.status_def[status];
}


int Actor::GetStatusDef( int status ) const
{
	return m_attributes.status_def[status] +
		m_equipment.GetCombinedAttributes().status_def[status] +
		m_buffs.GetCombinedAttributes().status_def[status];
}


int Actor::CalculateModifiedMaxParamValue( int param ) const
{
	return m_equipment.GetCombinedAttributes().max_params[param] +
		m_buffs.GetCombinedAttributes().max_params[param];
}


int Actor::CalculateModifiedStatValue( int stat ) const
{
	return m_equipment.GetCombinedAttributes().stats[stat] +
		m_buffs.GetCombinedAttributes().stats[stat];
}


void Actor::SetParam( int param, int value )
{
	m_params[param] = fc::clamp<int>(value, 0, MAX_PARAM_VALUE);
}


void Actor::SetBaseMaxParam( int param, int value )
{
	value = fc::clamp(value, 0, MAX_PARAM_VALUE);
	m_attributes.max_params[param] = value;
	if( m_params[param] > value )
		m_params[param] = value;
}


void Actor::SetBaseStat( int stat, int value )
{
	m_attributes.SetStat(stat, value);
}


void Actor::SetBaseElementalDef( int element, int value )
{
	m_attributes.SetElementalDef(element, value);
}


void Actor::SetBaseStatusAtk( int status, int value )
{
	m_attributes.SetStatusAtk(status, value);
}


void Actor::SetBaseStatusDef( int status, int value )
{
	m_attributes.SetStatusDef(status, value);
}




