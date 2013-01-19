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

#include "Precompiled.h"

#include "GLImageView.h"
#include "OpenGL.h"
#include "Editor.h"


BEGIN_EVENT_TABLE(GLImageViewCanvas, wxGLCanvas)
	EVT_PAINT			(GLImageViewCanvas::OnPaint)
	EVT_ERASE_BACKGROUND(GLImageViewCanvas::OnEraseBackground)
END_EVENT_TABLE()


BEGIN_EVENT_TABLE(GLImageView, wxScrolledWindow)
	EVT_SIZE			(GLImageView::OnSize)
	EVT_PAINT			(GLImageView::OnPaint)
	EVT_ERASE_BACKGROUND(GLImageView::OnEraseBackground)
END_EVENT_TABLE()


BEGIN_EVENT_TABLE(GLImageViewFrame, wxFrame)
	EVT_CLOSE		(GLImageViewFrame::OnExit)
END_EVENT_TABLE()



GLImageViewCanvas::GLImageViewCanvas(wxWindow* parent, Image* imagePtr, wxGLContext* glContext) :
	wxGLCanvas(parent, glContext, wxID_ANY, wxDefaultPosition, wxDefaultSize),
	m_ptrGLContext(glContext),
	m_ptrImage(imagePtr)
{
	Show();
}


void GLImageViewCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);
	OpenGL::PrepareRenderingContext(this, m_ptrGLContext);

	const wxRect windowRect = GetSize();
	OpenGL::ClearFrameBuffer(Colorf::Black(0.f));
	OpenGL::SetOrtho( windowRect );

	m_spritebatch.Begin();
	m_ptrImage->Render( &m_spritebatch, Vector2::Zero );
	m_spritebatch.Render();
	m_spritebatch.End();
}



GLImageView::GLImageView(wxWindow* parent, Image* imagePtr, wxGLContext* glContext) :
	wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL)
{
	m_canvas = new GLImageViewCanvas( this, imagePtr, glContext );
	SetScrollbars(1, 1, imagePtr->Width(), imagePtr->Height());
	Show();
}


void GLImageView::SetImage(Image* image)
{
	if(!image)
	{
		wxLogStatus(wxT("GLImageView::SetImage: image is null."));
		return;
	}

	m_canvas->SetImage(image);
	SetScrollbars(1, 1, image->Width(), image->Height());
	Refresh();
}


void GLImageView::OnSize(wxSizeEvent& event)
{
	wxScrolledWindow::OnSize(event);
}


void GLImageView::OnPaint(wxPaintEvent& event)
{
	wxScrolledWindow::OnPaint(event);
}


void GLImageView::OnEraseBackground(wxEraseEvent& event)
{
	wxScrolledWindow::OnEraseBackground(event);
}




GLImageViewFrame::GLImageViewFrame(wxWindow* parent, Image* imagePtr, wxGLContext* glContext, const wxString& title) :
	wxFrame(parent, wxID_ANY, title)
{
	if(!imagePtr)
	{
		Destroy();
	}
	else
	{
		m_scrolledWindow = new GLImageView(this, imagePtr, glContext);
		SetMinSize( wxSize(320, 240) );
		Show();
	}
}


void GLImageViewFrame::OnExit(wxCloseEvent& WXUNUSED(event))
{
	Destroy();
}



