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
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <fc/vector.h>



enum ImageMenu
{
	ID_FILE_EXIT = MainMenu::ID_MAX + 1,
	ID_IMAGE_LOAD,
	ID_IMAGE_SAVE_AS,
	ID_IMAGE_SAVE_TILE_BUFFER_AS,
	ID_IMAGE_RIP_TILES,
	ID_IMAGE_RIP_TILES_TO_BUFFER

};




class ImageWindow;
class ImageViewWindow;

class ImageWindowFrame : public wxFrame
{
public:
	ImageWindowFrame(wxFrame *parent, wxBitmap* bitmap, const wxString& title, const wxPoint& pos, const wxSize& size);
	~ImageWindowFrame();

protected:
	void OnExit(wxCloseEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnQuit(wxCommandEvent& event);

	void OnLoadImage(wxCommandEvent& event);
	void OnSaveImage(wxCommandEvent& event);
	void OnSaveTileBufferAs(wxCommandEvent& event);
	void OnRipTilesToBuffer(wxCommandEvent& event);

protected:
	wxFrame			*m_parent;
	wxMenuBar		*m_menuBar;
	ImageWindow		*m_canvas;


	DECLARE_EVENT_TABLE()
};




class ImageWindow : public wxScrolledWindow
{
public:
	ImageWindow(wxFrame* parent, wxBitmap* bitmap, const wxSize& size);
	~ImageWindow();

	void AddTileToQueue();
	void RemoveTileFromQueue();
	void LoadNewImage();
	void SaveImageAs();
	void SaveTileBufferAs();
	void RipTilesToBuffer();

	//Window events
	void OnSize(wxSizeEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnEraseBackground(wxEraseEvent& event);

	//Mouse events
	void OnLeftClickPress(wxMouseEvent& event);
	void OnLeftClickRelease(wxMouseEvent& event);
	void OnRightClickPress(wxMouseEvent& event);
	void OnRightClickRelease(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnMouseLeaveWindow(wxMouseEvent& event);
	void OnMouseEnterWindow(wxMouseEvent& event);

	//Key events
	void OnKeyDown(wxKeyEvent& event);
	void OnKeyUp(wxKeyEvent& event);

protected:
	wxFrame *m_parent;
	wxBitmap *m_bitmap;

	wxPoint m_tileOffset;
	wxPoint m_mousePos;
	wxPoint m_mouseOffset;
	bool	m_mouseIsInWindow;
	bool	m_mouseLeftButton;
	bool	m_mouseRightButton;
	bool	m_showGrid;

	fc::vector<wxPoint> m_clickedTiles;

	UniqueTileRipper	*m_uniqueTileRipper;
	ImageViewWindow		*m_tileView;

	DECLARE_EVENT_TABLE()
};



