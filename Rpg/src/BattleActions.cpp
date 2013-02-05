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

#include "BattleActions.h"


BattleActionQueue::BattleActionQueue() :
	m_actions(),
	m_finishedActions(),
	m_currentAction(0)
{
}

void BattleActionQueue::AddAction( BattleAction* action )
{
	if( !action )
		return;

	action->SetParent(this);
	size_t index = action->HasPriority() ? (size_t)0 : m_actions.size();
	m_actions.insert_at(index, action);
}


void BattleActionQueue::RemoveAction( BattleAction* action )
{
	vec_type::iterator it = fc::find(m_actions.begin(), m_actions.end(), action);
	if( it != m_actions.end() )
	{
		m_actions.erase(it);
		action->SetParent(0);
	}
}


void BattleActionQueue::ClearActions()
{
	m_finishedActions.insert( m_finishedActions.end(), m_actions.begin(), m_actions.end() );
	for( vec_type::iterator it = m_actions.begin(); it != m_actions.end(); ++it )
	{
		(*it)->Cancel();
	}

	m_actions.clear();
	m_currentAction->Cancel();
}


void BattleActionQueue::CancelAction( size_t index )
{
	if( index < m_actions.size() )
		m_actions[index]->Cancel();
}


void BattleActionQueue::CancelAction( BattleAction* action )
{
	action->Cancel();
}


void BattleActionQueue::MoveToFront( BattleAction* action )
{
	vec_type::iterator it = fc::find(m_actions.begin(), m_actions.end(), action);
	if( it != m_actions.end() )
	{
		m_actions.erase(it);
	}
	else
	{
		if( action != GetCurrentAction() )
		{
			// action is not inside this queue
			BattleActionQueue* p = action->GetParent();
			if( p != 0 )
				p->RemoveAction(action);

			action->SetParent(this);
		}
	}

	if( action->HasPriority() )
	{
		m_actions.insert_at(0, action);
	}
	else
	{
		// iterate through the queue and find the first valid slot to insert.
		for( it = m_actions.begin(); it != m_actions.end(); ++it )
		{
			if( !(*it)->HasPriority() )
			{
				m_actions.insert(it, action);
				break;
			}
		}

		if( it == m_actions.end() )
		{
			// 'MoveToFront' just moved it to the end!
			m_actions.push_back(action);
		}
	}
}


BattleAction* BattleActionQueue::GetCurrentAction()
{
	return m_currentAction;
}


void BattleActionQueue::SetCurrentAction()
{
	if( m_currentAction && m_currentAction->IsCancelled() )
	{
		m_finishedActions.push_back(m_currentAction);
		m_currentAction = 0;
	}

	if( !m_currentAction )
	{
		if( m_actions.empty() )
			return;

		if( m_actions[0]->IsReady() )
		{
			m_currentAction = m_actions[0];
			m_actions.erase_at(0);
			m_currentAction->OnTrigger(); //...something like this.
		}
	}
}


void BattleActionQueue::RemoveCancelledActions()
{
	for( vec_type::iterator it = m_actions.begin(); it != m_actions.end(); )
	{
		if( (*it)->IsCancelled() )
		{
			m_actions.erase(it);
			m_finishedActions.push_back(*it);
		}
		else
		{
			++it;
		}
	}
}


void BattleActionQueue::Update()
{
	RemoveCancelledActions();
	SetCurrentAction();

	if( m_currentAction )
		m_currentAction->Update();

	for( vec_type::iterator it = m_actions.begin(); it != m_actions.end(); )
	{
		(*it)->Update();
	}
}

