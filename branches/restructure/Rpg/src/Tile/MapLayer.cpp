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


#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/IO/XmlReader.h>
#include "MapLayer.h"
#include "Tileset.h"


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


void MapLayer::SerializeXml( XmlWriter* xml )
{
	xml->SetUInt("width", m_tiles.x());
	xml->SetUInt("height", m_tiles.y());
	xml->SetUInt("color", m_color.packed_value);
	xml->SetUInt("blend", m_blendmode.value);

	for( array_type::iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
	{
		xml->BeginNode("Tile");

		int id = -1, tileset_id = -1;
		if(*it)
		{
			id = (*it)->GetIndex();
			tileset_id = (*it)->GetTileset()->GetId();
		}

		xml->SetInt("id", id);
		xml->SetInt("tid", tileset_id);
		xml->EndNode();
	}
}


void MapLayer::DeserializeXml( XmlReader* xml )
{
	m_tiles.resize(0, 0);

	size_t w = xml->GetUInt("width");
	size_t h = xml->GetUInt("height");
	m_color.packed_value = xml->GetUInt("color");
	m_blendmode.value = xml->GetUInt("blend");

	m_tiles.resize(w, h);
	m_tiles.assign((Tile*)0);

	while( xml->NextChild("Tile") )
	{
		int id = xml->GetInt("id", -1);
		int tileset_id = xml->GetInt("tid", -1);
		if( tileset_id != -1 )
		{
			//get tileset pointer
			//get tile pointer
		}
	}
}


