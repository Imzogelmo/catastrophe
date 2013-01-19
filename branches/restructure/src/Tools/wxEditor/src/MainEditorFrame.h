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
#include <wx/splitter.h>
#include <wx/glcanvas.h>
#include <wx/aui/aui.h>

#include "GLTileCanvas.h"
#include "GLMapCanvas.h"


class FileTree;
class Map;
class MapLayer;
class MinimapWindow;
class MediaPlayerWindow;

class MainMenuBar;

class MainEditorFrame : public wxFrame
{
public:
	MainEditorFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	~MainEditorFrame();

	void CreateNewMap( const wxString& name, uint w, uint h );
	void ResizeMap( const wxString& name, uint w, uint h );

	void RefreshMapWindow();

	GLMapCanvasWindow*	GetSelectedMapWindow();
	Map*				GetSelectedMap();
	MapLayer*			GetSelectedMapLayer();
	MinimapWindow*		GetMinimap();

	bool GetMapPageID( const wxString& mapName, uint& pageID );
	
	//GLMapCanvasWindow*	GetMapCanvas() { return m_mapWindow; }
	//GLTileCanvasWindow* GetTilesetCanvas() { return m_tilesetWindow; }

protected:
	void InitializeMainMenu();
	void InitializeToolBars();

	void OnIdle(wxIdleEvent& event);
	void OnExit(wxCloseEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnQuit(wxCommandEvent& event);

/*
	void OnFileNew(wxCommandEvent& event);
	void OnFileOpen(wxCommandEvent& event);
	void OnFileClose(wxCommandEvent& event);
	void OnFileSave(wxCommandEvent& event);
	void OnFileSaveAs(wxCommandEvent& event);

	void OnEditUndo(wxCommandEvent& event);
	void OnEditRedo(wxCommandEvent& event);
	void OnEditCut(wxCommandEvent& event);
	void OnEditCopy(wxCommandEvent& event);
	void OnEditPaste(wxCommandEvent& event);

	void OnHelpAbout(wxCommandEvent& event);
*/

	void OnProjectNew(wxCommandEvent& event);
	void OnProjectOpen(wxCommandEvent& event);
	void OnProjectSave(wxCommandEvent& event);

	void OnMapNew(wxCommandEvent& event);
	void OnMapResize(wxCommandEvent& event);
	void OnMapSave(wxCommandEvent& event);
	void OnMapLoad(wxCommandEvent& event);
	void OnMapGenerateFromImage(wxCommandEvent& event);


	void OnTilesetSave(wxCommandEvent& event);
	void OnTilesetLoad(wxCommandEvent& event);


	void OnAudioLoad(wxCommandEvent& event);


	void OnViewAuiWindowPane(wxCommandEvent& event, wxWindow* window);
	void OnViewMaps(wxCommandEvent& event) { OnViewAuiWindowPane(event, (wxWindow*)m_mapNotebook); }
	void OnViewTilesets(wxCommandEvent& event) { OnViewAuiWindowPane(event, (wxWindow*)m_tilesetNotebook); }
	void OnViewSprites(wxCommandEvent& event) { OnViewAuiWindowPane(event, (wxWindow*)m_spritesNotebook); }
	void OnViewMapProperties(wxCommandEvent& event) { OnViewAuiWindowPane(event, (wxWindow*)m_mapPropertiesNotebook); }
	void OnViewMinimap(wxCommandEvent& event) { OnViewAuiWindowPane(event, (wxWindow*)m_minimapWindow); }
	void OnViewFileTree(wxCommandEvent& event) { OnViewAuiWindowPane(event, (wxWindow*)m_fileTree); }

	void OnLoadImage(wxCommandEvent& event);
	

	//wxAuiNotebook Events
	void OnMapAuiNotebookPageChanged(wxAuiNotebookEvent& event);
	void OnMapAuiNotebookPageClose(wxAuiNotebookEvent& event);

	void OnTilesetAuiNotebookPageChanged(wxAuiNotebookEvent& event);
	void OnTilesetAuiNotebookPageClose(wxAuiNotebookEvent& event);


protected:
	friend class AppEditor;

	//Menus
	wxMenuBar*		m_menuBar;
		wxMenu*			m_fileMenu;
		wxMenu*			m_editMenu;
		wxMenu*			m_viewMenu;
		wxMenu*			m_mapsMenu;
		wxMenu*			m_audioMenu;


	//Toolbars
	wxToolBar*			m_toolBar;
	wxToolBar*			m_paintTools;

	wxGLContext*		m_glContext;
	GLMapCanvasWindow*	m_mapWindow;
	GLTileCanvasWindow* m_tilesetWindow;

	FileTree*			m_fileTree;

	wxAuiManager		m_auiManager;
	wxAuiNotebook*		m_mapNotebook;
	wxAuiNotebook*		m_tilesetNotebook;
	wxAuiNotebook*		m_spritesNotebook;
	wxAuiNotebook*		m_mapPropertiesNotebook;

	MinimapWindow*		m_minimapWindow;
	MediaPlayerWindow*	m_mediaPlayer;


	DECLARE_EVENT_TABLE()
};


