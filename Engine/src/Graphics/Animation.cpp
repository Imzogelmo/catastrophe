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

#include <fc/string.h>
#include <fc/math.h>

#include "Graphics/Animation.h"

CE_NAMESPACE_BEGIN


Animation::Animation( const Texture* texture, bool loop, bool startPaused ) :
	AnimationFrames(),
	m_texture(texture),
	m_frameCounter(0),
	m_currentFrame(0),
	m_frameSpeed(0),
	m_loop(loop),
	m_paused(startPaused)
{
}


Animation::Animation( const Texture* texture,
		const Rect& sourceRect,
		int numberOfFrames,
		int frameOffsetX,
		int frameOffsetY,
		bool loop,
		bool startPaused
	) :
	AnimationFrames(),
	m_texture(texture),
	m_frameCounter(0),
	m_currentFrame(0),
	m_frameSpeed(0),
	m_loop(loop),
	m_paused(startPaused)
{
	SetFrameData(sourceRect, numberOfFrames, frameOffsetX, frameOffsetY);
}


void Animation::SetTexture( const Texture* texture )
{
	CE_ASSERT(texture != 0);
	m_texture = texture;
}


void Animation::SetFrameData( const Rectf* uv, int numberOfFrames )
{
	AnimationFrames::SetFrameData(uv, numberOfFrames);
}


void Animation::SetFrameData( const Rect* sourceRectangles, int numberOfFrames )
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


void Animation::SetFrameData( const Rect& sourceRectangle, int numberOfFrames, int frameOffsetX, int frameOffsetY )
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
	//const float s = sourceRect.Right() / fw;
	//const float t = sourceRect.Bottom() / fh;

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


void Animation::AddFrame( const Rect& sourceRect )
{
	CE_ASSERT(m_texture != 0);
	if(m_texture)
	{
		m_uv.push_back( m_texture->GetUVRect(sourceRect) );
	}
}


void Animation::AddFrame( const Rectf& uv )
{
	AnimationFrames::AddFrame(uv);
}


void Animation::SetAnimationSpeed( float frameSpeed )
{
	m_frameSpeed = fc::max<float>(frameSpeed, 1.f);
	m_frameCounter = fc::min<float>(m_frameSpeed, m_frameCounter);
}


void Animation::SetCurrentFrame( size_t frame )
{
	m_currentFrame = fc::min<size_t>( frame, (size_t)NumFrames() - 1 );
	m_frameCounter = 0;
}


void Animation::Update()
{
	if( !IsAnimated() || m_paused )
		return;

	++m_frameCounter;
	if( m_frameCounter >= m_frameSpeed )
	{
		//advance frame.
		m_frameCounter -= m_frameSpeed;

		const size_t maxFrames = NumFrames();
		if( ++m_currentFrame >= maxFrames )
		{
			if(m_loop)
			{
				m_currentFrame -= maxFrames;
			}
			else
			{
				--m_currentFrame;
				m_frameCounter += m_frameSpeed; //hack
			}
		}
	}
}


bool Animation::IsFinished() const
{
	return ( !m_loop && IsAnimated() && 
		(m_currentFrame == NumFrames() - 1) &&
		(m_frameCounter >= m_frameSpeed)
	);
}


float Animation::GetAnimSpeed() const
{
	return m_frameSpeed;
}



CE_NAMESPACE_END

