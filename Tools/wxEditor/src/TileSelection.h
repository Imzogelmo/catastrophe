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

#include <wx/wx.h>
#include <fc/vector.h>

#include "Tile.h"
#include "Tileset.h"
#include "TileLocationData.h"


class TileSelection
{
public:
	fc::dynamic_array2d<uint>	selected;
	Tileset *parent;

	TileSelection() : selected() {}
	TileSelection( const TileSelection& ts ) : selected(ts.selected) {}
	~TileSelection()
	{}

	bool operator == ( const TileSelection& ts ) const {
		return (parent == ts.parent && selected == ts.selected);
	}

	bool operator != ( const TileSelection& ts ) const {
		return !(*this == ts);
	}

	uint Size() const { return selected.size(); }
	uint Width() const { return selected.x(); }
	uint Height() const { return selected.y(); }
	bool Empty() const { return selected.empty(); }

	void Set( const wxRect& selectedRect, uint tileSize );

	void GetTileArray( fc::dynamic_array2d<Tile*> &refArray ) const;
	void GetTileVector( fc::vector<Tile*> &refVector ) const;
	void GetTileLocationDataArray( fc::dynamic_array2d<TileLocationData> &refArray ) const;

	void Draw( SpriteBatch* spriteBatch, const Vector2& pos, uint tileSize );
	void DrawTransparent( SpriteBatch* spriteBatch, const Vector2& pos, uint tileSize, float alphaMul = 0.5f );


};





