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

#include "Graphics/AnimationFrames.h"

CE_NAMESPACE_BEGIN


AnimationFrames::AnimationFrames( const Texture* texture ) :
	m_texture(texture),
	m_uv()
{
	//...err fixme:
	m_uv.push_back(Rectf::One);
}


AnimationFrames::AnimationFrames( const Texture* texture, const Rect& sourceRect, int numberOfFrames, int frameOffsetX, int frameOffsetY )
{
	SetTexture(texture);
	SetFrameData(sourceRect, numberOfFrames, frameOffsetX, frameOffsetY);
}


void AnimationFrames::Clear()
{
	m_uv.reset();
}


void AnimationFrames::SetTexture( const Texture* texture )
{
	CE_ASSERT(texture != 0);
	m_texture = texture;
}


void AnimationFrames::SetFrameData( const Rectf* uv, int numberOfFrames )
{
	Clear();
	m_uv.resize(numberOfFrames);
	for( int i(0); i < numberOfFrames; ++i )
	{
		m_uv[i] = uv[i];
	}
}

void AnimationFrames::SetFrameData( const Rect* sourceRectangles, int numberOfFrames )
{
	CE_ASSERT(m_texture != 0);

	if(m_texture)
	{
		Clear();
		m_uv.resize(numberOfFrames);
		for( int i(0); i < numberOfFrames; ++i )
		{
			const Rect& sourceRect = sourceRectangles[i];
			m_uv[i] = m_texture->GetUVRect(sourceRect);
		}
	}
}


void AnimationFrames::SetFrameData( const Rect& sourceRectangle, int numberOfFrames, int frameOffsetX, int frameOffsetY )
{
	CE_ASSERT(m_texture != 0);
	CE_ASSERT(m_texture->Width() != 0 && m_texture->Height() != 0);

	Clear();
	m_uv.resize(numberOfFrames);

	Rect sourceRect = sourceRectangle;
	int textureWidth = m_texture->Width();
	int textureHeight = m_texture->Height();

	const float fw = (float)textureWidth;
	const float fh = (float)textureHeight;
	const float s = sourceRect.Right() / fw;
	const float t = sourceRect.Bottom() / fh;

	for( int i(0); i < numberOfFrames; ++i )
	{
		Rectf& uv = m_uv[i];

		uv.min.x  = sourceRect.pos.x / fw;
		uv.min.y  = sourceRect.pos.y / fh;
		uv.max.x  = sourceRect.Right() / fw;
		uv.max.y  = sourceRect.Bottom() / fh;

		sourceRect.pos.x += frameOffsetX;
		sourceRect.pos.y += frameOffsetY;

		//Wrap around to next row.
		if( sourceRect.Right() > textureWidth )
		{
			sourceRect.pos.x = 0;
			sourceRect.pos.y += sourceRect.size.y;
		}

		//Wrap around to top
		if( sourceRect.Bottom() > textureHeight )
		{
			sourceRect.pos.y = 0;
		}
	}
}


void AnimationFrames::AddFrame( const Rect& sourceRect )
{
	CE_ASSERT(m_texture != 0);
	if(m_texture)
	{
		m_uv.push_back( m_texture->GetUVRect(sourceRect) );
	}
}


void AnimationFrames::AddFrame( const Rectf& uv )
{
	m_uv.push_back(uv);
}


void AnimationFrames::RemoveFrame( size_t loc )
{
	if( loc < m_uv.size() )
	{
		m_uv.erase_at( loc );
	}
}



CE_NAMESPACE_END

