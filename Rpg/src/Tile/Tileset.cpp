
#include "Tileset.h"



Tileset::Tileset() : m_tiles(), m_ptr_animated_tiles()
{}


Tileset::~Tileset()
{
	Dispose();
}


void Tileset::Dispose()
{
	m_tiles.resize(0, 0);
	m_ptr_animated_tiles.clear();
}


void Tileset::Resize( size_t w, size_t h )
{
	m_tiles.resize(h, w);
	ValidateTiles();
	ReconfigureAnimatedTileList();
}


void Tileset::Update()
{
	// we only need to update the animated tiles, not the whole kit 'n kaboodle.
	for( anim_vec_type::iterator it = m_ptr_animated_tiles.begin(); it != m_ptr_animated_tiles.end(); ++it )
	{
		(*it)->Update();
	}
}


void Tileset::ReconfigureAnimatedTileList()
{
	m_ptr_animated_tiles.clear();
	for( array_type::iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
	{
		if( it->NumFrames() > 1 )
			m_ptr_animated_tiles.push_back(it);
	}
}


void Tileset::ResetAnimations()
{
	for( anim_vec_type::iterator it = m_ptr_animated_tiles.begin(); it != m_ptr_animated_tiles.end(); ++it )
	{
		(*it)->SetCurrentFrame(0);
	}
}


void Tileset::ValidateTiles()
{
	//make sure all tile data is correct.
	//since we do no runtime checks on these later 
	//it's possible to get undefined behavior otherwise.
	for( size_t i(0); i < m_tiles.size(); ++i )
	{
		Tile &tile = m_tiles[i];
		tile.SetTileset(this);
		tile.SetIndex(i);
	}
}


Tile* Tileset::GetTile( size_t index )
{
	if( index < m_tiles.size() )
		return &m_tiles[index];

	return 0;
}


Tile* Tileset::GetTile( size_t x, size_t y )
{
	if( x < m_tiles.x() && y < m_tiles.y() )
		return &m_tiles(y, x);

	return 0;
}



