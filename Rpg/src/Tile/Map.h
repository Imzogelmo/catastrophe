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

#include "MapLayer.h"

#include <fc/vector.h>



class Map
{
public:
	enum : size_t
	{
		MaxLayers = 16//,
		//MaxDimension = MapLayer::MaxDimension
	};

	typedef fc::vector<MapLayer*>	vec_type;

	//Map();
	Map( const fc::string& mapName, size_t numLayers, size_t mapWidth, size_t mapHeight );
	~Map();

	void DeleteLayers();
	void Clear();

	size_t Size() const { return m_width * m_height; }
	size_t Width() const { return m_width; }
	size_t Height() const { return m_height; }
	size_t NumLayers() const { return m_layers.size(); }

	bool AddLayer( MapLayer* layer = 0 );
	//void InsertLayer( MapLayer* layer, size_t index );
	void RemoveLayer( MapLayer* layer );
	void RemoveLayer( size_t index = size_t(-1) );
	void Resize( size_t w, size_t h, size_t numLayers = size_t(-1) );
	void SwapLayer( size_t first, size_t second );

	MapLayer* GetLayer( size_t layer ) const;

	fc::string&	GetName() { return m_name; }
	const fc::string& GetName() const { return m_name; }

	//void Render( SpriteBatch* spriteBatch, Rect viewRect, size_t tileSize );

public:
	fc::string		m_name;
	vec_type		m_layers;
	size_t			m_width;
	size_t			m_height;

};

