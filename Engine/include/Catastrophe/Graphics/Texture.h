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

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/Math/Rect.h"
#include "Catastrophe/Core/Math/Vector2.h"
#include "Catastrophe/Core/Resource/Resource.h"
#include "Catastrophe/Graphics/Common.h"

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

class CE_API Texture : public Resource
{
public:
	Texture();
	Texture( const String& filename );
	Texture( int w, int h, int format, int filterMode, int wrapMode, const void *const data );

	void Dispose();
	bool CreateBlank( const Color& backgroundColor, int w, int h );
	bool CreateFromData( const void* data, int w, int h );

	bool LoadFromFile( const String& filename );
	bool LoadFromFile( const String& path, const String& filename );

	bool Load(Deserializer* deserializer) override;

	bool SaveToFile( const String& filename );

	void SetWrapMode( int wrapMode );
	void SetFilterMode( int filterMode );

	/// Binds this texture to the gpu.
	void Bind() const;

	/// True if this is a valid texture in gpu memory.
	bool IsValid() const;

	/// Update pixel area. pixels must be large enough for rect.
	void UpdateTexture( const Rect& subRect, u8* pixels );

	int Width() const { return m_width; }
	int Height() const { return m_height; }
	float Widthf() const { return m_floatWidth; }
	float Heightf() const { return m_floatHeight; }

	/// Gets the textures pixel data. ptr must be large enough to hold the data.
	bool GetPixels( u8* ptr ) const;

	/// Gets the OpenGL id of this texture.
	u32 GetTextureID() const { return m_texture; }

	/// Gets the normalized uv coords from a point on the texture.
	Vector2 GetUV( const Point& position ) const;
	Vector2 GetUV( int x, int y ) const;

	/// Gets the texture coordinates coords from a source rectangle.
	Rectf GetUVRect( const Rect& sourceRect ) const;

	/// Gets the texture coordinates from a source rectangle.
	Rectf GetUVRect( const PackedRect& sourceRect ) const;

	/// Retrieves the source rect, in pixel size, from a uv rect.
	Rect GetSourceRect( const Rectf& uv ) const;

	/// Gets the max texture size that can be uploaded to the gpu.
	static int GetMaxTextureSize();

protected:
	u32	m_texture;
	int		m_width;
	int		m_height;
	float	m_floatWidth;
	float	m_floatHeight;
	int		m_format;
	int		m_wrapMode;
	int		m_filterMode;
	int		m_internalformat;
	bool	m_mipmaps;
};



CE_NAMESPACE_END

