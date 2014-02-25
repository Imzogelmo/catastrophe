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

#include "BattleAction.h"


BattleAction::BattleAction() :
	m_parent(0),
	m_performer(0),
	m_speedModifier(1.f),
	m_waitDelayTime(60.f),
	m_cooldownDelayTime(0.f),
	m_waitDelayCounter(0.f),
	m_targetInfo(0)
{
	BattleSpeed = 1.0f;
}


void BattleAction::Cancel()
{
	m_cancelled = true;
}


void BattleAction::GivePriority()
{
}


void BattleAction::MakeReady()
{
	m_waitDelayCounter = m_waitDelayTime;
	m_isReady = true;
}


void BattleAction::Update()
{
	if( !m_isReady )
	{
		if( m_waitDelayCounter < m_waitDelayTime )
		{
			float t = BattleSpeed * m_speedModifier;
			m_waitDelayCounter += t;
		}
		else
		{
			m_isReady = true;
		}
	}
}


