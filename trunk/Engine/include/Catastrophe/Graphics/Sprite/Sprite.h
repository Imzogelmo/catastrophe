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

#include "Catastrophe/Core/Math/Vector2.h"
#include "Catastrophe/Core/Math/Color.h"
#include "Catastrophe/Core/Math/Rectf.h"

#include "Catastrophe/Graphics/BlendMode.h"
#include "Catastrophe/Graphics/Sprite/StaticSprite.h"

CE_NAMESPACE_BEGIN


/// @Sprite
///
class CE_API Sprite : public StaticSprite
{
public:
	/// The scale value of the sprite.
	Vector2 scale;

	/// The rotation angle of the sprite.
	float angle;

	Sprite();
	Sprite(Texture* texturePtr, const Rect& sourceRectangle);
	Sprite(Texture* texturePtr, const PackedRect& sourceRectangle);

	/// Gets the size of the sprite.
	FORCEINLINE const Vector2& GetScale() const { return scale; }

	/// Sets the size of the sprite.
	FORCEINLINE void SetScale(const Vector2& value) { scale = value; }

	/// Gets the angle of this sprite.
	FORCEINLINE float GetAngle() const { return angle; }

	/// Sets the angle of this sprite.
	FORCEINLINE void SetAngle(float value) { angle = value; }

	/// Renders the sprite at the given position.
	void Render(SpriteBatch* spriteBatch, const Vector2& position);

};



CE_NAMESPACE_END

