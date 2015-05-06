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

/*
AnimatedSpriteSet::~AnimatedSpriteSet()
{
	if(m_texture)
		m_texture->ReleaseRef();
}
*/

void AnimatedSpriteSet::Reserve( u32 capacity )
{
	m_animations.Reserve(capacity);
}


void AnimatedSpriteSet::Resize( u32 newSize )
{
	m_animations.Resize(newSize);
	SetCurrentAnimation(m_currentAnimation);
}


void AnimatedSpriteSet::SetTexture( Texture* texture )
{
	if(m_texture)
		m_texture->ReleaseRef();

	m_texture = texture;

	if(texture)
		texture->AddRef();

	for( vec_type::Iterator it = m_animations.begin(); it != m_animations.end(); ++it )
	{
		it->SetTexture(m_texture);
	}
}


void AnimatedSpriteSet::SetCurrentAnimation( u32 index )
{
	u32 size = m_animations.Size();
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
	m_animations.Add(anim);
}


void AnimatedSpriteSet::InsertAnimation( const SpriteAnimation& anim, u32 index )
{
	if( index > m_animations.Size() )
		index = m_animations.Size();

	m_animations.InsertAt(index, anim);

	if( m_currentAnimation >= index )
	{
		SetCurrentAnimation(m_currentAnimation + 1);
	}
}


void AnimatedSpriteSet::RemoveAnimation( u32 index )
{
	if( index < m_animations.Size() )
	{
		m_animations.EraseAt(index);

		if( m_currentAnimation >= index && m_currentAnimation > 0 )
		{
			SetCurrentAnimation(m_currentAnimation - 1);
		}
	}
}


void AnimatedSpriteSet::Update()
{
	if( m_animations.Empty() )
		return;

	GetCurrentAnimation().Update();
}


u32 AnimatedSpriteSet::GetTextureID() const
{
	return m_texture ? m_texture->GetTextureID() : 0;
}



CE_NAMESPACE_END

