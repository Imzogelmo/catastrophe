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


#include "Catastrophe/Core/Math/Packed/PackedRect.h"
#include "Catastrophe/Graphics/Texture.h"
#include "Catastrophe/Graphics/SpriteBatch.h"
#include "Catastrophe/Graphics/Sprite/StaticSprite.h"

CE_NAMESPACE_BEGIN



StaticSprite::StaticSprite() :
	SpriteBase(),
	size(Vector2::Zero),
	color(Color::White()),
	blendmode(BlendMode::Alpha),
	flipX(false),
	flipY(false)
{
}


StaticSprite::StaticSprite(Texture* texturePtr, const Rect& sourceRectangle) :
	SpriteBase(texturePtr, sourceRectangle),
	size(sourceRectangle.Size()),
	color(Color::White()),
	blendmode(BlendMode::Alpha),
	flipX(false),
	flipY(false)
{
}


StaticSprite::StaticSprite(Texture* texturePtr, const PackedRect& sourceRectangle) :
	SpriteBase(texturePtr, sourceRectangle),
	size(sourceRectangle.Size()),
	color(Color::White()),
	blendmode(BlendMode::Alpha),
	flipX(false),
	flipY(false)
{
}


void StaticSprite::Render(SpriteBatch* spriteBatch, const Vector2& position)
{
	if( texture == null )
		return;

	Rectf textureCoords(uv);
	if(flipX) textureCoords.FlipX();
	if(flipY) textureCoords.FlipY();

	Quad2D quad2D;
	quad2D.SetVertexUVData(position, position + size, textureCoords);
	quad2D.SetColorData(color);

	spriteBatch->DrawQuad(texture->GetTextureID(), quad2D);
}


CE_NAMESPACE_END


