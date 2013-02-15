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

#include "Editor.h"
#include "LayersWindowList.h"


class LayersWindow : public wxWindow
{
DECLARE_CLASS(LayersWindow)

public:
	LayersWindow(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0);

	virtual ~LayersWindow();

protected:
	enum
	{
		idPanelLayers = 3000,
		idToolNew,
		idToolUp,
		idToolDown,
		idToolDelete
	};

	LayersWindowList*	m_wndLayersList;
	wxToolBar*			m_toolBar;

	virtual void OnNewLayer(wxCommandEvent& event);
	virtual void OnNewLayerUI(wxUpdateUIEvent& event);
	virtual void OnMoveLayerUp(wxCommandEvent& event);
	virtual void OnMoveLayerUpUI(wxUpdateUIEvent& event);
	virtual void OnMoveLayerDown(wxCommandEvent& event);
	virtual void OnMoveLayerDownUI(wxUpdateUIEvent& event);
	virtual void OnDeleteLayer(wxCommandEvent& event);
	virtual void OnDeleteLayerUI(wxUpdateUIEvent& event);

	virtual void OnSize(wxSizeEvent& event);
	virtual void Refresh();

};




