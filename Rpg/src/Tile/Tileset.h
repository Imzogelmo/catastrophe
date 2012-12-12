
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

	void Dispose();
	void Update();
	void ReconfigureAnimatedTileList();
	void ResetAnimations();
	void ValidateTiles();
	void Resize( size_t w, size_t h );

	void SetName( const fc::string& name ) { m_name = name; }
	void SetTexture( Texture* texture ) { m_texture = texture; } //uhh...fixme

	size_t Size() const { return m_tiles.size(); }
	size_t Width() const { return m_tiles.x(); }
	size_t Height() const { return m_tiles.y(); }

	Texture* GetTexture() const { return m_texture; }
	const fc::string& GetName() const { return m_name; }
	const fc::string& GetFileName() const { return m_filename; }

	Tile* GetTile( size_t index );
	Tile* GetTile( size_t x, size_t y );

private:
	fc::string		m_name;
	fc::string		m_filename;
	anim_vec_type	m_ptr_animated_tiles;
	array_type		m_tiles;
	Texture*		m_texture;

};


