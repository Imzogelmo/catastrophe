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


class GLImageViewCanvas : public wxGLCanvas
{
public:
	GLImageViewCanvas(wxWindow* parent, Image* imagePtr, wxGLContext* glContext);

	void SetImage(Image* image) {
		m_ptrImage = image;
	}

protected:
	//void OnSize( wxSizeEvent& event );
	void OnPaint(wxPaintEvent& event);
	void OnEraseBackground(wxEraseEvent& event){}

	wxGLContext*	m_ptrGLContext;
	Image*			m_ptrImage;
	SpriteBatch		m_spritebatch;

	DECLARE_EVENT_TABLE()
};


class GLImageView : public wxScrolledWindow
{
public:
	GLImageView(wxWindow* parent, Image* imagePtr, wxGLContext* glContext);

	void SetImage(Image* image);

protected:
	void OnSize(wxSizeEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnEraseBackground(wxEraseEvent& event);

	GLImageViewCanvas*		m_canvas;
	DECLARE_EVENT_TABLE()
};



class GLImageViewFrame : public wxFrame
{
public:
	GLImageViewFrame(wxWindow* parent, Image* imagePtr, wxGLContext* glContext, const wxString& title);

	void SetImage(Image* image) {
		m_scrolledWindow->SetImage(image);
	}

protected:
	void OnExit(wxCloseEvent& event);

	GLImageView	*m_scrolledWindow;

	DECLARE_EVENT_TABLE()
};
