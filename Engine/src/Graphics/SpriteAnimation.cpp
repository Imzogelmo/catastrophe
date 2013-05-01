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

#include "Graphics/SpriteAnimation.h"
#include "Graphics/Texture.h"

CE_NAMESPACE_BEGIN


SpriteAnimation::SpriteAnimation() :
	m_texture(0),
	m_sourceRect(Rect::Zero),
	m_uv(Rectf::Zero),
	m_currentFrame(0),
	m_numFrames(1),
	m_frameCounter(0.f),
	m_frameSpeed(16.f),
	m_frameOffsetX(0),
	m_frameOffsetY(0),
	m_flags(0)
{
}


SpriteAnimation::SpriteAnimation( Texture* texturePtr, const Rect& sourceRect, int numberOfFrames, int frameOffsetX, int frameOffsetY ) :
	m_texture(0),
	m_sourceRect(Rect::Zero),
	m_uv(Rectf::Zero),
	m_currentFrame(0),
	m_numFrames(1),
	m_frameCounter(0.f),
	m_frameSpeed(16.f),
	m_frameOffsetX(0),
	m_frameOffsetY(0),
	m_flags(0)
{
	Create(texturePtr, sourceRectangle, numberOfFrames, frameOffsetX, frameOffsetY );
}


void SpriteAnimation::SetTexture( Texture* texturePtr )
{
	CE_ASSERT(texturePtr != 0);
	CE_ASSERT(texturePtr->Width() != 0 && texturePtr->Height() != 0);
	m_texture = texturePtr;
}


void SpriteAnimation::SetNumberOfFrames( int numFrames )
{
	m_numFrames = fc::max(numFrames, 1);
	if( m_currentFrame >= m_numFrames )
	{
		m_currentFrame = 0;
	}
}


void SpriteAnimation::Create( Texture* texturePtr, const Rect& sourceRectangle, int numberOfFrames = 1, int frameOffsetX = 0, int frameOffsetY = 0 )
{
	SetTexture(texturePtr);
	SetNumberOfFrames(numberOfFrames);
	m_frameOffsetX = (frameOffsetX > 0 ? frameOffsetX : sourceRectangle.Width());
	m_frameOffsetY = (frameOffsetY > 0 ? frameOffsetY : sourceRectangle.Height());

	//SetAnimationSpeed();
	SetSourceRect(sourceRectangle);
	SetCurrentFrame(0);
}


void SpriteAnimation::SetSourceRect( const Rect& sourceRectangle )
{
	CE_ASSERT(m_texture != 0);
	m_sourceRect = sourceRectangle;

	// set uv as if this is being initialized for the first time.
	float w = (float)texture->Width();
	float h = (float)texture->Height();
	uv.min.x = sourceRectangle.Left() / w;
	uv.max.x = sourceRectangle.Right() / w;
	uv.min.y = sourceRectangle.Top() / h;
	uv.max.y = sourceRectangle.Bottom() / h;

	SetCurrentFrame(m_currentFrame);
}


void SpriteAnimation::SetCurrentFrame( int index )
{
	// texture must be assigned first.
	CE_ASSERT(texture != 0);

	if( index < m_numFrames )
	{
		current_frame = index;

		float tw = (float)texture->Width();
		float th = (float)texture->Height();

		int x = m_sourceRect.pos.x + (m_frameOffsetX * (int)m_currentFrame);
		int yOffset = x / texture->Width();

		// if the row is the same, calculation of top, bottom uv will be the same also.
		if( yOffset > 0 )
		{
			x %= texture->Width();
			int y = source_rect.pos.y + (m_frameOffsetY * yOffset);
			float texHeightf = (float)texture->Width();

			uv.min.y = y / texHeightf;
			uv.max.y = (y + m_frameOffsetY) / texHeightf;
		}

		float texWidthf = (float)texture->Width();
		uv.min.x = x / texWidthf;
		uv.max.x = (x + m_frameOffsetX) / texWidthf;
	}
}


void SpriteAnimation::Update()
{
	if( m_numFrames > 1 )
	{
		m_frameCounter += 16;
		if( m_frameCounter >= m_frameSpeed )
		{
			m_frameCounter -= m_frameSpeed;
			if( ++current_frame >= m_numFrames )
			{
				m_currentFrame -= m_numFrames;
			}

			// update our texture coords
			SetCurrentFrame(m_currentFrame);
		}
	}
}






CE_NAMESPACE_END
