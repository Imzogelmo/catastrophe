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

#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/event.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/splitter.h>
#include <wx/aui/aui.h>

#include "MainEditorFrame.h"
#include "MainMenuBar.h"
#include "GLTileCanvas.h"
#include "GLMapCanvas.h"
#include "Editor.h"
#include "LayersWindow.h"
#include "FileTree.h"
#include "MinimapWindow.h"
#include "MediaPlayerWindow.h"



MainEditorFrame::MainEditorFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : 
	wxFrame((wxWindow*)0, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE, _T("MainEditorFrame")),
	m_glContext(0)
{

	Editor = new AppEditor(this);


	wxGLCanvas *tempGLCanvas = new wxGLCanvas(this,
		wxID_ANY, 
		wxDefaultPosition, 
		wxDefaultSize
	);

	m_glContext = new wxGLContext(tempGLCanvas);
	m_glContext->SetCurrent(*tempGLCanvas);

	//Editor->GetTextureManager()->LoadImageFromFile( "data/_FF1_world_tiles.png" );
	//Image *image = Editor->GetTextureManager()->GetImage( "data/_FF1_world_tiles.png" );

	Editor->GetTextureManager()->LoadImageFromFile( "data/smb2.png" );
	Image *image = Editor->GetTextureManager()->GetImage( "data/smb2.png" );

	Tileset *tileset = new Tileset();
	tileset->CreateFromPixmap( image, "world tiles" );

	Editor->GetTilesets()->push_back( tileset );
	Editor->GetActiveTileset() = tileset;

	delete tempGLCanvas;


	int clientWidth, clientHeight;
	::wxDisplaySize(&clientWidth, &clientHeight);
	//this->SetSize(clientWidth - 100, clientHeight - 100);
	this->CentreOnScreen();

	this->InitializeMainMenu();
	this->InitializeToolBars();


	//**************************************************
	// wxAuiManager
	//**************************************************
	//m_auiManager = new wxAuiManager(this);
	m_auiManager.SetManagedWindow(this);

	const wxSize clientSize = GetClientSize();


	//**************************************************
	// File Tree
	//**************************************************
	//wxPanel* tpanel = new wxPanel(this);
	//FileTree* ftree = new FileTree(tpanel);
	FileTree* ftree = new FileTree(this);

	m_auiManager.AddPane(
		ftree,
		wxAuiPaneInfo().Name(_("Files")).
		Show(true).
		Caption("Files").
		//MinSize(120,320).
		MinSize(20,20).
		//FloatingSize(160,320).
		Left().
		Layer(1).
		Position(1).
		CloseButton(true).
		//TopDockable(false).
		//BottomDockable(false).
		MaximizeButton(false)
		);

	//**************************************************
	// Maps
	//**************************************************
	m_mapNotebook = new wxAuiNotebook(
		this, wxID_ANY,
		wxPoint(clientSize.x, clientSize.y),
		wxSize(clientWidth,clientHeight),
		wxAUI_NB_DEFAULT_STYLE
		);

	m_mapWindow = GLMapCanvas::CreateInstance(this, m_glContext);
	m_mapWindow->SetScrollbars(16, 16, 80, 80);
	//mp->GetScrollPos(wxVERTICAL);
	if( !m_mapNotebook->AddPage(m_mapWindow, "Map 0", true, wxNullBitmap) )
		throw 3456;

	m_auiManager.AddPane(
		m_mapNotebook,
		wxAuiPaneInfo().Name(_("Maps")).
		CenterPane().
		PaneBorder(true)
		);

	//**************************************************
	// Minimap
	//**************************************************
	m_minimapWindow = new MinimapWindow(this, m_glContext);

	m_auiManager.AddPane(
		m_minimapWindow,
		wxAuiPaneInfo().Name(_("MinimapWindow")).
		Show(true).
		Caption("Minimap").
		MinSize(160,160).
		FloatingSize(160,160).
		Right().
		Layer(1).
		Position(1).
		CloseButton(true).
		//TopDockable(false).
		//BottomDockable(false).
		MaximizeButton(false)
		);


	//**************************************************
	// Tiles
	//**************************************************
	m_tilesetNotebook = new wxAuiNotebook(
		this,
		wxID_ANY,
		wxDefaultPosition,
		wxSize(160,512)
		);

	//GLTileCanvasWindow *tp = GLTileCanvas::CreateTileCanvas(this, m_glContext);
	m_tilesetWindow = GLTileCanvas::CreateInstance(m_tilesetNotebook, m_glContext);
	m_tilesetWindow->SetScrollbars(16, 16, 80, 80);
	m_tilesetWindow->SetScrollbarUnits( tileset->Width(), tileset->Height() );
	if( !m_tilesetNotebook->AddPage(m_tilesetWindow, "Tileset 0", true, wxNullBitmap) )
		throw 3459;

	m_auiManager.AddPane(
		m_tilesetNotebook,
		wxAuiPaneInfo().Name(_("Tilesets")).
		Show(true).
		Caption("Tilesets").
		MinSize(160,160).
		FloatingSize(160,160).
		Right().
		Layer(1).
		Position(2).
		CloseButton(true).
		//TopDockable(false).
		//BottomDockable(false).
		MaximizeButton(false)
		);


	//**************************************************
	// Map Properties
	//**************************************************
	m_mapPropertiesNotebook = new wxAuiNotebook(
		this,
		wxID_ANY,
		wxDefaultPosition,
		wxSize(120,120),
		wxAUI_NB_TOP|wxAUI_NB_TAB_SPLIT|wxAUI_NB_TAB_MOVE|wxAUI_NB_SCROLL_BUTTONS|wxAUI_NB_MIDDLE_CLICK_CLOSE
		);


	LayersWindow* layersWindow = new LayersWindow(
		m_mapPropertiesNotebook,
		wxID_ANY
		);
/*
	wxWindow *layers = new wxWindow(
		this,
		wxID_ANY,
		wxDefaultPosition,
		wxSize(80,80)
		);
*/
	m_mapPropertiesNotebook->AddPage(layersWindow, "Layers", true, wxNullBitmap);

	m_auiManager.AddPane(
		m_mapPropertiesNotebook,
		wxAuiPaneInfo().Name(_("Map Properties")).
		Show(true).
		Caption("Map Properties").
		MinSize(80,80).
		FloatingSize(80,80).
		Left().
		Layer(1).
		Position(2).
		CloseButton(true).
		//PinButton().
		//Gripper().GripperTop().
		//Dockable()
		MaximizeButton(true)
		);



	//**************************************************
	// Media Player
	//**************************************************
	m_mediaPlayer = new MediaPlayerWindow(this);

	m_auiManager.AddPane(
		m_mediaPlayer,
		wxAuiPaneInfo().Name(_("Media Player")).
		Show(true).
		Caption("Audio Player").
		//Float().PinButton().
		//MinSize(80,80).
		//FloatingSize(80,80).
		Left().
		Layer(1).
		Position(2).
		CloseButton(true).
		MaximizeButton(false)
		);


	m_auiManager.Update();
	
	m_mapNotebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( MainEditorFrame::OnMapAuiNotebookPageChanged ), (wxObject*)0, this );
	m_mapNotebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE, wxAuiNotebookEventHandler( MainEditorFrame::OnMapAuiNotebookPageClose ), (wxObject*)0, this );

	m_tilesetNotebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( MainEditorFrame::OnTilesetAuiNotebookPageChanged ), (wxObject*)0, this );
	m_tilesetNotebook->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE, wxAuiNotebookEventHandler( MainEditorFrame::OnTilesetAuiNotebookPageClose ), (wxObject*)0, this );


	this->CreateStatusBar();
	this->SetStatusText(wxT("Status bar.. needs to show x,y, selected x, layer x, etc.."), 0);

}


MainEditorFrame::~MainEditorFrame()
{

	m_mapNotebook->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( MainEditorFrame::OnMapAuiNotebookPageChanged ), (wxObject*)0, this );
	m_mapNotebook->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE, wxAuiNotebookEventHandler( MainEditorFrame::OnMapAuiNotebookPageClose ), (wxObject*)0, this );
	m_tilesetNotebook->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( MainEditorFrame::OnTilesetAuiNotebookPageChanged ), (wxObject*)0, this );
	m_tilesetNotebook->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE, wxAuiNotebookEventHandler( MainEditorFrame::OnTilesetAuiNotebookPageClose ), (wxObject*)0, this );

	m_auiManager.UnInit();

	if(Editor)
		delete Editor, Editor = 0;

}


void MainEditorFrame::OnIdle(wxIdleEvent& WXUNUSED(event))
{
}


void MainEditorFrame::OnExit(wxCloseEvent& event)
{
	wxCommandEvent e;
	//OnMapSave( e );
#ifdef _DEBUG
	if( false ) // quick exit
#else
	if( true )
#endif
	{
		wxMessageDialog* dialog = new wxMessageDialog( this,
				"Dou you want to quit?",
				"Are you super-duper ultra shure?",
				wxYES_NO|wxCANCEL
			);

		int result = dialog->ShowModal();
		dialog->Destroy();

		switch(result)
		{
			case wxID_YES:
			{
			}
			break;
			case wxID_NO:
			{
			}
			//fall through
			case wxID_CANCEL:
			default:
			{
				if( event.CanVeto() )
				{
					event.Veto();
					return;
				}
			}
			break;
		}
	}

	this->Destroy();
}


void MainEditorFrame::OnSize(wxSizeEvent& event)
{
	//.....

	wxFrame::OnSize(event);
}



void MainEditorFrame::OnMapAuiNotebookPageChanged(wxAuiNotebookEvent& event)
{
	//event.Skip(false);

	printf("page changed\n");

	uint id = (uint)event.GetSelection();
	m_mapNotebook->SetSelection( id );
	Map* map = Editor->SetActiveMap( m_mapNotebook->GetPageText( id ).c_str() );
	//m_mapNotebook->Get

	//event.Skip();
}


void MainEditorFrame::OnMapAuiNotebookPageClose(wxAuiNotebookEvent& event)
{
	printf("page closed\n");
	//event.Skip();
	uint id = (uint)event.GetSelection();
	m_mapNotebook->SetSelection( id );

	//wxAuiNotebook* ctrl = (wxAuiNotebook*)evt.GetEventObject();
	//if (ctrl->GetPage(evt.GetSelection())->IsKindOf(CLASSINFO(wxHtmlWindow)))

}


void MainEditorFrame::OnTilesetAuiNotebookPageChanged(wxAuiNotebookEvent& event)
{
	printf("page changed\n");
	event.Skip();
}

void MainEditorFrame::OnTilesetAuiNotebookPageClose(wxAuiNotebookEvent& event)
{
	printf("page closed\n");
	event.Skip();
}




void MainEditorFrame::OnViewAuiWindowPane(wxCommandEvent& event, wxWindow* window)
{
	wxAuiPaneInfo &pane = m_auiManager.GetPane(window);
	if(pane.IsOk())
	{
		pane.Show(!pane.IsShown());
		m_auiManager.Update();
	}
}


void MainEditorFrame::CreateNewMap( const wxString& name, uint w, uint h )
{
	Map *map = Editor->CreateMap( name, 1, w, h );
	if(!map)
	{}

	GLMapCanvasWindow *mapWindow = new GLMapCanvasWindow(this, m_glContext);
	if( !m_mapNotebook->AddPage( mapWindow, name.c_str(), true, wxNullBitmap) )
	{
		throw -8;
	}

	mapWindow->SetScrollbarUnits( Editor->GetActiveMap()->Width(), Editor->GetActiveMap()->Height() );
}


void MainEditorFrame::ResizeMap( const wxString& name, uint w, uint h )
{
	Editor->ResizeMap(w, h);
	m_mapWindow->SetScrollbarUnits( Editor->GetActiveMap()->Width(), Editor->GetActiveMap()->Height() );
}



bool MainEditorFrame::GetMapPageID( const wxString& mapName, uint& pageID )
{
	wxString name = mapName.c_str();
	for( uint i(0); i < m_mapNotebook->GetPageCount(); ++i )
	{
		if( m_mapNotebook->GetPageText(i) = name )
		{
			pageID = i;
			return true;
		}
	}

	return false;
}



GLMapCanvasWindow* MainEditorFrame::GetSelectedMapWindow()
{
	int selection = m_mapNotebook->GetSelection();
	if( selection == wxNOT_FOUND )
		return 0;

	return (GLMapCanvasWindow*)m_mapNotebook->GetPage( (size_t)selection );
}


Map* MainEditorFrame::GetSelectedMap()
{
	GLMapCanvasWindow* activeMapWindow = GetSelectedMapWindow();
	if(!activeMapWindow)
		return 0;

	return ((GLMapCanvas*)(activeMapWindow->GetUserCanvas()))->GetMap();
}


MapLayer* MainEditorFrame::GetSelectedMapLayer()
{
	Map* map = GetSelectedMap();
	if(!map)
		return 0;

	return map->GetActiveLayer();
}


MinimapWindow* MainEditorFrame::GetMinimap()
{
	return m_minimapWindow;
}


void MainEditorFrame::RefreshMapWindow()
{
	GLMapCanvasWindow* activeMapWindow = GetSelectedMapWindow();
	if(activeMapWindow)
	{
		activeMapWindow->Refresh();
	}
}


