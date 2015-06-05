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

#include "Catastrophe/Graphics/Sprite/AnimatedSpriteSet.h"
#include "Catastrophe/Graphics/Texture.h"

CE_NAMESPACE_BEGIN


AnimatedSpriteSet::AnimatedSpriteSet() :
	m_currentAnimation(0),
	m_spriteSetAnimations()
{
}


void AnimatedSpriteSet::Reserve(u32 capacity)
{
	m_spriteSetAnimations.Reserve(capacity);
}


void AnimatedSpriteSet::Resize(u32 newSize)
{
	m_spriteSetAnimations.Resize(newSize);
	SetCurrentAnimation(m_currentAnimation);
}


void AnimatedSpriteSet::SetCurrentAnimation(u32 index)
{
	m_currentAnimation = index < m_spriteSetAnimations.Size() ? index : 
		Math::Min<u32>(0, m_spriteSetAnimations.Size() - 1);
}


u32 AnimatedSpriteSet::AddAnimation(const SpriteSetAnimation& spriteSetAnimation)
{
	m_spriteSetAnimations.Add(spriteSetAnimation);
	return m_spriteSetAnimations.Size() - 1;
}


void AnimatedSpriteSet::InsertAnimation(const SpriteSetAnimation& spriteSetAnimation, u32 index)
{
	if(index > m_spriteSetAnimations.Size())
		index = m_spriteSetAnimations.Size();

	m_spriteSetAnimations.InsertAt(index, spriteSetAnimation);

	if(m_currentAnimation >= index)
		SetCurrentAnimation(m_currentAnimation + 1);
}


void AnimatedSpriteSet::RemoveAnimation(u32 index)
{
	if(index < m_spriteSetAnimations.Size())
	{
		m_spriteSetAnimations.EraseAt(index);

		if(m_currentAnimation >= index && m_currentAnimation != 0)
		{
			m_currentAnimation = m_currentAnimation - 1;
		}
	}
}


void AnimatedSpriteSet::Update()
{
	if(m_spriteSetAnimations.Empty())
		return;

	GetCurrentAnimation()->Update();
}


void AnimatedSpriteSet::Render(SpriteBatch* spriteBatch, const Vector2& position)
{
	SpriteSetAnimation* currentAnimation = GetCurrentAnimation();
	Texture* texture = currentAnimation ? currentAnimation->GetTexture() : null;
	if(texture == null)
		return;

	Rectf textureCoords(currentAnimation->GetUVRect());
	if(flipX) textureCoords.FlipX();
	if(flipY) textureCoords.FlipY();

	Quad2D quad2D;
	quad2D.SetVertexUVData(position, position - (size * 0.5f), textureCoords);
	quad2D.SetColorData(color);
	quad2D.Transform(angle, scale, position);

	spriteBatch->DrawQuad(texture->GetTextureID(), quad2D);
}



CE_NAMESPACE_END

