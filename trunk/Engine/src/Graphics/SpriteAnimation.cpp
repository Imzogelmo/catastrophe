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
	Create(texturePtr, sourceRect, numberOfFrames, frameOffsetX, frameOffsetY );
}


void SpriteAnimation::SetTexture( Texture* texturePtr )
{
	if( m_texture && texturePtr && m_texture != texturePtr )
	{
		m_texture = texturePtr;

		// recompute out uv coords.
		SetSourceRect(m_sourceRect);
	}

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


void SpriteAnimation::SetAnimationSpeed( float animationDelay )
{
	m_frameSpeed = animationDelay;
	m_frameCounter = 0.f;
}


void SpriteAnimation::Create( const Rect& sourceRectangle, int numberOfFrames, int frameOffsetX, int frameOffsetY )
{
	SetNumberOfFrames(numberOfFrames);
	m_frameOffsetX = (frameOffsetX > 0 ? frameOffsetX : sourceRectangle.Width());
	m_frameOffsetY = (frameOffsetY > 0 ? frameOffsetY : sourceRectangle.Height());

	SetSourceRect(sourceRectangle);
	SetCurrentFrame(0);
}


void SpriteAnimation::Create( const Rect& sourceRectangle, float animationDelay, int numberOfFrames, int frameOffsetX, int frameOffsetY )
{
	SetAnimationSpeed(animationDelay);
	Create(sourceRectangle, numberOfFrames, frameOffsetX, frameOffsetY);
}


void SpriteAnimation::Create( Texture* texturePtr, const Rect& sourceRectangle, int numberOfFrames, int frameOffsetX, int frameOffsetY )
{
	SetTexture(texturePtr);
	Create(sourceRectangle, numberOfFrames, frameOffsetX, frameOffsetY);
}


void SpriteAnimation::Create( Texture* texturePtr, const Rect& sourceRectangle, float animationDelay, int numberOfFrames, int frameOffsetX, int frameOffsetY )
{
	SetTexture(texturePtr);
	Create(sourceRectangle, animationDelay, numberOfFrames, frameOffsetX, frameOffsetY);
}


void SpriteAnimation::SetSourceRect( const Rect& sourceRectangle )
{
	m_sourceRect = sourceRectangle;
	if( m_texture )
	{
		float h = (float)m_texture->Height();
		m_uv.min.y = (float)sourceRectangle.Top() / h;
		m_uv.max.y = (float)sourceRectangle.Bottom() / h;

		if( m_flags & 2 )
			fc::swap(m_uv.min.y, m_uv.max.y);

		if( m_currentFrame > 0 )
		{
			SetCurrentFrame(m_currentFrame);
		}
		else
		{
			float w = (float)m_texture->Width();
			m_uv.min.x = (float)sourceRectangle.Left() / w;
			m_uv.max.x = (float)sourceRectangle.Right() / w;

			if( m_flags & 1 )
				fc::swap(m_uv.min.x, m_uv.max.x);
		}
	}
}


void SpriteAnimation::SetCurrentFrame( size_t index )
{
	if( index < m_numFrames )
	{
		m_currentFrame = index;

		// texture must be assigned first to generate uv coords.
		if( m_texture )
		{
			int x = m_sourceRect.pos.x + (m_frameOffsetX * (int)m_currentFrame);
			int yOffset = x / m_texture->Width();

			// if the row is the same, calculation of top, bottom uv will be the same also.
			if( yOffset > 0 )
			{
				x %= m_texture->Width();
				int y = m_sourceRect.pos.y + (m_frameOffsetY * yOffset);
				float texHeightf = (float)m_texture->Height();

				m_uv.min.y = y / texHeightf;
				m_uv.max.y = (y + m_frameOffsetY) / texHeightf;

				if( m_flags & 2 )
					fc::swap(m_uv.min.y, m_uv.max.y);
			}

			float texWidthf = (float)m_texture->Width();
			m_uv.min.x = x / texWidthf;
			m_uv.max.x = (x + m_frameOffsetX) / texWidthf;

			if( m_flags & 1 )
				fc::swap(m_uv.min.x, m_uv.max.x);
		}
	}
}


void SpriteAnimation::Update()
{
	if( m_numFrames > 1 && !IsPaused() )
	{
		m_frameCounter += 16;
		if( m_frameCounter >= m_frameSpeed )
		{
			m_frameCounter -= m_frameSpeed;
			if( ++m_currentFrame >= m_numFrames )
			{
				m_currentFrame -= m_numFrames;
			}

			// update our texture coords
			SetCurrentFrame(m_currentFrame);
		}
	}
}


void SpriteAnimation::SetPaused( bool pause )
{
	if( pause ) m_flags |= 4;
	else m_flags &= ~4;
}


void SpriteAnimation::SetLooping( bool loop )
{
	// loop when no bit is set.
	if( loop ) m_flags &= ~8;
	else m_flags |= 8;
}


bool SpriteAnimation::IsFinished() const
{
	//todo:
	return m_currentFrame == (m_numFrames - 1) && m_frameCounter > m_frameSpeed;
}


gluint SpriteAnimation::GetTextureID() const
{
	return m_texture ? m_texture->GetTextureID() : 0;
}





CE_NAMESPACE_END
