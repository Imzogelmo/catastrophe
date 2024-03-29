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

#include "Catastrophe/Core/Containers/Array2D.h"
#include "Catastrophe/Core/Math/Color.h"

#include "Catastrophe/Graphics/Common.h"
#include "Catastrophe/Graphics/Font.h"
#include "Catastrophe/Graphics/Texture.h"
#include "Catastrophe/Graphics/TextureLoader.h"
#include "Util/TexturePacker.h"

#if CE_SUPPORT_FREETYPE
	#include <ft2build.h>
	#include FT_FREETYPE_H
	#include FT_GLYPH_H
#endif

CE_NAMESPACE_BEGIN


#if CE_SUPPORT_FREETYPE
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
				LogError("FT_Init_FreeType error: (%i)", error);
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
#endif


Font::Font() :
	m_texture(),
	m_faceSize(0)
{
	InternalInitialize();
}


Font::Font( const String& filename, int faceSize, int dpi ) :
	m_texture(),
	m_faceSize(0)
{
	InternalInitialize();
	LoadFromFile(filename, faceSize, dpi);
}


Font::~Font()
{
#if CE_SUPPORT_FREETYPE
	FreetypeLibrary::GetInstance().ReleaseRef();
#endif

	Dispose();
}


void Font::Dispose()
{
	m_texture.Dispose();
}


void Font::InternalInitialize()
{
#if CE_SUPPORT_FREETYPE
	FreetypeLibrary::GetInstance().AddRef();
#endif

	::memset( m_glyphMap, 0, sizeof(int) * 256 );
}



int Font::LoadFromFile( const String& filename )
{
	return LoadFromFile("", filename, 16);
}


int Font::LoadFromFile( const String& path, const String& filename )
{
	return LoadFromFile(path, filename, 16);
}


int Font::LoadFromFile( const String& filename, int faceSize, int dpi )
{
	return LoadFromFile("", filename, faceSize, dpi);
}


int Font::LoadFromFile( const String& path, const String& filename, int faceSize, int dpi )
{
	if( filename.Empty() )
		return 1;

	SetResourceName(filename);

	//String fileExtension = filename.Substring(filename.size() - 3, 3);
	String fileExtension = filename.GetFileExtension(true);
	if( fileExtension == "bmp" || fileExtension == "png" || fileExtension == "tga" )
	{
		//return InternalLoadBitmapFont(path + filename);
		//return InternalLoadShadowedStripFont(path + filename, 32, 2);
		return InternalLoadAsciiStripFont(path + filename, 32);
	}

#if CE_SUPPORT_FREETYPE
	// current limitation
	if( (u32)faceSize > MaxGlyphSize )
		faceSize = MaxGlyphSize;

	FT_Error error = 0;
	FT_Library library = FreetypeLibrary::GetInstance().GetFTLibrary();
	if( !library )
	{
		return -1;
	}

	FT_Face face;
	error = FT_New_Face(library, filename.CString(), 0, &face);
	if( error )
	{
		Log("FT_New_Face error (%i)", error);
		FT_Done_Face(face);
		return -2;
	}

	int fszs = face->num_fixed_sizes ;
	FT_Bitmap_Size* bs = face->available_sizes ;
	for(int i(0); i < fszs; ++i)
	{
		Log("w (%i)", bs[i].width);
		Log("h (%i)", bs[i].height);
		Log("x_ppem (%i)", bs[i].x_ppem);
		Log("y_ppem (%i)", bs[i].y_ppem);
	}


	FT_F26Dot6 charHeight = faceSize << 6;
	error = FT_Set_Char_Size(face, 0, charHeight, dpi, dpi);
	if( error )
	{
		Log("FT_Set_Char_Size error (%i) face size(%i) dpi(%i).", error, faceSize, dpi);
		FT_Done_Face(face);
		return -3;
	}


	/*
	error = FT_Set_Pixel_Sizes(face, 0, faceSize);
	if( error )
	{
		Log( "FT_Set_Pixel_Sizes error: face size(%i) dpi(i).", faceSize, dpi );
		return -3;
	}
	*/


	// find available glyphs and map them to char codes.
	int max_glyphs = 0;
	int glyph_index = 0;
	FT_ULong charcode = FT_Get_First_Char(face, (FT_UInt*)&glyph_index);

	while( glyph_index != 0 )
	{
		max_glyphs = Clamp(max_glyphs, glyph_index + 1, 256);
		if( charcode < 256 )
		{
			//no unicode or utf-8 support.
			m_glyphMap[charcode] = glyph_index;
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

	m_glyphs.Clear();
	m_glyphs.Reserve(max_glyphs);
	Array2D<Color> pixels(tHeight, tWidth);
	Array2D<Color> glyphPixels( 128, 128 );
	pixels.fill(Color::Black(0));
	glyphPixels.fill(Color::White(0));

	RectangleTexturePacker texturePacker(tWidth, tHeight);
	int maxGlyphTranslationY = 0;
	int maxGlyphHeight = 0;

	FT_GlyphSlot slot = face->glyph;

	for( int i(0); i < max_glyphs; ++i )
	{
		m_glyphs.Add();
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
			//glyph.translation.y = (float)translation.y - faceSize/2; // TEST!!!!!
			glyph.advance = (float)advance;

			maxGlyphTranslationY = Math::Max(translation.y, maxGlyphTranslationY);
			maxGlyphHeight = Math::Max(size.y, maxGlyphHeight);
		}

		error = FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
	//	error = FT_Render_Glyph(slot, FT_RENDER_MODE_MONO);
		if( error )
		{
			Log("FT_Render_Glyph error.");
			continue;
		}
		else
		{
			glyphPixels.fill( Color::White(0) );
			for( int y(0); y < size.y; ++y )
			{
				u8* bitmapPixels = slot->bitmap.buffer + slot->bitmap.pitch * y;
				for( int x(0); x < size.x; ++x )
				{
					//only set the alpha channel.
					u32 i = glyphPixels.offset(y, x);

					//Log("gray = %i", (int)bitmapPixels[x]);
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

	m_faceSize = faceSize;
	m_maxAdvance = maxGlyphTranslationY;
	m_lineHeight = face->size->metrics.height >> 6;
	//m_lineHeight = (face->size->metrics.height + 63) >> 6;
	if( m_lineHeight != maxGlyphHeight )
	{
		m_lineHeight = maxGlyphHeight;
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
	for( GlyphVectorType::Iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it )
	{
		float x = it->uv.min.x;
		float y = it->uv.min.y;
		it->uv.min.x = x / (float)tWidth;
		it->uv.min.y = y / (float)tHeight;
		it->uv.max.x = (x + it->size.x) / (float)tWidth;
		it->uv.max.y = (y + it->size.y) / (float)tHeight;
	}

	// todo: make this optional.
	m_texture.SetFilterMode( 0x2601 );
	if( !m_texture.CreateFromData( pixels.data(), tWidth, tHeight ) )
		return -12;

	FT_Done_Face(face);
#endif

	return 0;
}


int Font::InternalLoadGenericBitmapFont( const String& filename, int startCode )
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
	int numGlyphs = Math::Min(numRows * 16, 256 - startCode);

	for( int i(startCode); i < numGlyphs + startCode; ++i )
		m_glyphMap[i] = i - startCode;

	m_glyphs.Resize(numGlyphs);

	for( int i(0); i < numGlyphs; ++i )
	{
		m_glyphMap[i + 32] = i;

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

	m_faceSize = glyphSize;
	m_maxAdvance = glyphSize;
	m_lineHeight = glyphSize;

	return 0;
}


int Font::InternalLoadBitmapFont( const String& filename, int startCode )
{
	CE_ASSERT(startCode > 0 && startCode < 128);

	// bitmap font metrics are generated by pixel offsets from
	// top, bottom, left, right. advance is calculated by (right - left + 1).

	Point textureSize;
	Array2D<Color> pixels;

	if( !InternalLoadPixelArrayFromFile(filename, pixels, textureSize) )
	{
		return -1;
	}

	float textureWidth = (float)textureSize.x;
	float textureHeight = (float)textureSize.y;
	Color maskColor = pixels[0];

	// calculate bounding rectangles.
	int numRows = 8 - ((startCode + 15) / 16);
	int numColumns = 16;
	int numGlyphs = Math::Min(numRows * 16, 128 - startCode);

	m_glyphs.Resize(numGlyphs);

	// set character map.
	for( int i(startCode); i < numGlyphs + startCode; ++i )
		m_glyphMap[i] = i - startCode;

	int blockWidth = textureSize.x / numColumns;
	int blockHeight = textureSize.y / numRows;

	int currentChar(0);

	for( int row(0); row < numRows; ++row )
	{
		for( int col(0); col < numColumns; ++col )
		{
			Glyph& glyph = m_glyphs[currentChar];

			// rect pixel uv bounds
			int left = col * blockWidth;
			int right = (col + 1) * blockWidth;
			int top = row * blockHeight;
			int bottom = (row + 1) * blockHeight;

			int minX = left;
			int maxX = right;
			int minY = top;
			int maxY = bottom;

			// left
			for( int x(minX); x < maxX; ++x )
			{
				for( int y(minY); y < maxY; ++y )
				{
					if( pixels.at(y, x).a != 0 || pixels.at(y, x) != maskColor )
					{
						left = x;

						// break loop
						x = maxX;
						y = maxY;
					}
				}
			}

			// right
			for( int x(maxX - 1); x >= minX; --x )
			{
				for( int y(minY); y < maxY; ++y )
				{
					if( pixels.at(y, x).a != 0 || pixels.at(y, x) != maskColor )
					{
						right = x + 1;

						// break loop
						x = minX;
						y = maxY;
					}
				}
			}

			// top
			for( int y(minY); y < maxY; ++y )
			{
				for( int x(minX); x < maxX; ++x )
				{
					if( pixels.at(y, x).a != 0 || pixels.at(y, x) != maskColor )
					{
						top = y;

						// break loop
						x = maxX;
						y = maxY;
					}
				}
			}

			// bottom
			for( int y(maxY - 1); y >= minY; --y )
			{
				for( int x(minX); x < maxX; ++x )
				{
					if( pixels.at(y, x).a != 0 || pixels.at(y, x) != maskColor )
					{
						bottom = y + 1;

						// break loop
						x = maxX;
						y = minY;
					}
				}
			}

			glyph.advance = (float)(right - left + 1);
			glyph.size.x = (float)(right - left);
			glyph.size.y = (float)(bottom - top);
			glyph.translation.x = (float)(0.f);
			glyph.translation.y = (float)(top - (row * blockHeight));

			glyph.uv.min.x = left / textureWidth;
			glyph.uv.min.y = top / textureHeight;
			glyph.uv.max.x = right / textureWidth;
			glyph.uv.max.y = bottom / textureHeight;

			m_maxAdvance = Math::Max(m_maxAdvance, (int)glyph.advance);

			// Abort if we are out of bounds.
			if( ++currentChar >= numGlyphs )
			{
				row = numRows;
				col = numColumns;
			}
		}
	}

	// Fix the space character.
	//m_glyphs[' '].size.x = float(blockWidth / 2.f);
	GetGlyph(' ').advance = float((blockWidth / 2.f) + 1);
	//m_glyphs[' '].advance /= 2.f;

	m_faceSize = Math::Max(blockWidth, blockHeight);
	m_lineHeight = blockHeight;

	// create the texture.
	//m_texture.SetFilterMode( 0x2601 );
	m_texture.CreateFromData( (void*)pixels.Data(), pixels.Width(), pixels.Height() );

	return 0;
}


int Font::InternalLoadAsciiStripFont( const String& filename, int startCode )
{
	Point textureSize;
	Array2D<Color> pixels;
	if( !InternalLoadPixelArrayFromFile(filename, pixels, textureSize) )
	{
		return -1;
	}

	m_glyphs.Reserve(127 - startCode); // best guess

	int w = textureSize.x;
	int h = textureSize.y;
	int i = 0;

	// Get the mask color to text rows against
	Color maskColor = pixels[0];

	for( int x(0); x < w; ++x )
	{
		for( int y(0); y < h; ++y )
		{
			Color color = pixels(y, x);
			if(color != maskColor) // Found the start of glyph
			{
				int x1 = x;
				int y1 = 0;
				int x2 = 0;
				int y2 = 0;

				while(++x < w)
				{
					for( y = 0; y < h; ++y )
						if(pixels(y, x) != maskColor)
							// Scan next column until we find a break.
							break;

					if(y == h)
					{
						x2 = x;
						y2 = y;
						break;
					}

				}

				if(x == w)
				{
					// break loop
					y = h;
					break;
				}

				Glyph glyph;
				glyph.size.x = (float)(x2 - x1);
				glyph.size.y = (float)(y2 - y1);
				glyph.translation.x = 0.f;
				glyph.translation.y = 0.f;
				glyph.advance = (float)((x2 - x1) + 1);

				glyph.uv.min.x = x1 / (float)w;
				glyph.uv.min.y = y1 / (float)h;
				glyph.uv.max.x = x2 / (float)w;
				glyph.uv.max.y = y2 / (float)h;

				// Special case:
				// The space char has no glyph, so we can only accurately extrapolate the advance
				// by counting the pixels that have been advanced.
				if(i + startCode == (int)' ')
				{
					glyph.advance = (float)x;

					//fixme
					m_glyphs.Add(glyph);
					m_glyphMap[i + startCode] = i;
					++i;
				}

				m_glyphs.Add(glyph);
				m_glyphMap[i + startCode] = i;
				++i;

				// advance column
				y = h;
			}
		}

		// Too many glyphs, break. (...bad font?)
		if(i + startCode > 255)
			break;
	}

	// Free up any unused memory to keep the font lean.
	m_glyphs.ShrinkToFit();

	m_faceSize = h;
	m_maxAdvance = 12;
	m_lineHeight = h;

	// Finally, create the texture from the raw pixel data
	m_texture.CreateFromData( (void*)pixels.Data(), pixels.Width(), pixels.Height() );

	return 0;
}


int Font::InternalLoadShadowedStripFont( const String& filename, int startCode, int shadowOffset )
{
	Point textureSize;
	Array2D<Color> pixels;
	if( !InternalLoadPixelArrayFromFile(filename, pixels, textureSize) )
	{
		return -1;
	}

	m_glyphs.Reserve(127 - startCode); // best guess

	int w = textureSize.x;
	int h = textureSize.y / 2; // Upper half contains glyphs
	int i = 0;
	int cumulativeOffsetX = shadowOffset;

	Array2D<Color> tile; // temporary array

	// The actual pixel array uploaded to the texture.
	Array2D<Color> internalPixels(h + shadowOffset, w, Color::TransparentBlack());

	// Get the mask color to text rows against
	Color maskColor = pixels[0];

	for( int x(0); x < w; ++x )
	{
		for( int y(0); y < h; ++y )
		{
			Color color = pixels(y, x);
			if(color != maskColor) // Found the start of glyph
			{
				int x1 = x;
				int y1 = 0;
				int x2 = 0;
				int y2 = 0;

				while(++x < w)
				{
					for( y = 0; y < h; ++y )
						if(pixels(y, x) != maskColor)
							// Scan next column until we find a break.
							break;

					if(y == h)
					{
						x2 = x;
						y2 = y;
						break;
					}

				}

				if(x == w)
				{
					// break loop
					y = h;
					break;
				}

				int maxIX = (x2 - x1) + 1;
				pixels.CopyRegion(x1, y, maxIX, y, tile);

				// Copy the shadow data first
				internalPixels.WriteRegion(x1 + cumulativeOffsetX, shadowOffset, maxIX, y, tile);

				for( int iy(0); iy < h; ++iy )
				{
					for( int ix(0); ix < maxIX; ++ix )
					{
						//Color alphaBlendedColor = pixels(iy, x1 + ix).AlphaBlend( tile(iy, ix) );
						Color alphaBlendedColor = pixels(iy, x1 + ix).AlphaBlend( internalPixels(iy, x1 + ix + cumulativeOffsetX - shadowOffset) );
						internalPixels(iy, x1 + ix + cumulativeOffsetX - shadowOffset) = alphaBlendedColor;
					}
				}

				cumulativeOffsetX += shadowOffset;

				Glyph glyph;
				glyph.size.x = (float)((x2 - x1) + shadowOffset);
				glyph.size.y = (float)y;
				glyph.translation.x = 0.f;
				glyph.translation.y = 0.f;
				glyph.advance = (float)((x2 - x1) + shadowOffset + 1);

				glyph.uv.min.x = x1 / (float)internalPixels.Width();
				glyph.uv.min.y = y1 / (float)internalPixels.Height();
				glyph.uv.max.x = x2 / (float)internalPixels.Width();
				glyph.uv.max.y = y2 / (float)internalPixels.Height();

				// Special case:
				// The space char has no glyph, so we can only accurately extrapolate the advance
				// by counting the pixels that have been advanced.
				if(i + startCode == (int)' ')
				{
					Glyph g = glyph;
					g.advance = (float)x;

					//fixme
					m_glyphs.Add(g);
					m_glyphMap[i + startCode] = i;
					++i;
				}

				m_glyphs.Add(glyph);
				m_glyphMap[i + startCode] = i;
				++i;

				// advance column
				y = h;
			}
		}

		// Too many glyphs, break. (...bad font?)
		if(i + startCode > 127)
			break;
	}

	// Free up any unused memory to keep the font lean.
	m_glyphs.ShrinkToFit();

	m_faceSize = h;
	m_maxAdvance = 14;
	m_lineHeight = h;

	//Debug save
	TextureLoader::SaveToFile("testShadowFont.png", internalPixels.Data(), internalPixels.Width(), internalPixels.Height());

	// Finally, create the texture from the raw pixel data
	m_texture.CreateFromData( (void*)internalPixels.Data(), internalPixels.Width(), internalPixels.Height() );

	return 0;
}


bool Font::InternalLoadPixelArrayFromFile(const String& filename, Array2D<Color>& pixels, Point& textureSize, bool maskColor)
{
	u8* ptr = TextureLoader::LoadFromFile(filename, textureSize);
	if( ptr == null || textureSize.IsZero() )
	{
		return false;
	}

	pixels.Resize(textureSize.y, textureSize.x);
	for( u32 i(0); i < pixels.Size(); ++i )
	{
		u32 offset = i * 4;
		pixels[i].r = ptr[offset];
		pixels[i].g = ptr[offset + 1];
		pixels[i].b = ptr[offset + 2];
		pixels[i].a = ptr[offset + 3];
	}

	TextureLoader::FreePtr(ptr);

	if(maskColor)
	{
		// mask top-left pixel color
		Color colorToMask = pixels[0];
		Color maskColor(colorToMask.r, colorToMask.b, colorToMask.g, 0);
		for( u32 i(0); i < pixels.Size(); ++i )
		{
			if( pixels[i] == colorToMask )
				pixels[i] = maskColor;
		}
	}

	return true;
}


void Font::SetAdvance( int advance )
{
	float a = (float)advance;
	for( GlyphVectorType::Iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it )
	{
		it->advance = a;
	}
}


void Font::SetMaxGlyphHeight( float y )
{
	for( GlyphVectorType::Iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it )
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
	m_lineHeight = height;
}


int Font::GetTextWidth( const String& text ) const
{
	return GetTextWidth(text.begin(), text.end());
}


int Font::GetTextWidth( const char* first, const char* last ) const
{
	float width(0.f);
	for( ; first != last && *first != '\n'; ++first )
	{
		width += GetGlyph(*first).advance;
	}

	return Math::Round(width);
}



CE_NAMESPACE_END

