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
#include "Catastrophe/Graphics/Sprite/StaticSprite.h"

CE_NAMESPACE_BEGIN


/// @BorderSprite
///
/// Specialized sprite that represents a border such as a frame
/// of a window. The sprite is broken up into a type of '9-patch'
/// data structure so there are no stretching artifacts when
/// upscaling the sprite to any size.
///
/// Normally the 'center' patch of the sprite is not drawn as the
/// sprite is assumed to be a border only. The border sprite must be
/// made solid by using SetSolid(true) in this case.
///

class CE_API BorderSprite : public StaticSprite
{
public:
	Vector2 borderSize;
	bool isTiled;
	bool isSolid;

	BorderSprite();
	BorderSprite(TexturePtr texture, const PackedRect& sourceRectangle);

	/// Gets whether the frame should be tiled or stretched.
	FORCEINLINE bool GetIsTiled() const { return isTiled; }

	/// Gets whether the frame should be tiled or stretched.
	FORCEINLINE void SetIsTiled(bool value) { isTiled = value; }

	/// Gets whether the center patch of the sprite should be drawn.
	FORCEINLINE bool GetIsSolid() const { return isSolid; }

	/// Sets whether the center patch of the sprite should be drawn.
	FORCEINLINE void SetIsSolid(bool value) { isSolid = value; }

	/// Sets the texture and uv data for this sprite.
	void SetSpriteData(Texture* texture, const PackedRect& sourceRect);

	/// Render the sprite at position with the specified size.
	NOINLINE void Render(SpriteBatch* spriteBatch, const Vector2& position, const Vector2& size);

};



CE_NAMESPACE_END


