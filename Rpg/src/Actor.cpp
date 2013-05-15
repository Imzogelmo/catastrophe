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

#include "Actor.h"

Actor::Actor()
{
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


void Actor::SetLv( int val )
{
	m_lv = val;
}


void Actor::SetExp( int val )
{
	m_exp = fc::clamp(val, 0, MAX_EXP);
}


void Actor::SetGold( int val )
{
	m_gold = fc::clamp(val, 0, MAX_GOLD);
}


void Actor::AddExp( int val )
{
	SetExp(m_exp + val);
}


void Actor::AddGold( int val )
{
	SetGold(m_exp + val);
}


void Actor::RemoveExp( int val )
{
	SetExp(m_exp - val);
}


void Actor::RemoveGold( int val )
{
	SetGold(m_exp - val);
}



int Actor::GetParam( int param ) const
{
	return m_params[param];
}


int Actor::GetMaxParam( int param ) const
{
	// ...todo:
	if( (unsigned)param >= MAX_PARAMS )
	{
		param = 0;
		LogDebug("Attribute access out of range!");
	}

	return m_attributes.max_params[param] +
		m_equipment.GetCombinedAttributes().max_params[param] +
		m_buffs.GetCombinedAttributes().max_params[param];
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
	return m_attributes.stats[stat] +
		m_equipment.GetCombinedAttributes().stats[stat] +
		m_buffs.GetCombinedAttributes().stats[stat];
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





