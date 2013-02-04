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
		gluint texture;
		Rectf uv;
		Vector2 size;

		Patch( gluint texture_id = 0, const Rectf& uv = Rectf::Zero, const Vector2& size = Vector2::Zero)
			: texture(texture_id), uv(uv), size(size)
		{}
	};

	Frame();

	void SetBackground( const Sprite& bgSprite );
	void SetBackgroundTexture( const Texture* texture );
	void SetBackgroundOffset( const Vector2& offset );
	void UseBackGround( bool enable = true );

	void SetTexture( const Texture* texture );
	void SetFromSprite( const Sprite& sprite );
	void SetFromSprite( const AnimatedSprite& sprite );
	void SetPatchData( const Texture* texture, const Vector2& spriteSize, const Rectf& uv );
	void SetBlendMode( const BlendMode& value ) { m_blendmode = value; }

	const BlendMode& GetBlendMode() const { return m_blendmode; }
	const Vector2& GetBackgroundOffset() const { return m_bgOffset; }
	const Sprite& GetBackground() const { return m_backgroundSprite; }
	Sprite& GetBackground() { return m_backgroundSprite; }

	void Render( SpriteBatch* spriteBatch );

protected:
	BlendMode		m_blendmode;
	Patch			m_corners[4];
	Patch			m_sides[4];
	Sprite			m_backgroundSprite;
	Vector2			m_bgOffset;
	bool			m_tiled;
	bool			m_bgTiled;
	bool			m_useBg;

};


CE_NAMESPACE_END
