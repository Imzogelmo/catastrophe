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

#include "Texture.h"

#include "../Common.h"
#include "../Math/Color.h"

#include <fc/dynamic_array2d.h>

CE_NAMESPACE_BEGIN


class CE_API Image //TODO: should inherit from Texture...
{
public:
	typedef fc::dynamic_array2d<Color> array_type;

	Image();
	Image( int width, int height, const ubyte *const data = 0, int wrapmode = 0, int minfilter = 0, int magfilter = 0, bool mipmapping = false );
	~Image();

	void SetPixelArray( const array_type& pixelData );
	void CopyPixelArray( array_type& outPixelData );
	const array_type& GetPixelArray() const { return m_pixels; }
	const Color* GetPixelData() const { return m_pixels.data(); }

	void CreateFromPixels( int width, int height, const ubyte *const data = 0, int wrapmode = 0, int minfilter = 0, int magfilter = 0, bool mipmapping = false );

	size_t Width() const { return m_pixels.x(); }
	size_t Height() const { return m_pixels.y(); }
	size_t Size() const { return m_pixels.size(); }

	const Texture& GetTexture() const { return m_texture; }
	gluint GetTextureID() const { return m_texture.GetTextureID(); }

	Color GetPixel( size_t x, size_t y ) const;

	void SetPixel( size_t x, size_t y, const Color& pixel );
	void MaskColor( const Color& mask );
	void MaskColorRegion( const Rect& subrect, const Color& mask );

	void AdjustRed( int red );
	void AdjustBlue( int green );
	void AdjustGreen( int blue );
	void AdjustAlpha( int alpha );
	void AdjustColor( size_t colorIndex, int shift );
	void AdjustColorRegion( size_t colorIndex, int shift, const Rect& subrect );
	void SwapColor( size_t firstColorIndex, size_t secondColorIndex );
	void SwapColorRegion( size_t firstColorIndex, size_t secondColorIndex, const Rect& subrect );

	Rectf GetUVRect( const Rect& subrect );
	
	void Update();
	void UpdateRegion( const Rect& subrect );
	void Dispose();

protected:
	void InternalPackPixels( int width, int height, const ubyte *const data );

	Texture		m_texture;
	array_type	m_pixels;

};


CE_NAMESPACE_END

