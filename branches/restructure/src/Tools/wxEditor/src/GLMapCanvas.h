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

#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/glcanvas.h>

#include "GLScrolledWindow.h"


#ifdef _MSC_VER
	#pragma warning( disable : 4100 )
#endif


class GLMapCanvas : public wxGLCanvas
{
public:
	friend class GLScrolledWindow<GLMapCanvas>;

	GLMapCanvas(GLScrolledWindow<GLMapCanvas>* parent, wxGLContext* glContext);
	~GLMapCanvas();

	//required
	static GLScrolledWindow<GLMapCanvas> *
		CreateInstance(wxWindow* parent, wxGLContext* glContext);

	Map* GetMap() { return 0; }

protected:
	void OnSize( wxSizeEvent& event );
	void OnPaint(wxPaintEvent& event);
	void OnEraseBackground(wxEraseEvent& event){}

	void OnTimer();
	void Update();
	void Render();

	void HandleMouseEvents( int middlePos = 0, bool leftRelease = false, bool rightRelease = false );

	//Mouse events
	void OnLeftClickPress(wxMouseEvent& event);
	void OnLeftClickRelease(wxMouseEvent& event);
	void OnRightClickPress(wxMouseEvent& event);
	void OnRightClickRelease(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnMouseLeaveWindow(wxMouseEvent& event);
	void OnMouseEnterWindow(wxMouseEvent& event);
	void OnMouseWheel(wxMouseEvent& event);

	//Key events
	void OnKeyDown(wxKeyEvent& event);
	void OnKeyUp(wxKeyEvent& event);

protected:
	GLScrolledWindow<GLMapCanvas>	*m_parent;
	wxGLContext						*m_ptrGLContext;

	static SpriteBatch		m_spritebatch;
	static PrimitiveBatch	m_primbatch;
	static Primitive		m_prim;

	Mouse			m_mouse;

	DECLARE_EVENT_TABLE()
};



#ifdef _MSC_VER
	#pragma warning( default : 4100 )
#endif


