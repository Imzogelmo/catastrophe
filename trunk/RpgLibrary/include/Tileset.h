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

#include "RpgCommon.h"
#include "Tile.h"


class RPG_API Tileset
{
public:
	typedef fc::dynamic_array2d<Tile>	array_type;
	typedef fc::vector<Tile*>			anim_vec_type;

	Tileset();
	~Tileset();

	void Clear();
	void Update();
	void Resize( u32 w, u32 h );

	void SetName( const String& name ) { m_name = name; }
	void SetFileName( const String& filename ) { m_filename = filename; }
	void SetTexture( Texture* texture );
	void SetTileSize( u32 tileSize );

	bool Empty() const { return m_tiles.empty(); }
	u32 Size() const { return m_tiles.size(); }
	u32 Width() const { return m_tiles.x(); }
	u32 Height() const { return m_tiles.y(); }

	const String& GetName() const { return m_name; }
	const String& GetFileName() const { return m_filename; }
	Texture* GetTexture() const { return m_texture; }
	u32 GetTextureId() const;
	u32 GetTileSize() const { return m_tileSize; }

	Tile* GetTile( u32 index ) const;
	Tile* GetTile( u32 x, u32 y ) const;

	// fast index operators with no error checking.
	Tile& operator []( u32 index ) { return m_tiles[index]; }
	const Tile& operator []( u32 index ) const { return m_tiles[index]; }

	// these are usually only called internally.
	void ReconfigureAnimatedTileList();
	void ResetAnimations();
	void ValidateTiles();

	NO_INLINE bool Save( const String& directory );
	NO_INLINE bool Load( const String& directory, const String& filename );

protected:
	Texture*		m_texture;
	String			m_name;
	String			m_filename;
	u32				m_tileSize;
	array_type		m_tiles;
	anim_vec_type	m_ptr_animated_tiles;

};



