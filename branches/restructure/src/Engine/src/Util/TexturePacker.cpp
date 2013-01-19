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

#include "Util/TexturePacker.h"

CE_NAMESPACE_BEGIN


bool RectangleTexturePacker::Pack( int w, int h, Point& outPos )
{
	if( w > Width() || m_pos.y + h > Height() )
		return false;

	if( m_pos.x + w > Width() )
	{
		IncrementRow();
	}

	//use current position.
	outPos = m_pos;

	m_pos.x += w;
	if( h > m_yoffset )
		m_yoffset = h;

	return true;
}


void RectangleTexturePacker::IncrementRow()
{
	m_pos.x = 0;
	m_pos.y += m_yoffset;
	m_yoffset = 0;
}


bool GridTexturePacker::Pack( int w, int h, Point& outPos )
{
	//extend size to be a multiple or gridSize.
	w = int((w + m_gridSize - 1) / m_gridSize) * m_gridSize;
	h = int((h + m_gridSize - 1) / m_gridSize) * m_gridSize;

	return this->RectangleTexturePacker::Pack(w, h, outPos);
}


CE_NAMESPACE_END

