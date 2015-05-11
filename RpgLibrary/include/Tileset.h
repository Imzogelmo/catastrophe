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

#include "Catastrophe/Core/Containers/Array2D.h"
#include "Catastrophe/Core/Containers/Vector.h"

#include "RpgCommon.h"
#include "Tile.h"


class RPG_API Tileset
{
public:
	typedef Array2D<Tile>	ArrayType;

	Tileset();
	~Tileset();

	/// Clears all the tiles in this tileset to their default state.
	void Clear();

	/// Update this tilesets state and animations.
	void Update();

	/// Resize this tileset. Width and Height must both be > 0.
	void Resize( u32 w, u32 h );

	/// Sets the name of this tileset.
	void SetName( const String& name ) { m_name = name; }

	/// Gets the name of this tileset.
	const String& GetName() const { return m_name; }

	/// Sets the filename of this tileset.
	void SetFileName( const String& filename ) { m_filename = filename; }

	/// Gets the filename of this tileset.
	const String& GetFileName() const { return m_filename; }

	/// Sets the texture that will be used by all tiles in this tileset.
	void SetTexture( Texture* texture );

	/// Gets the texture that is used by all the tiles in this tileset.
	Texture* GetTexture() const { return m_texture; }

	/// Sets the size of the tiles w, h components, in pixels. Should be PO2.
	void SetTileSize( u32 tileSize );

	/// Gets the size of the tiles w, h components.
	u32 GetTileSize() const { return m_tileSize; }

	bool Empty() const { return m_tiles.Empty(); }
	u32 Size() const { return m_tiles.Size(); }
	u32 Width() const { return m_tiles.Width(); }
	u32 Height() const { return m_tiles.Height(); }

	/// The internal GPU texture id of the assigned texture.
	u32 GetTextureId() const;

	/// Gets the tile at the specified index.
	Tile* GetTile( u32 index ) const;

	/// Gets the tile at the specified x, y coordinate.
	Tile* GetTile( u32 x, u32 y ) const;

	// Fast index operators with no error checking.
	Tile& operator []( u32 index ) { return m_tiles[index]; }
	const Tile& operator []( u32 index ) const { return m_tiles[index]; }

	// These are usually only called internally.
	void ReconfigureAnimatedTileList();
	void ResetAnimations();
	void ValidateTiles();

	NOINLINE bool Save( const String& directory );
	NOINLINE bool Load( const String& directory, const String& filename );

protected:
	Texture*		m_texture;
	String			m_name;
	String			m_filename;
	u32				m_tileSize;
	ArrayType		m_tiles;
	Vector<Tile*>	m_pAnimatedTiles;

};



