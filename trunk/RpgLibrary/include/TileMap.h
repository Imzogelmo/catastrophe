// catastrophe rpg engine
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#pragma once

#include "TileMapLayer.h"

#include <fc/static_vector.h>


struct TileMapInfo
{
	u16 music;


};


class RPG_API TileMap
{
public:
	enum : u32
	{
		MaxLayers = 16
	};

	typedef fc::static_vector<TileMapLayer*, MaxLayers>	vec_type;

	TileMap();
	TileMap( const String& mapName, u32 numLayers, u32 mapWidth, u32 mapHeight );
	~TileMap();

	void DeleteLayers();
	void Clear();

	u32 Width() const { return m_width; }
	u32 Height() const { return m_height; }
	u32 NumLayers() const { return m_layers.size(); }

	bool AddLayer( TileMapLayer* layer = 0 );
	void RemoveLayer( u32 index = u32(-1) );
	void Resize( u32 w, u32 h, u32 numLayers = u32(-1) );
	void SwapLayer( u32 first, u32 second );

	TileMapLayer* GetLayer( u32 index ) const;

	void SetName( const String& name ) { m_name = name; }
	void SetFileName( const String& filename ) { m_name = filename; }

	const String& GetName() const { return m_name; }
	const String& GetFileName() const { return m_filename; }


	void Render( SpriteBatch* spriteBatch, const Rect& viewRect, bool mapWraparound = false );


	NO_INLINE bool Save( const String& path = "" );
	NO_INLINE bool Load( const String& path, const String& filename );

protected:
	String		m_name;
	String		m_filename;
	vec_type	m_layers;
	u32			m_width;
	u32			m_height;
	//u32			m_tileSize;

};

