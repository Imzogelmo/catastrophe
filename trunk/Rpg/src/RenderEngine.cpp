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

#include "RenderEngine.h"
#include "Tile/Map.h"


#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )
#endif


RenderEngine::RenderEngine()
{
}




void RenderEngine::DrawMap( const Map* map, const Vector2& pos, const Rect& viewRect )
{
	SpriteBatch* spriteBatch = 0; //todo

	const size_t n = map->NumLayers();
	for( size_t i(0); i < n; ++i )
	{
		const MapLayer* layer = map->GetLayer(i);
		if( layer->IsVisible() )
		{
			DrawMapLayer(spriteBatch, layer, pos, viewRect);
		}
	}
}


void RenderEngine::DrawMapLayer( SpriteBatch* spriteBatch, const MapLayer* layer, Vector2 pos, const Rect& viewRect )
{
	const int TILE_SIZE = 16;//fixme
	const float TILE_SIZEf = 16.f;//fixme

	//todo: offset or parallax here...
	int x1 = viewRect.pos.x / TILE_SIZE;
	int y1 = viewRect.pos.y / TILE_SIZE;
	int x2 = x1 + viewRect.Width() / TILE_SIZE;
	int y2 = y1 + viewRect.Height() / TILE_SIZE;

	//todo: overworld type wraparound needs a special function...
	const MapLayer::array_type & array = layer->GetTileArray();
	x1 = fc::clamp<int>(x1, 0, (int)array.x());
	y1 = fc::clamp<int>(y1, 0, (int)array.y());
	x2 = fc::clamp<int>(x2, 0, (int)array.x());
	y2 = fc::clamp<int>(y2, 0, (int)array.y());

	SpriteData sd;
	::memset(&sd, 0, sizeof(SpriteData));
	sd.SetBlendMode(layer->GetBlendMode());
	sd.SetDepth(layer->GetIndex());

	Color layerColor = layer->GetColor();
	sd.data[0].color = layerColor;
	sd.data[1].color = layerColor;
	sd.data[2].color = layerColor;
	sd.data[3].color = layerColor;

	for( int y(y1); y < y2; ++y )
	{
		const size_t last = array.offset(y, x2);
		for( size_t first = array.offset(y, x1); first < last; ++first )
		{
			const Tile* tile = array[first];
			if( tile != 0 )
			{
				const Vector2 max = pos + TILE_SIZEf;
				const Rectf & uv = tile->GetUVRect();
				sd.SetTexture(tile->GetTextureID());
				sd.data[0].pos = pos;
				sd.data[0].uv = uv.min;
				sd.data[1].pos = Vector2(pos.x, max.y);
				sd.data[1].uv = Vector2(uv.min.x, uv.max.y);
				sd.data[2].pos = max;
				sd.data[2].uv = uv.max;
				sd.data[3].pos = Vector2(max.x, pos.y);
				sd.data[3].uv = Vector2(uv.min.x, uv.max.y);

				spriteBatch->DrawSpriteData(sd);
			}

			pos.x += TILE_SIZEf;
		}

		pos.y += TILE_SIZEf;
	}
}






