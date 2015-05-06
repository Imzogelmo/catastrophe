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

#include "Catastrophe/Graphics/Common.h"
#include "Catastrophe/Graphics/Texture.h"
#include "Catastrophe/Core/Containers/String.h"


enum TextureFormat
{
	tfInvalid,
	tfLuminance,
	tfLuminanceAlpha,
	tfRgb,
	tfRgba
};

enum ImageFileFormat
{
	Tga,
	Bmp,
	Png
};


class CE_API TextureLoader
{
public:
	//TextureLoader& GetInstance();

	static u8* LoadFromFile( const String& filename, Point& size, TextureFormat format = tfRgba );
	static u8* LoadFromMemory( const void* data, u32 sizeBytes, Point& size, TextureFormat format = tfRgba );

	static bool SaveToFile( const String& filename, const void* data, int w, int h, TextureFormat tFormat = tfRgba, ImageFileFormat fFormat = Png );
	static bool SaveToFile( const String& filename, const Texture& texture, ImageFileFormat fFormat = Png );
	static bool SaveToFile( const String& filename, const Image& image, ImageFileFormat fFormat = Png );

	static void FreePtr( u8* ptr );
	static String GetErrorMsg();

};


