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
#include "Catastrophe/Core/Math/Rectf.h"
#include "Catastrophe/Core/Math/Packed/PackedRect.h"
#include "Catastrophe/Graphics/Texture.h"

CE_NAMESPACE_BEGIN


/// @SpriteBase
///
/// Base class for most 2D sprite classes.
/// Provides a common interface for managing texture coordinates
/// and source rectangles from a given texture resource.
///

class CE_API SpriteBase
{
public:

	/// The texture used by this sprite.
	SharedPtr<Texture> texture;

	/// The texture coordinates.
	Rectf uv;

	/// The source rectangle of the sprite, in pixels, within the texture or image file.
	PackedRect sourceRect;

	SpriteBase();
	SpriteBase(Texture* texture, const Rect& sourceRectangle);
	SpriteBase(Texture* texture, const PackedRect& sourceRectangle);

	/// Set the texture used by this sprite.
	void SetTexture(Texture* texture);

	/// Get the texture used by this sprite.
	FORCEINLINE Texture* GetTexture() const { return texture; }

	/// Gets the ID of this sprites' texture.
	u32 GetTextureID() const;

	/// Gets the uv rect used to render the sprite.
	const Rectf& GetUVRect() const { return uv; }

	/// Sets the uv rect used to render the sprite.
	void SetUVRect(const Rectf& value) { uv = value; }

	/// Sets the source rectangle of this sprite.
	void SetSourceRect(const PackedRect& sourceRectangle);

	/// Sets the source rectangle of this sprite.
	FORCEINLINE void SetSourceRect(const Rect& sourceRectangle)
	{
		SetSourceRect(PackedRect(sourceRectangle));
	}

	/// Sets the sprite texture coordinates from a source rectangle.
	FORCEINLINE const PackedRect& GetSourceRect() const { return sourceRect; }

	/// Sets the texture, source rectangle, and uv data for this sprite.
	FORCEINLINE void SetSpriteData(Texture* texturePtr, const Rect& sourceRectangle)
	{
		SetSpriteData(texturePtr, PackedRect(sourceRectangle));
	}

	/// Sets the texture and uv data for this sprite.
	void SetSpriteData(Texture* texturePtr, const PackedRect& sourceRectangle);

};


CE_NAMESPACE_END


