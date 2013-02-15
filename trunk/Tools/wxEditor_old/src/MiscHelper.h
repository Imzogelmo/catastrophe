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

#include "Mouse.h"
#include "Tileset.h"



class MiscHelper
{
public:

	static wxPoint SnapToGrid( const wxPoint& pos, const uint tileSize );
	static wxSize SnapToGrid( const wxSize& size, const uint tileSize );
	static wxRect SnapToGrid( const wxRect& selected, const uint tileSize );

	static wxPoint SnapToIndexGrid( const wxPoint& pos, const uint tileSize );

	//Resizes an array while maintaining previous dimension-order.
	template<class ArrayType, class DataType> static
		void ResizeArray( ArrayType& refArray, uint w, uint h, const DataType& defaultValue )
		{
			ArrayType subArray;

			const uint current_w = refArray.x();
			const uint current_h = refArray.y();
			uint min_w = current_w < w ? current_w : w;
			uint min_h = current_h < h ? current_h : h;

			if( refArray.empty() )
			{
				refArray.resize( h, w );
				refArray.assign( defaultValue );
			}
			else if( w * h == 0 )
			{
				refArray.resize(0);
			}
			else
			{
				refArray.copy_subregion( 0, 0, min_w, min_h, subArray );
				refArray.resize( h, w );
				refArray.assign( defaultValue );
				refArray.write_subregion( 0, 0, min_w, min_h, &subArray );
			}
		}

};





