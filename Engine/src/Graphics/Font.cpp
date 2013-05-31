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


class FreetypeLibrary
{
public:
	static FreetypeLibrary& GetInstance() 
	{
		return m_instance;
	}

	static FT_Library& GetFTLibrary() 
	{
		CE_ASSERT(m_instance.m_refCount > 0);
		return m_instance.m_library;
	}

	void AddRef()
	{
		CE_ASSERT(m_refCount >= 0);

		if( m_refCount == 0 )
		{
			FT_Error error = FT_Init_FreeType(&m_library);
			if( error )
			{
				LogError("FT_Init_FreeType error");
			}
		}

		++m_refCount;
	}

	void ReleaseRef()
	{
		CE_ASSERT(m_refCount > 0);

		--m_refCount;
		if( m_refCount == 0 )
		{
			FT_Done_FreeType( m_library );
		}
	}

private:
	FreetypeLibrary() : m_library(0), m_refCount(0) {}
	FreetypeLibrary( const FreetypeLibrary& ) {}
	FreetypeLibrary& operator =( const FreetypeLibrary& );

	// the freetype library is itself a singleton.
	static FreetypeLibrary m_instance;

	FT_Library	m_library;
	int			m_refCount;

};

FreetypeLibrary FreetypeLibrary::m_instance;



Font::Font() :
	m_texture(),
	m_face_size(0)
{
	InternalInitialize();
}


Font::Font( const fc::string& filename, int faceSize, int dpi ) :
	m_texture(),
	m_face_size(0)
{
	InternalInitialize();
	LoadFromFile(filename, faceSize, dpi);
}


Font::~Font()
{
	FreetypeLibrary::GetInstance().ReleaseRef();
	Dispose();
}


void Font::Dispose()
{
	m_texture.Dispose();
}


void Font::InternalInitialize()
{
	FreetypeLibrary::GetInstance().AddRef();
	::memset( m_glyph_map, 0, sizeof(int) * 256 );
}



int Font::LoadFromFile( const fc::string& filename, int faceSize, int dpi )
{
	// current limitation
	if( (size_t)faceSize > MaxGlyphSize )
		faceSize = MaxGlyphSize;

	FT_Error error = 0;
	FT_Library library = FreetypeLibrary::GetInstance().GetFTLibrary();
	if( !library )
	{
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

	// get the closest fit without going under.
	// (if possible this gets optimized later)
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
			glyphPixels.assign( Color::White(0) );
			for( int y(0); y < size.y; ++y )
			{
				ubyte* bitmapPixels = slot->bitmap.buffer + slot->bitmap.pitch * y;
				for( int x(0); x < size.x; ++x )
				{
					//only set the alpha channel.
					size_t i = glyphPixels.offset(y, x);
					glyphPixels[i].a = bitmapPixels[x];
					if( glyphPixels[i].a == 0 )
						glyphPixels[i] = Color::Black(0);
				}
			}

			// we add a single pixel to the rendered glyphs so that we
			// can use texture filtering on the font faces.
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

			// store the position and size in the glyph so we can access it later.
			glyph.uv.min.x = (float)sourcePos.x;
			glyph.uv.min.y = (float)sourcePos.y;
		}
	}

	m_face_size = faceSize;
	m_max_advance = maxGlyphTranslationY;
	m_line_height = face->size->metrics.height >> 6;
	//m_line_height = (face->size->metrics.height + 63) >> 6;
	if( m_line_height < maxGlyphHeight )
	{
		m_line_height = maxGlyphHeight;
	}

	// we can now try to compress the texture size further.
	int compressedHeight = tHeight;
	while( compressedHeight > faceSize && ((compressedHeight / 2) > texturePacker.GetUsedHeight()) )
	{
		compressedHeight /= 2;
	}

	if( compressedHeight != tHeight )
	{
		tHeight = compressedHeight;
	}

	// now that we know the final texture size, we can
	// iterate through the glyphs and calculate the texture coordinates.
	for( vec_type::iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it )
	{
		float x = it->uv.min.x;
		float y = it->uv.min.y;
		it->uv.min.x = x / (float)tWidth;
		it->uv.min.y = y / (float)tHeight;
		it->uv.max.x = (x + it->size.x) / (float)tWidth;
		it->uv.max.y = (y + it->size.y) / (float)tHeight;
	}

	// todo: make this optional.
	//m_texture.SetMagFilter( 0x2601 );
	if( !m_texture.CreateFromData( pixels.data(), tWidth, tHeight ) )
		return -12;

	FT_Done_Face( face );
	return 0;
}


int Font::InternalLoadGenericBitmapFont( const fc::string& filename, int startCode )
{
	// generic bitmap fonts contain no font metrics and
	// are basically a bunch of rectangles inside a bitmap.

	m_texture.SetFilterMode( 0x2601 );
	if( !m_texture.LoadFromFile(filename) )
		return -1;

	int w = m_texture.Width();
	int h = m_texture.Height();
	int glyphSize = w / 16;
	int numRows = h / glyphSize;
	int numGlyphs = fc::min(numRows * 16, 256 - startCode);

	for( int i(startCode); i < numGlyphs + startCode; ++i )
		m_glyph_map[i] = i - startCode;

	m_glyphs.resize(numGlyphs);
	for( int i(0); i < numGlyphs; ++i )
	{
		m_glyph_map[i + 32] = i;

		Glyph& glyph = m_glyphs[i];
		glyph.size.x = (float)glyphSize;
		glyph.size.y = (float)glyphSize;
		glyph.translation.x = (float)glyphSize;
		glyph.translation.y = (float)glyphSize;
		glyph.advance = (float)glyphSize;

		float xPos = float((i % 16) * glyphSize);
		float yPos = float(((i & 240) / 16) * glyphSize);

		glyph.uv.min.x = xPos / (float)w;
		glyph.uv.min.y = yPos / (float)h;
		glyph.uv.max.x = (xPos + glyphSize) / (float)w;
		glyph.uv.max.y = (yPos + glyphSize) / (float)h;
	}

	m_face_size = glyphSize;
	m_max_advance = glyphSize;
	m_line_height = glyphSize;

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


void Font::SetMaxGlyphHeight( float y )
{
	for( vec_type::iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it )
	{
		Glyph & g = *it;
		if( g.size.y > y )
		{
			float d = 1.f - (y / g.size.y);
			g.uv.min.y += g.uv.Height() * d;
			g.size.y = y;
		}
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

