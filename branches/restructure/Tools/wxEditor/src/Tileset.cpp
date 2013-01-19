//////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify //
// it under the terms of the GNU General Public License as published by //
// the Free Software Foundation, either version 3 of the License, or    //
// (at your option) any later version.                                  //
//                                                                      //
// This program is distributed in the hope that it will be useful,      //
// but WITHOUT ANY WARRANTY; without even the implied warranty of       //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        //
// GNU General Public License for more details.                         //
//////////////////////////////////////////////////////////////////////////


#include "Precompiled.h"


#include "Tileset.h"
#include "TileHelper.h"
#include "Editor.h"


Tileset::Tileset() : 
	name(), tiles(), m_uniqueID(0)
{
}


Tileset::~Tileset()
{
}


void Tileset::Resize( uint w, uint h )
{
	try
	{
		TileHelper::ResizeArray( tiles, w, h, Tile(this) );
		VerifyTileParentPtrs();
	}
	catch(...)
	{
		tiles.resize(0);
		printf("Tileset::Resize error: Memory exhausted. ");
	}
}


Tile *Tileset::GetTile( uint index )
{
	if( index >= tiles.size() )
		return 0;

	return &tiles[ index ];
}


Tile *Tileset::GetTile( uint x, uint y )
{
	if( x >= tiles.x() || y >= tiles.y() )
		return 0;

	return &tiles(y, x);
}


const Tile *Tileset::GetTile( uint index ) const
{
	if( index >= tiles.size() )
		return 0;

	return &tiles[ index ];
}


const Tile *Tileset::GetTile( uint x, uint y ) const
{
	if( x >= tiles.x() || y >= tiles.y() )
		return 0;

	return &tiles(y, x);
}


void Tileset::DestroyTileset()
{
	tiles.resize(0);
}


void Tileset::UpdateAnimation()
{
	for( tile_iter it = tiles.begin(); it != tiles.end(); ++it )
	{
		it->animation.Update();
	}
}


void Tileset::CreateFromPixmap( Image* image, const wxString& assetName )
{
	//const uint size = image->pixels.size();
	const uint pixmap_w = image->pixels.x();
	const uint pixmap_h = image->pixels.y();

	if( pixmap_w < Tile::TileSize || pixmap_h < Tile::TileSize )
		throw(-1);

	this->asset_name = assetName;
	const uint w = pixmap_w / Tile::TileSize;
	const uint h = pixmap_h / Tile::TileSize;

	tiles.resize(h, w);
	VerifyTileParentPtrs();

	for( uint y(0); y < h; ++y )
	{
		for( uint x(0); x < w; ++x )
		{
			Tile &t = tiles(y, x);

			t.SetTint(Color::White());
			t.animation.SetTexture( image->GetTexture() );

			Rect rect(
				x * Tile::TileSize,
				y * Tile::TileSize,
				Tile::TileSize,
				Tile::TileSize
			);

			t.sourceRect = rect;
			t.animation.AddFrame( image->GetUVRect(rect) );
		}
	}

	m_pixmap = image;

}

// (Internal) called after any resize
void Tileset::VerifyTileParentPtrs()
{
	for( tile_iter it = tiles.begin(); it != tiles.end(); ++it )
	{
		it->m_parent = this;
	}
}

