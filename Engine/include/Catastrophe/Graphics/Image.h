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


class CE_API Image : public Texture
{
public:
	typedef fc::dynamic_array2d<Color> array_type;

	Image();
	Image( const String& filename );
	Image( int w, int h, int filterMode, int wrapMode, const void *const data );
	~Image();

	void Dispose();
	bool CreateFromData( const void* data, int w, int h );
	bool LoadFromFile( const String& filename );
	bool SaveToFile( const String& filename );

	void SetPixelArray( const array_type& pixelData );
	void CopyPixelArray( array_type& outPixelData );

	bool GetPixels( u8* ) const;
	array_type& GetPixelArray() { return m_pixels; }
	const array_type& GetPixelArray() const { return m_pixels; }
	const Color* GetPixelData() const { return m_pixels.data(); }

	u32 Size() const { return m_pixels.size(); }
	Color GetPixel( u32 x, u32 y ) const;

	void SetPixel( u32 x, u32 y, const Color& pixel );
	void MaskColor( const Color& mask );
	void MaskColorRegion( const Rect& subrect, const Color& mask );

	void AdjustRed( int red );
	void AdjustBlue( int green );
	void AdjustGreen( int blue );
	void AdjustAlpha( int alpha );
	void AdjustColor( u32 colorIndex, int shift );
	void AdjustColorRegion( u32 colorIndex, int shift, const Rect& subrect );
	void SwapColor( u32 firstColorIndex, u32 secondColorIndex );
	void SwapColorRegion( u32 firstColorIndex, u32 secondColorIndex, const Rect& subrect );

	void Update();
	void UpdateRegion( const Rect& subrect );

protected:
	void InternalPackPixels( int width, int height, const u8 *const data );

	array_type	m_pixels;

};


CE_NAMESPACE_END

