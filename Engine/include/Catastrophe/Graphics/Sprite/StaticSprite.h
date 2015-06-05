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
#include "Catastrophe/Core/SharedPtr.h"
#include "Catastrophe/Core/Math/Vector2.h"
#include "Catastrophe/Core/Math/Color.h"
#include "Catastrophe/Core/Math/Rectf.h"
#include "Catastrophe/Core/Math/Packed/PackedRect.h"
#include "Catastrophe/Graphics/BlendMode.h"
#include "Catastrophe/Graphics/Sprite/SpriteBase.h"

CE_NAMESPACE_BEGIN


/// @StaticSprite
///
/// Basic sprite class that represents a static image, or rect, with a size,
/// within a sprite-sheet. This sprite cannot be rotated or scaled.
///
/// Used mostly for UI Elements, menus, etc.
///
class CE_API StaticSprite : public SpriteBase
{
public:
	/// The size of the sprite.
	Vector2 size;

	/// The tint color of the sprite.
	Color color;

	/// The blendmode of the sprite.
	BlendMode blendmode;

	/// Whether the sprite is flipped horizontally.
	bool flipX;

	/// Whether the sprite is flipped vertically.
	bool flipY;

	StaticSprite();
	StaticSprite(Texture* texture, const Rect& sourceRectangle);
	StaticSprite(Texture* texture, const PackedRect& sourceRectangle);

	/// Gets the size of the sprite.
	FORCEINLINE const Vector2& GetSize() const { return size; }

	/// Sets the size of the sprite.
	FORCEINLINE void SetSize(const Vector2& value) { size = value; }

	/// Gets the tint color of the sprite.
	FORCEINLINE Color GetColor() const { return color; }

	/// Sets the tint color of the sprite.
	FORCEINLINE void SetColor(const Color& value) { color = value; }

	/// Gets the blendmode used when rendering the sprite.
	FORCEINLINE const BlendMode& GetBlendmode() const { return blendmode; }

	/// Sets the blendmode used when rendering the sprite.
	FORCEINLINE void SetBlendmode(const BlendMode& value) { blendmode = value; }

	/// Sets whether this sprite is flipped horizontally.
	FORCEINLINE void SetFlipX(bool value) { flipX = value; }

	/// Gets whether this sprite is flipped horizontally.
	FORCEINLINE bool GetFlipX() const { return flipX; }

	/// Sets whether this sprite is flipped vertically.
	FORCEINLINE void SetFlipY(bool value) { flipY = value; }

	/// Gets whether this sprite is flipped vertically.
	FORCEINLINE bool GetFlipY() const { return flipY; }

	/// Renders the sprite at the given position.
	void Render(SpriteBatch* spriteBatch, const Vector2& position);

};



/*
Serializer& operator <<(Serializer& serializer, const StaticSprite& staticSprite)
{
	serializer << texture ? texture->GetResourceName() : String("");
	serializer << texture ? texture->GetPackedSourceRect(uv) : PackedRect::Zero;
	serializer << size;
	serializer << color;
	serializer << blendmode;

	return serializer;
}

Deserializer& operator >>(Deserializer& deserializer, StaticSprite& staticSprite)
{
	PackedRect sourceRect = PackedRect::Zero;
	String resourceName;

	deserializer >> resourceName;
	deserializer >> sourceRect;
	deserializer >> size;
	deserializer >> color;
	deserializer >> blendmode;

	if(!resourceName.Empty())
	{
		texture = GetTextureManager()->Load(resourceName);
		if(texture != null)
			uv = Texture->GetUVRect(sourceRect);
	}

	return deserializer;
}
*/

CE_NAMESPACE_END


