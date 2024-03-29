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

#include "Catastrophe/Core/Containers/String.h"
#include "Catastrophe/Core/Containers/Array2D.h"
#include "Catastrophe/Core/Math/Color.h"
#include "Catastrophe/Core/Math/Rect.h"
#include "Catastrophe/Core/Math/Packed/PackedRect.h"
#include "Catastrophe/Core/IO/Deserializer.h"

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


Texture::Texture( const String& filename ) :
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
	glBindTexture(GL_TEXTURE_2D, m_texture);
}


bool Texture::LoadFromFile( const String& filename )
{
	return LoadFromFile("", filename);
}


bool Texture::LoadFromFile( const String& path, const String& filename )
{
	Point size;
	u8* ptr = TextureLoader::LoadFromFile(path + filename, size);
	if(!ptr)
		return false;

	SetResourceName(filename);

	bool ret = CreateFromData(ptr, size.x, size.y);
	TextureLoader::FreePtr(ptr);
	return ret;
}


bool Texture::Load(Deserializer* deserializer)
{
	const u32 fileSize = deserializer->Size();
	if(fileSize == 0)
		return false;

	Point imageSize;

	//todo: find a way to remove this.
	void* ptrFileMemory = Memory::Allocate(fileSize);

	deserializer->Read(ptrFileMemory, fileSize);
	u8* ptr = (u8*)TextureLoader::LoadFromMemory(ptrFileMemory, fileSize, imageSize);
	if(!ptr)
		return false;

	bool success = CreateFromData(ptr, imageSize.x, imageSize.y);

	Memory::Deallocate(ptrFileMemory, fileSize);
	TextureLoader::FreePtr(ptr);

	return success;
}


bool Texture::SaveToFile( const String& filename )
{
	return TextureLoader::SaveToFile(filename, *this);
}


bool Texture::CreateBlank( const Color& backgroundColor, int w, int h )
{
	Array2D<Color> p(h, w, backgroundColor);
	return CreateFromData( (void*)p.Data(), w, h );
}


bool Texture::CreateFromData( const void* data, int w, int h )
{
	CE_ASSERT(w > 0 && h > 0);

	int maxTextureSize = GetMaxTextureSize();
	w = Math::Min(w, maxTextureSize);
	h = Math::Min(h, maxTextureSize);

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

	glBindTexture(GL_TEXTURE_2D, m_texture);

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
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode );
	}
}


void Texture::SetFilterMode( int filterMode )
{
	m_filterMode = filterMode;
	if( m_texture != 0 )
	{
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMode );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMode );
	}
}


void Texture::UpdateTexture( const Rect& regionRect, u8* pixels )
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, regionRect.x, regionRect.y, regionRect.width, regionRect.height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}


bool Texture::GetPixels( u8* ptr ) const
{
	if( !IsValid() )
		return false;

	Bind();
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr);

	return true;
}


Vector2 Texture::GetUV( const Point& position ) const
{
	return GetUV(position.x, position.y);
}


Vector2 Texture::GetUV( int x, int y ) const
{
	CE_ASSERT(m_width != 0 && m_height != 0);
	return Vector2( x / m_floatWidth, y / m_floatHeight );
}


Rectf Texture::GetUVRect( const Rect& sourceRect ) const
{
	if(m_width == 0)
		return Rectf::Zero;

	return Rectf(
		(float)sourceRect.x / m_floatWidth,
		(float)sourceRect.y / m_floatHeight,
		(float)sourceRect.Right() / m_floatWidth,
		(float)sourceRect.Bottom() / m_floatHeight
	);
}


Rectf Texture::GetUVRect( const PackedRect& sourceRect ) const
{
	if(m_width == 0)
		return Rectf::Zero;

	return Rectf(
		(float)sourceRect.x / m_floatWidth,
		(float)sourceRect.y / m_floatHeight,
		(float)sourceRect.Right() / m_floatWidth,
		(float)sourceRect.Bottom() / m_floatHeight
	);
}


Rect Texture::GetSourceRect( const Rectf& uv ) const
{
	int x = Math::Round(m_floatWidth * uv.Left());
	int y = Math::Round(m_floatHeight * uv.Top());
	int width = Math::Round(m_floatWidth * uv.Right()) - x;
	int height = Math::Round(m_floatHeight * uv.Bottom()) - y;

	return Rect(x, y, width, height);
}


int Texture::GetMaxTextureSize()
{
	int maxTextureSize;
	glGetIntegerv( GL_MAX_TEXTURE_SIZE, &maxTextureSize );
	return maxTextureSize;
}



CE_NAMESPACE_END
