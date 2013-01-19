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

#include "LayersWindow.h"
#include "Tokenizer.h"

#include "../icons/layers_new.xpm"
#include "../icons/layers_up.xpm"
#include "../icons/layers_down.xpm"
#include "../icons/layers_delete.xpm"
#include "../icons/layers_eye.xpm"


IMPLEMENT_CLASS(LayersWindow, wxWindow);


LayersWindow::LayersWindow(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxWindow(parent, id, pos, size, style)
{
	SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_wndLayersList = new LayersWindowList(this,
		wxID_ANY,
		wxDefaultPosition,
		wxDefaultSize,
		wxVSCROLL | wxNO_BORDER | wxFULL_REPAINT_ON_RESIZE
		);


	m_toolBar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxSize(-1, 28), wxTB_HORIZONTAL );

	m_toolBar->SetToolBitmapSize(wxSize(16,16));
	//m_toolBar->SetToolSeparation(3);
	m_toolBar->SetMargins(0,0);

	//m_toolBar->AddSeparator();
	m_toolBar->AddTool( idToolNew, _T("Add Layer"), wxBitmap(layers_new_xpm), wxNullBitmap, wxITEM_NORMAL, _T("Add Layer"), wxEmptyString );
	//m_toolBar->AddSeparator();
	m_toolBar->AddTool( idToolUp, _T("Move Up"), wxBitmap(layers_up_xpm), wxNullBitmap, wxITEM_NORMAL, _T("Swap current layer with previous"), wxEmptyString );
	m_toolBar->AddTool( idToolDown, _T("Move Up"), wxBitmap(layers_down_xpm), wxNullBitmap, wxITEM_NORMAL, _T("Swap current layer with next"), wxEmptyString );
	//m_toolBar->AddSeparator();
	m_toolBar->AddTool( idToolDelete, _T("Delete Layer"), wxBitmap(layers_delete_xpm), wxNullBitmap, wxITEM_NORMAL, _T("Delete Layer"), wxEmptyString );
	m_toolBar->Realize();

	wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );

	sizer->Add( m_wndLayersList, 1, wxEXPAND, 5 );
	sizer->Add( m_toolBar, 0, wxEXPAND, 5 );

	SetSizer( sizer );
	Layout();

	Connect( idToolNew, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LayersWindow::OnNewLayer ) );
	Connect( idToolNew, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( LayersWindow::OnNewLayerUI ) );
	Connect( idToolUp, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LayersWindow::OnMoveLayerUp ) );
	Connect( idToolUp, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( LayersWindow::OnMoveLayerUpUI ) );
	Connect( idToolDown, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LayersWindow::OnMoveLayerDown ) );
	Connect( idToolDown, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( LayersWindow::OnMoveLayerDownUI ) );
	Connect( idToolDelete, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LayersWindow::OnDeleteLayer ) );
	Connect( idToolDelete, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( LayersWindow::OnDeleteLayerUI ) );

	Connect( wxEVT_SIZE, wxSizeEventHandler( LayersWindow::OnSize ), 0, this );
}


LayersWindow::~LayersWindow()
{
	Disconnect( idToolNew, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LayersWindow::OnNewLayer ) );
	Disconnect( idToolNew, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( LayersWindow::OnNewLayerUI ) );
	Disconnect( idToolUp, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LayersWindow::OnMoveLayerUp ) );
	Disconnect( idToolUp, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( LayersWindow::OnMoveLayerUpUI ) );
	Disconnect( idToolDown, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LayersWindow::OnMoveLayerDown ) );
	Disconnect( idToolDown, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( LayersWindow::OnMoveLayerDownUI ) );
	Disconnect( idToolDelete, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( LayersWindow::OnDeleteLayer ) );
	Disconnect( idToolDelete, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( LayersWindow::OnDeleteLayerUI ) );

	Disconnect( wxEVT_SIZE, wxSizeEventHandler( LayersWindow::OnSize ), 0, this );
}


void LayersWindow::OnNewLayer(wxCommandEvent& event)
{
	event.Skip(false);

	Map* map = Editor->GetActiveMap();
	if(!map)
		return;

	map->AddLayer();

	Refresh();
	m_wndLayersList->RecalculateScrollBarValues();
}


void LayersWindow::OnNewLayerUI(wxUpdateUIEvent& event)
{
	Map* map = Editor->GetActiveMap();
	event.Enable( map != 0 && map->NumLayers() < Map::MaxLayers );
}


void LayersWindow::OnMoveLayerUp(wxCommandEvent& event)
{
	event.Skip(false);

	Map* map = Editor->GetActiveMap();
	if(map)
	{
		map->MoveLayerUp();
		Refresh();
	}
}


void LayersWindow::OnMoveLayerUpUI(wxUpdateUIEvent& event)
{
	Map* map = Editor->GetActiveMap();
	//event.Enable( map != 0 && map->NumLayers() < Map::MaxLayers );
	event.Enable( map && map->GetActiveLayerIndex() > 0 );
}


void LayersWindow::OnMoveLayerDown(wxCommandEvent& event)
{
	event.Skip(false);

	Map* map = Editor->GetActiveMap();
	if(map)
	{
		map->MoveLayerDown();
		Refresh();
	}
}


void LayersWindow::OnMoveLayerDownUI(wxUpdateUIEvent& event)
{
	Map* map = Editor->GetActiveMap();
	event.Enable( map && map->GetActiveLayerIndex() < map->NumLayers() - 1 );
}


void LayersWindow::OnDeleteLayer(wxCommandEvent& event)
{
	event.Skip(false);

	Map* map = Editor->GetActiveMap();
	if(map)
	{
		map->RemoveLayer();
		Refresh();
	}
}


void LayersWindow::OnDeleteLayerUI(wxUpdateUIEvent& event)
{
	Map* map = Editor->GetActiveMap();
	event.Enable( map && map->NumLayers() > 1 );
}


void LayersWindow::OnSize(wxSizeEvent& event)
{
	event.Skip(true);
	Layout();
}


void LayersWindow::Refresh()
{
	wxWindow::Refresh();
	Editor->GetMainFrame()->RefreshMapWindow();
}



