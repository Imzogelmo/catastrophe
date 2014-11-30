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

#include "Gui/Frame.h"
#include "Graphics/SpriteBatch.h"
#include "Graphics/Sprite.h"

CE_NAMESPACE_BEGIN



Frame::Frame() : Widget(),
	m_texture(0)
{
	m_backgroundImage = 0;
	m_tiled = false;
}


void Frame::SetBackgroundImage( BackgroundImage* backgroundImage )
{
	m_backgroundImage = backgroundImage;
}


void Frame::SetTexture( Texture* texture )
{
	if(texture)
	{
		m_texture = texture;
	}
}


void Frame::SetFromSprite( const Sprite& sprite )
{
	SetBlendMode(sprite.blendmode);
	SetPatchData( sprite.GetTexture(),
		sprite.GetSize(),
		sprite.GetUVRect()
	);
}


void Frame::SetFromSprite( const AnimatedSprite& sprite )
{
	SetBlendMode(sprite.blendmode);
	SetPatchData( sprite.GetTexture(),
		sprite.GetSize(),
		sprite.GetUVRect()
	);
}


void Frame::SetPatchData( Texture* texture, const Vector2& spriteSize, const Rectf& uv )
{
	SetTexture(texture);
	Vector2 size = spriteSize / 3.f;
	Vector2 dist = uv.max - uv.min;
	Vector2 d = dist / 3.f;

	// split into a "9-patch" structure.
	// 1 - 2    - 1 -
	// -   -    2   3
	// 3 - 4    - 4 -
	float x[4], y[4];
	x[0] = uv.min.x;
	x[1] = uv.min.x + d.x;
	x[2] = uv.max.x - d.x;
	x[3] = uv.max.x;
	y[0] = uv.min.y;
	y[1] = uv.min.y + d.y;
	y[2] = uv.max.y - d.y;
	y[3] = uv.max.y;

	m_sides[0].uv = Rectf( x[1], y[0], x[2], y[1] );
	m_sides[1].uv = Rectf( x[0], y[1], x[1], y[2] );
	m_sides[2].uv = Rectf( x[2], y[1], x[3], y[2] );
	m_sides[3].uv = Rectf( x[1], y[2], x[2], y[3] );
	m_sides[0].size = size;
	m_sides[1].size = size;
	m_sides[2].size = size;
	m_sides[3].size = size;

	m_corners[0].uv = Rectf( x[0], y[0], x[1], y[1] );
	m_corners[1].uv = Rectf( x[2], y[0], x[3], y[1] );
	m_corners[2].uv = Rectf( x[0], y[2], x[1], y[3] );
	m_corners[3].uv = Rectf( x[2], y[2], x[3], y[3] );
	m_corners[0].size = size;
	m_corners[1].size = size;
	m_corners[2].size = size;
	m_corners[3].size = size;
}


void Frame::Render( SpriteBatch* spriteBatch )
{
	Vector2 min = GetScreenPosition();
	Vector2 max = min + GetSize();

	// render the background first.
	if( m_backgroundImage )
	{
		m_backgroundImage->Render(spriteBatch);
	}

	if( m_texture )
	{
		gluint textureID = m_texture->GetTextureID();

		Rectf vtx;
		vtx.min.x = min.x;
		vtx.min.y = min.y;
		vtx.max.x = min.x + m_corners[0].size.x;
		vtx.max.y = min.y + m_corners[0].size.y;
		spriteBatch->Draw( textureID, vtx, m_corners[0].uv, m_color );

		vtx.min.x = max.x - m_corners[1].size.x;
		vtx.min.y = min.y;
		vtx.max.x = max.x;
		vtx.max.y = min.y + m_corners[1].size.y;
		spriteBatch->Draw( textureID, vtx, m_corners[1].uv, m_color );

		vtx.min.x = min.x;
		vtx.min.y = max.y - m_corners[2].size.y;
		vtx.max.x = min.x + m_corners[2].size.x;
		vtx.max.y = max.y;
		spriteBatch->Draw( textureID, vtx, m_corners[2].uv, m_color );

		vtx.min.x = max.x - m_corners[3].size.x;
		vtx.min.y = max.y - m_corners[3].size.y;
		vtx.max.x = max.x;
		vtx.max.y = max.y;
		spriteBatch->Draw( textureID, vtx, m_corners[3].uv, m_color );

		if( m_tiled )
		{
			SpriteData q;

			q.SetTexture(textureID);
			q.SetBlendMode(m_blendmode);

			q.data[0].color = m_color;
			q.data[1].color = m_color;
			q.data[2].color = m_color;
			q.data[3].color = m_color;

			q.data[0].uv.x = m_corners[0].uv.min.x;

		}
		else
		{
			vtx.min.x = min.x + m_corners[0].size.x;
			vtx.min.y = min.y;
			vtx.max.x = max.x - m_corners[1].size.x;
			vtx.max.y = min.y + m_sides[0].size.y;
			spriteBatch->Draw( textureID, vtx, m_sides[0].uv, m_color );

			vtx.min.x = min.x;
			vtx.min.y = min.y + m_corners[0].size.y;
			vtx.max.x = min.x + m_sides[1].size.x;
			vtx.max.y = max.y - m_corners[2].size.y;
			spriteBatch->Draw( textureID, vtx, m_sides[1].uv, m_color );

			vtx.min.x = max.x - m_sides[2].size.x;
			vtx.min.y = min.y + m_corners[1].size.y;
			vtx.max.x = max.x;
			vtx.max.y = max.y - m_corners[3].size.y;
			spriteBatch->Draw( textureID, vtx, m_sides[2].uv, m_color );

			vtx.min.x = min.x + m_corners[2].size.x;
			vtx.min.y = max.y - m_sides[3].size.y;
			vtx.max.x = max.x - m_corners[3].size.x;
			vtx.max.y = max.y;
			spriteBatch->Draw( textureID, vtx, m_sides[3].uv, m_color );

		}
	}

	// render children.
	Widget::Render(spriteBatch);
}


CE_NAMESPACE_END
