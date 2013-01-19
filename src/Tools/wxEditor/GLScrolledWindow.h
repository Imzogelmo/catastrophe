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

#include <wx/scrolwin.h>
#include <wx/glcanvas.h>

#include "Mouse.h"


class GLMapCanvas;
class GLTileCanvas;


#ifdef _MSC_VER
	#pragma warning( disable : 4100 )
#endif


/* 
	Window that handles event functions for a GLCanvas 
*/

template<class T>
class GLScrolledWindow : public wxScrolledWindow
{
public:
	friend class GLMapCanvas;
	friend class GLTileCanvas;

	GLScrolledWindow(wxWindow* parent, wxGLContext* glContext);
	~GLScrolledWindow();


	//Global events
	void OnSize(wxSizeEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnEraseBackground(wxEraseEvent& event);

	//Scroll events
	void OnScrollTop(wxScrollWinEvent& event);
	void OnScrollBottom(wxScrollWinEvent& event);
	void OnScrollLineUp(wxScrollWinEvent& event);
	void OnScrollLineDown(wxScrollWinEvent& event);
	void OnScrollPageUp(wxScrollWinEvent& event);
	void OnScrollPageDown(wxScrollWinEvent& event);
	void OnScrollThumbTrack(wxScrollWinEvent& event);
	void OnScrollThumbRelease(wxScrollWinEvent& event);
	void Scroll(int orient, int amount);
	void SetScrollbarUnits(int x, int y);

	wxPoint GetScrollbarPositions() const;
	wxPoint GetScrollbarPixelPositions() const;

	T*		GetUserCanvas() { return m_canvas; }

protected:
	wxWindow	*m_parent;
	T			*m_canvas;


	DECLARE_EVENT_TABLE()
};



typedef GLScrolledWindow<GLMapCanvas> GLMapCanvasWindow;
typedef GLScrolledWindow<GLTileCanvas> GLTileCanvasWindow;

#include "GLTileCanvas.h"
#include "GLMapCanvas.h"


#define BEGIN_GLSCROLLEDWINDOW_EVENT_TABLE_TEMPLATE(__class_t_)	\
BEGIN_EVENT_TABLE_TEMPLATE1(GLScrolledWindow, wxScrolledWindow, __class_t_)	\
    EVT_SIZE					(GLScrolledWindow::OnSize)					\
	EVT_PAINT					(GLScrolledWindow::OnPaint)					\
	EVT_ERASE_BACKGROUND		(GLScrolledWindow::OnEraseBackground)		\
	EVT_SCROLLWIN_TOP			(GLScrolledWindow::OnScrollTop)				\
	EVT_SCROLLWIN_BOTTOM		(GLScrolledWindow::OnScrollBottom)			\
	EVT_SCROLLWIN_LINEUP		(GLScrolledWindow::OnScrollLineUp)			\
	EVT_SCROLLWIN_LINEDOWN		(GLScrolledWindow::OnScrollLineDown)		\
	EVT_SCROLLWIN_PAGEUP		(GLScrolledWindow::OnScrollPageUp)			\
	EVT_SCROLLWIN_PAGEDOWN		(GLScrolledWindow::OnScrollPageDown)		\
	EVT_SCROLLWIN_THUMBTRACK	(GLScrolledWindow::OnScrollThumbTrack)		\
	EVT_SCROLLWIN_THUMBRELEASE	(GLScrolledWindow::OnScrollThumbRelease)	\
END_EVENT_TABLE()


template<class T> inline
GLScrolledWindow<T>::GLScrolledWindow(wxWindow* parent, wxGLContext* glContext) :
	wxScrolledWindow(parent, 
		wxID_ANY, 
		wxDefaultPosition, 
		wxDefaultSize, 
		wxHSCROLL | wxVSCROLL | wxALWAYS_SHOW_SB
	),
	m_parent(parent)
{
	m_canvas = new T(this, glContext);
	this->Show(true);
}


template<class T> inline
GLScrolledWindow<T>::~GLScrolledWindow()
{
	//this->RemoveChild(m_canvas);
}


template<class T> inline
void GLScrolledWindow<T>::OnSize( wxSizeEvent& event )
{
	/*
	int x = this->GetScrollPos(wxHORIZONTAL);
	int y = this->GetScrollPos(wxVERTICAL);
	int px, py;
	this->GetScrollPixelsPerUnit( &px, &py );
	SetScrollbars( px, py, 80, 80, x, y, false );
*/
	wxScrolledWindow::OnSize(event);

//	this->SetSize(event.GetSize());
	m_canvas->OnSize(event);


	//this->SetScrollPos(wxHORIZONTAL, x);
	//this->SetScrollPos(wxVERTICAL, y);
}


template<class T> inline
void GLScrolledWindow<T>::OnPaint(wxPaintEvent& event)
{
	wxScrolledWindow::OnPaint(event);
}


template<class T> inline
void GLScrolledWindow<T>::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
	//handled by OpenGL Canvas
}


/////////////////////
//  Scroll events  //
/////////////////////

template<class T> inline
void GLScrolledWindow<T>::OnScrollTop(wxScrollWinEvent& event)
{
	event.Skip();
}


template<class T> inline
void GLScrolledWindow<T>::OnScrollBottom(wxScrollWinEvent& event)
{
	event.Skip();
}


template<class T> inline
void GLScrolledWindow<T>::OnScrollLineUp(wxScrollWinEvent& event)
{
	int x = 1, y = 1, orient = event.GetOrientation();
	//GetScrollPixelsPerUnit(&x, &y);
	Scroll( orient, -x );
}


template<class T> inline
void GLScrolledWindow<T>::OnScrollLineDown(wxScrollWinEvent& event)
{
	int x = 1, y = 1, orient = event.GetOrientation();
	//GetScrollPixelsPerUnit(&x, &y);
	Scroll( orient, x );
}


template<class T> inline
void GLScrolledWindow<T>::OnScrollPageUp(wxScrollWinEvent& event)
{
	int orient = event.GetOrientation();
	Scroll( orient, -GetScrollPageSize(orient) );
}


template<class T> inline
void GLScrolledWindow<T>::OnScrollPageDown(wxScrollWinEvent& event)
{
	int orient = event.GetOrientation();
	Scroll( orient, GetScrollPageSize(orient) );
}


template<class T> inline
void GLScrolledWindow<T>::OnScrollThumbTrack(wxScrollWinEvent& event)
{
	int orient = event.GetOrientation();
	int pos = event.GetPosition();

	this->SetScrollPos( orient, pos );
	Refresh();
}


template<class T> inline
void GLScrolledWindow<T>::OnScrollThumbRelease(wxScrollWinEvent& event)
{
	int orient = event.GetOrientation();
	int pos = event.GetPosition();

	this->SetScrollPos( orient, pos );
	Refresh();
}


template<class T> inline
void GLScrolledWindow<T>::Scroll(int orient, int amount)
{
	this->SetScrollPos( orient, GetScrollPos(orient) + amount );
	Refresh();
}


template<class T> inline
void GLScrolledWindow<T>::SetScrollbarUnits(int x, int y)
{
	wxPoint scrollPos = GetScrollbarPositions();

	this->SetScrollbars(16, 16, x, y, scrollPos.x, scrollPos.y );
}


template<class T> inline
wxPoint GLScrolledWindow<T>::GetScrollbarPositions() const
{
	return wxPoint(
		GetScrollPos(wxHORIZONTAL),
		GetScrollPos(wxVERTICAL)
		);
}


template<class T> inline
wxPoint GLScrolledWindow<T>::GetScrollbarPixelPositions() const
{
	wxPoint scrollPos = GetScrollbarPositions();

	int x(1), y(1);
	GetScrollPixelsPerUnit(&x, &y);
	scrollPos.x *= x;
	scrollPos.y *= y;

	return scrollPos;
}




#ifdef _MSC_VER
	#pragma warning( default : 4100 )
#endif

