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

#include <fc/sort.h>

CE_NAMESPACE_BEGIN


enum SpriteSortMode
{
	Deferred,
	BackToFrontSort,
	FrontToBackSort,
	TextureSort,
	YSort,
	BlendSort
};


template<class T>
struct SpriteTextureSorter
{
	bool operator()(const T& lhs, const T& rhs) {
		return( lhs.GetTexture() < rhs.GetTexture() );
	}
};

template<class T>
struct SpriteBlendSorter
{
	bool operator()(const T& lhs, const T& rhs) {
		return( lhs.GetBlendMode() < rhs.GetBlendMode() );
	}
};

template<class T>
struct SpriteYSorter
{
	bool operator()(const T& lhs, const T& rhs) {
		return( lhs.GetYPosition() < rhs.GetYPosition() );
	}
};

template<class T>
struct SpriteBackToFrontSorter
{
	bool operator()(const T& lhs, const T& rhs) {
		return( lhs.GetDepth() < rhs.GetDepth() );
	}
};

template<class T>
struct SpriteFrontToBackSorter
{
	bool operator()(const T& lhs, const T& rhs) {
		return( rhs.GetDepth() < lhs.GetDepth() );
	}
};


template<class T>
class SpriteSorter
{
public:
	SpriteSortMode mode;

	SpriteSorter() : mode(Deferred)
	{}

	void Sort(T* first, T* last)
	{
		switch(mode)
		{
			default:
			case (Deferred):
			break;
			case (TextureSort):
			{
				fc::sort( first, last, SpriteTextureSorter<T>() );
			}
			break;
			case (YSort):
			{
				fc::sort( first, last, SpriteYSorter<T>() );
			}
			break;
			case (BlendSort):
			{
				fc::sort( first, last, SpriteBlendSorter<T>() );
			}
			break;
			case (BackToFrontSort):
			{
				fc::sort( first, last, SpriteBackToFrontSorter<T>() );
			}
			break;
			case (FrontToBackSort):
			{
				fc::sort( first, last, SpriteFrontToBackSorter<T>() );
			}
			break;
		}
	}
};



CE_NAMESPACE_END
