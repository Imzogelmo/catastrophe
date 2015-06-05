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
#include "Catastrophe/Graphics/Sprite.h"
#include "Catastrophe/Graphics/Sprite/SpriteBase.h"

CE_NAMESPACE_BEGIN


class CE_API BackgroundSprite : public SpriteBase
{
public:
	Vector2 borderOffset;

	/// The blendmode of the sprite.
	BlendMode blendmode;

	/// The gradient colors of the corners.
	Color cornerColors[4];

	BackgroundSprite();
	BackgroundSprite(Texture* texturePtr, const Rect& sourceRect, const Vector2& spriteBorderOffset = Vector2::Zero);

	/// Sets the corner color data of this sprite from an array.
	void SetCornerColors(const Color* colors);

	/// Gets the corner color data of this sprite and copies them into an array.
	void GetCornerColors(Color* colorArray);

	/// Draws the sprite with the given size at position.
	void Render(SpriteBatch* spritebatch, const Vector2& position, const Vector2& size);

};



CE_NAMESPACE_END
