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

#include "Graphics/AnimatedSpriteSet.h"
#include "Graphics/Texture.h"

CE_NAMESPACE_BEGIN


AnimatedSpriteSet::AnimatedSpriteSet() :
	SpriteBase(),
	m_texture(0),
	m_animations(),
	m_currentAnimation(0)
{
}


AnimatedSpriteSet::AnimatedSpriteSet(
		const Vector2& size,
		const Vector2& scale, 
		const Color& color,
		const BlendMode& blendmode,
		float angle
	) :
	SpriteBase(size, scale, color, blendmode, angle),
	m_texture(0),
	m_animations(),
	m_currentAnimation(0)
{
}


void AnimatedSpriteSet::Reserve( size_t capacity )
{
	m_animations.reserve(capacity);
}


void AnimatedSpriteSet::Resize( size_t newSize )
{
	m_animations.resize(newSize);
	SetCurrentAnimation(m_currentAnimation);
}


void AnimatedSpriteSet::SetCurrentAnimation( size_t index )
{
	size_t size = m_animations.size();
	if( index < size )
	{
		m_currentAnimation = index;
	}
	else
	{
		m_currentAnimation = ((size == 0) ? 0 : size - 1);
	}
}


void AnimatedSpriteSet::AddAnimation( const Rect& sourceRect, float animationDelay, int numberOfFrames, int frameOffsetX, int frameOffsetY )
{
	SpriteAnimation a;
	a.Create(m_texture, sourceRect, animationDelay, numberOfFrames, frameOffsetX, frameOffsetY);
	AddAnimation(a);
}


void AnimatedSpriteSet::AddAnimation( const Rect& sourceRect, int numberOfFrames, int frameOffsetX, int frameOffsetY )
{
	AddAnimation( SpriteAnimation(m_texture, sourceRect, numberOfFrames, frameOffsetX, frameOffsetY) );
}


void AnimatedSpriteSet::AddAnimation( const SpriteAnimation& anim )
{
	m_animations.push_back(anim);
}


void AnimatedSpriteSet::InsertAnimation( const SpriteAnimation& anim, size_t index )
{
	if( index > m_animations.size() )
		index = m_animations.size();

	m_animations.insert_at(index, anim);

	if( m_currentAnimation >= index )
	{
		SetCurrentAnimation(m_currentAnimation + 1);
	}
}


void AnimatedSpriteSet::RemoveAnimation( size_t index )
{
	if( index < m_animations.size() )
	{
		m_animations.erase_at(index);

		if( m_currentAnimation >= index && m_currentAnimation > 0 )
		{
			SetCurrentAnimation(m_currentAnimation - 1);
		}
	}
}


void AnimatedSpriteSet::Update()
{
	if( m_animations.empty() )
		return;

	GetCurrentAnimation().Update();
}




CE_NAMESPACE_END

