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

class CE_API Texture
{
public:
	Texture();
	Texture( const fc::string& filename );
	Texture( int w, int h, int format, int filterMode, int wrapMode, const void *const data );

	void Dispose();
	bool CreateFromData( const void* data, int w, int h );

	bool LoadFromFile( const fc::string& filename );
	bool SaveToFile( const fc::string& filename );

	void SetWrapMode( int wrapMode );
	void SetFilterMode( int filterMode );

	/// Binds this texture to the gpu.
	void Bind() const;

	/// True if this is a valid texture in gpu memory.
	bool IsValid() const;

	/// Update pixel area. pixels must be large enough for rect.
	void UpdateTexture( const Rect& subRect, ubyte* pixels );

	void SetName( const fc::string& name ) { m_name = name; }
	const fc::string& GetName() const { return m_name; }
	//void* GetUserData() const { return m_userdata; }
	int Width() const { return m_width; }
	int Height() const { return m_height; }
	float Widthf() const { return m_floatWidth; }
	float Heightf() const { return m_floatHeight; }

	/// Gets the textures pixel data. ptr must be large enough to hold the data.
	bool GetPixels( ubyte* ptr ) const;

	/// Gets the OpenGL id of this texture.
	gluint GetTextureID() const { return m_texture; }

	/// Gets the normalized uv coords from a point on the texture.
	Vector2 GetUV( const Point& pos ) const;
	Vector2 GetUV( int x, int y ) const;

	/// Gets the normalized uv coords from a source rectangle.
	Rectf GetUVRect( const Rect& sourceRect ) const;

	/// Retrieves the source rect, in pixel size, from a uv rect.
	Rect GetSourceRect( const Rectf& uv ) const;

	/// Gets the max texture size that can be uploaded to the gpu.
	static int GetMaxTextureSize();

protected:
	fc::string m_name;
	gluint	m_texture;
	int		m_width;
	int		m_height;
	float	m_floatWidth;
	float	m_floatHeight;
	int		m_format;
	int		m_wrapMode;
	int		m_filterMode;
	//void	m_userdata;
	int		m_internalformat;
	bool	m_mipmaps;
};



CE_NAMESPACE_END

