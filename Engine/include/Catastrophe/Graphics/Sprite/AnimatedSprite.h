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

#include "Catastrophe/Graphics/Common.h"
#include "Catastrophe/Graphics/Sprite/Sprite.h"
#include "Catastrophe/Graphics/Sprite/SpriteAnimation.h"

CE_NAMESPACE_BEGIN



class CE_API AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	AnimatedSprite(Texture* texturePtr, const PackedRect& sourceRectangle);

	/// Sets the source rectangle of this sprite.
	void SetSourceRect(const PackedRect& sourceRectangle);

	/// Set and initialize the animation data.
	FORCEINLINE void SetAnimationData(AnimationType type, float animationFrameDelay, u16 numberOfFrames)
	{
		m_spriteAnimation.SetAnimationData(type, animationFrameDelay, numberOfFrames);
	}

	/// Gets the number of animation frames.
	FORCEINLINE u16 GetNumFrames() const { return m_spriteAnimation.GetNumFrames(); }

	/// Sets the number of animation frames.
	FORCEINLINE void SetNumFrames(u16 value) { m_spriteAnimation.SetNumFrames(value); }

	/// Gets the current frame.
	FORCEINLINE u16 GetCurrentFrame() const { return m_spriteAnimation.GetCurrentFrame(); }

	/// Sets the current frame.
	FORCEINLINE void SetCurrentFrame(u16 frame) { m_spriteAnimation.SetCurrentFrame(frame, texture, sourceRect, uv); }

	/// Gets whether the animation is paused.
	FORCEINLINE bool GetPaused() const { return m_spriteAnimation.GetPaused(); }

	/// Sets whether the animation is paused.
	FORCEINLINE void SetPaused(bool value) { m_spriteAnimation.SetPaused(value); }

	/// Gets the type of animation used.
	FORCEINLINE AnimationType GetAnimationType() const { return m_spriteAnimation.GetAnimationType(); }

	/// Sets the type of animation used.
	FORCEINLINE void SetAnimationType(AnimationType animationType) { m_spriteAnimation.SetAnimationType(animationType); }

	/// Sets the animation speed of each frame in frames.
	FORCEINLINE float GetAnimationSpeedFrames() const { m_spriteAnimation.GetAnimationLengthFrames(); }

	/// Sets the animation speed of each frame in frames.
	FORCEINLINE void SetAnimationSpeedFrames(float value) { m_spriteAnimation.SetAnimationSpeedFrames(value); }

	/// Whether the animation has more than one frame.
	FORCEINLINE bool IsAnimated() const { return m_spriteAnimation.IsAnimated(); };

	/// Sets the texture, source rectangle, and uv data for this sprite.
	FORCEINLINE void SetSpriteData(Texture* texturePtr, const Rect& sourceRectangle) { SetSpriteData(texturePtr, sourceRectangle); }

	/// Sets the texture, source rectangle, and uv data for this sprite.
	void SetSpriteData(Texture* texturePtr, const PackedRect& sourceRectangle);

	/// Updates the animation.
	void Update();

	/// Renders the sprite at the given position.
	void Render(SpriteBatch* spriteBatch, const Vector2& position);

	SpriteAnimation& GetSpriteAnimation() { return m_spriteAnimation; }
	const SpriteAnimation& GetSpriteAnimation() const { return m_spriteAnimation; }

	void SetSpriteAnimation(const SpriteAnimation& value) { m_spriteAnimation = value; }

protected:
	/// The animation data of this sprite.
	SpriteAnimation m_spriteAnimation;

};



CE_NAMESPACE_END


