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

#include "Gui/Frame.h"
#include "Graphics/SpriteBatch.h"
#include "Graphics/Sprite.h"

CE_NAMESPACE_BEGIN



Frame::Frame() : Widget()
{
	m_bgOffset = Vector2::Zero;
	m_tiled = false;
	m_bgTiled = false;
	m_useBg = false;
}


void Frame::SetBackground( const Sprite& bgSprite )
{
	CE_ASSERT(bgSprite.GetTexture() != 0);
	m_backgroundSprite = bgSprite;
	m_useBg = true;
}


void Frame::SetBackgroundTexture( Texture* texture )
{
	CE_ASSERT(texture);
	if(texture)
	{
		m_backgroundSprite.SetTexture(texture);
		m_backgroundSprite.SetSize( Vector2( Point(texture->Width(), texture->Height()) ) );
		m_useBg = true;
	}
}


void Frame::SetBackgroundOffset( const Vector2& offset )
{
	m_bgOffset = offset;
}


void Frame::UseBackGround( bool enable )
{
	m_useBg = enable;
}


void Frame::SetTexture( Texture* texture )
{
	CE_ASSERT(texture);
	if(texture)
	{
		gluint id = texture->GetTextureID();
		m_corners[0].texture = id;
		m_corners[1].texture = id;
		m_corners[2].texture = id;
		m_corners[3].texture = id;
		m_sides[0].texture = id;
		m_sides[1].texture = id;
		m_sides[2].texture = id;
		m_sides[3].texture = id;
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
	if( m_useBg && m_backgroundSprite.GetTexture() != 0 )
	{
		if( m_bgTiled )
		{
			//todo...
		}
		else
		{
			spriteBatch->DrawRotatedScaled(
				m_backgroundSprite.GetTextureID(),
				m_backgroundSprite.angle,
				m_backgroundSprite.scale,
				Rectf(min + m_bgOffset, max - m_bgOffset),
				m_backgroundSprite.GetUVRect(),
				m_backgroundSprite.color,
				0
			);
		}
	}

	Rectf vtx;
	vtx.min.x = min.x;
	vtx.min.y = min.y;
	vtx.max.x = min.x + m_corners[0].size.x;
	vtx.max.y = min.y + m_corners[0].size.y;
	spriteBatch->Draw( m_corners[0].texture, vtx, m_corners[0].uv, m_color );

	vtx.min.x = max.x - m_corners[1].size.x;
	vtx.min.y = min.y;
	vtx.max.x = max.x;
	vtx.max.y = min.y + m_corners[1].size.y;
	spriteBatch->Draw( m_corners[1].texture, vtx, m_corners[1].uv, m_color );

	vtx.min.x = min.x;
	vtx.min.y = max.y - m_corners[2].size.y;
	vtx.max.x = min.x + m_corners[2].size.x;
	vtx.max.y = max.y;
	spriteBatch->Draw( m_corners[2].texture, vtx, m_corners[2].uv, m_color );

	vtx.min.x = max.x - m_corners[3].size.x;
	vtx.min.y = max.y - m_corners[3].size.y;
	vtx.max.x = max.x;
	vtx.max.y = max.y;
	spriteBatch->Draw( m_corners[3].texture, vtx, m_corners[3].uv, m_color );

	if( m_tiled )
	{
		//todo...
	}
	else
	{
		vtx.min.x = min.x + m_corners[0].size.x;
		vtx.min.y = min.y;
		vtx.max.x = max.x - m_corners[1].size.x;
		vtx.max.y = min.y + m_sides[0].size.y;
		spriteBatch->Draw( m_sides[0].texture, vtx, m_sides[0].uv, m_color );

		vtx.min.x = min.x;
		vtx.min.y = min.y + m_corners[0].size.y;
		vtx.max.x = min.x + m_sides[1].size.x;
		vtx.max.y = max.y - m_corners[2].size.y;
		spriteBatch->Draw( m_sides[1].texture, vtx, m_sides[1].uv, m_color );

		vtx.min.x = max.x - m_sides[2].size.x;
		vtx.min.y = min.y + m_corners[1].size.y;
		vtx.max.x = max.x;
		vtx.max.y = max.y - m_corners[3].size.y;
		spriteBatch->Draw( m_sides[2].texture, vtx, m_sides[2].uv, m_color );

		vtx.min.x = min.x + m_corners[2].size.x;
		vtx.min.y = max.y - m_sides[3].size.y;
		vtx.max.x = max.x - m_corners[3].size.x;
		vtx.max.y = max.y;
		spriteBatch->Draw( m_sides[3].texture, vtx, m_sides[3].uv, m_color );

	}

	// render children.
	Widget::Render(spriteBatch);
}


CE_NAMESPACE_END