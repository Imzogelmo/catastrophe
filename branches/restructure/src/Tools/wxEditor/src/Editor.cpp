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
#include "Forward.h"

#include "Editor.h"
#include "MainEditorFrame.h"

#include <fc/algorithm.h>
#include <fc/math.h>
#include <wx/wx.h>

#include "TextureManager.h"
//#include "Animation.h"
#include "Tile.h"
#include "Tileset.h"
#include "MapLayer.h"
#include "CollisionLayer.h"
#include "Map.h"
#include "TileSelection.h"
#include "Project.h"


AppEditor *Editor = 0;

/*
class EditorInternal
{
public:

	Project*			GetProject() { return m_project; }
	MainEditorFrame*	GetMainEditorFrame() { return m_mainEditorFrame; }
	TileSelection*		GetTileSelection() { return &m_selectedTiles; }
	Tileset*			GetActiveTileset() { return m_activeTileset; }
	Map*				GetActiveMap() { return m_currentMap; }

	TextureManager		m_textureManager;
	map_vec_type		m_maps;
	tileset_vec_type	m_tilesets;

	Project*			m_project;
	MainEditorFrame*	m_mainEditorFrame;

	//uint				m_selectedMapLayer;
	TileSelection		m_selectedTiles; //should belong to tileset??

	Tileset*			m_activeTileset;
	Map*				m_currentMap;

};
*/

AppEditor::AppEditor( MainEditorFrame* parent ) :
	m_mainEditorFrame(parent)
{
	m_project = 0;
	//m_selectedMapLayer = 0;

	Initialize();
}


AppEditor::~AppEditor()
{
	if(m_project)
		delete m_project;

	ClearMaps();
	ClearTilesets();
}


void AppEditor::Initialize()
{
	m_currentMap = CreateMap( "map what" );
}



TextureManager*		AppEditor::GetTextureManager() { return &m_textureManager; }
tileset_vec_type*	AppEditor::GetTilesets() { return &m_tilesets; }
map_vec_type*		AppEditor::GetMaps() { return &m_maps; }

bool AppEditor::MapExists( const wxString& mapName ) { return GetMap(mapName) != 0; }
bool AppEditor::TilesetExists( const wxString& tilesetName ) { return GetTileset(tilesetName) != 0; }

uint AppEditor::GetNumMaps() const { return m_maps.size(); }
uint AppEditor::GetNumTilesets() const { return m_tilesets.size(); }

Map*		AppEditor::GetActiveMap() { return m_currentMap; }//m_mainEditorFrame->GetSelectedMap(); }
MapLayer*	AppEditor::GetActiveMapLayer() { return m_currentMap->GetActiveLayer(); }
TileSelection&	AppEditor::GetTileSelection() { return *m_selectedTiles; }
Tileset*		&AppEditor::GetActiveTileset() { return m_activeTileset; }
MainEditorFrame*	AppEditor::GetMainEditorFrame() { return m_mainEditorFrame; }
MainEditorFrame*	AppEditor::GetMainFrame() { return m_mainEditorFrame; }
MinimapWindow*		AppEditor::GetMinimap() { return m_mainEditorFrame->GetMinimap(); }


void AppEditor::ResizeMap( uint w, uint h )
{
	GetActiveMap()->Resize(w, h);
}

void AppEditor::AddMap( Map* map )
{
	m_currentMap = map;
	GetMaps()->push_back( map );
}


Map* AppEditor::CreateMap( const wxString& mapName, uint numLayers, uint mapWidth, uint mapHeight )
{
	Map *map = new Map( mapName, mapWidth, mapHeight, numLayers );
	AddMap(map);

	return map;
}


void AppEditor::AddTileset( Tileset* tileset )
{
	m_activeTileset = tileset;
	GetTilesets()->push_back( tileset );
}


Tileset* AppEditor::CreateTileset( const wxString& tilesetName, Image* image )
{
	//TODO: 
	Tileset *tileset = new Tileset();
	AddTileset(tileset);

	return tileset;
}


void AppEditor::ClearMaps()
{
	for( map_iter it = m_maps.begin(); it != m_maps.end(); ++it )
	{
		delete *it;
	}

	m_maps.clear();
}


void AppEditor::ClearTilesets()
{
	for( tileset_iter it = m_tilesets.begin(); it != m_tilesets.end(); ++it )
	{
		delete *it;
	}

	m_tilesets.clear();
}


Map* AppEditor::GetMap( const wxString& mapName )
{
	for( map_iter it = m_maps.begin(); it != m_maps.end(); ++it )
	{
		if( (*it)->GetName() == mapName )
			return *it;
	}

	return 0;
}


Tileset* AppEditor::GetTileset( const wxString& tilesetName )
{
	for( tileset_iter it = m_tilesets.begin(); it != m_tilesets.end(); ++it )
	{
		if( (*it)->GetName() == tilesetName )
			return *it;
	}

	return 0;
}


Map* AppEditor::SetActiveMap( const wxString& mapName )
{
	Map* map = GetMap( mapName );
	if(map)
	{
		m_currentMap = map;

		uint id;
		if( m_mainEditorFrame->GetMapPageID( mapName, id ) )
		{
			m_mainEditorFrame->m_mapNotebook->SetSelection( id );
		}
	}

	return map;
}












