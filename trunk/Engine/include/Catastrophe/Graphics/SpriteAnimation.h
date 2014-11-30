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

#include "../Common.h"
#include "../Math/Vector2.h"
#include "../Math/Color.h"
#include "../Math/Rectf.h"
#include "../Math/Rect.h"

CE_NAMESPACE_BEGIN


enum AnimationType
{
	AnimationType_None,
	AnimationType_Loop,
	AnimationType_OneTime,
	AnimationType_PingPong
};


class CE_API SpriteAnimation
{
public:
	SpriteAnimation();
	SpriteAnimation( Texture* texturePtr,
			const Rect& sourceRect,
			int numberOfFrames = 1,
			int frameOffsetX = 0,
			int frameOffsetY = 0
			);

	void Create( const Rect& sourceRect, int numberOfFrames = 1, int frameOffsetX = 0, int frameOffsetY = 0 );
	void Create( const Rect& sourceRect, float animationDelay, int numberOfFrames = 1, int frameOffsetX = 0, int frameOffsetY = 0 );
	void Create( Texture* texturePtr, const Rect& sourceRect, int numberOfFrames = 1, int frameOffsetX = 0, int frameOffsetY = 0 );
	void Create( Texture* texturePtr, const Rect& sourceRect, float animationDelay, int numberOfFrames = 1, int frameOffsetX = 0, int frameOffsetY = 0 );
	void SetTexture( Texture* texturePtr );
	void SetSourceRect( const Rect& sourceRect );
	void SetAnimationSpeed( float animationDelay );
	void SetCurrentFrame( u32 frame );
	void SetNumFrames( int frames );
	void Update();

	//void SetFlipX( bool flip = true );
	//void SetFlipHorizontal( bool flip = true );
	//void SetFlipVertical( bool flip = true );
	void SetPaused( bool pause = true );
	void SetAnimationType( AnimationType animationType );
	inline void SetFrameOffsetX( int offsetX ) { m_frameOffsetX = offsetX; }
	inline void SetFrameOffsetY( int offsetY ) { m_frameOffsetY = offsetY; }
	//inline bool IsFlippedHorizontal() const { return (m_flags & 1) != 0; };
	//inline bool IsFlippedVertical() const { return (m_flags & 2) != 0; };
	inline bool IsPaused() const { return (m_flags & 4) != 0; };
	inline bool IsAnimated() const { return m_numFrames > 1; };
	bool IsAnimationFinished() const;

	inline AnimationType GetAnimationType() const { return (AnimationType)m_animationType; };
	inline int GetFlags() const { return m_flags; }
	inline int GetFrameOffsetX() const { return m_frameOffsetX; }
	inline int GetFrameOffsetY() const { return m_frameOffsetY; }
	inline u32 GetNumFrames() const { return m_numFrames; }
	inline u32 GetCurrentFrame() const { return m_currentFrame; }
	inline float GetAnimationSpeed() const { return m_frameSpeed; }
	inline const Rect& GetSourceRect() const { return m_sourceRect; }
	inline Texture* GetTexture() const { return m_texture; }
	float GetAnimationLength() const;

	u32 GetTextureID() const;

	inline Rectf& GetUVRect() { return m_uv; }
	inline const Rectf& GetUVRect() const { return m_uv; }

protected:
	Texture*	m_texture;
	Rect		m_sourceRect;
	Rectf		m_uv;
	u32			m_currentFrame;
	u32			m_numFrames;
	float		m_frameCounter;
	float		m_frameSpeed;
	int			m_frameOffsetX;
	int			m_frameOffsetY;
	u16			m_flags; //todo
	u8			m_animationType;
	u8			m_animationDirection;

	/*
	enum SpriteAnimationFlags
	{
		FlipHorizontal = 1,
		FlipVertical = 2,
		Pause = 4,
		NoRepeat = 8
	};
	*/

};



CE_NAMESPACE_END
