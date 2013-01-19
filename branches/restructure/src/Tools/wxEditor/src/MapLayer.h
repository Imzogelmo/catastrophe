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

#pragma once

#include <wx/gdicmn.h>

#include "TileLocationData.h"
#include "TileSelection.h"


class MapLayer
{
public:
	static const uint TileSize = Tile::TileSize;
	static const uint MaxDimension = 0xffff;

	typedef fc::dynamic_array2d<TileLocationData> array_type;


	MapLayer() : ptrTiles(), m_blendmode(), m_visible(true) {}
	MapLayer( const MapLayer& l ) : ptrTiles(l.ptrTiles), m_blendmode(l.m_blendmode), m_visible(l.m_visible) {}
	~MapLayer()
	{}

	MapLayer &operator = ( const MapLayer& l );

	bool IsVisible() const { return m_visible; }
	void SetVisible( bool isVisible ) { m_visible = isVisible; }

	void Clear();
	void Resize( uint w, uint h );
	void AddTileSelection( const wxPoint& posIndex );
	void AddTileSelection( const wxPoint& posIndex, const TileSelection& tileSelection );

	void FlipHorizontally( uint x = 0, uint y = 0, uint width = MaxDimension, uint height = MaxDimension );
	void FlipVertically( uint x = 0, uint y = 0, uint width = MaxDimension, uint height = MaxDimension );

	void Floodfill( const wxPoint& posIndex, const TileSelection& ts );


	// getters, setters
	array_type*			GetTileArrayPtr() { return &ptrTiles; }
	const array_type*	GetTileArrayPtr() const { return &ptrTiles; }
	array_type&			GetTileArray() { return ptrTiles; }
	const array_type&	GetTileArray() const { return ptrTiles; }

	/// without bounds checking
	__FORCE Tile*		GetTileFast(uint x, uint y) { return ptrTiles(y, x).GetTile(); }
	__FORCE const Tile* GetTileFast(uint x, uint y) const { return ptrTiles(y, x).GetTile(); }

	/// with bounds checking
	__FORCE Tile*		GetTile(uint x, uint y);
	__FORCE const Tile* GetTile(uint x, uint y) const;


	void Render( SpriteBatch* spriteBatch, wxRect indexRect, uint tileSize );

protected:
	array_type	ptrTiles;
	BlendMode	m_blendmode;
	bool		m_visible;

};




__FORCE Tile* MapLayer::GetTile(uint x, uint y)
{
	if( ptrTiles.x() <= x || ptrTiles.y() <= y )
		return 0;

	return ptrTiles(y, x).GetTile();
}


__FORCE const Tile* MapLayer::GetTile(uint x, uint y) const
{
	if( ptrTiles.x() <= x || ptrTiles.y() <= y )
		return 0;

	return ptrTiles(y, x).GetTile();
}



