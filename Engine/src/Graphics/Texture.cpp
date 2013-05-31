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
#include <fc/math.h>

#include "Math/Rect.h"

#include "Graphics/Texture.h"
#include "Graphics/TextureLoader.h"
#include "Graphics/OpenGL.h"

CE_NAMESPACE_BEGIN


Texture::Texture() :
	m_texture		(0),
	m_width			(0),
	m_height		(0),
	m_floatWidth	(0.f),
	m_floatHeight	(0.f),
	m_format		(GL_RGBA),
	m_wrapMode		(GL_CLAMP), //OPENGL_ES - GL_CLAMP_TO_EDGE
	m_filterMode	(GL_NEAREST),//(GL_LINEAR),
	m_internalformat(GL_RGBA),
	m_mipmaps		(false)
{
}


Texture::Texture( const fc::string& filename ) :
	m_texture		(0),
	m_width			(0),
	m_height		(0),
	m_floatWidth	(0.f),
	m_floatHeight	(0.f),
	m_format		(GL_RGBA),
	m_wrapMode		(GL_CLAMP), //OPENGL_ES - GL_CLAMP_TO_EDGE
	m_filterMode	(GL_NEAREST),//(GL_LINEAR),
	m_internalformat(GL_RGBA),
	m_mipmaps		(false)
{
	LoadFromFile(filename);
}


Texture::Texture( int w, int h, int format, int filterMode, int wrapMode, const void *const data ) :
	m_texture		(0),
	m_width			(0),
	m_height		(0),
	m_floatWidth	(0.f),
	m_floatHeight	(0.f),
	m_format		(format),
	m_wrapMode		(wrapMode),
	m_filterMode	(filterMode),
	m_internalformat(GL_RGBA),
	m_mipmaps		(false)
{
	CreateFromData(data, w, h);
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


void Texture::Bind() const
{
	glBindTexture( GL_TEXTURE_2D, m_texture );
}


bool Texture::LoadFromFile( const fc::string& filename )
{
	Point size;
	uchar* ptr = TextureLoader::LoadFromFile(filename, size);
	if(!ptr)
		return false;

	bool ret = CreateFromData(ptr, size.x, size.y);
	TextureLoader::FreePtr(ptr);
	return ret;
}


bool Texture::SaveToFile( const fc::string& filename )
{
	return TextureLoader::SaveToFile(filename, *this);
}


bool Texture::CreateFromData( const void* data, int w, int h )
{
	m_width = w;
	m_height = h;
	m_floatWidth = (float)w;
	m_floatHeight = (float)h;

	if(m_width == 0 || m_height == 0)
		return false;

	//todo: PO2 error?

	if( m_texture == 0 )
	{
		glGenTextures( 1, &m_texture );
	}

	Bind();

	if( m_mipmaps )
	{
		gluBuild2DMipmaps( GL_TEXTURE_2D, m_internalformat, m_width, m_height, m_format, GL_UNSIGNED_BYTE, data );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMode );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMode );
	}
	else
	{
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMode );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMode );
		glTexImage2D( GL_TEXTURE_2D, 0, m_internalformat, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, data );
	}

	return true;
}


void Texture::SetWrapMode( int wrapMode )
{
	m_wrapMode = wrapMode;
	if( m_texture != 0 )
	{
		Bind();
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode );
	}
}


void Texture::SetFilterMode( int filterMode )
{
	m_filterMode = filterMode;
	if( m_texture != 0 )
	{
		Bind();
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMode );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMode );
	}
}


void Texture::UpdateTexture( const Rect& r, ubyte* pixels )
{
	Bind();
	glTexSubImage2D( GL_TEXTURE_2D, 0, r.pos.x, r.pos.y, r.Width(), r.Height(), GL_RGBA, GL_UNSIGNED_BYTE, pixels );
}


bool Texture::GetPixels( ubyte* ptr ) const
{
	if( !IsValid() )
		return false;

	Bind();
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr);

	return true;
}


Vector2 Texture::GetUV( const Point& pos ) const
{
	return GetUV(pos.x, pos.y);
}


Vector2 Texture::GetUV( int x, int y ) const
{
	CE_ASSERT(m_width != 0 && m_height != 0);
	return Vector2( x / m_floatWidth, y / m_floatHeight );
}


Rectf Texture::GetUVRect( const Rect& sourceRect ) const
{
	CE_ASSERT(m_width != 0 && m_height != 0);

	return Rectf(
		(float)sourceRect.Left() / m_floatWidth,
		(float)sourceRect.Top() / m_floatHeight,
		(float)sourceRect.Right() / m_floatWidth,
		(float)sourceRect.Bottom() / m_floatHeight
	);
}


Rect Texture::GetSourceRect( const Rectf& uv ) const
{
	int min_x = fc::iround(m_floatWidth * uv.Left());
	int min_y = fc::iround(m_floatHeight * uv.Top());
	int max_x = fc::iround(m_floatWidth * uv.Right());
	int max_y = fc::iround(m_floatHeight * uv.Bottom());

	return Rect(
		min_x,
		min_y,
		max_x - min_x,
		max_y - min_y
	);
}


int Texture::GetMaxTextureSize()
{
	int maxTextureSize;
	glGetIntegerv( GL_MAX_TEXTURE_SIZE, &maxTextureSize );
	return maxTextureSize;
}



CE_NAMESPACE_END
