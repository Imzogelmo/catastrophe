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

#include "ImageWindow.h"
#include "Dialogs.h"
#include "wxImageViewWindow.h"
#include "ColorConverter.h"

#include "MainMenuBar.h"
#include "UniqueTileRipper.h"



BEGIN_EVENT_TABLE(ImageWindowFrame, wxFrame)
	EVT_CLOSE		(ImageWindowFrame::OnExit)
	EVT_SIZE		(ImageWindowFrame::OnSize)
	EVT_MENU		(ID_FILE_EXIT, ImageWindowFrame::OnQuit)
	EVT_MENU		(ID_IMAGE_LOAD, ImageWindowFrame::OnLoadImage)
	EVT_MENU		(ID_IMAGE_SAVE_AS, ImageWindowFrame::OnSaveImage)
	EVT_MENU		(ID_IMAGE_SAVE_TILE_BUFFER_AS, ImageWindowFrame::OnSaveTileBufferAs)
	EVT_MENU		(ID_IMAGE_RIP_TILES_TO_BUFFER, ImageWindowFrame::OnRipTilesToBuffer)
END_EVENT_TABLE()



BEGIN_EVENT_TABLE(ImageWindow, wxScrolledWindow)
	EVT_SIZE			(ImageWindow::OnSize)
	EVT_PAINT			(ImageWindow::OnPaint)
	EVT_ERASE_BACKGROUND(ImageWindow::OnEraseBackground)

	//Mouse events
	EVT_LEFT_DOWN		(ImageWindow::OnLeftClickPress)
	EVT_LEFT_UP			(ImageWindow::OnLeftClickRelease)
	EVT_RIGHT_DOWN		(ImageWindow::OnRightClickPress)
	EVT_RIGHT_UP		(ImageWindow::OnRightClickRelease)
	EVT_MOTION			(ImageWindow::OnMouseMove)
	EVT_LEAVE_WINDOW	(ImageWindow::OnMouseLeaveWindow)
	EVT_ENTER_WINDOW	(ImageWindow::OnMouseEnterWindow)
	EVT_KEY_DOWN		(ImageWindow::OnKeyDown)
	EVT_KEY_UP			(ImageWindow::OnKeyUp)
END_EVENT_TABLE()



ImageWindowFrame::ImageWindowFrame(wxFrame *parent, wxBitmap* bitmap, const wxString& title, const wxPoint& pos, const wxSize& size) : 
	wxFrame(parent, 
		wxID_ANY, 
		title, 
		pos, 
		wxSize(	std::max(80, std::min(800, size.GetWidth())), 
				std::max(60, std::min(600, size.GetHeight()))
		)
	),
	m_parent(parent)
{

	m_canvas = new ImageWindow(this, bitmap, size);


	wxMenu *fileMenu = new wxMenu;
	fileMenu->Append(ID_FILE_EXIT, _T("&Close"));

	wxMenu *imageMenu = new wxMenu;
	imageMenu->Append(ID_IMAGE_LOAD, _T("&Load Image"));
	imageMenu->Append(ID_IMAGE_SAVE_AS, _T("&Save Image As..."));
	imageMenu->AppendSeparator();
	imageMenu->Append(ID_IMAGE_SAVE_TILE_BUFFER_AS, _T("&Save Tile Buffer As Image..."));
	//imageMenu->Append(ID_FILE_EXIT, _T("&Close"));

	wxMenu *ripMenu = new wxMenu;
	ripMenu->Append(ID_IMAGE_RIP_TILES_TO_BUFFER, _T("&Rip Unique Tiles To Buffer"));


	m_menuBar = new wxMenuBar;
	m_menuBar->Append(fileMenu, _T("&Window"));
	m_menuBar->Append(imageMenu, _T("&Image"));
	m_menuBar->Append(ripMenu, _T("&Rip"));
	SetMenuBar(m_menuBar);



	CreateStatusBar(2);
	SetStatusText(wxT("Status bar"), 0);

	this->SetMinSize( wxSize(80, 60) );
	this->Show(true);
}


ImageWindowFrame::~ImageWindowFrame()
{
}


void ImageWindowFrame::OnExit(wxCloseEvent& WXUNUSED(event))
{
	this->Destroy();
}


void ImageWindowFrame::OnSize(wxSizeEvent& event)
{
	wxFrame::OnSize(event);
}


void ImageWindowFrame::OnLoadImage(wxCommandEvent& WXUNUSED(event))
{
	m_canvas->LoadNewImage();
}


void ImageWindowFrame::OnSaveImage(wxCommandEvent& WXUNUSED(event))
{
	m_canvas->SaveImageAs();
}


void ImageWindowFrame::OnSaveTileBufferAs(wxCommandEvent& WXUNUSED(event))
{
	m_canvas->SaveTileBufferAs();
}


void ImageWindowFrame::OnRipTilesToBuffer(wxCommandEvent& WXUNUSED(event))
{
	m_canvas->RipTilesToBuffer();
}


void ImageWindowFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
   // this->Close(true);
	this->Destroy();
}




ImageWindow::ImageWindow(wxFrame* parent, wxBitmap* bitmap, const wxSize& size) :
	wxScrolledWindow(parent,
		wxID_ANY,
		wxDefaultPosition,
		wxDefaultSize,
		wxHSCROLL | wxVSCROLL
	),
	m_parent(parent),
	m_bitmap(bitmap),
	m_mouseLeftButton(false),
	m_mouseRightButton(false),
	m_showGrid(true)
{
	m_uniqueTileRipper = 0;
	m_tileView = 0;

	if(!m_bitmap)
		parent->Destroy();


	this->SetScrollbars(1, 1, size.GetWidth(), size.GetHeight());
}


ImageWindow::~ImageWindow()
{
	if(m_bitmap) delete m_bitmap;
	if(m_uniqueTileRipper) delete m_uniqueTileRipper;
}


void ImageWindow::OnSize(wxSizeEvent& event)
{
	wxScrolledWindow::OnSize(event);
}


void ImageWindow::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	//wxGCDC dc(this);
	wxPaintDC paintDC(this);
	//wxGraphicsContext* gdc = wxGraphicsContext::Create( dc );

	//wxPaintDC dc( this );
	//PrepareDC( dc );

	wxGCDC dc(paintDC);//paintDC) ;
	PrepareDC(dc);
	m_parent->PrepareDC(dc);

	if( m_bitmap && m_bitmap->Ok() )
	{
		//Sub-bitmap rect must be valid
		const int x = Math::Clamp(GetScrollPos(wxHORIZONTAL) - 1, 0, m_bitmap->GetWidth());
		const int y = Math::Clamp(GetScrollPos(wxVERTICAL) - 1, 0, m_bitmap->GetHeight());
		const int w = Math::Clamp(GetSize().GetX(), 0, m_bitmap->GetWidth() - x);
		const int h = Math::Clamp(GetSize().GetY(), 0, m_bitmap->GetHeight() - y);
		const wxRect clippingRect = wxRect(x, y, w, h);

		m_mouseOffset = wxPoint(x, y);

		dc.DrawBitmap( m_bitmap->GetSubBitmap(clippingRect), clippingRect.GetPosition(), true );


		if(m_showGrid)
		{
			dc.SetPen( wxPen(wxColor(255, 255, 255, 192), 1, wxSOLID) );

			const wxPoint offset = wxPoint(x % 16, y % 16);
			const int xSize = x + w;
			const int ySize = y + h;
			wxPoint p1 = wxPoint(x, y) - offset + m_tileOffset;
			wxPoint p2 = wxPoint(xSize, y) - offset + m_tileOffset;

			for( int i(y); i < ySize; i += 16 )
			{
				dc.DrawLine(p1, p2);
				p1.y += 16;
				p2.y += 16;
			}

			p1 = wxPoint(x, y) - offset + m_tileOffset;
			p2 = wxPoint(x, ySize) - offset + m_tileOffset;
			for( int i(x); i < xSize; i += 16 )
			{
				dc.DrawLine(p1, p2);
				p1.x += 16;
				p2.x += 16;
			}
		}

		dc.SetPen( wxPen(wxColor(208, 208, 208, 192), 1, wxSOLID) );
		dc.SetBrush( wxBrush(wxColor(208, 208, 208, 192), wxSOLID) );

		const int top = clippingRect.GetTop();
		const int bottom = clippingRect.GetBottom();
		const int left = clippingRect.GetLeft();
		const int right = clippingRect.GetRight();

		const wxSize tileSize = wxSize(16,16);
		for( fc::vector<wxPoint> ::iterator it = m_clickedTiles.begin(); it != m_clickedTiles.end(); ++it )
		{
			const wxPoint& p = *it;
			if( p.x > left && p.x < right && p.y > top && p.y < bottom )
			{
				//Only draw what we can see
				dc.DrawRectangle( *it + m_tileOffset, tileSize );
			}
		}

	}
}


void ImageWindow::OnEraseBackground(wxEraseEvent& event)
{
	//Do not erase the background. (May cause flicker)
	//todo: sometimes we need to erase it tho. :P
	//grr..
	wxScrolledWindow::OnEraseBackground(event);
}


void ImageWindow::AddTileToQueue()
{
	const wxPoint pos = wxPoint(m_mousePos + m_mouseOffset);
	const wxPoint offset = wxPoint(pos.x % 16, pos.y % 16);
	const wxPoint point = pos - offset;

	if( std::find( m_clickedTiles.begin(), m_clickedTiles.end(), point ) != m_clickedTiles.end() )
		return;

	struct UpperBoundPredicate {
		bool operator() ( const wxPoint& a, const wxPoint& b ) { return a.y < b.y; }
	} _Pred;

	m_clickedTiles.insert( std::upper_bound( m_clickedTiles.begin(), m_clickedTiles.end(), point, _Pred ), point );
	Refresh(false);
}


void ImageWindow::RemoveTileFromQueue()
{
	const wxPoint pos = wxPoint(m_mousePos + m_mouseOffset);
	const wxPoint offset = wxPoint(pos.x % 16, pos.y % 16);
	const wxPoint point = pos - offset;

	fc::vector<wxPoint> ::iterator it = std::find( m_clickedTiles.begin(), m_clickedTiles.end(), point );
	if( it != m_clickedTiles.end() )
	{
		m_clickedTiles.erase(it);
		Refresh(false);
	}
}


void ImageWindow::OnLeftClickPress(wxMouseEvent& WXUNUSED(event))
{
	m_mouseLeftButton = true;
	AddTileToQueue();
}


void ImageWindow::OnLeftClickRelease(wxMouseEvent& WXUNUSED(event))
{
	m_mouseLeftButton = false;
}


void ImageWindow::OnRightClickPress(wxMouseEvent& WXUNUSED(event))
{
	m_mouseRightButton = true;
	RemoveTileFromQueue();
}


void ImageWindow::OnRightClickRelease(wxMouseEvent& WXUNUSED(event))
{
	m_mouseRightButton = false;
}


void ImageWindow::OnMouseMove(wxMouseEvent& event)
{
	m_mousePos = event.GetPosition();

	char s[128];
	sprintf(s, "x: %d y: %d", m_mousePos.x + m_mouseOffset.x, m_mousePos.y + m_mouseOffset.y);
	m_parent->SetStatusText(_T(s), 1);

	if(m_mouseIsInWindow)
	{
		if(m_mouseLeftButton)
		{
			AddTileToQueue();
		}
		else if(m_mouseRightButton)
		{
			RemoveTileFromQueue();
		}
	}
}


void ImageWindow::OnMouseLeaveWindow(wxMouseEvent& WXUNUSED(event))
{
	m_mouseIsInWindow = false;
	m_mouseLeftButton = false;
	m_mouseRightButton = false;
}


void ImageWindow::OnMouseEnterWindow(wxMouseEvent& WXUNUSED(event))
{
	m_mouseIsInWindow = true;
}



//Key events
void ImageWindow::OnKeyDown(wxKeyEvent& event)
{
	switch(event.GetKeyCode())
	{
		case WXK_UP:	m_tileOffset.y += 15;	break;
		case WXK_DOWN:	m_tileOffset.y ++;		break;
		case WXK_LEFT:	m_tileOffset.x += 15;	break;
		case WXK_RIGHT:	m_tileOffset.x ++;		break;
	}

	m_tileOffset.x %= 16;
	m_tileOffset.y %= 16;
	Refresh(false);

}


void ImageWindow::OnKeyUp(wxKeyEvent& WXUNUSED(event))
{
}



void ImageWindow::LoadNewImage()
{
	wxImage image;
	wxString filename;

	if( !Dialog::LoadImageDialog(&image, filename) )
		return;

	m_clickedTiles.clear();

	delete m_bitmap;
	m_bitmap = new wxBitmap(image);

	m_parent->SetTitle(filename);
	SetScrollbars(1, 1, image.GetWidth(), image.GetHeight());
}


void ImageWindow::SaveImageAs()
{
	wxImage image = m_bitmap->ConvertToImage();
	wxString filename;

	Dialog::SaveImageDialog(&image, filename);
}


void ImageWindow::RipTilesToBuffer()
{
	if(!m_uniqueTileRipper)
		m_uniqueTileRipper = new UniqueTileRipper;

	wxImage image = m_bitmap->ConvertToImage();
	ubyte *pixelData = ColorConverter::ConvertImageToRGBA( &image );
	if(!pixelData)
	{
		Dialog::ErrorDialog(_T("Could not convert image to a valid RGBA format. Pixel conversions for this type are unsupported."));
		return;
	}

	m_uniqueTileRipper->Rip( pixelData, (uint)m_bitmap->GetWidth(), (uint)m_bitmap->GetHeight() );


	wxImage *viewImage = ColorConverter::ConvertRGBAToImage( &m_uniqueTileRipper->tiles[0].r, 
			m_uniqueTileRipper->tile_pixmap_width, 
			m_uniqueTileRipper->tile_pixmap_height
		);

	wxBitmap *bitmap = new wxBitmap(*viewImage);
	delete viewImage;

	if(!m_tileView)
	{
		//wxString extension;
		//wxFileName::SplitPath(m_parent->GetTitle(), NULL, NULL, &extension);

		m_tileView = new ImageViewWindow(m_parent, bitmap, _T("Image View"));
	}
	else
	{
		m_tileView->SetBitmap(bitmap);
	}

}


void ImageWindow::SaveTileBufferAs()
{
	if(!m_uniqueTileRipper)
	{
		Dialog::ErrorDialog(_T("Tile buffer is empy!"));
		return;
	}

	m_uniqueTileRipper->SaveUniqueTilesAs();
}
