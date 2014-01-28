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

#include "Gui/AnimatedIcon.h"
#include "Graphics/SpriteBatch.h"

CE_NAMESPACE_BEGIN



AnimatedIcon::AnimatedIcon() :
	Widget()
{
}


void AnimatedIcon::Update()
{
	m_sprite.Update();

	// update children
	Widget::Update();
}


void AnimatedIcon::Render( SpriteBatch* spritebatch )
{
	Texture* texture = m_sprite.GetTexture();
	if( !texture )
		return;

	Vector2 pos = GetScreenPosition();
	Vector2 size = m_sprite.size;

	if( m_stretchSprite )
	{
		size = m_size;
	}
	else if( m_centerSprite )
	{
		Vector2 diff = (m_size - size) * 0.5f;
		pos += diff;
	}

	spritebatch->DrawRotatedScaled(
		texture->GetTextureID(),
		m_sprite.angle,
		m_sprite.scale,
		pos + (size * 0.5f),
		Rectf(pos, pos + size),
		m_sprite.GetUVRect(),
		m_sprite.color
	);

	// render children
	Widget::Render(spritebatch);
}


void AnimatedIcon::SetAutoFitSprite( bool stretch )
{
	m_stretchSprite = stretch;
}


void AnimatedIcon::SetAutoCenterSprite( bool center )
{
	m_centerSprite = center;
}




CE_NAMESPACE_END


