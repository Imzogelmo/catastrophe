//////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify //
// it under the terms of the GNU General Public License as published by //
// the Free Software Foundation, either version 3 of the License, or    //
// (at your option) any later version.                                  //
//                                                                      //
// This program is distributed in the hope that it will be useful,      //
// but WITHOUT ANY WARRANTY; without even the implied warranty of       //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        //
// GNU General Public License for more details.                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/gdicmn.h>
#include <wx/glcanvas.h>
#include <wx/stopwatch.h>


class MinimapWindow : public wxGLCanvas
{
public:
	MinimapWindow(wxWindow* parent, wxGLContext* glContext);
	~MinimapWindow();

protected:
	void OnSize( wxSizeEvent& event );
	void OnPaint(wxPaintEvent& event);
	void OnEraseBackground(wxEraseEvent& event){}


	wxGLContext*	m_ptrGLContext;
	SpriteBatch		m_spritebatch;
	wxStopWatch		m_stopwatch;

	//limit the amount this window needs to paint itself.
	long			m_swDuration;
	bool			m_forceUpdate;

	DECLARE_EVENT_TABLE()
};


