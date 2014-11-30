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

#include <fc/algorithm.h>

#include "Math/Rect.h"
#include "Math/Rectf.h"
#include "Math/Color.h"
#include "Math/Colorf.h"
#include "Math/Math.h"

#include "Graphics/OpenGL.h"
#include "Graphics/Image.h"
#include "Graphics/TextureLoader.h"


CE_NAMESPACE_BEGIN


Image::Image() :
	Texture(), m_pixels()
{
}


Image::Image( const String& filename ) :
	Texture(), m_pixels()
{
	LoadFromFile(filename);
}


Image::Image( int w, int h, int filterMode, int wrapMode, const void *const data ) :
	Texture(), m_pixels()
{
	m_wrapMode = wrapMode;
	m_filterMode = filterMode;

	CreateFromData(data, w, h);
}


Image::~Image()
{
}


void Image::Dispose()
{
	Texture::Dispose();
	m_pixels.resize(0, 0);
}


bool Image::CreateFromData( const void* data, int w, int h )
{
	Texture::Dispose();

	bool success = Texture::CreateFromData(data, w, h);
	if( success )
	{
		InternalPackPixels(w, h, (u8*)data);
	}

	return success;
}


bool Image::LoadFromFile( const String& filename )
{
	Point size;
	u8* ptr = TextureLoader::LoadFromFile(filename, size);
	if(!ptr)
		return false;

	bool ret = CreateFromData(ptr, size.x, size.y);
	TextureLoader::FreePtr(ptr);
	return ret;
}


bool Image::SaveToFile( const String& filename )
{
	return TextureLoader::SaveToFile(filename, *this);
}


void Image::CopyPixelArray( array_type& outPixelData )
{
	outPixelData = m_pixels;
}


Color Image::GetPixel( u32 x, u32 y ) const
{
	return m_pixels.at( y, x );
}


void Image::SetPixel( u32 x, u32 y, const Color& pixel )
{
	m_pixels.at( y, x ) = pixel;
}


void Image::MaskColor( const Color& mask )
{
	const Color colorMask
		(
			mask.r, mask.g, mask.b, 0
		);

	fc::replace( m_pixels.begin(), m_pixels.end(), mask, colorMask );
}


void Image::MaskColorRegion( const Rect& r, const Color& mask )
{
	const u32 x1		= (u32)r.Left();
	const u32 x2		= (u32)r.Right();
	const u32 y		= (u32)r.Top();
	const u32 height	= (u32)r.Height();
	const Color colorMask( mask.r, mask.g, mask.b, 0 );

	for( u32 i(0); i < height; ++i )
	{
		array_type::iterator first = m_pixels.iterator_at(y + i, x1);
		array_type::iterator last = m_pixels.iterator_at(y + i, x2);

		fc::replace( first, last, mask, colorMask );
	}
}


void Image::AdjustRed( int red )
{
	AdjustColor( 0, red );
}


void Image::AdjustBlue( int green )
{
	AdjustColor( 1, green );
}


void Image::AdjustGreen( int blue )
{
	AdjustColor( 2, blue );
}


void Image::AdjustAlpha( int alpha )
{
	AdjustColor( 3, alpha );
}


void Image::AdjustColor( u32 colorIndex, int shift )
{
	AdjustColorRegion( colorIndex, shift, Rect(0, 0, Width(), Height()) );
}


void Image::AdjustColorRegion( u32 colorIndex, int shift, const Rect& r )
{
	const int x1	= r.Left();
	const int y1	= r.Top();
	const int x2	= r.Right();
	const int y2	= r.Bottom();

	for( int i(y1); i < y2; ++i )
		for( int j(x1); j < x2; ++j )
		{
			Color& p = m_pixels( i, j );
			p[ colorIndex ] = (u8)Math::Clamp<int>( p[ colorIndex ] + shift, 0, 255 );
		}
}


void Image::SwapColor( u32 firstColorIndex, u32 secondColorIndex )
{
	SwapColorRegion( firstColorIndex, secondColorIndex, Rect(0, 0, Width(), Height()) );
}


void Image::SwapColorRegion( u32 firstColorIndex, u32 secondColorIndex, const Rect& r )
{
	const int x1 = r.Left();
	const int y1 = r.Top();
	const int x2 = r.Right();
	const int y2 = r.Bottom();

	for( int i(y1); i < y2; ++i )
		for( int j(x1); j < x2; ++j )
		{
			Color& p = m_pixels( i, j );
			Math::Swap( p[firstColorIndex], p[secondColorIndex] );
		}
}


void Image::Update()
{
	UpdateRegion( Rect(0, 0, Width(), Height()) );
}


void Image::UpdateRegion( const Rect& r )
{
	Rect thisRect(0, 0, Width(), Height());
	CE_ASSERT(thisRect.Contains(r));

	array_type temp;
	Color* ptr = m_pixels.data();

	//check if we only need to update a portion of the texture
	if( r != thisRect )
	{
		m_pixels.copy_region( (u32)r.pos.x, (u32)r.pos.y, (u32)r.Width(), (u32)r.Height(), temp );
		ptr = temp.data();
	}

	Texture::UpdateTexture(r, (u8*)ptr);
}


void Image::SetPixelArray( const array_type& pixelData )
{
	//TODO:
	m_pixels = pixelData;
	Update();
}


void Image::InternalPackPixels( int width, int height, const u8 *const data )
{
	m_pixels.resize( height, width );

	if(data)
	{
		int i(0);
		for( int k(0); k < height; ++k )
		{
			for( int j(0); j < width; ++j )
			{
				Color *pixel = & m_pixels( k, j );
				(*pixel).r = *(data + i++);
				(*pixel).g = *(data + i++);
				(*pixel).b = *(data + i++);
				(*pixel).a = *(data + i++);
			}
		}
	}
}


CE_NAMESPACE_END

