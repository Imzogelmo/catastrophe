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

#include "ColorConverter.h"


void ColorConverter::DeleteData(ubyte* &dataPtr)
{
	delete [] dataPtr;
	dataPtr = 0;
}


ubyte *ColorConverter::ConvertImageToRGBA(wxImage *image)
{
	//wxImages store RGB and A seperately.
	//This makes it very difficult to work with
	//and incompatable with OpenGL format, so
	//we have to join them together.

	const int w = image->GetWidth();
	const int h = image->GetHeight();
	const int size = w * h;

	if( size == 0 )
		return 0;

	ubyte *rgb	= image->GetData();
	ubyte *a	= image->GetAlpha();
	ubyte *data = new ubyte[ size * 4 ];

	if( a && image->HasAlpha() )
	{
		for( int i(0); i < size; ++i )
		{
			const int index = i * 4;
			const int rgbIndex = index - i;

			data[ index ] = rgb[ rgbIndex ];
			data[ index + 1 ] = rgb[ rgbIndex + 1 ];
			data[ index + 2 ] = rgb[ rgbIndex + 2 ];
			data[ index + 3 ] = a[ i ];
		}
	}
	else
	{
		for( int i(0); i < size; ++i )
		{
			const int index = i * 4;
			const int rgbIndex = index - i;

			data[ index ] = rgb[ rgbIndex ];
			data[ index + 1 ] = rgb[ rgbIndex + 1 ];
			data[ index + 2 ] = rgb[ rgbIndex + 2 ];
			data[ index + 3 ] = 255;
		}
	}

	return data;
}


void ColorConverter::ConvertImageToPixelArray(wxImage *image, fc::dynamic_array2d<Color> &pixels)
{
	const int w = image->GetWidth();
	const int h = image->GetHeight();
	const int size = w * h;

	if( size == 0 )
		return;

	pixels.resize(h, w);

	ubyte *rgb	= image->GetData();
	ubyte *a	= image->GetAlpha();

	if( a && image->HasAlpha() )
	{
		for( int i(0); i < size; ++i )
		{
			const int rgbIndex = i * 4;

			pixels[i].r = rgb[ rgbIndex ];
			pixels[i].g = rgb[ rgbIndex + 1 ];
			pixels[i].b = rgb[ rgbIndex + 2 ];
			pixels[i].a = a[ i ];
		}
	}
	else
	{
		for( int i(0); i < size; ++i )
		{
			const int index = i * 4;
			const int rgbIndex = index - i;

			pixels[i].r = rgb[ rgbIndex ];
			pixels[i].g = rgb[ rgbIndex + 1 ];
			pixels[i].b = rgb[ rgbIndex + 2 ];
			pixels[i].a = 255;
		}
	}
}


wxImage *ColorConverter::ConvertRGBAToImage(const Image* image)
{
	return ConvertRGBAToImage( &image->pixels[0].r, image->pixels.x(), image->pixels.y() );
}


wxImage *ColorConverter::ConvertRGBAToImage(const ubyte* const data, uint w, uint h)
{
	const uint size = w * h;

	if( size == 0 )
		return 0;

	wxImage *image = new wxImage(w, h);
	image->InitAlpha();

	ubyte *rgb = image->GetData();
	ubyte *a = image->GetAlpha();

	for( uint i(0); i < size; ++i )
	{
		const int index = i * 4;
		const int rgbIndex = index - i;

		*(rgb + rgbIndex) = *(data + index);
		*(rgb + rgbIndex + 1) = *(data + index + 1);
		*(rgb + rgbIndex + 2) = *(data + index + 2);
		*(a + i) = *(data + index + 3);
	}

	return image;
}



void ColorConverter::CreateMask(fc::dynamic_array2d<Color> &pixels, bool preserveRgbMask)
{
	//get the top-left pixel
	Color colorToMask = pixels[0];
	CreateMask( pixels, colorToMask, preserveRgbMask );
}


void ColorConverter::CreateMask(fc::dynamic_array2d<Color> &pixels, const Color &colorToMask, bool preserveRgbMask)
{
	Color mask = Color::TransparentBlack();
	if( preserveRgbMask )
		mask = Color(colorToMask.r, colorToMask.g, colorToMask.b, 0 );

	ReplaceColor( pixels, colorToMask, mask );
}


void ColorConverter::ReplaceColor(fc::dynamic_array2d<Color> &pixels, const Color &colorToReplace, const Color &newColor)
{
	fc::replace( pixels.begin(), pixels.end(), colorToReplace, newColor );
}


void ColorConverter::RemoveTileSeparationLinesOldFormat(fc::dynamic_array2d<Color> &pixels, uint tileWidth, uint tileHeight, uint spacing)
{
	if( spacing == 0 )
		return;

	fc::dynamic_array2d<Color> p( pixels.y(), pixels.x() );
	p.assign( Color::Black() );

	const uint w = pixels.x();
	const uint h = pixels.y();

	uint py(0), xHeigth = tileHeight;
	for( uint y(0); y < h; ++y )
	{
		//horizontal row
		if( y == xHeigth )
		{
			y += spacing - 1;
			xHeigth += tileHeight + spacing;

			continue;
		}

		uint px(0), xWidth = tileWidth;
		for( uint x(0); x < w; ++x )
		{
			//vertical row
			if( x == xWidth )
			{
				x += spacing - 1;
				xWidth += tileWidth + spacing;

				continue;
			}

			//pixel is part of the tile, copy it.
			p(py, px) = pixels(y, x);

			++px;
		}
		++py;
	}

	pixels = p;
}



