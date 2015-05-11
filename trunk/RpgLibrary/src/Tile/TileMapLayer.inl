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

#include <Catastrophe/Graphics/SpriteBatch.h>

#include <Catastrophe/Core/IO/AttributeWriter.h>
#include <Catastrophe/Core/IO/AttributeReader.h>
#include <Catastrophe/Core/IO/File.h>
#include <Catastrophe/Core/IO/MemoryFile.h>

#include "TileMapLayer.h"
#include "Tileset.h"
#include "TilesetManager.h"


TileMapLayer::TileMapLayer() :
	m_name(),
	m_tileset(0),
	m_tiles(),
	m_blendmode(BlendMode::Alpha),
	m_color(Color::White()),
	m_offset(Point::Zero),
	m_parallax(1.f),
	m_tileSize(DEFAULT_TILE_SIZE),
	m_visible(true)
{
}


void TileMapLayer::Clear()
{
	m_tiles.Fill(TileMapLayerCell());
}


void TileMapLayer::Resize( u32 width, u32 height )
{
	m_tiles.Resize(height, width);
}


void TileMapLayer::SetTileset( Tileset* tileset )
{
	m_tileset = tileset;
}


void TileMapLayer::Render( SpriteBatch* spriteBatch, const Rect& viewRect, bool wrap )
{
	if( !m_tileset )
	{
		LogDebug("TileMapLayer::Render: TileSet is null!");
		return;
	}

	s32 x1 = (viewRect.Left() - (m_tileSize - 1)) / m_tileSize;
	s32 y1 = (viewRect.Top() - (m_tileSize - 1)) / m_tileSize;
	s32 x2 = (viewRect.Right() + (m_tileSize - 1)) / m_tileSize;
	s32 y2 = (viewRect.Bottom() + (m_tileSize - 1)) / m_tileSize;

	//const u32 intTileSize = m_tileset->GetTileSize();

	Rect viewableRect = viewRect;

	// parallax
	if( m_parallax != 1.f )
	{
		f32 parallaxMultiplier = m_parallax;
		viewableRect.position.x = Math::Round((f32)viewableRect.position.x * parallaxMultiplier);
		viewableRect.position.y = Math::Round((f32)viewableRect.position.y * parallaxMultiplier);
	}

	//offset
	viewableRect.position -= m_offset;

	//s32 x1 = viewableRect.Left() / m_tileSize;
	//s32 y1 = viewableRect.Top() / m_tileSize;
	//s32 x2 = viewableRect.Right() / m_tileSize;
	//s32 y2 = viewableRect.Bottom() / m_tileSize;

	//s32 x1 = (viewRect.Left() - (intTileSize - 1)) / intTileSize;
	//s32 y1 = (viewRect.Top() - (intTileSize - 1)) / intTileSize;
	//s32 x2 = (viewRect.Right() + (intTileSize - 1)) / intTileSize;
	//s32 y2 = (viewRect.Bottom() + (intTileSize - 1)) / intTileSize;

	if( wrap )
	{
		InternalDrawWrap(spriteBatch, x1, y1, x2, y2);
	}
	else
	{
		InternalDrawNormal(spriteBatch, x1, y1, x2, y2);
	}
}


void TileMapLayer::InternalDrawNormal( SpriteBatch* spriteBatch, s32 x1, s32 y1, s32 x2, s32 y2 )
{
	const u32 intTileSize = m_tileSize;
	const float floatTileSize = (float)m_tileSize;

	Point p = Point(x1, y1);
	Point tp = Point(x1, y1) * intTileSize;
	//Vector2 tilePos = Point(x1, y1) * intTileSize;

	// clamp indices to valid range.
	x1 = Clamp<s32>(x1, 0, (s32)m_tiles.Width());
	y1 = Clamp<s32>(y1, 0, (s32)m_tiles.Height());
	x2 = Clamp<s32>(x2, 0, (s32)m_tiles.Width());
	y2 = Clamp<s32>(y2, 0, (s32)m_tiles.Height());

	// get the top-leftmost tile position, taking clamping into account.
	tp.x += (x1 - p.x) * intTileSize; 
	tp.y += (y1 - p.y) * intTileSize;
	Vector2 tilePos = tp;

	spriteBatch->SetBlendMode(m_blendmode);
	spriteBatch->SetTextureID(m_tileset->GetTextureId());

	Quad2D quad;
	Memory::Memset(&quad, 0, sizeof(Quad2D));
	quad.SetColorData(m_color);

	Vector2 minPosition = tilePos;

	for( s32 y(y1); y < y2; ++y )
	{
		const u32 last = m_tiles.PointerOffset(y, x2);
		for( u32 first = m_tiles.PointerOffset(y, x1); first < last; ++first )
		{
			const TileMapLayerCell& tileMapLayerCell = m_tiles[first];
			const Tile* tile = tileMapLayerCell.tile;
			const s32 flags = tileMapLayerCell.flags;

			if( tile != null )
			{
				const Vector2 maxPosition = minPosition + floatTileSize;
				Rectf uv = tile->GetUVRect();

				// flip
				if( flags & 3 )
				{
					if( flags & 1 ) Swap(uv.min.x, uv.max.x);
					if( flags & 2 ) Swap(uv.min.y, uv.max.y);
				}

				quad.SetVertexUVData(minPosition, maxPosition, uv);
				spriteBatch->DrawQuad(quad);
			}

			minPosition.x += floatTileSize;
		}

		minPosition.x = tilePos.x;
		minPosition.y += floatTileSize;
	}
}



void TileMapLayer::InternalDrawWrap( SpriteBatch* spriteBatch, s32 x1, s32 y1, s32 x2, s32 y2 )
{
	const u32 intTileSize = m_tileSize;
	const float floatTileSize = (float)m_tileSize;

	Vector2 tilePos = Point(x1, y1) * intTileSize;

	const s32 maxMapTilesX = (s32)m_tiles.Width();
	const s32 maxMapTilesY = (s32)m_tiles.Height();

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

	//InternalDrawNormal(spriteBatch, x1, y2, x2, y2);


//	Vector2 tilePos = ((viewRect.pos / TILE_SIZE) * TILE_SIZE);
	//Vector2 tilePos = ((viewRect.pos / TILE_SIZE) * TILE_SIZE) - viewRect.pos;
	//Vector2 tilePos = viewRect.pos;


	spriteBatch->SetBlendMode(m_blendmode);
	spriteBatch->SetTextureID(GetTileset()->GetTextureId());

	Quad2D quad2D;
	quad2D.SetColorData(GetColor());

	Vector2 minPosition = tilePos;

	for( s32 row(y1); row < y2; ++row )
	{
		const s32 y = row % maxMapTilesY;
		for( s32 col(x1); col < x2; ++col )
		{
			const u32 index = m_tiles.PointerOffset(y, col % maxMapTilesX);
			const Tile* tile = m_tiles[index].tile;
			const s32 flags = m_tiles[index].flags;
			if( tile != null )
			{
				const Vector2 maxPosition = minPosition + floatTileSize;
				Rectf uv = tile->GetUVRect();

				// flip
				if( flags & 3 )
				{
					if( flags & 1 ) Swap(uv.min.x, uv.max.x);
					if( flags & 2 ) Swap(uv.min.y, uv.max.y);
				}

				quad2D.SetVertexUVData(minPosition, maxPosition, uv);
				spriteBatch->DrawQuad(quad2D);
			}

			minPosition.x += floatTileSize;
		}

		minPosition.x = tilePos.x;
		minPosition.y += floatTileSize;
	}
}

/*
void TileMapLayer::Serialize( AttributeWriter* f )
{
	f->SetString("name", m_name.CString());
	f->SetAttribute("width", m_tiles.Width());
	f->SetAttribute("height", m_tiles.Height());
	f->SetAttribute("color", m_color.packed_value);
	f->SetAttribute("blendmode", m_blendmode.value);
	f->SetAttribute("tileSize", m_tileSize);

	String tilesetFilename = m_tileset ? m_tileset->GetFileName() : "";
	if( tilesetFilename.Empty() )
	{
		LogInfo("TileMapLayer::Serialize: tileset filename is empty.");
	}

	f->SetString("tileset", tilesetFilename.CString());

	for( array_type::Iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
	{
		f->BeginNode("Tile");

		s32 id = -1;
		Tile* p = it->tile;
		if(p)
		{
			id = p->GetIndex();
		}

		f->SetAttribute("id", id);
		f->SetAttribute("flags", it->flags);
		f->EndNode();
	}
}
*/

void TileMapLayer::Serialize( Serializer* f )
{
	// Assert failure on corrupted data or uninitialized memory
	CE_ASSERT(m_name.size() < 256);
	CE_ASSERT(m_tiles.Width() < 65535);
	CE_ASSERT(m_tiles.Height() < 65535);
	CE_ASSERT(m_tileSize < 65535);

	f->WriteString(m_name);
	f->WriteUShort((u16)m_tiles.Width());
	f->WriteUShort((u16)m_tiles.Height());
	f->WriteColor(m_color);
	f->WriteUInt(m_blendmode.value);
	f->WriteUShort((u16)m_tileSize);
	f->WritePoint(m_offset);

	f->WriteInt(0); //reserved for future use
	f->WriteInt(0); //reserved for future use

	String tilesetFilename = m_tileset ? m_tileset->GetFileName() : "";
	if( tilesetFilename.Empty() )
		LogInfo("TileMapLayer::Serialize: tileset filename is empty.");

	f->WriteString(tilesetFilename);

	for( array_type::Iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
	{
		Tile* p = it->tile;
		f->WriteShort((s16)(p != null ? p->GetIndex() : -1));
		f->WriteByte((u8)it->flags);
	}
}


void TileMapLayer::Deserialize( Deserializer* f )
{
	Clear();

	f->ReadString(m_name);
	u32 w = (u32)f->ReadUShort();
	u32 h = (u32)f->ReadUShort();

	f->ReadColor(m_color);
	f->ReadUInt(m_blendmode.value);
	m_tileSize = (u32)f->ReadUShort();
	f->ReadPoint(m_offset);

	f->ReadInt(); //reserved for future use
	f->ReadInt(); //reserved for future use

	Resize(w, h);

	String tilsetFilename = f->ReadString();
	if( tilsetFilename.Empty() )
	{
		Log("TileMapLayer::Deserialize: unknown tileset");
		return;
	}
	else
	{
		m_tileset = GetTilesetManager()->Load(tilsetFilename);
		if( !m_tileset )
		{
			Log("Tileset::Deserialize: (%s) tileset could not be loaded.", tilsetFilename.CString());
			return;
		}
	}

	for( array_type::Iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
	{
		s16 id = -1;

		f->ReadShort(id);
		if( id != -1 )
			it->tile = m_tileset->GetTile((u32)id);

		f->ReadByte(it->flags);
	}
}


void TileMapLayer::Deserialize( AttributeReader* f )
{
	Clear();
/*
	m_name = f->GetString("name");
	u32 w = f->GetUInt("width");
	u32 h = f->GetUInt("height");
	m_color.packed_value = f->GetUInt("color", m_color.packed_value);
	m_blendmode.value = f->GetUInt("blendmode", m_blendmode.value);
	m_tileSize = f->GetUInt("tileSize", m_tileSize);

	Resize(w, h);

	String tilsetFilename = f->GetString("tileset");
	if( tilsetFilename.empty() )
	{
		Log("TileMapLayer::Deserialize: unknown tileset");
		return;
	}
	else
	{
		m_tileset = GetTilesetManager()->Load(tilsetFilename);
		if( !m_tileset )
		{
			Log("Tileset::Deserialize: (%s) tileset could not be loaded.", tilsetFilename.CString());
			return;
		}
	}

	for( array_type::Iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
	{
		if( !f->NextChild("Tile") )
			break;

		s32 id = f->GetInt("id", -1);

		it->tile = m_tileset->GetTile((u32)id);
		f->GetByte("flags", it->flags);

	}
	*/
}







