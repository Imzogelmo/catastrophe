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


#include "wxImageViewWindow.h"
#include "Dialogs.h"



BEGIN_EVENT_TABLE(ImageViewWindow, wxFrame)
	EVT_CLOSE		(ImageViewWindow::OnExit)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(ImageViewWindow::ImageViewScrolledWindow, wxScrolledWindow)
	EVT_SIZE			(ImageViewWindow::ImageViewScrolledWindow::OnSize)
	EVT_PAINT			(ImageViewWindow::ImageViewScrolledWindow::OnPaint)
	EVT_ERASE_BACKGROUND(ImageViewWindow::ImageViewScrolledWindow::OnEraseBackground)
END_EVENT_TABLE()



ImageViewWindow::ImageViewWindow(wxFrame *parent, wxBitmap* bitmap, const wxString& title) :
	wxFrame(parent, wxID_ANY, title),
	m_parent(parent)
	{
		if(!bitmap)
			this->Destroy();

		else
		{
			m_canvas = new ImageViewScrolledWindow(this, bitmap);
			SetMinSize( wxSize(320, 240) );
			Show(true);
		}
	}


ImageViewWindow::~ImageViewWindow()
	{
	}


void ImageViewWindow::OnExit(wxCloseEvent& WXUNUSED(event))
	{
		Destroy();
	}


void ImageViewWindow::ImageViewScrolledWindow::OnSize(wxSizeEvent& event)
	{
		wxScrolledWindow::OnSize(event);
	}


void ImageViewWindow::ImageViewScrolledWindow::OnPaint(wxPaintEvent& WXUNUSED(event))
	{
		wxPaintDC dc( this );
		PrepareDC( dc );

		dc.DrawBitmap( *m_bitmap, 0, 0, true );
	}


void ImageViewWindow::ImageViewScrolledWindow::OnEraseBackground(wxEraseEvent& event)
	{
		wxScrolledWindow::OnEraseBackground(event);
	}


