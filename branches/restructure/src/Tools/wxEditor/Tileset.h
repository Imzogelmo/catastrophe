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


#include "Tile.h"


class Tileset
{
public:
	typedef fc::dynamic_array2d<Tile> ::iterator tile_iter;


	Tileset();
	~Tileset();

	void Resize( uint w, uint h );
	void CreateFromPixmap( Image* image, const wxString& assetName );
	void DestroyTileset();
	void UpdateAnimation();

	uint Size() const { return tiles.size(); }
	uint Width() const { return tiles.x(); }
	uint Height() const { return tiles.y(); }


	const Tile *GetTile( uint index ) const;
	const Tile *GetTile( uint x, uint y ) const;
	Tile *GetTile( uint index );
	Tile *GetTile( uint x, uint y );


	Image *GetImage() { return m_pixmap; }
	const Image *GetImage() const { return m_pixmap; }

	wxString& GetName() { return name; }
	const wxString& GetName() const { return name; }

	void SetName( const wxString& name ) { this->name = name; }
	int GetID() const { return m_uniqueID; }

	void VerifyTileParentPtrs();

public:
	wxString		name;
	wxString		asset_name;
	fc::dynamic_array2d<Tile>		tiles;


private:
	//should be copyable
	//Tileset( const Tileset& );
	//Tileset &operator = ( const Tileset& );

	Image		*m_pixmap;
	int m_uniqueID;
};


