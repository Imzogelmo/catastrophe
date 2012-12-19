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

#include "Screen.h"
#include "ScreenManager.h"


Screen::Screen( ScreenManager* parent ) :
	m_screenManager(parent),
	m_active(true),
	m_visible(true),
	m_popup(false),
	m_blocking(true)
{
	ASSERT(m_screenManager != 0);
}


void Screen::OnEnter()
{
	//m_state == StateActive;
}


void Screen::OnExit()
{
	//m_state == StateFinished;
}


bool Screen::IsTop()
{ 
	return m_screenManager->GetTop() == this;
}


void Screen::Remove()
{
     m_screenManager->Remove(this);
}


void Screen::SetActive( bool enable )
{
	m_active = enable;
}


void Screen::SetVisible( bool enable )
{
	m_visible = enable;
}


void Screen::SetHidden( bool enable )
{
	m_hidden = enable;
}


