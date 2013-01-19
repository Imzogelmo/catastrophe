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

#include "Tileset.h"


/* Simple struct that contains data on where a tile is located in memory. */
struct TileLocationData
{
public:
	typedef ubyte size_type;

	Tileset* parent;
	size_type x, y; //loacation of tile in tileset

	TileLocationData() : parent(0), x(0), y(0) {}
	TileLocationData( Tileset* p, uint x, uint y ) : parent(p), x(x), y(y) {}
	TileLocationData( Tileset* p, uint index )
	{
		Set(index, p);
	}

	bool operator == ( const TileLocationData& t ) const {
		return (parent == t.parent && x == t.x && y == t.y);
	}

	bool operator != ( const TileLocationData& t ) const {
		return !(*this == t);
	}

	__FORCE bool IsValid() const { return parent != 0; }
	__FORCE void SetX( uint _x ) { x = (size_type)_x; }
	__FORCE void SetY( uint _y ) { y = (size_type)_y; }
	__FORCE void SetLoc( uint _x, uint _y ) { x = (size_type)_x; y = (size_type)_y; }
	__FORCE uint GetX() const { return (uint)x; }
	__FORCE uint GetY() const { return (uint)y; }

	__FORCE uint GetIndex() const
	{
		if(!parent) return 0;
		return (y * parent->Width()) + x;
	}

	__FORCE uint GetIndexFast() const
	{
		return (y * parent->Width()) + x;
	}

	__FORCE Tile* GetTile()
	{
		if(!parent) return 0;
		return parent->GetTile( GetX(), GetY() );
	}
	__FORCE const Tile* GetTile() const
	{
		if(!parent) return 0;
		return parent->GetTile( GetX(), GetY() );
	}

	__FORCE void Set( uint index, Tileset* _parent = 0 )
	{
		if(!parent)
		{
			if(!_parent)
				return;

			parent = _parent;
		}

		const uint w = parent->Width();
		//uint h = parent->Height();

		SetLoc( index % w, index / w );
	}

};
