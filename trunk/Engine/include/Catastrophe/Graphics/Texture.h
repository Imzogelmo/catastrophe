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

#include <fc/string.h>

#include "../Common.h"
#include "../Math/Rect.h"
#include "../Math/Vector2.h"

CE_NAMESPACE_BEGIN

/*
enum eTextureFilter
{
	filterNEAREST = 0x2600,
	filterLINEAR,
	filterNEAREST_MIPMAP_NEAREST,
	filterLINEAR_MIPMAP_NEAREST,
	filterNEAREST_MIPMAP_LINEAR,
	filterLINEAR_MIPMAP_LINEAR
};
*/

class Texture
{
public:
	Texture();
	Texture( int w, int h, int m_format, int m_internalformat, int m_wrapmode, int m_minfilter, int m_magfilter, bool m_mipmaps, const void *const data );

	void Dispose();
	bool CreateTexture( const void* data );
	bool CreateTexture( const void* data, int w, int h );

	bool LoadFromFile( const fc::string& filename );

	ubyte* GetPixels();
	void SetName( const fc::string& name ) { m_name = name; }
	void SetMinFilter( int filter );
	void SetMagFilter( int filter );
	void Bind();
	bool IsValid() const;

	const fc::string& GetName() const { return m_name; }
	//void* GetUserData() const { return m_userdata; }
	gluint GetTextureID() const { return m_texture; }
	int Width() const { return m_width; }
	int Height() const { return m_height; }

	Vector2 GetUV( const Point& pos ) const;
	Vector2 GetUV( int x, int y ) const;
	Rectf GetUVRect( const Rect& sourceRect ) const;
	Rect GetSourceRect( const Rectf& uv ) const;

protected:
	fc::string m_name;
	gluint	m_texture;
	int		m_width;
	int		m_height;
	int		m_format;
	int		m_internalformat;
	int		m_wrapmode;
	int		m_minfilter;
	int		m_magfilter;
	//void	m_userdata;
	bool	m_mipmaps;
};



CE_NAMESPACE_END

