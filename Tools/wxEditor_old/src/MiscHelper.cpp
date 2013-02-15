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


#include "Precompiled.h"


#include "MiscHelper.h"



wxPoint MiscHelper::SnapToGrid( const wxPoint& pos, const uint tileSize )
	{
		const int TileSize = int(tileSize);

		int x = (pos.x / TileSize) * TileSize;
		int y = (pos.y / TileSize) * TileSize;

		return wxPoint( x, y );
	}


wxSize MiscHelper::SnapToGrid( const wxSize& size, const uint tileSize )
	{
		const int TileSize = int(tileSize);

		int x = int( ceilf(size.x / (float)TileSize) ) * TileSize;
		int y = int( ceilf(size.y / (float)TileSize) ) * TileSize;

		return wxSize( x, y );
	}


wxRect MiscHelper::SnapToGrid( const wxRect& selected, const uint tileSize )
	{
		wxPoint pos = SnapToGrid( selected.GetPosition(), tileSize );
		wxSize size = SnapToGrid( selected.GetSize(), tileSize );

		return wxRect( pos, size );
	}


wxPoint MiscHelper::SnapToIndexGrid( const wxPoint& pos, const uint tileSize )
	{
		const int TileSize = int(tileSize);

		wxPoint point = SnapToGrid( pos, tileSize );
		point.x = abs(point.x / TileSize);
		point.y = abs(point.y / TileSize);

		return point;
	}


