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

#include <wx/image.h>
#include <fc/dynamic_array2d.h>
#include <Catastrophe/Graphics.h>


class ColorConverter
{
public:

	//Don't forget to delete the data when you're done with it.
	static void DeleteData(ubyte* &dataPtr);

	ubyte *ConvertImageToRGBA(wxImage *image);
	void ConvertImageToPixelArray(wxImage *image, fc::dynamic_array2d<Color> &pixels);
	wxImage* ConvertRGBAToImage(const Image* image);
	wxImage* ConvertRGBAToImage(const ubyte* const data, uint w, uint h);

	void CreateMask(fc::dynamic_array2d<Color> &pixels, bool preserveRgbMask = true);
	void CreateMask(fc::dynamic_array2d<Color> &pixels, const Color &colorToMask, bool preserveRgbMask = true);
	void ReplaceColor(fc::dynamic_array2d<Color> &pixels, const Color &colorToReplace, const Color &newColor);

	// People used to make tileset *images* with solid color 'gaps' between each tile. (true story)
	// While this might be useful for tilset metadata, I say it is stupid so we can just remove them.
	static void RemoveTileSeparationLinesOldFormat(fc::dynamic_array2d<Color> &pixels, uint tileWidth = 16, uint tileHeight = 16, uint spacing = 1);

};





