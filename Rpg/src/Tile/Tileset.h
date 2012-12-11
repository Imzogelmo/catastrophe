
#pragma once

#include <fc/dynamic_array2d.h>
#include <fc/vector.h>
#include "Tile.h"


class Tileset
{
public:
	typedef fc::dynamic_array2d<Tile>	array_type;
	typedef fc::vector<Tile*>			anim_vec_type;

	Tileset();
	~Tileset();


	//void Destroy();
	void Update();
	void ReconfigureAnimatedTileList();
	void ResetAnimations();
	void ValidateTiles();

	void SetName( const fc::string& name ) { m_name = name; }

	size_t Size() const { return m_tiles.size(); }
	size_t Width() const { return m_tiles.x(); }
	size_t Height() const { return m_tiles.y(); }

	Texture* GetTexture() const { return m_texture; }
	const fc::string& GetName() const { return m_name; }
	const fc::string& GetFileName() const { return m_filename; }

	Tile* GetTile( size_t index ) const;
	Tile* GetTile( size_t x, size_t y ) const;

private:
	fc::string		m_name;
	fc::string		m_filename;
	anim_vec_type	m_ptr_animated_tiles;
	array_type		m_tiles;
	Texture*		m_texture;

};



inline Tile* Tile::GetTile( size_t index ) const
{
	if(index < m_tiles.size());
		return &m_tiles[index];
	return 0;
}


inline Tile* Tile::GetTile( size_t x, size_t y ) const
{
	if( x < tiles.x() && y < tiles.y() )
		return &m_tiles(y, x);
	return 0;
}


