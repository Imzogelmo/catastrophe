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

#include "Catastrophe/Graphics/Texture.h"
#include "Catastrophe/Graphics/Sprite/BackgroundSprite.h"

CE_NAMESPACE_BEGIN



BackgroundSprite::BackgroundSprite() :
	SpriteBase(),
	borderOffset(Vector2::Zero),
	blendmode(BlendMode::Alpha)
{
	const Color defaultColor = Color::White();
	cornerColors[0] = defaultColor;
	cornerColors[1] = defaultColor;
	cornerColors[2] = defaultColor;
	cornerColors[3] = defaultColor;
}


BackgroundSprite::BackgroundSprite(Texture* texturePtr, const Rect& sourceRectangle, const Vector2& spriteBorderOffset) :
	SpriteBase(texturePtr, sourceRectangle),
	borderOffset(spriteBorderOffset),
	blendmode(BlendMode::Alpha)
{
	const Color defaultColor = Color::White();
	cornerColors[0] = defaultColor;
	cornerColors[1] = defaultColor;
	cornerColors[2] = defaultColor;
	cornerColors[3] = defaultColor;
}


void BackgroundSprite::SetCornerColors(const Color* colors)
{
	cornerColors[0] = colors[0];
	cornerColors[1] = colors[1];
	cornerColors[2] = colors[2];
	cornerColors[3] = colors[3];
}


void BackgroundSprite::GetCornerColors(Color* colorArray)
{
	colorArray[0] = cornerColors[0];
	colorArray[1] = cornerColors[1];
	colorArray[2] = cornerColors[2];
	colorArray[3] = cornerColors[3];
}


void BackgroundSprite::Render(SpriteBatch* spritebatch, const Vector2& position, const Vector2& size)
{
	if( texture == null )
		return;

	// Dont render anything if the sprite is negative-sized or invisible due to border offset.
	const Vector2 halfSize = size * 0.5f;
	if(borderOffset.x < halfSize.x && borderOffset.y < halfSize.y)
	{
		Quad2D quad;
		quad.SetVertexUVData(position + borderOffset, position + size - borderOffset, uv);
		quad.SetColorData(cornerColors);

		spritebatch->DrawQuad(texture->GetTextureID(), quad);
	}
}


CE_NAMESPACE_END


