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


MapLayer::MapLayer() :
	m_name(),
	m_tileset(0),
	m_tiles(),
	m_blendmode(BlendMode::Alpha),
	m_color(Color::White()),
	m_visible(true)
{
}


void MapLayer::Clear()
{
	m_tiles.assign(LayerTile());
}


void MapLayer::Resize( size_t w, size_t h )
{
	m_tiles.resize(h, w);
}


void MapLayer::SetTileset( Tileset* tileset )
{
	m_tileset = tileset;
}


void MapLayer::SerializeXml( XmlWriter* xml )
{
	xml->SetString("name", m_name.c_str());
	xml->SetUInt("width", m_tiles.x());
	xml->SetUInt("height", m_tiles.y());
	xml->SetUInt("color", m_color.packed_value);
	xml->SetUInt("blendmode", m_blendmode.value);

	fc::string tilesetFilename = m_tileset ? m_tileset->GetFileName() : "";
	if( tilesetFilename.empty() )
	{
		Log("MapLayer::SerializeXml: tileset filename is empty.");
	}

	xml->SetString("tileset", tilesetFilename.c_str());

	for( array_type::iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
	{
		xml->BeginNode("Tile");

		int id = -1;
		Tile* p = it->tile;
		if(p)
		{
			id = p->GetIndex();
		}

		xml->SetInt("id", id);
		xml->SetInt("flags", it->flags);
		xml->EndNode();
	}
}


void MapLayer::DeserializeXml( XmlReader* xml )
{
	Clear();

	m_name = xml->GetString("name");
	size_t w = xml->GetUInt("width");
	size_t h = xml->GetUInt("height");
	m_color.packed_value = xml->GetUInt("color");
	m_blendmode.value = xml->GetUInt("blendmode");

	Resize(w, h);

	fc::string tilsetFilename = xml->GetString("tileset");
	if( tilsetFilename.empty() )
	{
		Log("MapLayer::DeserializeXml: unknown tileset");
		return;
	}
	else
	{
		/*
		m_tileset = tilesetManager->LoadTileset(tilsetFilename);
		if( !m_tileset )
		{
			Log("Tileset::DeserializeXml: (%s) tileset is null.", filename.c_str());
			return;
		}
		*/
	}

	while( xml->NextChild("Tile") )
	{
		int id = xml->GetInt("id", -1);
		//xml->SetInt("flags", it->flags);
	}
}


