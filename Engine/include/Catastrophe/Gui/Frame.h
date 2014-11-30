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

#include "Widget.h"
#include "../Math/Vector2.h"
#include "../Math/Rectf.h"
#include "../Graphics/BlendMode.h"
#include "../Graphics/Sprite.h"

CE_NAMESPACE_BEGIN


class Frame : public Widget
{
public:
	struct Patch
	{
		Rectf uv;
		Vector2 size;

		Patch( const Rectf& uv = Rectf::Zero, const Vector2& size = Vector2::Zero )
			: uv(uv), size(size)
		{}
	};

	Frame();

	void SetColor( const Color& color ) { m_color = color; }

	void SetBackgroundImage( BackgroundImage* backgroundImage );
	void SetTexture( Texture* texture );
	void SetFromSprite( const Sprite& sprite );
	void SetFromSprite( const AnimatedSprite& sprite );
	void SetPatchData( Texture* texture, const Vector2& spriteSize, const Rectf& uv );

	BackgroundImage* GetBackgroundImage() const { return m_backgroundImage; }
	void Render( SpriteBatch* spriteBatch );

protected:
	Texture*			m_texture;
	Patch				m_corners[4];
	Patch				m_sides[4];
	BackgroundImage*	m_backgroundImage;
	bool				m_tiled;

};


CE_NAMESPACE_END
