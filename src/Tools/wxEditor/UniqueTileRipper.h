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
#include <wx/string.h>

#include <fc/vector.h>
#include <fc/dynamic_array2d.h>



class UniqueTileRipper
{
public:
	fc::vector< fc::dynamic_array2d<Color> > unique;
	fc::dynamic_array2d<Color> map;
	fc::dynamic_array2d<Color> tiles;
	Image tile_pixmap;
	uint tile_pixmap_width;
	uint tile_pixmap_height;
	uint tile_size;
	uint map_w, map_h;

	wxString lastfilename;

	UniqueTileRipper() : tile_size(16), map_w(0), map_h(0), map(), tiles(), unique(), lastfilename()
	{}


	bool Rip( const ubyte* const data, uint w, uint h );
	bool SaveUniqueTilesAs();

protected:
	void CropToTileSizeMultiplier();
	void Create2DColorArray( fc::dynamic_array2d<Color>& p, uint width, uint height, const ubyte *const data );
	bool AlreadyHaveTile( const fc::dynamic_array2d<Color>& tile );
	void GetUniqueTiles();
	int	 ArrangeUniqueTiles();
};



