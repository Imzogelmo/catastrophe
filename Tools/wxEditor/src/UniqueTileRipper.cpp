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

#include <wx/wx.h>
#include <wx/frame.h>

#include "UniqueTileRipper.h"
#include "ColorConverter.h"
#include "Dialogs.h"


bool UniqueTileRipper::Rip( const ubyte* const data, uint w, uint h )
{
	Create2DColorArray( map, w, h, data );

	map_w = (uint)w;
	map_h = (uint)h;
	CropToTileSizeMultiplier();


	GetUniqueTiles();

	return ( ArrangeUniqueTiles() == 0 );
}


void UniqueTileRipper::CropToTileSizeMultiplier()
{
	uint x = (uint) (map_w - (uint)((uint)(map_w / tile_size) * tile_size));
	uint y = (uint) (map_h - (uint)((uint)(map_h / tile_size) * tile_size));
	map_w -= x;
	map_h -= y;
}


void UniqueTileRipper::Create2DColorArray( fc::dynamic_array2d<Color>& p, uint width, uint height, const ubyte *const data )
{
	p.resize( height, width );

	uint i(0);
	const uint w = width;
	const uint h = height;

	for( uint k(0); k < h; ++k )
		for( uint j(0); j < w; ++j )
		{
			Color *pixel = & p( k, j );
			(*pixel).r = *(data + i++);
			(*pixel).g = *(data + i++);
			(*pixel).b = *(data + i++);
			(*pixel).a = *(data + i++);
		}
}

/*
bool UniqueTileRipper::AlreadyHaveTile( const fc::dynamic_array2d<Color>& tile )
{
	for( uint i(0); i < unique.size(); ++i )
	{
		if( unique[ i ] == tile )
			return true;
	}

	return false;
}
*/

bool ColEqCol( const Color& l, const Color& r, int thresh = 16 )
{
	if( //todo: optimize me
		abs((int)l.r - (int)r.r) <= thresh &&
		abs((int)l.g - (int)r.g) <= thresh &&
		abs((int)l.b - (int)r.b) <= thresh &&
		abs((int)l.a - (int)r.a) <= thresh 
	)
	{
		return true;
	}
	return false;
}

bool UniqueTileRipper::AlreadyHaveTile( const fc::dynamic_array2d<Color>& tile )
{
	for( uint i(0); i < unique.size(); ++i )
	{
		int matched(0);
		for( uint j(0); j < 256; ++j )
		{
			if( !ColEqCol(unique[ i ][ j ], tile[ j ], 16 ) )
				break;
			else
				++matched;
		}
		if(matched > 255)
			return true;
	}

	return false;
}


void UniqueTileRipper::GetUniqueTiles()
{
	const fc::dynamic_array2d<Color> &p = map;

	fc::dynamic_array2d<Color> temp_tile;

	for( uint y(0); y < map_h; y += tile_size )
	{
		for( uint x(0); x < map_w; x += tile_size )
		{
			p.copy_subregion( x, y, tile_size, tile_size, temp_tile );

			if( !AlreadyHaveTile( temp_tile ) )
				unique.push_back( temp_tile );

		}
	}
}


int UniqueTileRipper::ArrangeUniqueTiles()
{
	uint size = unique.size();

	if( size == 0 )
		return 1;

	uint square_size = (uint) ceilf( sqrtf(size) );
	uint w = square_size * tile_size;
	uint h = square_size * tile_size;
	uint current_progress(0);
	tiles.resize( h, w );

	for( uint y(0); y < h; y += tile_size )
	{
		for( uint x(0); x < w; x += tile_size )
		{
			if( current_progress >= size )
				goto __donearranging;

			tiles.write_subregion( x, y, tile_size, tile_size, &unique[ current_progress ] );
			current_progress++;
		}
	}

__donearranging:

	//tile_pixmap.CreateFromPixels( GL_CLAMP, GL_NEAREST, GL_NEAREST, 0, w, h, &tiles[0].r );
	tile_pixmap_width	= w;
	tile_pixmap_height	= h;
	return 0;

}


bool UniqueTileRipper::SaveUniqueTilesAs()
{
	bool ret = false;

	wxImage *image = ColorConverter::ConvertRGBAToImage( &tiles[0].r, tile_pixmap_width, tile_pixmap_height );
	if(!image)
	{
		Dialog::ErrorDialog(_T("Cannot save unique tiles"));
		return false;
	}

	wxString filename;
	ret = Dialog::SaveImageDialog(image, filename);
	delete image;

	return ret;
}


/*
int UniqueTileRipper::SaveImage( uint w, uint h )
{
	wxMessageDialog popup
		( 
		NULL, 
		_T(" Are you a GOD...? "),
		_T(" Tile Disextrapolaction Complete! "),
		wxNO_DEFAULT|wxYES_NO
		);

	switch ( popup.ShowModal() )
	{
		case wxID_YES:
			break;

		case wxID_NO:
		case wxID_CANCEL:
			return 0;
	}

	wxFileDialog dialog
		(
		(wxMessageDialog*)NULL,
		_T("During the third reconciliation of the last of the Meketrex Supplicants..."),
		wxEmptyString,
		_T("sloar.png"),
		_T("Moving Torb Files (*.png)|*.png"),
		wxFD_SAVE | wxFD_OVERWRITE_PROMPT
		);

	dialog.SetFilterIndex(1);

	if (dialog.ShowModal() == wxID_OK)
	{
		//return Soil::SavePng( dialog.GetPath().c_str(), w, h, &tiles[0].r );
					// dialog.GetPath().c_str(), dialog.GetFilterIndex());
	}

	return 0;//Soil::SavePng( path, w, h, &tiles[0].r );
}
*/


