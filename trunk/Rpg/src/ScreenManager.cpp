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
		if( (*it)->IsActive() )
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
	Screen* top = GetTop();
	if(top)
	{
		//transition bottom..? maybe.
	}

	screen->OnEnter();
	m_screens.push_back(screen);
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

}


void ScreenManager::Render()
{
}


