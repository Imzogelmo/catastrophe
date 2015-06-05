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

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/Math/Vector2.h"
#include "Catastrophe/Core/Math/Color.h"
#include "Catastrophe/Core/Math/Rectf.h"
#include "Catastrophe/Core/Containers/Vector.h"

#include "Catastrophe/Graphics/Common.h"
#include "Catastrophe/Graphics/Sprite.h"
#include "Catastrophe/Graphics/Sprite/SpriteSetAnimation.h"


CE_NAMESPACE_BEGIN


/// @AnimatedSpriteSet
///
/// Holds an array of SpriteSetAnimations.
/// The difference between this class and an array of sprites is that
/// all the animation states share the same color, size, scale, and
/// rotation information regardless of what animation state the sprite is currently in.
/// Thus, this class is really more of a single sprite with many possible animation states.
/// 

class AnimatedSpriteSet
{
public:
	AnimatedSpriteSet();

	/// Adds an animation to the end of the array.
	u32 AddAnimation(const SpriteSetAnimation& spriteSetAnimation);

	/// Inserts an animation into the given index.
	void InsertAnimation(const SpriteSetAnimation& spriteSetAnimation, u32 index);

	/// Removes an animation at the given index.
	void RemoveAnimation(u32 index);

	/// Sets the current animation index.
	void SetCurrentAnimation(u32 index);

	void Reserve(u32 capacity);

	/// Resizes the aniamtion array.
	void Resize(u32 newSize);

	/// Updates the current animation.
	void Update();

	/// Renders the current sprite at the given position.
	void Render(SpriteBatch* spriteBatch, const Vector2& position);

	/// True if there are no animations in this srriteset.
	FORCEINLINE bool Empty() const { return m_spriteSetAnimations.Empty(); }
	FORCEINLINE u32 GetNumAnimations() const { return m_spriteSetAnimations.Size(); }
	FORCEINLINE u32 GetCurrentAnimationIndex() const { return m_currentAnimation; }

	FORCEINLINE SpriteSetAnimation* GetAnimation(u32 index) const
	{
		if(index < m_spriteSetAnimations.Size())
			return (SpriteSetAnimation*)&m_spriteSetAnimations[index];

		return null;
	}

	FORCEINLINE SpriteSetAnimation* GetCurrentAnimation() const
	{
		return const_cast<SpriteSetAnimation*>(
			m_spriteSetAnimations.Empty() ? null : &m_spriteSetAnimations[m_currentAnimation]);
	}

	FORCEINLINE Vector<SpriteSetAnimation>& GetAnimationsVector() const
	{
		return *const_cast<Vector<SpriteSetAnimation>*>(&m_spriteSetAnimations);
	}

protected:
	/// The size of the sprite.
	Vector2 size;

	/// The scale of the sprite.
	Vector2 scale;

	/// The angle of the sprite.
	float angle;

	/// The tint color of the sprite.
	Color color;

	/// The blendmode of the sprite.
	BlendMode blendmode;

	/// Whether the sprite is flipped horizontally.
	bool flipX;

	/// Whether the sprite is flipped vertically.
	bool flipY;

	/// The current animation
	u32 m_currentAnimation;

	/// Sprite animation array.
	Vector<SpriteSetAnimation> m_spriteSetAnimations;

};



CE_NAMESPACE_END
