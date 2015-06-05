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

#include "Catastrophe/Graphics/Sprite/SpriteSetAnimation.h"

CE_NAMESPACE_BEGIN


SpriteSetAnimation::SpriteSetAnimation() :
	SpriteBase(),
	PackedSpriteAnimation()
{
}


SpriteSetAnimation::SpriteSetAnimation
(Texture* texturePtr, const PackedRect& sourceRectangle, AnimationType type, u16 animationFrameDelay, u8 numberOfFrames) :
	SpriteBase(texturePtr, sourceRectangle),
	PackedSpriteAnimation(type, animationFrameDelay, numberOfFrames)
{
}


void SpriteSetAnimation::SetTexture(Texture* texturePtr)
{
	SpriteBase::SetTexture(texturePtr);
}


void SpriteSetAnimation::SetSourceRect(const PackedRect& sourceRectangle)
{
	SpriteBase::SetSourceRect(sourceRectangle);
	SetCurrentFrame(currentFrame);
}


void SpriteSetAnimation::SetSpriteData(Texture* texturePtr, const PackedRect& sourceRectangle)
{
	SpriteBase::SetTexture(texturePtr);
	SetSourceRect(sourceRectangle);
}


void SpriteSetAnimation::Create(Texture* texturePtr, const PackedRect& sourceRectangle, u16 animationFrameDelay, u8 numberOfFrames)
{
	SetSpriteData(texturePtr, sourceRectangle);
	SetNumFrames(numberOfFrames);
	SetAnimationSpeedFrames(animationFrameDelay);
}


void SpriteSetAnimation::Create(Texture* texturePtr, const PackedRect& sourceRectangle, AnimationType type, u16 animationFrameDelay, u8 numberOfFrames)
{
	SetSpriteData(texturePtr, sourceRectangle);
	SetAnimationData(type, animationFrameDelay, numberOfFrames);
}




CE_NAMESPACE_END
