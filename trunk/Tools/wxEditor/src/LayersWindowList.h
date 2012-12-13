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

#include "MainEditorFrame.h"
#include "Editor.h"


class LayersWindowList : public wxScrolledWindow
{
DECLARE_CLASS(LayersWindowList)

public:
	LayersWindowList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxALWAYS_SHOW_SB | wxVSCROLL | wxHSCROLL | wxNO_BORDER
		);

	virtual ~LayersWindowList();

	void SetMap(Map *map);
	void RecalculateScrollBarValues();

	Map* GetMap() { return m_map; }

protected:

	void CreateEyesBitmaps();
	void MouseMoveOnEye(int x, int y);

	virtual void OnEnterWindow(wxMouseEvent& event);
	virtual void OnLeaveWindow(wxMouseEvent& event);
	virtual void OnLeftDown(wxMouseEvent& event);
	virtual void OnMouseMove(wxMouseEvent& event);
	virtual void OnEraseBackground(wxEraseEvent& event);
	virtual void OnPaint(wxPaintEvent& event);
	virtual void OnSize(wxSizeEvent& event);

	void GetLayerName( wxString& outName, int layer );

	wxBitmap m_bitmapEye;
	wxBrush  m_brushBackground;
	wxPen    m_penBackground;
	wxBrush  m_brushSelected;

	wxColour m_colorText;
	wxColour m_colorTextSelected;

	int      m_needRefresh;
	int      m_mouseInsideEyeLayerNum;

	Map  *m_map;

	wxBitmap  m_bmpNoEyeSelectedSquared;
	wxBitmap  m_bmpNoEyeNotSelectedSquared;
	wxBitmap  m_bmpEyeSelectedSquared;
	wxBitmap  m_bmpEyeNotSelectedSquared;

};

