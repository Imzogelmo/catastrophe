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
#include <Engine/Math/Color.h>
#include <Engine/Graphics/BlendMode.h>
#include <Engine/Util/Indexable.h>

#include "Tile.h"


class RPG_API MapLayer : public Indexable<>
{
public:
	typedef fc::dynamic_array2d<Tile*> array_type;

	MapLayer( Map* parent = 0 );

	void SetVisible( bool enable = true ) { m_visible = enable; }
	void SetColor( const Color& color ) { m_color = color; }
	void SetMap( Map* map ) { m_parent = map; }
	
	void Resize( size_t w, size_t h );
	void Clear();

	size_t Size() const { return m_tiles.size(); }
	size_t Width() const { return m_tiles.x(); }
	size_t Height() const { return m_tiles.y(); }

	bool IsVisible() const { return m_visible; }
	Color GetColor() const { return m_color; }
	BlendMode GetBlendMode() const { return m_blendmode; }
	Tile* GetTile( size_t x, size_t y ) const { return m_tiles.at(y, x); }
	Map* GetMap() const { return m_parent; }

	array_type& GetTileArray() { return m_tiles; }
	const array_type& GetTileArray() const { return m_tiles; }

	void Update();
	void Render();

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

protected:
	Map*		m_parent;
	array_type	m_tiles;
	BlendMode	m_blendmode;
	Color		m_color;
	//Point		m_offset;
	bool		m_visible;
	//bool		m_parallax;

};

