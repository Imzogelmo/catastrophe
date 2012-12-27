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

#include <fc/math.h>
#include "Graphics/Font.h"
#include "Util/TexturePacker.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H


CE_NAMESPACE_BEGIN



Font::Font() :
	m_texture(),
	m_face_size(0)
{
	for( int i(0); i < 256; ++i )
		m_glyph_map[i] = 0;
}


Font::Font( const fc::string& filename, int faceSize, int dpi ) :
	m_texture(),
	m_face_size(0)
{
	for( int i(0); i < 256; ++i )
		m_glyph_map[i] = 0;

	LoadFromFile(filename, faceSize, dpi);
}


Font::~Font()
{
	Dispose();
}


void Font::Dispose()
{
	m_texture.Dispose();
}


int Font::LoadFromFile( const fc::string& filename, int faceSize, int dpi )
{
	// current limitation
	if( (size_t)faceSize > MaxGlyphSize )
		faceSize = MaxGlyphSize;

	// todo: break these up for easier reload
	FT_Library library;
	FT_Error error = FT_Init_FreeType(&library);
	if( error )
	{
		LogError("FT_Init_FreeType error");
		return -1;
	}

	FT_Face face;
	error = FT_New_Face(library, filename.c_str(), 0, &face);
	if( error )
	{
		Log("FT_New_Face: error reading file (%s).", filename.c_str());
		return -2;
	}

	FT_F26Dot6 charHeight = faceSize << 6;
	error = FT_Set_Char_Size(face, 0, charHeight, dpi, dpi);
	if( error )
	{
		Log( "FT_Set_Char_Size error: face size(%i) dpi(i).", faceSize, dpi );
		return -3;
	}

	// find available glyphs and map them to char codes.
	int max_glyphs = 0;
	int glyph_index = 0;
	FT_ULong charcode = FT_Get_First_Char(face, (FT_UInt*)&glyph_index);

	while( glyph_index != 0 )
	{
		max_glyphs = fc::clamp(max_glyphs, glyph_index + 1, 256);
		if( charcode < 256 )
		{
			//no unicode or utf-8 support.
			m_glyph_map[charcode] = glyph_index;
		}
		if( max_glyphs > 127 )
			break;

		charcode = FT_Get_Next_Char(face, charcode, (FT_UInt*)&glyph_index);
	}

	//get the closest fit without going under.
	int squareDimensions = faceSize * (int)::ceilf(::sqrtf((float)max_glyphs));
	int tWidth = Math::Min<int>( (int)Math::NextPowerOfTwo(squareDimensions), MaxTextureSize );
	int tHeight = Math::Min<int>( (int)Math::NextPowerOfTwo(squareDimensions), MaxTextureSize );

	m_glyphs.clear();
	m_glyphs.reserve(max_glyphs);
	fc::dynamic_array2d<Color> pixels(tHeight, tWidth);
	fc::dynamic_array2d<Color> glyphPixels( 128, 128 );
	pixels.assign(Color::Black(0));
	glyphPixels.assign(Color::White(0));

	RectangleTexturePacker texturePacker(tWidth, tHeight);
	int maxGlyphTranslationY = 0;
	int maxGlyphHeight = 0;

	FT_GlyphSlot slot = face->glyph;

	for( int i(0); i < max_glyphs; ++i )
	{
		m_glyphs.push_back();
		Glyph & glyph = m_glyphs.back();

		Point size = Point::Zero;
		Point translation = Point::Zero;
		int advance = 0;

		error = FT_Load_Glyph(face, i, FT_LOAD_DEFAULT);
		if( error )
		{
			Log("FT_Load_Glyph (%i) error.", i);
			continue;
		}
		else
		{
			size.x = (int)(slot->metrics.width >> 6);
			size.y = (int)(slot->metrics.height >> 6);
			translation.x = (int)(slot->metrics.horiBearingX >> 6);
			translation.y = (int)((face->size->metrics.ascender - slot->metrics.horiBearingY) >> 6);
			advance = (int)(slot->metrics.horiAdvance >> 6);

			glyph.size.x = (float)size.x;
			glyph.size.y = (float)size.y;
			glyph.translation.x = (float)translation.x;
			glyph.translation.y = (float)translation.y;
			glyph.advance = (float)advance;

			maxGlyphTranslationY = fc::max(translation.y, maxGlyphTranslationY);
			maxGlyphHeight = fc::max(size.y, maxGlyphHeight);
		}

		error = FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
		if( error )
		{
			Log("FT_Render_Glyph error.");
			continue;
		}
		else
		{
			for( int y(0); y < size.y; ++y )
			{
				ubyte* bitmapPixels = slot->bitmap.buffer + slot->bitmap.pitch * y;
				for( int x(0); x < size.x; ++x )
				{
					//only set the alpha channel.
					glyphPixels(y, x).a = bitmapPixels[x];
				}
			}

			Point sourcePos = Point::Zero;
			if( !texturePacker.Pack(size.x + 1, size.y + 1, sourcePos) )
			{
				//this should not happen.
				Log("TexturePacker error: out of space.");
			}

			pixels.write_region( 
				sourcePos.x,
				sourcePos.y,
				size.x,
				size.y,
				glyphPixels 
			);

			glyph.uv.min.x = (float)sourcePos.x / (float)tWidth;
			glyph.uv.min.y = (float)sourcePos.y / (float)tHeight;
			glyph.uv.max.x = (float)(sourcePos.x + size.x) / (float)tWidth;
			glyph.uv.max.y = (float)(sourcePos.y + size.y) / (float)tHeight;
		}

	}

    m_face_size = faceSize;
	m_max_advance = maxGlyphTranslationY;
    m_line_height = (face->size->metrics.height + 63) >> 6;
	if( m_line_height < maxGlyphHeight )
	{
		m_line_height = maxGlyphHeight;
		Log("info: face height lied");
	}

	m_texture.SetMagFilter( 0x2601 );
	if( !m_texture.CreateTexture( pixels.data(), pixels.x(), pixels.y() ) )
		;

	FT_Done_Face( face );
	FT_Done_FreeType( library );

	return 0;
}


void Font::SetAdvance( int advance )
{
	float a = (float)advance;
	for( vec_type::iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it )
	{
		it->advance = a;
	}
}


void Font::SetLineHeight( int height )
{
	m_line_height = height;
}


int Font::GetTextWidth( const fc::string& text ) const
{
	float width(0.f);
	for( fc::string::const_iterator it = text.begin(); it != text.end(); ++it )
	{
		if(*it == '\n')
			break;

		width += GetGlyph((ubyte)*it).advance;
	}

	return fc::iround(width);
}


int Font::GetTextWidth( const char* first, const char* last ) const
{
	float width(0.f);
	for( ; first != last && *first != '\n'; ++first )
	{
		width += GetGlyph(*first).advance;
	}

	return fc::iround(width);
}



CE_NAMESPACE_END

