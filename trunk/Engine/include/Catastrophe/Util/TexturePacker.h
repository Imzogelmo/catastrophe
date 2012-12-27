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

#include "../Math/Point.h"

CE_NAMESPACE_BEGIN


class TexturePackerBase
{
public:
	TexturePackerBase(int w, int h) : m_size(w, h) {}

	int Width() { return m_size.x; }
	int Height() { return m_size.y; }
	Point Size() { return m_size; }

	virtual bool Pack( int w, int h, Point& outPos ) = 0;

protected:
	Point m_size;
};


/**
 * Basic packing algorithm that fits rectangles using rows.
 * @note - this is not efficient if the input sizes vary by large amounts.
 */
class RectangleTexturePacker : public TexturePackerBase
{
public:
	RectangleTexturePacker(int w, int h)
		: TexturePackerBase(w, h), m_pos(Point::Zero), m_yoffset(0)
	{}

	bool Pack( int w, int h, Point& outPos );

protected:
	Point	m_pos;
	int		m_yoffset;
};


/**
 * Basic packing algorithm similar to RectangleTexturePacker except
 * that all output rects are aligned to a size grid.
 */
class GridTexturePacker : public RectangleTexturePacker
{
public:
	GridTexturePacker(int w, int h, int gridSize = 16)
		: RectangleTexturePacker(w, h), m_gridSize(gridSize)
	{}

	bool Pack( int w, int h, Point& outPos )
	{
		//extend size to be a multiple or gridSize.
		w = int((w + m_gridSize - 1) / m_gridSize) * m_gridSize;
		h = int((h + m_gridSize - 1) / m_gridSize) * m_gridSize;

		return this->RectangleTexturePacker::Pack(w, h, outPos);
	}

protected:
	int	m_gridSize;
};



CE_NAMESPACE_END


