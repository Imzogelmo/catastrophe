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

#include <fc/fixed_vector.h>



class RPG_API Map
{
public:
	enum : size_t
	{
		MaxLayers = 16
	};

	typedef fc::fixed_vector<MapLayer*, MaxLayers>	vec_type;

	Map();
	Map( const fc::string& mapName, size_t numLayers, size_t mapWidth, size_t mapHeight );
	~Map();

	void DeleteLayers();
	void Clear();

	size_t Width() const { return m_width; }
	size_t Height() const { return m_height; }
	size_t NumLayers() const { return m_layers.size(); }

	bool AddLayer( MapLayer* layer = 0 );
	void RemoveLayer( size_t index = size_t(-1) );
	void Resize( size_t w, size_t h, size_t numLayers = size_t(-1) );
	void SwapLayer( size_t first, size_t second );

	MapLayer* GetLayer( size_t index ) const;

	void SetName( const fc::string& name ) { m_name = name; }
	void SetFileName( const fc::string& filename ) { m_name = filename; }
	const fc::string& GetName() const { return m_name; }
	const fc::string& GetFileName() const { return m_filename; }

	NO_INLINE bool SerializeXml( const fc::string& filename );
	NO_INLINE bool DeserializeXml( const fc::string& filename );

public:
	fc::string		m_name;
	fc::string		m_filename;
	vec_type		m_layers;
	size_t			m_width;
	size_t			m_height;

};

