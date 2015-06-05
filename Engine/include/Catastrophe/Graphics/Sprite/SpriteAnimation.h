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
#include "Catastrophe/Graphics/Common.h"

CE_NAMESPACE_BEGIN



class CE_API SpriteAnimation
{
public:
	/// The frame counter.
	float frameCounter;

	/// The animation speed of each frame.
	float frameSpeed;

	/// The current animation frame.
	u16 currentFrame;

	/// The current animation frame.
	u16 numFrames;

	/// The sourceRect x-offset.
	s16 frameOffsetX;

	/// The sourceRect y-offset.
	s16 frameOffsetY;

	/// The type of animation.
	u8 animationType;

	/// Animation flags.
	u8 animationFlags;

	SpriteAnimation();
	SpriteAnimation(AnimationType type, float animationFrameDelay, u16 numberOfFrames);

	/// Set and initialize the animation data.
	void SetAnimationData(AnimationType type, float animationFrameDelay, u16 numberOfFrames);

	/// Gets the number of animation frames.
	FORCEINLINE u16 GetNumFrames() const { return numFrames; }

	/// Sets the number of animation frames.
	void SetNumFrames(u16 value);

	/// Gets the current frame.
	FORCEINLINE u16 GetCurrentFrame() const { return currentFrame; }

	/// Sets the current frame.
	/// The texture and rect information must be supplied in case the uv needs to be recalculated.
	void SetCurrentFrame(u16 frame, Texture* texture, const PackedRect& sourceRectangle, Rectf& uv);

	/// Gets the frame x-offset from the source rectangle.
	FORCEINLINE s16 GetFrameOffsetX() const { return frameOffsetX; }

	/// Sets the frame x-offset from the source rectangle.
	FORCEINLINE void SetFrameOffset(s16 x, s16 y) { frameOffsetX = x; frameOffsetY = y; }

	/// Sets the frame x-offset from the source rectangle.
	FORCEINLINE void SetFrameOffsetX(s16 value) { frameOffsetX = value; }

	/// Gets the frame y-offset from the source rectangle.
	FORCEINLINE s16 GetFrameOffsetY() const { return frameOffsetY; }

	/// Sets the frame y-offset from the source rectangle.
	FORCEINLINE void SetFrameOffsetY(s16 value) { frameOffsetY = value; }

	/// Gets whether to flip the uv horizontally when the frame is recalculated.
	FORCEINLINE bool GetFlipX() const { return (animationFlags & AnimationFlags_FlipX) != 0; }

	/// Sets whether to flip the uv horizontally when the frame is recalculated.
	void SetFlipX(bool value);

	/// Gets whether to flip the uv vertically when the frame is recalculated.
	FORCEINLINE bool GetFlipY() const { return (animationFlags & AnimationFlags_FlipY) != 0; }

	/// Sets whether to flip the uv vertically when the frame is recalculated.
	void SetFlipY(bool value);

	/// Gets whether the animation is paused.
	FORCEINLINE bool GetPaused() const { return (animationFlags & AnimationFlags_Pause) != 0; }

	/// Sets whether the animation is paused.
	void SetPaused(bool value);

	/// Gets the type of animation used.
	FORCEINLINE AnimationType GetAnimationType() const { return (AnimationType)animationType; }

	/// Sets the type of animation used.
	void SetAnimationType(AnimationType type);

	/// Updates the current animation using the supplied texture and sourcerect.
	/// If the texture coordinates are recalculated for the current frame of animation
	/// they will be set to the uv parameter.
	void Update(Texture* texture, const PackedRect& sourceRect, Rectf& uv);

	/// Whether the animation has more than one frame.
	FORCEINLINE bool IsAnimated() const { return numFrames > 1; };

	/// Whether the animation has ended.
	/// If the animation is looped it will never end.
	bool IsAnimationFinished() const;

	/// Sets the animation speed in frames.
	FORCEINLINE void SetAnimationSpeedFrames(float value) { frameSpeed = value; }

	/// Sets the animation speed in frames.
	FORCEINLINE void SetAnimationSpeedSeconds(float value)
	{
		frameSpeed = (u16)((int)(value * 16.f * 60.f));
	}

	/// Gets the animation length in frames.
	float GetAnimationLengthFrames() const;

	/// Gets the animation length in seconds (This is assuming 60 FPS).
	float GetAnimationLengthSeconds() const;
};



CE_NAMESPACE_END
