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
#include "Catastrophe/Core/Math/Packed/PackedRect.h"
#include "Catastrophe/Graphics/Common.h"
#include "Catastrophe/Graphics/BlendMode.h"

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
	PackedRect	sourceRect;
	s16			frameCounter;
	s16			currentFrame;
	s16			animationSpeed;
	s16			numFrames;

	PackedSprite();
	PackedSprite( Texture* texturePtr, const PackedRect& sourceRectangle, int numberOfFrames, s16 frameDelay );

	void Create( Texture* texturePtr, const PackedRect& sourceRectangle, int numberOfFrames, s16 frameDelay = 128 );
	void Create( const PackedRect& sourceRectangle, int numberOfFrames, s16 frameDelay = 128 );

	void SetSize( const Vector2& value ) { size = value; }
	void SetAngle( float value ) { angle = value; }
	void SetColor( const Color& c ) { color = c; }
	void SetBlendMode( const BlendMode& value ) { blendmode = value; }
	void SetAnimationSpeed( s16 frameDelay );
	void SetTexture( Texture* texturePtr );
	void SetSourceRect( const PackedRect& sourceRectangle );
	void SetCurrentFrame( s16 index );

	void Update();

	Texture* GetTexture() const { return texture; }
	u32 GetTextureID() const;
	const Vector2& GetSize() const { return size; }
	const Color& GetColor() const { return color; }
	const BlendMode& GetBlendMode() const { return blendmode; }
	float GetAngle() const { return angle; }

	// a few utility functions for dealing with fixed crap.
	static s16 SecondsToFixed( float seconds )
	{
		return (s16)int(seconds * 960.f);
	}

	static s16 FramesToFixed( int frames )
	{
		return (s16)(frames * 16);
	}

};


CE_NAMESPACE_END
