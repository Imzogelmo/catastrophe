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

#include "Texture.h"

CE_NAMESPACE_BEGIN


struct Glyph
{
	enum GlyphCharacteristics
	{
		MaxSize = 128
	};

	Glyph() : translation(Vector2::Zero), size(Vector2::Zero), uv(Rectf::Zero), advance(0.f)
	{}

	Vector2 translation;
	Vector2 size;
	Rectf uv;
	float advance;

};


enum TextAlignment
{
	AlignLeft = 0,
	AlignCenter,
	AlignRight
};


class Font
{
public:
	typedef fc::vector<Glyph>	vec_type;

	enum FontDefaults
	{
		DefaultFaceSize = -1,
		MinTextureSize = 256,
		MaxTextureSize = 2048,
		DefaultDpi = 96,
		MaxGlyphSize = Glyph::MaxSize
	};

	Font();
	Font( const fc::string& filename, int faceSize, int dpi = DefaultDpi );
	~Font();

	int LoadFromFile( const fc::string& filename, int faceSize, int dpi = DefaultDpi );
	int CreateFromBitmapFontTexture( gluint texture, uint width, uint height );
	int CreateFromPixelData( const ubyte* pixels, uint pixelFormat, uint width, uint height );

	void SetAdvance( int advance );
	void SetLineHeight( int height );

	int GetTextWidth( const fc::string& text ) const;
	int GetTextWidth( const char* first, const char* last ) const;

	Texture* GetTexture() { return &m_texture; }
	const Texture* GetTexture() const { return &m_texture; }
	gluint GetTextureID() const { return m_texture.GetTextureID(); }
	gluint GetFaceSize() const { return m_face_size; }
	int GetLineHeight() const { return m_line_height; }

	Glyph& GetGlyph( ubyte glyph ) { return m_glyphs[ m_glyph_map[glyph] ]; }
	const Glyph& GetGlyph( ubyte glyph ) const { return m_glyphs[ m_glyph_map[glyph] ]; }

	void Dispose();

protected:
	vec_type	m_glyphs;
	int			m_glyph_map[256];
	Texture		m_texture;
	int			m_face_size;
	int			m_line_height;
	int			m_max_advance;

};



CE_NAMESPACE_END
