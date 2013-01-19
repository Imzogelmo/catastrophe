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


CE_NAMESPACE_BEGIN


Image::Image() : m_pixels(), m_texture()
{
}


Image::Image( int width, int height, const ubyte *const data, int wrapmode, int minfilter, int magfilter, bool mipmapping )
	: m_pixels(), m_texture()
{
	CreateFromPixels( width, height, data, wrapmode, minfilter, magfilter, mipmapping );
}


Image::~Image()
{
}


void Image::CreateFromPixels( int width, int height, const ubyte *const data, int wrapmode, int minfilter, int magfilter, bool mipmapping )
{
	if(m_texture.IsValid())
	{
		m_texture.Dispose();
		m_texture = Texture();
	}

	wrapmode = wrapmode;
	minfilter = minfilter;
	magfilter = magfilter;
	mipmapping = mipmapping;

	InternalPackPixels( width, height, data );
	m_texture.CreateTexture(data, width, height);
}


void Image::CopyPixelArray( array_type& outPixelData )
{
	outPixelData = m_pixels;
}


Color Image::GetPixel( size_t x, size_t y ) const
{
	return m_pixels.at( y, x );
}


void Image::SetPixel( size_t x, size_t y, const Color& pixel )
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
	const size_t x1		= (size_t)r.Left();
	const size_t x2		= (size_t)r.Right();
	const size_t y		= (size_t)r.Top();
	const size_t height	= (size_t)r.Height();
	const Color colorMask( mask.r, mask.g, mask.b, 0 );

	for( size_t i(0); i < height; ++i )
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


void Image::AdjustColor( size_t colorIndex, int shift )
{
	AdjustColorRegion( colorIndex, shift, Rect(0, 0, Width(), Height()) );
}


void Image::AdjustColorRegion( size_t colorIndex, int shift, const Rect& r )
{
	const int x1	= r.Left();
	const int y1	= r.Top();
	const int x2	= r.Right();
	const int y2	= r.Bottom();

	for( int i(y1); i < y2; ++i )
		for( int j(x1); j < x2; ++j )
		{
			Color& p = m_pixels( i, j );
			p[ colorIndex ] = (ubyte)Math::Clamp<int>( p[ colorIndex ] + shift, 0, 255 );
		}
}


void Image::SwapColor( size_t firstColorIndex, size_t secondColorIndex )
{
	SwapColorRegion( firstColorIndex, secondColorIndex, Rect(0, 0, Width(), Height()) );
}


void Image::SwapColorRegion( size_t firstColorIndex, size_t secondColorIndex, const Rect& r )
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


Rectf Image::GetUVRect( const Rect& r )
{
	return m_texture.GetUVRect(r);
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
		m_pixels.copy_region( (uint)r.pos.x, (uint)r.pos.y, (uint)r.Width(), (uint)r.Height(), temp );
		ptr = temp.data();
	}

	m_texture.Bind();
	glTexSubImage2D( GL_TEXTURE_2D, 0, r.pos.x, r.pos.y, r.Width(), r.Height(), GL_RGBA, GL_UNSIGNED_BYTE, ptr );
}


void Image::Dispose()
{
	m_texture.Dispose();
	m_pixels.resize(0, 0);
}


void Image::SetPixelArray( const array_type& pixelData )
{
	//TODO:
	m_pixels = pixelData;
	Update();
}


void Image::InternalPackPixels( int width, int height, const ubyte *const data )
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

