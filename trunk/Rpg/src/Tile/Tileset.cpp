
#include "Tileset.h"



Tileset::Tileset() : m_tiles(), m_ptr_animated_tiles()
{}


Tileset::~Tileset()
{
	Destroy();
}


void Tileset::Destroy()
{
	m_tiles.clear();
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
	for( vec_ptr_type::iterator it = m_ptr_animated_tiles.begin(); it != m_ptr_animated_tiles.end(); ++it )
	{
		(*it)->Update();
	}
}


void Tileset::ReconfigureAnimatedTileList()
{
	m_ptr_animated_tiles.clear();
	for( vec_ptr_type::iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
	{
		if( it->NumFrames() > 1 )
			m_ptr_animated_tiles.push_back(it);
	}
}


void Tileset::ResetAnimations()
{
	for( vec_ptr_type::iterator it = m_ptr_animated_tiles.begin(); it != m_ptr_animated_tiles.end(); ++it )
	{
		(*it)->SetCurrentFrame(0);
	}
}


void Tileset::ValidateTiles()
{
	for( size_t i(0); i < m_tiles.size(); ++i )
	{
		Tile &tile = m_tiles[i];
		tile.SetTileset(this);
		tile.SetIndex((int)i);
	}
}


