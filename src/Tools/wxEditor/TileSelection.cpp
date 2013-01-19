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

#include "TileSelection.h"
#include "Editor.h"


void TileSelection::Set( const wxRect& selectedRect, uint tileSize )
{
	// Translate selectedRect (pixel region) to an indices rect
	// and target the selected array, resizing it if needed, and
	// filling it with elements which point to the currently
	// used tileset array.

	Tileset *tileset = Editor->GetActiveTileset();
	if( !tileset || tileset->tiles.empty() )
		return;

	const int TileSize = int(tileSize);

	int x = selectedRect.x / TileSize;
	int y = selectedRect.y / TileSize;
	int w = selectedRect.width / TileSize;
	int h = selectedRect.height / TileSize;

	//sanity check
	if( w == 0 ) w = 1;
	else if( w < 0 )
	{
		w = abs(w);
		x = (x - w >= 0) ? x - w : 0;
	}
	if( h == 0 ) h = 1;
	else if( h < 0 )
	{
		h = abs(h);
		y = (y - h >= 0) ? y - h : 0;
	}
	
	const int tw = tileset->Width();
	const int th = tileset->Height();

	if( x >= tw ) 
	{
		x = tw - 1;
		w = 1;
	}
	if( y >= th ) 
	{
		y = th - 1;
		h = 1;
	}

	selected.resize(h, w);

	for( int j(0); j < h; ++j )
		for( int i(0); i < w; ++i )
		{
			selected(j, i) = tileset->tiles.offset(y + j, x + i);
		}
}


void TileSelection::GetTileArray( fc::dynamic_array2d<Tile*> &refArray ) const
{
	Tileset *tileset = Editor->GetActiveTileset();
	if(!tileset)
		return;

	refArray.resize( Height(), Width() );

	for( uint i(0); i < selected.size(); ++i )
		refArray[ i ] = tileset->GetTile( selected[i] );
}


void TileSelection::GetTileVector( fc::vector<Tile*> &refVector ) const
{
	Tileset *tileset = Editor->GetActiveTileset();
	if(!tileset)
		return;

	refVector.clear();

	for( uint i(0); i < selected.size(); ++i )
		refVector.push_back( tileset->GetTile( selected[i] ) );
}


void TileSelection::GetTileLocationDataArray( fc::dynamic_array2d<TileLocationData> &refArray ) const
{
	//fixme: just store the dang x,y instead of the single index..
	Tileset *tileset = Editor->GetActiveTileset();
	if(!tileset)
		return;

	refArray.resize( Height(), Width() );

	uint w = tileset->tiles.x();
	uint h = tileset->tiles.y();

	for( uint i(0); i < selected.size(); ++i )
	{
		TileLocationData td;
		td.SetX( selected[i] % w );
		td.SetY( selected[i] / w );
		td.parent = tileset;

		refArray[ i ] = td;
	}
}


void TileSelection::Draw( SpriteBatch* spriteBatch, const Vector2& pos, uint tileSize )
{
	DrawTransparent( spriteBatch, pos, tileSize, 1.0f );
}


void TileSelection::DrawTransparent( SpriteBatch* spriteBatch, const Vector2& pos, uint tileSize, float alphaMul )
{
	Tileset *tileset = Editor->GetActiveTileset();
	if(!tileset)
		return;

	const uint w = selected.x();
	const uint h = selected.y();

	for( uint y(0); y < h; ++y )
		for( uint x(0); x < w; ++x )
		{
			Tile* tile = tileset->GetTile( selected(y, x) );
			if(tile)
			{
				Vector2 position = pos + Vector2( float(x * tileSize), float(y * tileSize) );
				tile->DrawTransparent( spriteBatch, position, alphaMul );
			}
		}
}


