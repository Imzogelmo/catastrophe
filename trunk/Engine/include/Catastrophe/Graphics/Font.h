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
#include <fc/string.h>

#include "../Math/Vector2.h"
#include "../Math/Rectf.h"
#include "../Math/Color.h"

#include "Texture.h"

CE_NAMESPACE_BEGIN


/*
class Glyph
{
public:
	enum eGlyphCharacteristics
	{
		MaxSize = 128
	};

	Glyph() {}
	Glyph( const PackedPoint& advance, const PackedPoint& translation, const PackedPoint& size, const Rectf& uv )
		: m_advance(advance), m_translation(translation), m_size(size), m_uv(uv)
	{}

	PackedPoint GetAdvance( ubyte glyph ) { return m_advance; }
	PackedPoint GetTranslation( ubyte glyph ) { return m_translation; }
	PackedPoint GetSize( ubyte glyph ) { return m_size; }
	const Rectf& GetTexCoords( ubyte glyph ) { return m_uv; }

	
	//Convenience methods. With the exception of advane, these should 
	//generally never need to be tampered with as they are set according
	//to the font metrics as given by the truetype library.
	
	void SetAdvance( const PackedPoint& value ) { m_advance = value; }
	void SetTranslation( const PackedPoint& value ) { m_translation = value; }
	void SetSize( const PackedPoint& value ) { m_size = value; }
	void SetUV( const Rectf& value ) { m_uv = value; }

protected:
	PackedPoint m_advance;
	PackedPoint m_translation;
	PackedPoint m_size;
	Rectf m_uv;

};
*/


//
//TODO
//this, along with font loading, needs
//to be rewritten. Also needs to be able to load
//generic bitmap fonts with standard glyphs
//range from 32 - 96.
// ...possibly bmfonts also.
//
struct Glyph
{
	enum eGlyphCharacteristics
	{
		MaxSize = 128
	};

	//TODO: ...
	//PackedPoint advance;
	//PackedPoint translation;
	//PackedPoint size;
	Vector2 advance;
	Vector2 translation; //TODO only need the y value here.
	Vector2 size;
	Rectf uv;
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
	enum eFontDefaults
	{
		DefaultFaceSize = -1,
		MinTextureSize = 256,
		MaxTextureSize = 2048,
		DefaultDpi = 96,
		MaxGlyphSize = Glyph::MaxSize
	};

	Font();
	Font( const fc::string& filename, int faceSize );
	~Font();

	int LoadFromFile( const fc::string& filename, int faceSize );
	int CreateFromBitmapFontTexture( gluint texture, uint width, uint height );
	int CreateFromPixelData( const ubyte* pixels, uint pixelFormat, uint width, uint height );

	void SetAdvance( int advance );

	int GetTextWidth( const fc::string& text ) const;
	int GetTextWidth( const char* first, const char* last ) const;

	Texture* GetTexture() { return &m_texture; }
	const Texture* GetTexture() const { return &m_texture; }
	gluint GetTextureID() const { return m_texture.GetTextureID(); }
	gluint GetFaceSize() const { return m_face_size; }
	int GetLineHeight() const { return m_line_height; }

	Glyph& GetGlyph( ubyte glyph ) { return m_glyph[ glyph ]; }
	const Glyph& GetGlyph( ubyte glyph ) const { return m_glyph[ glyph ]; }

	void Dispose();

protected:
	Glyph	m_glyph[ 256 ];
	Texture m_texture;
	int		m_face_size;
	int		m_line_height;

};



CE_NAMESPACE_END
