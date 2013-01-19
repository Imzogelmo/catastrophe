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

#include "LayersWindowList.h"

#include "Icons.h"

#include "../icons/layers_new.xpm"
#include "../icons/layers_up.xpm"
#include "../icons/layers_down.xpm"
#include "../icons/layers_delete.xpm"
#include "../icons/layers_eye.xpm"


#define LAYER_CELL_SQUARE_EYE    16
#define LAYER_CELL_MARGIN_WIDTH  8
//#define LAYER_CELL_MARGIN_HEIGHT 8
#define LAYER_CELL_MARGIN_HEIGHT 0
#define LAYER_CELL_HEIGHT        (LAYER_CELL_SQUARE_EYE + (LAYER_CELL_MARGIN_HEIGHT * 2))
#define LAYER_BITMAP_SIZE        (LAYER_CELL_SQUARE_EYE + LAYER_CELL_MARGIN_HEIGHT)
#define LAYER_HALF_BITMAP_SIZE   (LAYER_BITMAP_SIZE / 2)


IMPLEMENT_CLASS(LayersWindowList, wxScrolledWindow);



LayersWindowList::LayersWindowList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxScrolledWindow(parent, id, pos, size, style)
{
	m_map = 0;

	m_needRefresh = false;
	m_mouseInsideEyeLayerNum = -1;

	//wxColour colourBackground = wxSystemSettings::GetColour(wxSYS_COLOUR_MENU); //wxSYS_COLOUR_WINDOWFRAME);
	//wxColour colourSelected   = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT); //wxSYS_COLOUR_ACTIVECAPTION);

	//m_colorText = wxSystemSettings::GetColour(wxSYS_COLOUR_MENUTEXT);
	//m_colorTextSelected = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT);

	wxColour colourBackground = wxColour(255,255,255);
	wxColour colourSelected   = wxColour(96,122,255);

	m_colorText = wxColour(0,0,0);
	m_colorTextSelected = wxColour(0,0,0);

	SetBackgroundColour(colourBackground);

	//m_bitmapEye = wxBitmap(layers_eye_xpm);
	m_bitmapEye = Icon::Quake3;

	m_brushBackground.SetColour(colourBackground);
	m_brushBackground.SetStyle(wxSOLID);

	m_penBackground.SetWidth(1);
	m_penBackground.SetColour(colourBackground);
	m_penBackground.SetStyle(wxSOLID);

	m_brushSelected.SetColour(colourSelected);
	m_brushBackground.SetStyle(wxSOLID);

	CreateEyesBitmaps();


	Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( LayersWindowList::OnEnterWindow ), 0, this );
	Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( LayersWindowList::OnLeaveWindow ), 0, this );
	Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( LayersWindowList::OnLeftDown ), 0, this );
	Connect( wxEVT_MOTION, wxMouseEventHandler( LayersWindowList::OnMouseMove ), 0, this );
	Connect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( LayersWindowList::OnEraseBackground ), 0, this );
	Connect( wxEVT_PAINT, wxPaintEventHandler( LayersWindowList::OnPaint ), 0, this );
	Connect( wxEVT_SIZE, wxSizeEventHandler( LayersWindowList::OnSize ), 0, this );
}


LayersWindowList::~LayersWindowList()
{
	Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( LayersWindowList::OnEnterWindow ), 0, this );
	Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( LayersWindowList::OnLeaveWindow ), 0, this );
	Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( LayersWindowList::OnLeftDown ), 0, this );
	Disconnect( wxEVT_MOTION, wxMouseEventHandler( LayersWindowList::OnMouseMove ), 0, this );
	Disconnect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( LayersWindowList::OnEraseBackground ), 0, this );
	Disconnect( wxEVT_PAINT, wxPaintEventHandler( LayersWindowList::OnPaint ), 0, this );
	Disconnect( wxEVT_SIZE, wxSizeEventHandler( LayersWindowList::OnSize ), 0, this );
}


void LayersWindowList::CreateEyesBitmaps()
{
	wxMemoryDC memDC;

	m_bmpNoEyeSelectedSquared.Create(LAYER_BITMAP_SIZE, LAYER_BITMAP_SIZE);
	memDC.SelectObject(m_bmpNoEyeSelectedSquared);
	memDC.SetPen(*wxLIGHT_GREY_PEN);
	memDC.SetBrush(m_brushSelected);
	memDC.DrawRectangle(0, 0, LAYER_BITMAP_SIZE, LAYER_BITMAP_SIZE);
	memDC.SetBrush(*wxTRANSPARENT_BRUSH);
	memDC.SetPen(*wxBLACK_DASHED_PEN);
	memDC.DrawRectangle(0, 0, LAYER_BITMAP_SIZE, LAYER_BITMAP_SIZE);

	m_bmpEyeSelectedSquared.Create(LAYER_BITMAP_SIZE, LAYER_BITMAP_SIZE);
	memDC.SelectObject(m_bmpEyeSelectedSquared);
	memDC.DrawBitmap(m_bmpNoEyeSelectedSquared, 0, 0);
	memDC.DrawBitmap(m_bitmapEye, 4, 4, true);

	m_bmpNoEyeNotSelectedSquared.Create(LAYER_BITMAP_SIZE, LAYER_BITMAP_SIZE);
	memDC.SelectObject(m_bmpNoEyeNotSelectedSquared);
	memDC.SetPen(m_penBackground);
	memDC.SetBrush(m_brushBackground);
	memDC.DrawRectangle(0, 0, LAYER_BITMAP_SIZE, LAYER_BITMAP_SIZE);
	memDC.SetBrush(*wxTRANSPARENT_BRUSH);
	memDC.SetPen(*wxBLACK_DASHED_PEN);
	memDC.DrawRectangle(0, 0, LAYER_BITMAP_SIZE, LAYER_BITMAP_SIZE);

	m_bmpEyeNotSelectedSquared.Create(LAYER_BITMAP_SIZE, LAYER_BITMAP_SIZE);
	memDC.SelectObject(m_bmpEyeNotSelectedSquared);
	memDC.DrawBitmap(m_bmpNoEyeNotSelectedSquared, 0, 0);
	memDC.DrawBitmap(m_bitmapEye, 4, 4, true);
}


void LayersWindowList::MouseMoveOnEye(int x, int y)
{
	Map* map = Editor->GetActiveMap();
	if(!map)
		return;

	int cellHeight = LAYER_CELL_HEIGHT;
	int celly      = y / cellHeight;
	int firstLayer = GetScrollPos(wxVERTICAL);
	int layer      = firstLayer + celly;

	if( layer >= (int)map->NumLayers() )
	{
		if(m_needRefresh)
			Refresh();
		return;
	}

	wxBitmap *bitmap = 0;
	int posY = celly * cellHeight;
	int posYFrom = posY + (cellHeight / 2) - LAYER_HALF_BITMAP_SIZE;
	int posYTo   = posYFrom + LAYER_BITMAP_SIZE;

	if( x >= LAYER_CELL_MARGIN_WIDTH && x <= LAYER_CELL_MARGIN_WIDTH + LAYER_BITMAP_SIZE && y >= posYFrom && y <= posYTo)
	{
		if (m_mouseInsideEyeLayerNum != layer)
		{
			bool visible = map->IsLayerVisible(layer);
			if( layer == map->GetActiveLayerIndex() )
			{
				bitmap = visible ? &m_bmpEyeSelectedSquared : &m_bmpNoEyeSelectedSquared;
			}
			else
			{
				bitmap = visible ? &m_bmpEyeNotSelectedSquared : &m_bmpNoEyeNotSelectedSquared;
			}

			if(m_needRefresh)
				Refresh();

			//CLIENTDC dc(this);
			wxClientDC dc(this);
			dc.DrawBitmap(*bitmap, LAYER_CELL_MARGIN_WIDTH, posYFrom);

			m_needRefresh = true;
			m_mouseInsideEyeLayerNum = layer;
		}
	}
	else
	{
		if (m_needRefresh)
			Refresh();
	}
}


void LayersWindowList::OnEnterWindow(wxMouseEvent& event)
{
	event.Skip(false);

	//GetParent()->SetFocus();
}


void LayersWindowList::OnLeaveWindow(wxMouseEvent& event)
{
	event.Skip(true);

	if(m_needRefresh)
		Refresh();
}


void LayersWindowList::OnLeftDown(wxMouseEvent& event)
{
	event.Skip(false);

	Map* map = Editor->GetActiveMap();
	if(!map)
		return;

	int cellHeight    = LAYER_CELL_HEIGHT;
	int x             = event.GetX();
	int y             = event.GetY();
	int celly         = y / cellHeight;
	int firstLayer    = GetScrollPos(wxVERTICAL);
	int selectedLayer = firstLayer + celly;

	if( selectedLayer >= (int)map->NumLayers() || selectedLayer < 0 )
		return;

	int posY = celly * cellHeight;
	int posYFrom = posY + (cellHeight / 2) - LAYER_HALF_BITMAP_SIZE;
	int posYTo   = posYFrom + LAYER_BITMAP_SIZE;

	if (x>=LAYER_CELL_MARGIN_WIDTH && x<=LAYER_CELL_MARGIN_WIDTH + LAYER_BITMAP_SIZE && y>=posYFrom && y<=posYTo)
	{
		bool visible = map->IsLayerVisible( (uint)selectedLayer );
		map->SetLayerVisibility( selectedLayer, !visible );
	}
	else
	{
		map->SetActiveLayer(selectedLayer);
	}

	Refresh();
	Editor->GetMainFrame()->Refresh();
}


void LayersWindowList::OnMouseMove(wxMouseEvent& event)
{
	event.Skip(false);
	MouseMoveOnEye(event.GetX(),event.GetY());
}


void LayersWindowList::OnEraseBackground(wxEraseEvent& event)
{
	event.Skip(false);
}


void LayersWindowList::OnPaint(wxPaintEvent& event)
{
	event.Skip(false);

#ifdef __UNIX__
	wxAutoBufferedPaintDC dc(this);
#else
	wxPaintDC dc(this);
#endif

	DoPrepareDC(dc);

	wxCoord rectWidth, rectHeight;
	dc.GetSize(&rectWidth, &rectHeight);

	dc.SetPen(m_penBackground);
	dc.SetBrush(m_brushBackground);
	dc.DrawRectangle(0, 0, rectWidth, rectHeight);

	dc.SetTextForeground(m_colorText);
	wxFont fontNormal = dc.GetFont();
	wxFont fontBold = dc.GetFont();
	fontNormal.SetWeight(wxFONTWEIGHT_NORMAL);
	fontBold.SetWeight(wxFONTWEIGHT_BOLD);


	Map* map = Editor->GetActiveMap();
	if(!map)
	{
	}
	else
	{
		// Draw layers
		int      posY, posYFrom;
		int      cellHeight = LAYER_CELL_HEIGHT;
		wxString layerName;

		wxPoint mousePosition = ScreenToClient (wxGetMousePosition());
		wxInt8  numLayer = 0;

		for( numLayer=0 && map->NumLayers() > 0; numLayer < (wxInt8)map->NumLayers(); numLayer++ )
		{
			if( numLayer == map->GetActiveLayerIndex() )
			{
				dc.SetPen(*wxLIGHT_GREY_PEN);
				dc.SetBrush(m_brushSelected);
				dc.SetFont(fontBold);
				dc.SetTextForeground(m_colorTextSelected);
			}
			else
			{
				dc.SetPen(m_penBackground);
				dc.SetBrush(m_brushBackground);
				dc.SetFont(fontNormal);
				dc.SetTextForeground(m_colorText);
			}

			//Background
			posY = numLayer * cellHeight;
			dc.DrawRectangle(0, posY, rectWidth, cellHeight);

			//Eye bitmap
			if( map->IsLayerVisible(numLayer) )
			{
				dc.DrawBitmap (m_bitmapEye,
					LAYER_CELL_MARGIN_WIDTH + 4,
					posY + (cellHeight / 2) - 8, true);
			}

			//Rectangle dashed Eye
			posYFrom = posY + (cellHeight / 2) - LAYER_HALF_BITMAP_SIZE;
			if (mousePosition.y>=posYFrom
				&& mousePosition.y<=posYFrom + LAYER_BITMAP_SIZE
				&& mousePosition.x>=LAYER_CELL_MARGIN_WIDTH
				&& mousePosition.x<=LAYER_CELL_MARGIN_WIDTH + LAYER_BITMAP_SIZE)
			{
				dc.SetBrush(*wxTRANSPARENT_BRUSH);
				dc.SetPen(*wxBLACK_DASHED_PEN);
				dc.DrawRectangle(LAYER_CELL_MARGIN_WIDTH, posYFrom, LAYER_BITMAP_SIZE, LAYER_BITMAP_SIZE);
			}

			//Layer Name
			GetLayerName( layerName, (int)numLayer );

			wxCoord textWidth, textHeight;
			dc.GetTextExtent(layerName, &textWidth, &textHeight);
			dc.DrawText(layerName,
				(LAYER_CELL_MARGIN_WIDTH * 2) + LAYER_BITMAP_SIZE,
				posY + (cellHeight/2) - (textHeight/2)
				);
		}

		dc.SetPen(m_penBackground);
		dc.SetBrush(m_brushBackground);
		posY = numLayer * cellHeight;
		dc.DrawRectangle(0, posY, rectWidth, cellHeight);
	}

	m_needRefresh = false;
	m_mouseInsideEyeLayerNum = -1;
}


void LayersWindowList::OnSize(wxSizeEvent& event)
{
	event.Skip();
	RecalculateScrollBarValues();
}


void LayersWindowList::SetMap(Map *map)
{
	//m_map     = map;
	RecalculateScrollBarValues();
}


void LayersWindowList::RecalculateScrollBarValues()
{
	Map* map = Editor->GetActiveMap();
	if(map)
	{
		int rectWidth, rectHeight;
		GetClientSize (&rectWidth, &rectHeight);

		//int visibleRows = rectHeight / LAYER_CELL_HEIGHT;
		int numLayers = (int)map->NumLayers();
		int posY = GetScrollPos(wxVERTICAL);

		SetScrollbars(0, LAYER_CELL_HEIGHT, 0, numLayers, 0, posY, false);
	}
	else
	{
		SetScrollbars(0, 0, 0, 0, 0, 0, false);
	}

	Refresh();
}


void LayersWindowList::GetLayerName( wxString& outName, int layer )
{
	outName = "Layer ";
	outName << layer;
}




