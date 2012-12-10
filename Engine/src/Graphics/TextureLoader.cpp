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

#include "Graphics/Texture.h"
#include "Graphics/Image.h"
#include "Graphics/TextureLoader.h"

#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )
#endif

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"

#ifdef _MSC_VER
	#pragma warning ( pop )
#endif


uchar* TextureLoader::LoadFromFile( const fc::string& filename, Point& size, TextureFormat format )
{
	if(format != tfRgba)
		return 0;

	int width, height, channels;
	uchar* ptr = stbi_load( filename.c_str(), &width, &height, &channels, STBI_rgb_alpha );
	if(!ptr)
	{
		//Log( "Image: " + filename + " failed to load. " + GetErrorMsg() );
		return 0;
	}

	size = Point(width, height);
	return ptr;
}


uchar* TextureLoader::LoadFromMemory( const void* data, size_t sizeBytes, Point& size, TextureFormat format )
{
	if(format != tfRgba)
		return 0;

	int width, height, channels;
	uchar* ptr = stbi_load_from_memory( (uchar*)data, (int)sizeBytes, &width, &height, &channels, STBI_rgb_alpha );
	if(!ptr)
	{
		//Log( "Failed to load image from memory: " + GetErrorMsg() );
		return 0;
	}

	size = Point(width, height);
	return ptr;
}


bool TextureLoader::SaveToFile( const fc::string& filename, const void* data, int w, int h, TextureFormat tFormat, ImageFileFormat fFormat )
{
	bool ret(false);

	switch(fFormat)
	{
	case Tga:
		ret = stbi_write_tga(filename.c_str(), w, h, tFormat, data) != 0;
		break;
	case Bmp:
		ret = stbi_write_bmp(filename.c_str(), w, h, tFormat, data) != 0;
		break;
	case Png:
		ret = stbi_write_png(filename.c_str(), w, h, tFormat, data, 0) != 0;
		break;
	}

	return ret;
}


bool TextureLoader::SaveToFile( const fc::string& filename, const Texture& texture, ImageFileFormat fFormat )
{
	return false;
}


bool TextureLoader::SaveToFile( const fc::string& filename, const Image& image, ImageFileFormat fFormat )
{
	if( image.GetPixelArray().empty() )
		return false;

	return SaveToFile(filename, image.GetPixelData(), (int)image.Width(), (int)image.Height(), tfRgba, fFormat);
}



void TextureLoader::FreePtr( ubyte* ptr )
{
	stbi_image_free(ptr);
}


fc::string TextureLoader::GetErrorMsg()
{
	return stbi_failure_reason();
}


