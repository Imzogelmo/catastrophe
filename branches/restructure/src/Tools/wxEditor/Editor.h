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

#define EDITOR


#include <fc/vector.h>
#include <fc/vector_map.h>

#include "Forward.h"
#include "TextureManager.h"



//class EditorInternal;

class AppEditor
{
public:
	AppEditor( MainEditorFrame* parent );
	~AppEditor();

	typedef fc::vector<Map*>			map_vec_type;
	typedef fc::vector<Tileset*>		tileset_vec_type;

	//Blarg.. todo: Load/save project file containing (preferably in order):
	//-bitmaps
	//-tilesets
	//-sprites(objects)
	//-maps

	void		AddMap( Map* map );
	Map*		CreateMap( const wxString& mapName, uint numLayers = 1, uint mapWidth = 80, uint mapHeight = 80 );

	void		AddTileset( Tileset* tileset );
	Tileset*	CreateTileset( const wxString& tilesetName, Image* image );

	void ClearMaps();
	void ClearTilesets();

	TextureManager*		GetTextureManager();
	tileset_vec_type*	GetTilesets();
	map_vec_type*		GetMaps();

	Map*			GetMap( const wxString& mapName );
	Tileset*		GetTileset( const wxString& tilesetName );

	bool MapExists( const wxString& mapName );
	bool TilesetExists( const wxString& tilesetName );

	uint GetNumMaps() const;
	uint GetNumTilesets() const;

	void ResizeMap( uint w, uint h );

	Map*		GetActiveMap();//m_mainEditorFrame->GetSelectedMap(); }
	MapLayer*	GetActiveMapLayer();

	//FIXME.. should not resort to ptr refs
	TileSelection	&GetTileSelection();
	Tileset			*&GetActiveTileset();
	//Map				*&GetActiveMap() { return m_currentMap; }
	//MapLayer		*GetActiveMapLayer() { return m_currentMap->GetLayer(m_selectedMapLayer); }


	Map*			SetActiveMap( const wxString& mapName );

	MainEditorFrame*		GetMainEditorFrame();
	MainEditorFrame*		GetMainFrame();
	MinimapWindow*			GetMinimap();

	void Initialize();

protected:
	friend class MainEditorFrame;

	//EditorInternal*		m_internal;

	Project*			m_project;
	MainEditorFrame*	m_mainEditorFrame;

	//uint				m_selectedMapLayer;
	TileSelection*		m_selectedTiles;

	TextureManager*		m_textureManager;
	map_vec_type		m_maps;
	tileset_vec_type	m_tilesets;

	Tileset*			m_activeTileset;
	Map*				m_currentMap;

};




extern AppEditor *Editor;

