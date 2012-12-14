// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include "Graphics/Font.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H


CE_NAMESPACE_BEGIN



Font::Font() : m_texture(), m_face_size(0)
{
}


Font::Font( const fc::string& filename, int faceSize ) : m_face_size(0)
{
	LoadFromFile(filename, faceSize);
}


Font::~Font()
{
	Dispose();
}


int Font::LoadFromFile( const fc::string& filename, int faceSize )
{

	// current limitation
	if( (size_t)faceSize > MaxGlyphSize )
		faceSize = MaxGlyphSize;


	// todo: break these up for easier reload
	FT_Library library;

	if ( FT_Init_FreeType( &library ) )
	{
		//_SetError( "FT_Init_FreeType error" );
		return -1;
	}

	FT_Face face;

	if ( FT_New_Face( library, filename.c_str(), 0, &face ) )
	{
		//Log("Font::Load(): error reading file " + filename);
		return -2;
	}

	if( FT_Set_Pixel_Sizes( face, 0, faceSize ) )
	{
		//Log( "FT_Set_Pixel_Sizes error" );
		return -3;
	}


	const uint maxSize = Math::IsPowerOfTwo( faceSize ) ? faceSize : Math::NextPowerOfTwo( faceSize );
	const uint maxArea = (4 * maxSize * maxSize);
	const uint textureWidth = maxSize * 16;
	const uint textureHeight = maxSize * 16;


	m_face_size = faceSize;
	m_line_height = faceSize;

	fc::dynamic_array2d<Color> pixels(textureHeight, textureWidth);
	fc::dynamic_array2d<Color> glyphPixels( maxSize, maxSize );

	uint minYdepth(64);


	for( int i(0); i < 256; i++ )
	{
		if( FT_Load_Glyph( face, FT_Get_Char_Index( face, i ), FT_LOAD_DEFAULT ) )
		{
			//_SetError("FT_Load_Glyph failed");
			return -4;
		}

		FT_Glyph glyph;

		if( FT_Get_Glyph( face->glyph, &glyph ) )
		{
			//_SetError("FT_Get_Glyph failed");
			return -5;
		}

		FT_Glyph_To_Bitmap( &glyph, FT_RENDER_MODE_NORMAL, 0, 1 );

		const FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph) glyph;
		const FT_Bitmap & bitmap = bitmap_glyph->bitmap;


		//re-initialize colors to white
		glyphPixels.assign(Color::White(0));

		const uint bitmapRows	= (uint)bitmap.rows;
		const uint bitmapWidth	= (uint)bitmap.width;

		//copy glyph color to pixels
		for( uint y(0); y < bitmapRows; ++y )
			for( uint x(0); x < bitmapWidth; ++x )
				glyphPixels( y, x ).a = bitmap.buffer[ x + bitmapWidth * y ];


		const float xPos = float((i % 16) * maxSize);
		const float yPos = float(((i & 240) / 16) * maxSize);
		const float yOffset = (float)((faceSize - bitmap.rows) + (bitmap.rows - bitmap_glyph->top));

		m_glyph[i].advance.x		= (float)(face->glyph->advance.x >> 6);
		m_glyph[i].advance.y		= (float)(face->glyph->advance.y >> 6);
		m_glyph[i].size.x			= (float)bitmap.width;
		m_glyph[i].size.y			= (float)bitmap.rows;
		m_glyph[i].translation.x	= (float)bitmap_glyph->left;
		m_glyph[i].translation.y	= (float)yOffset;

		m_glyph[i].uv.min.x			= (xPos / float(textureWidth));
		m_glyph[i].uv.min.y			= (yPos / float(textureHeight));
		m_glyph[i].uv.max.x			= m_glyph[i].uv.min.x + (1.0f / ((float)textureWidth / m_glyph[i].size.x));
		m_glyph[i].uv.max.y			= m_glyph[i].uv.min.y + (1.0f / ((float)textureHeight / m_glyph[i].size.y));


		uint xx = (i % 16) * maxSize;
		uint yy = ((i & 240) / 16) * maxSize;
		pixels.write_region( 
				xx,//(i % 16) * maxSize,
				yy,//((i & 240) / 16) * maxSize,
				maxSize,
				maxSize,
				glyphPixels 
			);


		// find the 'tallest' glyph, whichever one that is...
		const uint YspacingDiff = uint(maxSize - bitmap.rows);
		minYdepth = ( (minYdepth < YspacingDiff) ?  minYdepth : YspacingDiff );

	}

	//todo: 'padding' is stored as translation which causes scaling offsets.
	//for( uint i(0); i < 256; ++i )
		//m_glyph[i].pos.y = (float)minYdepth;


	//set unused pixels to black
	for( fc::dynamic_array2d<Color>::iterator it = glyphPixels.begin(); it != glyphPixels.end(); ++it )
	{
		if(it->a == 0)
		{
			it->r = 0;
			it->g = 0;
			it->b = 0;
		}
	}

	m_texture.SetMagFilter( 0x2601 );
	if( !m_texture.CreateTexture( pixels.data(), pixels.x(), pixels.y() ) )
		;


	FT_Done_Face( face );
	FT_Done_FreeType( library );

	return 0;
}


void Font::Dispose()
{
	m_texture.Dispose();
}


void Font::SetAdvance( int advance )
{
	float a = (float)advance;
	for( size_t i(0); i < 256; ++i )
	{
		m_glyph[i].advance.x = a;
	}
}


int Font::GetTextWidth( const fc::string& text ) const
{
	float width(0.f);
	for( fc::string::const_iterator it = text.begin(); it != text.end(); ++it )
	{
		if(*it == '\n')
			break;

		width += m_glyph[ (ubyte)*it ].advance.x;
	}

	return width;
}


int Font::GetTextWidth( const char* first, const char* last ) const
{
	float width(0.f);
	for( ; first != last && *first != '\n'; ++first )
	{
		width += m_glyph[ (ubyte)*first ].advance.x;
	}

	return width;
}



CE_NAMESPACE_END

