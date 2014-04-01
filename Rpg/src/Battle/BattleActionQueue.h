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

#include <fc/vector.h>

#include "Common.h"
#include "BattleAction.h"


class BattleActionQueue
{
public:
	typedef fc::vector<BattleAction*> vec_type;

	BattleActionQueue();

	void AddAction( BattleAction* action );
	void RemoveAction( BattleAction* action );
	void CancelAction( BattleAction* action );

	void ClearActions();
	void MoveToFront( BattleAction* action );

	BattleAction* GetCurrentAction();
	void SetCurrentAction();
	void RemoveCancelledActions();

	void Update();

protected:
	vec_type		m_queuedActions;
	vec_type		m_pendingActions;

	vec_type		m_finishedActions;
	BattleAction*	m_currentAction;

	bool			m_wait;

};

