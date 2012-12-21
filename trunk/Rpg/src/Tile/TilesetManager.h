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

#include <fc/vector.h>
#include <fc/string.h>

#include "../Common.h"
#include "Tileset.h"


class TilesetManager
{
public:
	typedef fc::vector<Tileset*>	vec_type;

	~TilesetManager();

	void DeleteTilesets();
	bool DeleteTileset( Tileset* tileset );
	Tileset* CreateTileset( const fc::string& name );

	Tileset* operator [] ( size_t index ) const { return GetTileset(index); }
	Tileset* operator [] ( const fc::string& name ) const { return GetTileset(name); }
	Tileset* GetTileset( size_t index ) const;
	Tileset* GetTileset( const fc::string& name ) const;

	void SetDirectory( const fc::string& directory );
	const fc::string& GetDirectory() const { return m_directory; };

	NO_INLINE bool LoadTilesetXml( const fc::string& filename );
	NO_INLINE bool SaveTilesetXml( Tileset* tileset );
	NO_INLINE bool SaveAllTilesetsXml();

protected:
	fc::string	m_directory;
	vec_type	m_tilesets;

};



