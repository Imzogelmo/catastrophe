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


class PackedSprite
{
public:
	Texture*	texture;
	Vector2		size;
	float		angle;
	Color		color;
	Rectf		uv;
	Rect		source_rect;
	short		frame_counter;
	short		current_frame;
	short		anim_speed;
	short		num_frames;

	PackedSprite();
	PackedSprite( Texture* texturePtr, const Rect& sourceRectangle, int numberOfFrames, short frameDelay );

	void PackedSprite::SetAnimationSpeed( short frameDelay );
	void SetTexture( Texture* texturePtr );
	void SetSourceRect( const Rect& sourceRectangle );
	void PackedSprite::Update();
	void PackedSprite::SetCurrentFrame( short index );
	void SetFrameData( const Rect& sourceRectangle, int numberOfFrames, short frameDelay );

	// a few utility functions for dealing with fixed crap.
	static short SecondsToFixed( float seconds )
	{
		return (short)int(seconds * 960.f);
	}

	static short FramesToFixed( int frames )
	{
		return (short)(frames * 16);
	}

};


CE_NAMESPACE_END
