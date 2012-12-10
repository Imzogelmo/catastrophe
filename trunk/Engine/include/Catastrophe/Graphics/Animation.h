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

#include "AnimationFrames.h"

CE_NAMESPACE_BEGIN


class Animation : public AnimationFrames
{
public:
	Animation( const Texture* texture = 0, bool loop = true, bool startPaused = false ) :
		AnimationFrames(texture),
		m_frameCounter(0), m_currentFrame(0),m_frameSpeed(0),
		m_loop(loop), m_paused(startPaused)
	{
	}

	Animation( const Texture* texture,
			const Rect& sourceRect,
			int numberOfFrames = 1,
			int frameOffsetX = 0,
			int frameOffsetY = 0,
			bool loop = true,
			bool startPaused = false
		) :
		AnimationFrames(texture, sourceRect, numberOfFrames, frameOffsetX, frameOffsetY),
		m_frameCounter(0), m_currentFrame(0),m_frameSpeed(0),
		m_loop(loop), m_paused(startPaused)
	{
	}

	void SetAnimationSpeed( float frameSpeed );
	void SetCurrentFrame( size_t frame );
	void Update();

	void SetPaused( bool pause = true ) { m_paused = pause; };
	void SetLooping( bool loop = true ) { m_loop = loop; };

	bool IsPaused() const { return m_paused; };
	bool IsLooping() const { return m_loop; };

	size_t GetCurrentFrame() const { return m_currentFrame; }
	size_t GetAnimSpeedAsInt() const { return m_frameSpeed; }
	float GetAnimSpeed() const;

	inline Rectf& GetFrameUVRect() { return m_uv.at(m_currentFrame); }
	inline const Rectf& GetFrameUVRect() const { return m_uv.at(m_currentFrame); }

protected:
	size_t m_frameCounter, m_currentFrame, m_frameSpeed;
	bool m_loop;
	bool m_paused;

};


CE_NAMESPACE_END

