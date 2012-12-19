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
	//m_tiles.assign(0, m_tiles.size());
	m_tiles.assign(0);
}


void MapLayer::Resize( size_t w, size_t h )
{
	size_t old_x = m_tiles.x();
	size_t old_y = m_tiles.y();
	m_tiles.resize(h, w);

	//make all new pointers null.
	if( old_x < m_tiles.x() )
	{
		for( size_t y(0); y < m_tiles.y(); ++y )
		{
			size_t i = m_tiles.offset(y, old_x);
			for( size_t x(old_x); x < m_tiles.x(); ++x )
			{
				m_tiles[i++] = 0;
			}
		}
	}
	if( old_y < m_tiles.y() )
	{
		size_t x_dist = fc::min(old_x, m_tiles.x());
		for( size_t y(old_y); y < m_tiles.y(); ++y )
		{
			size_t i = m_tiles.offset(y, 0);
			for( size_t x(0); x < x_dist; ++x )
			{
				m_tiles[i++] = 0;
			}
		}
	}
}

