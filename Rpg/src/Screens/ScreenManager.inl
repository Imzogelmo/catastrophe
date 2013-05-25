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

#include "ScreenManager.h"


ScreenManager::ScreenManager()
{
}


void ScreenManager::Clear()
{
	for( vec_type::iterator it = m_screens.begin(); it != m_screens.end(); ++it )
	{
		(*it)->OnRemove();
	}

	m_screens.clear();
}


Screen* ScreenManager::GetTop() const
{
	if( !IsEmpty() )
		return m_screens.back();

	return 0;
}


Screen* ScreenManager::GetActive() const
{
	for( vec_type::const_iterator it = m_screens.end() - 1; it >= m_screens.begin(); --it )
	{
		if( (*it)->IsActive() ) //hmm this is really the top..
		{
			return *it;
		}
	}

	return 0;
}


bool ScreenManager::IsEmpty() const
{
	return m_screens.empty();
}


void ScreenManager::Add( Screen* screen )
{
	ASSERT(screen != 0);

	ScreenManager* parent = screen->GetScreenManager();
	if( parent )
	{
		parent->Remove(screen);
	}

	Screen* top = GetTop();
	if( top )
	{
		//transition bottom..? maybe.
	}

	m_screens.push_back(screen);
	screen->SetScreenManager(this);
	screen->OnEnter();
}


void ScreenManager::Remove( Screen* screen )
{
	//...should just call OnExit and remove it during the update...?
	Screen* active = GetActive();
	if( active == screen )
	{
	}

	screen->OnExit();
}


void ScreenManager::Update()
{
	if( m_screens.empty() )
		return;

	//iterate through our screens and only update the ones
	//that are not being blocked by other game states.
	for( int i = int(m_screens.size() - 1); i >= 0; --i )
	{
		m_screens[i]->SetActive(true);
		if( m_screens[i]->IsBlocking() )
		{
			for( --i; i >= 0; --i )
			{
				m_screens[i]->SetActive(false);
			}

			break;
		}
	}

	for( vec_type::iterator it = m_screens.begin(); it != m_screens.end(); ++it )
	{
		if( (*it)->IsActive() )
		{
			(*it)->Update();
		}
	}
}


void ScreenManager::Render()
{
	if( m_screens.empty() )
		return;

	//iterate through our screens and only render the ones
	//that are not hidden from view.
	for( int i = int(m_screens.size() - 1); i >= 0; --i )
	{
		m_screens[i]->SetVisible(true);
		if( !m_screens[i]->IsPopup() )
		{
			for( --i; i >= 0; --i )
			{
				m_screens[i]->SetVisible(false);
			}

			break;
		}
	}

	for( vec_type::iterator it = m_screens.begin(); it != m_screens.end(); ++it )
	{
		if( (*it)->IsVisible() )
		{
			(*it)->Render();
		}
	}
}


