
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


