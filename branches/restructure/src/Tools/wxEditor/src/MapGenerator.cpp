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
#include <fc/vector.h>

#include <wx/wx.h>
#include <wx/progdlg.h>

#include "MapGenerator.h"
#include "ColorConverter.h"
#include "Dialogs.h"


Map* MapGenerator::CreateFromImage( Tileset *tileset )
{
	wxImage image;
	wxString filename;
	if( !Dialog::LoadImageDialog(&image, filename) )
		return 0;

	fc::dynamic_array2d<Color> pixels;
	ColorConverter::ConvertImageToPixelArray(&image, pixels);
	if( pixels.empty() || !tileset )
		return 0;

	const uint TILE_SIZE = Tile::TileSize;

	const uint tilesetSize = tileset->Size();
	const uint w = (pixels.x() / TILE_SIZE) * TILE_SIZE;
	const uint h = (pixels.y() / TILE_SIZE) * TILE_SIZE;
	//const uint size = w * h;
	uint mapWidth = w / TILE_SIZE;
	uint mapHeight = h / TILE_SIZE;

	Map *map = new Map( "generated", mapWidth, mapHeight, 1 );

	fc::dynamic_array2d<Color> mapSubRect;
	fc::dynamic_array2d<Color> tileRect;

	wxProgressDialog progressDialog( 
		_("Generate Map From Image"),
		_("Parsing Data... (This may take a minute)"),
		h,
		0,
		wxPD_APP_MODAL | wxPD_CAN_ABORT
	);
	progressDialog.SetSize( 320, 200 );


	for( uint y(0); y < h; y += TILE_SIZE )
	{
		uint mapIndexY = y / TILE_SIZE;

		if( !progressDialog.Update(y) )
		{
			delete map;
			return 0; // cancel button clicked
		}

		for( uint x(0); x < w; x += TILE_SIZE )
		{
			pixels.copy_subregion( x, y, TILE_SIZE, TILE_SIZE, mapSubRect );

			for( uint i(0); i < tilesetSize; ++i )
			{
				const Tile *currentTile = tileset->GetTile(i);
				const Rect &rect = currentTile->sourceRect;

				tileset->GetImage()->pixels.copy_subregion( rect.pos.x, rect.pos.y, rect.size.x, rect.size.y, tileRect );

				if( mapSubRect == tileRect )
				{
					TileLocationData & td = map->GetLayer(0)->GetTileArray().at( mapIndexY, x / TILE_SIZE );
					td.Set(i, tileset);

					break;
					//map->m_layers[0].m_tiles[ 0 ] = tileset->GetTile(i);
				}
			}
		}
	}

	return map;
}



