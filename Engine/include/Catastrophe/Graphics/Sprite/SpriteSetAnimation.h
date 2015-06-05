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
#include "Catastrophe/Graphics/Sprite/SpriteBase.h"
#include "Catastrophe/Graphics/Sprite/PackedSpriteAnimation.h"

CE_NAMESPACE_BEGIN


class CE_API SpriteSetAnimation : public SpriteBase, public PackedSpriteAnimation
{
public:
	SpriteSetAnimation();
	SpriteSetAnimation(Texture* texturePtr, const PackedRect& sourceRectangle, AnimationType type, u16 animationFrameDelay, u8 numberOfFrames);

	/// Set the texture used by this sprite.
	void SetTexture(Texture* texture);

	/// Sets the source rectangle of this sprite.
	void SetSourceRect(const PackedRect& sourceRectangle);

	/// Sets the sprite texture coordinates from a source rectangle.
	FORCEINLINE const PackedRect& GetSourceRect() const { return sourceRect; }

	/// Sets the texture and uv data for this sprite.
	void SetSpriteData(Texture* texturePtr, const PackedRect& sourceRectangle);

	FORCEINLINE void SetCurrentFrame(u8 frame)
	{
		PackedSpriteAnimation::SetCurrentFrame(frame, texture, sourceRect, uv);
	}

	void Create(Texture* texturePtr, const PackedRect& sourceRectangle, u16 animationFrameDelay, u8 numberOfFrames);
	void Create(Texture* texturePtr, const PackedRect& sourceRectangle, AnimationType type, u16 animationFrameDelay, u8 numberOfFrames);

	FORCEINLINE void Update()
	{
		PackedSpriteAnimation::Update(texture, sourceRect, uv);
	}

};



CE_NAMESPACE_END
