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

class BattleActionQueue;
class Character;


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
	BattleAction() : m_parent(0), m_performer(0), m_preparationTime(0)
	{
	}

	virtual ~BattleAction()
	{}

	void SetParent( BattleActionQueue* parent ) { m_parent = parent; }
	void Update()
	{
		if( m_preparationTime > 0 )
			--m_preparationTime;
	}

	void OnTrigger()
	{
	}

	void Cancel()
	{
		m_cancelled = true;
	}

	bool IsCancelled() const { return m_cancelled; }
	bool HasPriority() const { return m_hasPriority; }
	bool IsReady() const { return m_preparationTime <= 0; }

	BattleActionQueue* GetParent() const { return m_parent; }


	BattleActionQueue* m_parent;
	Character*	m_performer;
	//int			type;
	//int			flags;
	int			m_preparationTime;
	TargetInfo	targetInfo;
	bool		m_hasPriority;
	bool		m_cancelled;

};


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


