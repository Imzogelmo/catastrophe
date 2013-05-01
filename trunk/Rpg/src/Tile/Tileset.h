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
#include <fc/vector.h>

#include "../Common.h"
#include "Tile.h"


class RPG_API Tileset
{
public:
	typedef fc::dynamic_array2d<Tile>	array_type;
	typedef fc::vector<Tile*>			anim_vec_type;

	Tileset( TilesetManager* parent, const fc::string& name );
	~Tileset();

	void Clear();
	void Update();
	void Resize( size_t w, size_t h );

	void SetName( const fc::string& name ) { m_name = name; }
	void SetId( int id ) { m_id = id; }
	void SetTexture( Texture* texture ) { m_texture = texture; }

	size_t Size() const { return m_tiles.size(); }
	size_t Width() const { return m_tiles.x(); }
	size_t Height() const { return m_tiles.y(); }

	TilesetManager* GetTilesetManager() const { return m_parent; }
	Texture* GetTexture() const { return m_texture; }
	const fc::string& GetName() const { return m_name; }
	int GetId() const { return m_id; }

	Tile* GetTile( size_t index );
	Tile* GetTile( size_t x, size_t y );

	// fast index operators with no error checking.
	Tile& operator []( size_t index ) { return m_tiles[index]; }
	const Tile& operator []( size_t index ) const { return m_tiles[index]; }

	bool CreateFromTexture( Texture* texture );
	void ReconfigureAnimatedTileList();
	void ResetAnimations();
	void ValidateTiles();

	NO_INLINE bool SerializeXml( const fc::string& directory );
	NO_INLINE bool DeserializeXml( const fc::string& directory );

private:
	TilesetManager*	m_parent;
	Texture*		m_texture;
	fc::string		m_name;
	fc::string		m_filename;
	int				m_id;
	array_type		m_tiles;
	anim_vec_type	m_ptr_animated_tiles;

};


