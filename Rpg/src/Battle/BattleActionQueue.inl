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

#include "BattleActionQueue.h"


BattleActionQueue::BattleActionQueue() :
	m_queuedActions(),
	m_finishedActions(),
	m_currentAction(0),
	m_wait(false)
{
}

void BattleActionQueue::AddAction( BattleAction* action )
{
	if( !action )
		return;

	vec_type* p = action->IsReady() ? &m_pendingActions : &m_queuedActions;
	if( action->HasPriority() )
	{
		p->push_front(action);
	}
	else
	{
		p->push_back(action);
	}

	action->SetParent(this);
}


void BattleActionQueue::RemoveAction( BattleAction* action )
{
	vec_type::iterator it = fc::find(m_queuedActions.begin(), m_queuedActions.end(), action);
	if( it != m_queuedActions.end() )
	{
		m_queuedActions.erase(it);
		action->SetParent(0);
	}
}


void BattleActionQueue::ClearActions()
{
	m_finishedActions.insert( m_finishedActions.end(), m_queuedActions.begin(), m_queuedActions.end() );
	for( vec_type::iterator it = m_queuedActions.begin(); it != m_queuedActions.end(); ++it )
	{
		(*it)->Cancel();
	}

	m_queuedActions.clear();
	m_currentAction->Cancel();
}


void BattleActionQueue::CancelAction( size_t index )
{
	if( index < m_queuedActions.size() )
		m_queuedActions[index]->Cancel();
}


void BattleActionQueue::CancelAction( BattleAction* action )
{
	action->Cancel();
}


void BattleActionQueue::MoveToFront( BattleAction* action )
{
	vec_type::iterator it = fc::find(m_queuedActions.begin(), m_queuedActions.end(), action);
	if( it != m_queuedActions.end() )
	{
		m_queuedActions.erase(it);
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
		m_queuedActions.insert_at(0, action);
	}
	else
	{
		// iterate through the queue and find the first valid slot to insert.
		for( it = m_queuedActions.begin(); it != m_queuedActions.end(); ++it )
		{
			if( !(*it)->HasPriority() )
			{
				m_queuedActions.insert(it, action);
				break;
			}
		}

		if( it == m_queuedActions.end() )
		{
			// 'MoveToFront' just moved it to the end!
			m_queuedActions.push_back(action);
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
		if( m_queuedActions.empty() )
			return;

		if( m_queuedActions[0]->IsReady() )
		{
			m_currentAction = m_queuedActions[0];
			m_queuedActions.erase_at(0);
			//m_currentAction->OnTrigger(); //...something like this.
		}
	}
}


void BattleActionQueue::RemoveCancelledActions()
{
	for( vec_type::iterator it = m_queuedActions.begin(); it != m_queuedActions.end(); )
	{
		if( (*it)->IsCancelled() )
		{
			m_queuedActions.erase(it);
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

	if( !m_wait )
	{

		for( vec_type::iterator it = m_queuedActions.begin(); it != m_queuedActions.end(); )
		{
			BattleAction* action = *it;
			if( action->IsReady() )
			{
				m_pendingActions.push_back(action);
				m_queuedActions.erase(it);
			}
			else
			{
				++it;
			}
		}

		for( vec_type::iterator it = m_pendingActions.begin(); it != m_pendingActions.end(); )
		{
		}
	}

}

