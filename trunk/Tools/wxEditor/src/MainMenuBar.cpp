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

#include "MainMenuBar.h"
#include "MainEditorFrame.h"
#include "ImageWindow.h"
#include "GLTileCanvas.h"
#include "GLMapCanvas.h"
#include "Editor.h"
#include "MediaPlayerWindow.h"

#include "Dialogs.h"
#include "FileIO.h"

#include "MapGenerator.h"


BEGIN_EVENT_TABLE(MainEditorFrame, wxFrame)
	EVT_CLOSE		(MainEditorFrame::OnExit)
	EVT_IDLE		(MainEditorFrame::OnIdle)
	EVT_SIZE		(MainEditorFrame::OnSize)


	EVT_MENU		(MainMenu::ID_FILE_NEW_PROJECT, MainEditorFrame::OnProjectNew)
	EVT_MENU		(MainMenu::ID_FILE_OPEN_PROJECT, MainEditorFrame::OnProjectOpen)
	EVT_MENU		(MainMenu::ID_FILE_SAVE_PROJECT, MainEditorFrame::OnProjectSave)
	//EVT_MENU		(MainMenu::ID_FILE_OPEN, MainEditorFrame::OnLoadImage)
	EVT_MENU		(MainMenu::ID_FILE_QUIT, MainEditorFrame::OnQuit)

	EVT_MENU		(MainMenu::ID_VIEW_FILES, MainEditorFrame::OnViewFileTree)
	EVT_MENU		(MainMenu::ID_VIEW_MAPS, MainEditorFrame::OnViewMaps)
	EVT_MENU		(MainMenu::ID_VIEW_TILESETS, MainEditorFrame::OnViewTilesets)
	EVT_MENU		(MainMenu::ID_VIEW_LAYERS, MainEditorFrame::OnViewMapProperties)
	EVT_MENU		(MainMenu::ID_VIEW_SPRITES, MainEditorFrame::OnViewSprites)
	EVT_MENU		(MainMenu::ID_VIEW_MINIMAP, MainEditorFrame::OnViewMinimap)

	EVT_MENU		(MainMenu::ID_MAP_NEW, MainEditorFrame::OnMapNew)
	EVT_MENU		(MainMenu::ID_MAP_RESIZE, MainEditorFrame::OnMapResize)
	EVT_MENU		(MainMenu::ID_MAP_SAVE, MainEditorFrame::OnMapSave)
	EVT_MENU		(MainMenu::ID_MAP_GENERATE_FROM_IMAGE, MainEditorFrame::OnMapGenerateFromImage)

	EVT_MENU		(MainMenu::ID_AUDIO_LOAD, MainEditorFrame::OnAudioLoad)

END_EVENT_TABLE()



void MainEditorFrame::InitializeMainMenu()
{
	using namespace MainMenu;


	//**************************************************
	// File
	//**************************************************
	m_fileMenu = new wxMenu;

	m_fileMenu->Append(ID_FILE_NEW_PROJECT, _T("&New...\tCtrl-Shift-N"), _T("Create a new project"));
	m_fileMenu->Append(ID_FILE_OPEN_PROJECT, _T("&Open...\tCtrl-Shift-O"), _T("Open a project"));
	m_fileMenu->Append(ID_FILE_SAVE_PROJECT, _T("&Save Project\tCtrl-Shift-S"), _T("Save project"));


//	m_fileMenu->Append(ID_FILE_NEW_PROJECT, _T("&New...\tCtrl-Shift-N"), _T("Create a new project"));
	//m_fileMenu->Append(ID_FILE_OPEN, _T("&Open...\tCtrl-Shift-O"), _T("Open a project"));
//	m_fileMenu->Append(ID_FILE_SAVE, _T("&Save Project\tCtrl-S"), _T("Save entire project"));
//	m_fileMenu->Append(ID_FILE_SAVE_AS, _T("Save Project &As...\tCtrl-Shift-S"), _T("Save entire project as"));
	m_fileMenu->AppendSeparator();
	m_fileMenu->Append(ID_FILE_QUIT, _T("&Quit\tAlt-F4"), _T("Quit"));


	//**************************************************
	// Edit
	//**************************************************
/*
	m_editMenu = new wxMenu;
	m_editMenu->Append(ID_EDIT_UNDO, _T("&Undo\tCtrl-Z"), _T("Undo last action"));
	m_editMenu->Append(ID_EDIT_REDO, _T("&Redo\tCtrl-Shift-Z"), _T("Redo undone action"));
	m_editMenu->AppendSeparator();
	m_editMenu->Append(ID_EDIT_CUT, _T("Cu&t\tCtrl-X"), _T("Cut"));
	m_editMenu->Append(ID_EDIT_COPY, _T("&Copy\tCtrl-C"), _T("Copy"));
	m_editMenu->Append(ID_EDIT_PASTE, _T("&Paste\tCtrl-V"), _T("Paste"));
*/


	//**************************************************
	// View
	//**************************************************
	m_viewMenu = new wxMenu;
	m_viewMenu->Append(ID_VIEW_MAPS, _T("&Maps"), _T("Toggle Display Maps Pane"), wxITEM_CHECK)->Check(true);
	m_viewMenu->Append(ID_VIEW_TILESETS, _T("&Tilesets"), _T("Toggle Display Tilesets Pane"), wxITEM_CHECK)->Check(true);
	m_viewMenu->Append(ID_VIEW_LAYERS, _T("&Layers"), _T("Toggle Display Layers Pane"), wxITEM_CHECK)->Check(true);
	m_viewMenu->Append(ID_VIEW_SPRITES, _T("&Sprites"), _T("Toggle Display Sprites Pane"), wxITEM_CHECK)->Check(true);
	m_viewMenu->Append(ID_VIEW_MINIMAP, _T("&Minimap"), _T("Toggle Minimap Window"), wxITEM_CHECK)->Check(true);



	//**************************************************
	// Maps
	//**************************************************
	m_mapsMenu = new wxMenu;
	m_mapsMenu->Append(ID_MAP_NEW, _T("&New"), _T("Create a new map"));
	m_mapsMenu->Append(ID_MAP_RESIZE, _T("&Resize"), _T("Resize map"));
	m_mapsMenu->AppendSeparator();
	m_mapsMenu->Append(ID_MAP_SAVE, _T("&Save"), _T("Save map as xml"));
	//m_mapsMenu->Append(ID_DELETE_MAP, _T("&Delete"), _T("Delete current map"));
	m_mapsMenu->AppendSeparator();
	m_mapsMenu->Append(ID_MAP_GENERATE_FROM_IMAGE, _T("&Generate Map"), _T("not done"));


	//**************************************************
	// Audio
	//**************************************************
	m_audioMenu = new wxMenu;
	m_audioMenu->Append(ID_AUDIO_LOAD, _T("&Load"), _T("Load Audio"));


 	m_menuBar = new wxMenuBar;
	m_menuBar->Append(m_fileMenu, _T("&File"));
	//m_menuBar->Append(m_editMenu, _T("&Edit"));
	m_menuBar->Append(m_viewMenu, _T("&View"));
	m_menuBar->Append(m_mapsMenu, _T("&Maps"));
	m_menuBar->Append(m_audioMenu, _T("&Audio"));

	SetMenuBar(m_menuBar);
}


void MainEditorFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close();
}


void MainEditorFrame::OnProjectNew(wxCommandEvent& WXUNUSED(event))
{
}


void MainEditorFrame::OnProjectOpen(wxCommandEvent& WXUNUSED(event))
{
}


void MainEditorFrame::OnProjectSave(wxCommandEvent& WXUNUSED(event))
{
}


void MainEditorFrame::OnLoadImage(wxCommandEvent& WXUNUSED(event))
{
	wxImage image;
	wxString filename;

	if( !Dialog::LoadImageDialog(&image, filename) )
		return;

	wxBitmap *bitmap = new wxBitmap(image);

	ImageWindowFrame *imageWindow = new ImageWindowFrame(this, 
		bitmap, 
		filename, 
		wxDefaultPosition,
		wxSize( image.GetWidth(), image.GetHeight() )
	);

	(void*)imageWindow;
}


void MainEditorFrame::OnMapSave(wxCommandEvent& event)
{
	Map *map = Editor->GetActiveMap();

	//int success = FileIO::SaveMapXml( *map );
	int success = FileIO::SaveMapBin( *map );
	if(success != 0)
	{
		printf("Map Save failed.");
	}
}


void MainEditorFrame::OnMapLoad(wxCommandEvent& event)
{
	Map *map = 0;

	try
	{
		map = FileIO::LoadMapXml("");
	}
	catch(...) {
	}

	if(map)
	{
		Editor->AddMap(map);
	}
}


void MainEditorFrame::OnTilesetSave(wxCommandEvent& event)
{
	//event.Skip(false);
	Tileset *tileset = Editor->GetActiveTileset();

	int success = FileIO::SaveTilesetXml( *tileset );
	if(success != 0)
	{
		printf("Tileset Save failed.");
	}
}


void MainEditorFrame::OnTilesetLoad(wxCommandEvent& event)
{
	Tileset *tileset = 0;

	try
	{
		tileset = FileIO::LoadTilesetXml("");
	}
	catch(...) {
	}

	if(tileset)
	{
		Editor->AddTileset(tileset);
	}
}


void MainEditorFrame::OnMapNew(wxCommandEvent& event)
{
	NewMapDialog newMapDialog(this);
	newMapDialog.ShowModal();

	//TODO: put this in a better place.
	m_mapWindow->SetScrollbarUnits( Editor->GetActiveMap()->Width(), Editor->GetActiveMap()->Height() );
}


void MainEditorFrame::OnMapResize(wxCommandEvent& event)
{
	ResizeMapDialog resizeMapDialog(this);
	resizeMapDialog.ShowModal();

	m_mapWindow->SetScrollbarUnits( Editor->GetActiveMap()->Width(), Editor->GetActiveMap()->Height() );
}


void MainEditorFrame::OnMapGenerateFromImage(wxCommandEvent& event)
{
	Map *map = MapGenerator::CreateFromImage( Editor->GetActiveTileset() );
	if(!map)
		return;

	Editor->AddMap(map);
	m_mapWindow->SetScrollbarUnits( Editor->GetActiveMap()->Width(), Editor->GetActiveMap()->Height() );
}


void MainEditorFrame::OnAudioLoad(wxCommandEvent& event)
{
	wxString filename;
	if( Dialog::LoadAudioDialog(filename, this) )
	{
		m_mediaPlayer->Load(filename);
	}
}







