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
#include "TilesetManager.h"


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

/*
void MapLayer::Render( SpriteBatch* spriteBatch, const Rect& viewRect, bool wrap )
{
	if( !m_tileset )
		return;

	const int tileSize = 16;

	// todo: offset, parallax
	int x1 = (viewRect.Left() - tileSize - 1) / tileSize;
	int y1 = (viewRect.Top() - tileSize - 1) / tileSize;
	int x2 = (viewRect.Right() + tileSize - 1) / tileSize;
	int y2 = (viewRect.Bottom() + tileSize - 1) / tileSize;

	if( wrap )
	{
		InternalDrawWrap(spriteBatch, x1, y1, x2, y2);
	}
	else
	{
		InternalDrawNormal(spriteBatch, x1, y1, x2, y2);
	}
}


void MapLayer::InternalDrawNormal( SpriteBatch* spriteBatch, int x1, int y1, int x2, int y2 )
{
	const int tileSize = 16;
	const float tileSizef = 16.f;

	Point p = Point(x1, y1);
	Point tp = Point(x1, y1) * tileSize;
	Vector2 tilePos = Point(x1, y1) * tileSize;

	// clamp indices to valid range.
	x1 = fc::clamp<int>(x1, 0, (int)m_tiles.x());
	y1 = fc::clamp<int>(y1, 0, (int)m_tiles.y());
	x2 = fc::clamp<int>(x2, 0, (int)m_tiles.x());
	y2 = fc::clamp<int>(y2, 0, (int)m_tiles.y());

	// get the top-leftmost tile position, taking clamping into account.
	tp.x += (x1 - p.x) * tileSize; 
	tp.y += (y1 - p.y) * tileSize;
	Vector2 tilePos = tp;

	SpriteData sd;
	::memset(&sd, 0, sizeof(SpriteData));

	sd.SetBlendMode(m_blendmode);
	sd.SetTexture(m_tileset->GetTextureId());
	Color color = m_color;
	sd.data[0].color = color;
	sd.data[1].color = color;
	sd.data[2].color = color;
	sd.data[3].color = color;

	Vector2 pos = tilePos;

	for( int y(y1); y < y2; ++y )
	{
		const size_t last = m_tiles.offset(y, x2);
		for( size_t first = m_tiles.offset(y, x1); first < last; ++first )
		{
			const Tile* tile = m_tiles[first].tile;
			const int flags = m_tiles[first].flags;
			if( tile != 0 )
			{
				const Vector2 max = pos + tileSizef;
				Rectf uv = tile->GetUVRect();

				// flip
				if( flags & 3 )
				{
					if( flags & 1 ) fc::swap(uv.min.x, uv.max.x);
					if( flags & 2 ) fc::swap(uv.min.y, uv.max.y);
				}

				sd.data[0].pos = pos;
				sd.data[0].uv = uv.min;
				sd.data[1].pos.x = pos.x;
				sd.data[1].pos.y = max.y;
				sd.data[1].uv.x = uv.min.x;
				sd.data[1].uv.y = uv.max.y;
				sd.data[2].pos = max;
				sd.data[2].uv = uv.max;
				sd.data[3].pos.x = max.x;
				sd.data[3].pos.y = pos.y;
				sd.data[3].uv.x = uv.max.x;
				sd.data[3].uv.y = uv.min.y;

				spriteBatch->DrawSpriteData(sd);
			}

			pos.x += tileSizef;
		}

		pos.x = tilePos.x;
		pos.y += tileSizef;
	}
}



void MapLayer::InternalDrawWrap( SpriteBatch* spriteBatch, int x1, int y1, int x2, int y2 )
{
	const int TILE_SIZE = 16;//fixme
	const float TILE_SIZEf = 16.f;//fixme

	Vector2 tilePos = Point(x1, y1) * TILE_SIZE;

	const int maxMapTilesX = (int)m_tiles.x();
	const int maxMapTilesY = (int)m_tiles.y();

	// resolve to within positive range [0.. 2x) while keeping a valid rect
	x1 = (x1 % maxMapTilesX) + maxMapTilesX;
	x2 = (x2 % maxMapTilesX) + maxMapTilesX;
	y1 = (y1 % maxMapTilesY) + maxMapTilesY;
	y2 = (y2 % maxMapTilesY) + maxMapTilesY;
	x1 %= maxMapTilesX;
	x2 %= maxMapTilesX;
	y1 %= maxMapTilesY;
	y2 %= maxMapTilesY;
	if( x2 < x1 ) x2 += maxMapTilesX;
	if( y2 < y1 ) y2 += maxMapTilesY;


//	Vector2 tilePos = ((viewRect.pos / TILE_SIZE) * TILE_SIZE);
	//Vector2 tilePos = ((viewRect.pos / TILE_SIZE) * TILE_SIZE) - viewRect.pos;
	//Vector2 tilePos = viewRect.pos;

	SpriteData sd;
	::memset(&sd, 0, sizeof(SpriteData));
	sd.SetBlendMode(layer->GetBlendMode());

	Color layerColor = layer->GetColor();
	sd.data[0].color = layerColor;
	sd.data[1].color = layerColor;
	sd.data[2].color = layerColor;
	sd.data[3].color = layerColor;
	sd.SetTexture(layer->GetTileset()->GetTextureId());

	Vector2 pos = tilePos;
	//Vector2 pos = Vector2(0.f);

	for( int row(y1); row < y2; ++row )
	{
		const int y = row % maxMapTilesY;
		for( int col(x1); col < x2; ++col )
		{
			//const int x = col % maxMapTilesX;
			const size_t index = array.offset(y, col % maxMapTilesX);
			const Tile* tile = array[index].tile;
			const int flags = array[index].flags;
			if( tile != 0 )
			{
				const Vector2 max = pos + TILE_SIZEf;
				//const Rectf & uv = tile->GetUVRect();
				Rectf uv = tile->GetUVRect();

				// flip
				if( flags & 3 )
				{
					if( flags & 1 ) fc::swap(uv.min.x, uv.max.x);
					if( flags & 2 ) fc::swap(uv.min.y, uv.max.y);
				}

				sd.data[0].pos = pos;
				sd.data[0].uv = uv.min;
				sd.data[1].pos.x = pos.x;
				sd.data[1].pos.y = max.y;
				sd.data[1].uv.x = uv.min.x;
				sd.data[1].uv.y = uv.max.y;
				sd.data[2].pos = max;
				sd.data[2].uv = uv.max;
				sd.data[3].pos.x = max.x;
				sd.data[3].pos.y = pos.y;
				sd.data[3].uv.x = uv.max.x;
				sd.data[3].uv.y = uv.min.y;

				spriteBatch->DrawSpriteData(sd);
			}

			pos.x += TILE_SIZEf;
		}

		pos.x = tilePos.x;
		pos.y += TILE_SIZEf;
	}
}
*/

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
		m_tileset = g_tilesetManager->LoadXml(tilsetFilename);
		if( !m_tileset )
		{
			Log("Tileset::DeserializeXml: (%s) tileset could not be loaded.", tilsetFilename.c_str());
			return;
		}
	}

	for( array_type::iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
	{
		if( !xml->NextChild("Tile") )
			break;

		int id = xml->GetInt("id", -1);

		it->tile = m_tileset->GetTile((size_t)id);
		it->flags = xml->GetInt("flags", 0);

	}
}







