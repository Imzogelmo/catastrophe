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

#include "Common.h"


class Screen
{
public:
	/*
	enum ScreenState
	{
		StateInactive,
		StateActive,
		StateTransitionOn,
		StateTransitionOff,
		StateFinished
	};
	*/

	Screen( ScreenManager* parent );
	virtual ~Screen()
	{}
	
	virtual void Update() = 0;
	virtual void Render() = 0;

	// Transition on/off effects. Called one-time.
	virtual void OnEnter();
	virtual void OnExit();
	virtual void OnRemove() {} // The screen has been removed.

	void Remove();
	//void SetState( ScreenState state );
	void SetActive( bool enable = true );
	void SetVisible( bool enable = true );

	bool IsActive() const { return m_active; }
	bool IsVisible() const { return m_visible; }
	bool IsPopup() const { return m_popup; }
	bool IsBlocking() const { return m_blocking; }
	bool IsHidden() const { return m_hidden; }
	bool IsTop();

	ScreenManager* GetScreenManager() const { return m_screenManager; }

protected:
	friend class ScreenManager;
	void SetHidden( bool enable = true );

	ScreenManager*	m_screenManager;
	//ScreenState		m_state;
	bool			m_active;
	bool			m_visible;
	bool			m_popup;	//is this rendered on top of other screens?
	bool			m_blocking; //is this blocking update logic to underneath screens?
	bool			m_hidden; //manager will notify state if hidden from view.

};

