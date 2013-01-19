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

#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>


class ImageViewWindow : public wxFrame
{
public:
	
	class ImageViewScrolledWindow : public wxScrolledWindow
	{
	public:
		ImageViewScrolledWindow(ImageViewWindow* parent, wxBitmap* bitmap) :
			wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL),
			m_parent(parent), m_bitmap(bitmap)
			{
				SetScrollbars(1, 1, bitmap->GetWidth(), bitmap->GetHeight());
			}
		~ImageViewScrolledWindow()
			{
				if(m_bitmap)
					delete m_bitmap;
			}

		void SetBitmap(wxBitmap* bitmap)
			{
				if(m_bitmap)
					delete m_bitmap;

				m_bitmap = bitmap;
				SetScrollbars(1, 1, bitmap->GetWidth(), bitmap->GetHeight());
				Refresh();
			}

	protected:
		//Window events
		void OnSize(wxSizeEvent& event);
		void OnPaint(wxPaintEvent& event);
		void OnEraseBackground(wxEraseEvent& event);

		ImageViewWindow	*m_parent;
		wxBitmap		*m_bitmap;

		DECLARE_EVENT_TABLE()
	};

	ImageViewWindow(wxFrame *parent, wxBitmap* bitmap, const wxString& title);
	~ImageViewWindow();

	void SetBitmap(wxBitmap* bitmap)
	{
		m_canvas->SetBitmap(bitmap);
	}

protected:
	void OnExit(wxCloseEvent& event);

	wxFrame					*m_parent;
	ImageViewScrolledWindow	*m_canvas;

	DECLARE_EVENT_TABLE()
};




