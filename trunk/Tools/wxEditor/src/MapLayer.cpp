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


#include "MapLayer.h"
#include "Tileset.h"
#include "Editor.h"
#include "MapHelper.h"



MapLayer &MapLayer::operator = ( const MapLayer& l )
{
	ptrTiles	= l.ptrTiles;
	m_blendmode	= l.m_blendmode;
	m_visible		= l.m_visible;

	return *this;
}


void MapLayer::Clear()
{
	ptrTiles.assign( 0, ptrTiles.size(), TileLocationData() );
}


void MapLayer::Resize( uint w, uint h )
{
	MapHelper::ResizeArray( ptrTiles, w, h, TileLocationData() );
}


void MapLayer::AddTileSelection( const wxPoint& posIndex )
{
	TileSelection &selectedTiles = Editor->GetTileSelection();
	AddTileSelection( posIndex, selectedTiles );
}


void MapLayer::AddTileSelection( const wxPoint& posIndex, const TileSelection& tileSelection )
{
	Tileset *tileset = Editor->GetActiveTileset();
	if(!tileset)
		return;

	Map *map = Editor->GetActiveMap();
	if(!map)
		return;

	fc::dynamic_array2d<TileLocationData> selectionArray;
	tileSelection.GetTileLocationDataArray( selectionArray );

	const int w = (int)selectionArray.x() + posIndex.x;
	const int h = (int)selectionArray.y() + posIndex.y;
	const int map_w = (int)map->Width();
	const int map_h = (int)map->Height();

	for( int y(posIndex.y); y < h; ++y )
	{
		if( !(y < map_h) )
			break;

		for( int x(posIndex.x); x < w; ++x )
		{
			if( !(x < map_w) )
				break;

			//TileLocationData & data = ptrTiles(y, x);
			ptrTiles(y, x) = selectionArray(y - posIndex.y, x - posIndex.x);
		}
	}
}


void MapLayer::FlipHorizontally( uint x, uint y, uint width, uint height )
{
	x		= Math::Min( x, ptrTiles.x() );
	y		= Math::Min( y, ptrTiles.y() );
	width	= Math::Min( width, ptrTiles.x() );
	height	= Math::Min( height, ptrTiles.y() );

	for( uint i(0); i < height; ++i )
	{
		uint w	= width;
		const uint ybegin	= (y + i);

		for( uint j(0); j < --w; ++j )
			std::swap( ptrTiles( ybegin, x + j ), ptrTiles( ybegin, x + w ) );
	}
}


void MapLayer::FlipVertically( uint x, uint y, uint width, uint height )
{
	x		= Math::Min( x, ptrTiles.x() );
	y		= Math::Min( y, ptrTiles.y() );
	width	= Math::Min( width, ptrTiles.x() );
	height	= Math::Min( height, ptrTiles.y() );

	for( uint i(0); i < width; ++i )
	{
		uint h	= height;
		const uint xbegin	= (x + i);

		for( uint j(0); j < --h; ++j )
			std::swap( ptrTiles( y + j, xbegin ), ptrTiles( y + h, xbegin ) );
	}
}


void MapLayer::Floodfill( const wxPoint& posIndex, const TileSelection& ts )
{
	const int h = (int)ptrTiles.y();
	const int w = (int)ptrTiles.x();

	if( ts.Empty() || posIndex.y < 0 || posIndex.y >= h || posIndex.x < 0 || posIndex.x >= w )
		return;

	Vector<wxPoint> stack;
	stack.reserve( 4096 );
	stack.push_back( posIndex );

	const TileLocationData seedData = ptrTiles(posIndex.y, posIndex.x);

	//only takes the single top-left-most tile right now
	const TileLocationData fillData = TileLocationData( ts.parent, ts.selected[0] );

	while( !stack.empty() )
	{
		const wxPoint & p = stack.back();
		const int x = p.x;
		const int y = p.y;
		stack.pop_back();

		if( y < 0 || y >= h || x < 0 || x >= w )
			continue;

		TileLocationData &data = ptrTiles(y, x);
		if( data == seedData )
		{
			data = fillData;
			stack.push_back( wxPoint(x + 1, y) );
			stack.push_back( wxPoint(x - 1, y) );
			stack.push_back( wxPoint(x, y + 1) );
			stack.push_back( wxPoint(x, y - 1) );
		}
	}
}











void MapLayer::Render( SpriteBatch* spriteBatch, wxRect indexRect, uint tileSize )
{
	if( ptrTiles.empty() || !m_visible )
		return;

	const float TileSize = float(tileSize);

	const int w = indexRect.x + indexRect.width;
	const int h = indexRect.y + indexRect.height;

	Vector2 pos;
	spriteBatch->SetBlendMode( m_blendmode );

	for( int y(indexRect.y); y < h; ++y )
	//for( int y(0); y < h; ++y )
	{
		//pos.y = float(y) * TileSize;
		pos.y = float(y - indexRect.y) * TileSize;

		for( int x(indexRect.x); x < w; ++x )
		//for( int x(0); x < w; ++x )
		{
			pos.x = float(x - indexRect.x) * TileSize;

			const Tile* tile = GetTile(x, y);
			if(tile)
				tile->Draw( spriteBatch, pos );
		}
	}

}

