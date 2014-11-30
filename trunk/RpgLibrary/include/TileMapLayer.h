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

#include <fc/string.h>
#include <fc/dynamic_array2d.h>
#include <Catastrophe/Math/Point.h>
#include <Catastrophe/Math/Color.h>
#include <Catastrophe/Graphics/BlendMode.h>

#include "Tile.h"
#include "TileMapLayerCell.h"



class RPG_API TileMapLayer
{
public:
	typedef fc::dynamic_array2d<TileMapLayerCell> array_type;

	TileMapLayer();

	void SetOffset( const Point& offset ) { m_offset = offset; }
	void SetName( const String& name ) { m_name = name; }
	void SetVisible( bool enable = true ) { m_visible = enable; }
	void SetColor( const Color& color ) { m_color = color; }
	void SetBlendMode( const BlendMode& blendmode ) { m_blendmode = blendmode; }
	void SetTileset( Tileset* tileset );
	
	void Resize( u32 w, u32 h );
	void Clear();

	u32 GetSize() const { return m_tiles.size(); }
	u32 GetWidth() const { return m_tiles.x(); }
	u32 GetHeight() const { return m_tiles.y(); }
	Point GetOffset() const { return m_offset; }
	int GetOffsetX() const { return m_offset.x; }
	int GetOffsetY() const { return m_offset.y; }

	bool IsVisible() const { return m_visible; }
	const String& GetName() const { return m_name; }
	const Color& GetColor() const { return m_color; }
	const BlendMode& GetBlendMode() const { return m_blendmode; }
	Tileset* GetTileset() const { return m_tileset; }
	
	TileMapLayerCell& GetCell( u32 index ) { return m_tiles[index]; }
	TileMapLayerCell& GetCell( u32 x, u32 y ) { return m_tiles.at(y, x); }
	const TileMapLayerCell& GetCell( u32 index ) const { return m_tiles[index]; }
	const TileMapLayerCell& GetCell( u32 x, u32 y ) const { return m_tiles.at(y, x); }

	Tile* GetTile( u32 index ) const { return m_tiles[index].tile; }
	Tile* GetTile( u32 x, u32 y ) const { return m_tiles.at(y, x).tile; }

	//remove me.
	array_type& GetTileArray() { return m_tiles; }
	const array_type& GetTileArray() const { return m_tiles; }

	void Update();
	void Render( SpriteBatch* spriteBatch, const Rect& viewRect, bool wrap = false );

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

protected:
	void InternalDrawNormal( SpriteBatch* spriteBatch, s32 x1, s32 y1, s32 x2, s32 y2 );
	void InternalDrawWrap( SpriteBatch* spriteBatch, s32 x1, s32 y1, s32 x2, s32 y2 );

protected:
	String			m_name;
	TileMap*		m_parent;
	Tileset*		m_tileset;
	array_type		m_tiles;
	BlendMode		m_blendmode;
	Color			m_color;
	Point			m_offset;
	f32				m_parallax;
	u32				m_tileSize;
	bool			m_visible;
	//bool		m_parallax;

};

