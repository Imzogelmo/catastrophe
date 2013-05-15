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




int Character::GetLv() const
{
	return m_lv;
}


int Character::GetExp() const
{
	return m_exp;
}


int Character::GetGold() const
{
	return m_gold;
}


int Character::GetParam( int param ) const
{
	return m_params[param];
}


int Character::GetMaxParam( int param ) const
{
	if( (unsigned)param >= MAX_PARAMS )
		param = 
	return m_attributes.max_params[param] +
		m_equipment.GetCombinedAttributes().max_params[param] +
		m_buffs.GetCombinedAttributes().max_params[param];
}


int Character::GetBaseMaxParam( int param ) const
{
	return m_attributes.max_params[param];
}


int Character::GetBaseStat( int stat ) const
{
	return m_attributes.stats[stat];
}


int Character::GetStat( int stat ) const
{
	return m_attributes.stats[stat] +
		m_equipment.GetCombinedAttributes().stats[stat] +
		m_buffs.GetCombinedAttributes().stats[stat];
}


int Character::GetBaseStatusAttackValue( int status ) const
{
	return m_attributes.status_atk[status];
}


int Character::GetStatusAttackValue( int status ) const
{
	return m_attributes.status_atk[status] +
		m_equipment.GetCombinedAttributes().status_atk[status] +
		m_buffs.GetCombinedAttributes().status_atk[status];
}


