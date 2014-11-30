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

#include <fc/dynamic_array2d.h>
#include <fc/vector.h>
#include <fc/string.h>

#include "../Math/Vector2.h"
#include "../Math/Rectf.h"
#include "../Math/Color.h"
#include "../Resource/GraphicsResource.h"

#include "TextAlignment.h"
#include "Texture.h"

CE_NAMESPACE_BEGIN


struct Glyph
{
	Glyph() : translation(Vector2::Zero), size(Vector2::Zero), uv(Rectf::Zero), advance(0.f)
	{}

	Vector2 translation;
	Vector2 size;
	Rectf uv;
	float advance;

};


class CE_API Font : public GraphicsResource
{
public:
	typedef fc::vector<Glyph>	vec_type;

	enum FontDefaults
	{
		DefaultFaceSize = -1,
		MinTextureSize = 256,
		MaxTextureSize = 2048,
		DefaultDpi = 72,
		MaxGlyphSize = 128
	};

	/*
	enum FontType
	{
		Type_TrueType,
		Type_Bitmap
	};
	*/

	Font();
	Font( const String& filename, int faceSize, int dpi = DefaultDpi );
	~Font();

	int LoadFromFile( const String& filename );
	int LoadFromFile( const String& path, const String& filename );
	int LoadFromFile( const String& filename, int faceSize, int dpi = DefaultDpi );
	int LoadFromFile( const String& path, const String& filename, int faceSize, int dpi = DefaultDpi );
	//int CreateFromBitmapFontTexture( gluint texture, u32 width, u32 height );
	//int CreateFromPixelData( const u8* pixels, u32 pixelFormat, u32 width, u32 height );

	void SetAdvance( int advance );
	void SetLineHeight( int height );
	void SetMaxGlyphHeight( float y );

	int GetTextWidth( const String& text ) const;
	int GetTextWidth( const char* first, const char* last ) const;

	Texture* GetTexture() const { return const_cast<Texture*>(&m_texture); }
	gluint GetTextureID() const { return m_texture.GetTextureID(); }
	gluint GetFaceSize() const { return m_faceSize; }
	int GetLineHeight() const { return m_lineHeight; }

	Glyph& GetGlyph( u8 glyph ) { return m_glyphs[ m_glyphMap[glyph] ]; }
	const Glyph& GetGlyph( u8 glyph ) const { return m_glyphs[ m_glyphMap[glyph] ]; }

	void Dispose();

protected:
	void InternalInitialize();
	int InternalLoadGenericBitmapFont( const String& filename, int startCode = 32 );
	int InternalLoadBitmapFont( const String& filename, int startCode = 32 );

	vec_type	m_glyphs;
	int			m_glyphMap[256];
	Texture		m_texture;
	int			m_faceSize;
	int			m_lineHeight;
	int			m_maxAdvance;

};



CE_NAMESPACE_END
