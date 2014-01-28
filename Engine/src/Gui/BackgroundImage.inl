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

#include "Gui/BackgroundImage.h"
#include "Graphics/SpriteBatch.h"

CE_NAMESPACE_BEGIN



BackgroundImage::BackgroundImage() :
	Icon()
{
	for( int i(0); i < MAX_CORNERS; ++i )
		m_cornerColors[i] = Color::White();
}


void BackgroundImage::SetCornerColor( int corner, const Color& color )
{
	if( corner < MAX_CORNERS )
		m_cornerColors[corner] = color;
}


Color BackgroundImage::GetCornerColor( int corner ) const
{
	if( corner < MAX_CORNERS )
		return m_cornerColors[corner];

	return Color::White();
}


void BackgroundImage::Update()
{
	// update children
	Icon::Update();
}


void BackgroundImage::Render( SpriteBatch* spritebatch )
{
	if( !m_sprite.GetTexture() )
		return;

	Vector2 minPos = GetScreenPosition();
	Vector2 maxPos = minPos + m_sprite.size;

	Vector2 vtx[4];
	vtx[0] = minPos;
	vtx[1] = Vector2(minPos.x, maxPos.y);
	vtx[2] = maxPos;
	vtx[3] = Vector2(maxPos.x, minPos.y);

	Vector2 uv[4];
	m_sprite.GetUVRect().GetCorners(uv);

	Color colors[4];
	colors[0] = m_cornerColors[0];
	colors[1] = m_cornerColors[1];
	colors[2] = m_cornerColors[2];
	colors[3] = m_cornerColors[3];

	spritebatch->DrawRotatedScaled(
		m_sprite.GetTextureID(),
		m_sprite.angle,
		m_sprite.scale,
		minPos + (m_sprite.size * 0.5f),
		vtx,
		uv,
		colors,
		1
	);

	// render children
	Widget::Render(spritebatch);
}





CE_NAMESPACE_END


