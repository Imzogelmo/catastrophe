

#include "MapLayer.h"


MapLayer::MapLayer( Map* parent ) :
	m_parent(parent),
	m_tiles(),
	m_blendmode(BlendMode::Alpha),
	m_visible(true)
{
}


void MapLayer::Clear()
{
	m_tiles.assign(0, m_tiles.size());
}


void MapLayer::Resize( size_t w, size_t h )
{
	m_tiles.resize(h, w);
}

