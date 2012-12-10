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

#include <fc/string.h>

#include "Math/Rect.h"

#include "Graphics/Texture.h"
#include "Graphics/TextureLoader.h"
#include "Graphics/OpenGL.h"

CE_NAMESPACE_BEGIN


Texture::Texture() :
	m_texture		(0),
	m_width			(0),
	m_height		(0),
	m_format		(GL_RGBA),
	m_internalformat(GL_RGBA),
	m_wrapmode		(GL_CLAMP), //OPENGL_ES - GL_CLAMP_TO_EDGE
	m_minfilter		(GL_NEAREST),
	m_magfilter		(GL_NEAREST),//(GL_LINEAR),
	m_mipmaps		(false)
{
}


Texture::Texture( int w, int h, int m_format, int m_internalformat, int m_wrapmode, int m_minfilter, int m_magfilter, bool m_mipmaps, const void *const data ) :
	m_texture		(0),
	m_width			(w),
	m_height		(h),
	m_format		(m_format),
	m_internalformat(m_internalformat),
	m_wrapmode		(m_wrapmode),
	m_minfilter		(m_minfilter),
	m_magfilter		(m_magfilter),
	m_mipmaps		(m_mipmaps)
{
	CreateTexture(data);
}


void Texture::Dispose()
{
	if( IsValid() )
		glDeleteTextures( 1, &m_texture );
	m_texture = 0;
}


bool Texture::IsValid() const
{
	return (m_texture != 0 && glIsTexture(m_texture) == GL_TRUE);
}


void Texture::SetMinFilter( int filter )
{
	m_minfilter = filter;
}


void Texture::SetMagFilter( int filter )
{
	m_magfilter = filter;
}


bool Texture::CreateTexture( const void* data, int w, int h )
{
	m_width = w;
	m_height = h;
	return CreateTexture(data);
}


void Texture::Bind()
{
	glBindTexture( GL_TEXTURE_2D, m_texture );
}


bool Texture::LoadFromFile( const fc::string& filename )
{
	Point size;
	uchar* ptr = TextureLoader::LoadFromFile(filename, size);
	if(!ptr)
		return false;

	m_width = size.x;
	m_height = size.y;

	bool ret = CreateTexture(ptr);
	TextureLoader::FreePtr(ptr);
	return ret;
}


bool Texture::CreateTexture( const void* data )
{
	if(m_width == 0 || m_height == 0)
		return false;

	//todo: PO2 error?

	glGenTextures( 1, &m_texture );
	glBindTexture( GL_TEXTURE_2D, m_texture );

	if( m_mipmaps )
	{
		gluBuild2DMipmaps( GL_TEXTURE_2D, m_internalformat, m_width, m_height, m_format, GL_UNSIGNED_BYTE, data );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minfilter );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magfilter );
	}
	else
	{
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapmode );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapmode );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minfilter );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magfilter );
		glTexImage2D( GL_TEXTURE_2D, 0, m_internalformat, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, data );
	}

	return true;
}


ubyte* Texture::GetPixels()
{
	ubyte* pixels = 0;
	if(IsValid())
	{
		int format = GL_RGBA;
		pixels = new ubyte[ m_width *  m_height * 4 ];
		glGetTexImage(GL_TEXTURE_2D, 0, format, GL_UNSIGNED_BYTE, pixels);
	}

	return 0;
}


Vector2 Texture::GetUV( const Point& pos ) const
{
	return GetUV(pos.x, pos.y);
}


Vector2 Texture::GetUV( int x, int y ) const
{
	CE_ASSERT(m_width > 0 && m_height > 0);
	return Vector2( x / (float)m_width, y / (float)m_height );
}


Rectf Texture::GetUVRect( const Rect& r ) const
{
	CE_ASSERT(m_width > 0 && m_height > 0);
	const float w = (float)m_width;
	const float h = (float)m_height;

	return Rectf(
			r.pos.x / w,
			r.pos.y / h,
			r.Right() / w,
			r.Bottom() / h
		);
}


void Texture::GetUVRect( const Rect& r, float* uv ) const
{
	CE_ASSERT(m_width > 0 && m_height > 0);
	const float w = (float)m_width;
	const float h = (float)m_height;

	uv[0] = uv[2] = r.Left() / w;
	uv[1] = uv[7] = r.Top() / h;
	uv[4] = uv[6] = r.Right() / w;
	uv[3] = uv[5] = r.Bottom() / h;
}



CE_NAMESPACE_END
