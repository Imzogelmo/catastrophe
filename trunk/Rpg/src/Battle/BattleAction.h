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

#include <fc/string.h>
#include <fc/vector.h>

#include "Common.h"
//#include "TargetInfo.h"



struct TargetInfo
{
	enum TargetMode
	{
		Single,
		Many
	};

	enum TargetType
	{
		TargetNone,
		TargetSelf,
		TargetEnemy,
		TargetEnemyGroup,
		TargetAllEnemies,
		TargetAlly,
		TargetAllyGroup,
		TargetAllAllies,
		TargetAll,

		// (target > max) is user defined
		ProxyMaxDefined,
		TargetMaxDefined = ProxyMaxDefined - 1
	};

	TargetType type;
	TargetInfo( TargetType type = TargetNone ) : type(type)
	{}
};


class BattleAction
{
public:
	BattleAction();
	virtual ~BattleAction() {}

	void SetParent( BattleActionQueue* parent ) { m_parent = parent; }
	void SetPerformer( Combatant* performer ) { m_performer = performer; }

	void Update();

	void Cancel();
	void GivePriority();
	void MakeReady();

	bool HasPriority() const { return m_hasPriority; }
	bool IsCancelled() const { return m_cancelled; }
	bool IsReady() const { return m_isReady; }

	BattleActionQueue* GetParent() const { return m_parent; }
	Combatant* GetPerformer() const { return m_performer; }


protected:
	BattleActionQueue* m_parent;
	Combatant*	m_performer;

	//int			type;
	//int			flags;
	float		BattleSpeed; //replace me

	float		m_speedModifier;
	float		m_waitDelayTime;
	float		m_cooldownDelayTime;

	float		m_waitDelayCounter;
	float		m_cooldownDelayCounter;

	int			m_targetInfo;

	bool		m_hasPriority;
	bool		m_isReady;
	bool		m_cancelled;

};




/*
class ActionWait : public BattleAction
{
public:
	ActionWait( int duration = 0 )
		: duration(duration)
	{}

	void Update()
	{
		if( --duration < 0 )
			Cancel();
	}

protected:
	int duration;
};



class ActionDialogue : public BattleAction
{
public:
	ActionDialogue()
	{}

	void Update() {}

protected:

};
*/

