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

#include <fc/dynamic_array2d.h>
#include <Catastrophe/Math/Color.h>
#include <Catastrophe/Graphics/BlendMode.h>

#include "Tile.h"


/*
 * @LayerTile
 * represents an instance of a tile as it 
 * exists inside a layer of a map.
 */
struct LayerTile
{
	enum Flags
	{
		FlipHorizontal = 1,
		FlipVertical = 2
	};

	Tile* tile;
	int flags;

	LayerTile() : tile(0), flags(0)
	{}

	inline operator bool() const { return tile != 0; }
	inline bool Empty() const { return tile == 0; }
	inline void Clear()
	{
		tile = 0;
		flags = 0;
	}

	inline int GetFlags() const { return flags; }
	inline int GetFlip() const { return flags & (FlipVertical | FlipHorizontal); }

};


//todo: tile flip/flags
class RPG_API MapLayer
{
public:
	typedef fc::dynamic_array2d<LayerTile> array_type;

	MapLayer();

	void SetName( const fc::string& name ) { m_name = name; }
	void SetVisible( bool enable = true ) { m_visible = enable; }
	void SetColor( const Color& color ) { m_color = color; }
	void SetTileset( Tileset* tileset );
	
	void Resize( size_t w, size_t h );
	void Clear();

	size_t Size() const { return m_tiles.size(); }
	size_t Width() const { return m_tiles.x(); }
	size_t Height() const { return m_tiles.y(); }

	bool IsVisible() const { return m_visible; }

	Tileset* GetTileset() const { return m_tileset; }
	const fc::string& GetName() const { return m_name; }
	const Color& GetColor() const { return m_color; }
	const BlendMode& GetBlendMode() const { return m_blendmode; }
	
	LayerTile& GetLayerTile( size_t index ) { return m_tiles[index]; }
	LayerTile& GetLayerTile( size_t x, size_t y ) { return m_tiles.at(y, x); }
	const LayerTile& GetLayerTile( size_t index ) const { return m_tiles[index]; }
	const LayerTile& GetLayerTile( size_t x, size_t y ) const { return m_tiles.at(y, x); }

	Tile* GetTile( size_t index ) const { return m_tiles[index].tile; }
	Tile* GetTile( size_t x, size_t y ) const { return m_tiles.at(y, x).tile; }

	//remove me.
	array_type& GetTileArray() { return m_tiles; }
	const array_type& GetTileArray() const { return m_tiles; }

	void Update();
	void Render( SpriteBatch* spriteBatch, const Rect& viewRect, bool wrap );

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

protected:
	fc::string		m_name;
	Map*			m_parent;
	Tileset*		m_tileset;
	array_type		m_tiles;
	BlendMode		m_blendmode;
	Color			m_color;
	//Point			m_offset;
	bool			m_visible;
	//bool		m_parallax;

};

