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
#include "../Math/PackedRect.h"
#include "BlendMode.h"

CE_NAMESPACE_BEGIN


/* PackedSprite -
 * sprite class with a small memory footprint.
 */
class PackedSprite
{
public:
	Texture*	texture;
	Vector2		size;
	float		angle;
	Color		color;
	BlendMode	blendmode;
	Rectf		uv;
	PackedRect	source_rect;
	short		frame_counter;
	short		current_frame;
	short		anim_speed;
	short		num_frames;

	PackedSprite();
	PackedSprite( Texture* texturePtr, const PackedRect& sourceRectangle, int numberOfFrames, short frameDelay );

	void SetSize( const Vector2& value ) { size = value; }
	void SetColor( const Color& c ) { color = c; }
	void SetBlendMode( const BlendMode& value ) { blendmode = value; }
	void SetAnimationSpeed( short frameDelay );
	void SetTexture( Texture* texturePtr );
	void SetSourceRect( const PackedRect& sourceRectangle );
	void SetCurrentFrame( short index );
	void SetFrameData( const PackedRect& sourceRectangle, int numberOfFrames, short frameDelay );

	void Update();

	Texture* GetTexture() const { return texture; }
	//gluint GetTextureID() const { return texture->; }
	const Color& GetColor() const { return color; }
	const BlendMode& GetBlendMode() const { return blendmode; }
	float GetAngle() const { return angle; }

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
