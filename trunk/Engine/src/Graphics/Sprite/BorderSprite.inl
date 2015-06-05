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

#include "Catastrophe/Core/Math/Rect.h"
#include "Catastrophe/Graphics/Sprite/BorderSprite.h"
#include "Catastrophe/Graphics/Texture.h"
#include "Catastrophe/Graphics/Vertex.h"
#include "Catastrophe/Graphics/SpriteBatch.h"

CE_NAMESPACE_BEGIN


BorderSprite::BorderSprite() :
	StaticSprite(),
	borderSize(Vector2::Zero),
	isTiled(false),
	isSolid(false)
{
}


BorderSprite::BorderSprite(TexturePtr texture, const PackedRect& sourceRectangle) :
	StaticSprite(),
	borderSize(Vector2::Zero),
	isTiled(false),
	isSolid(false)
{
	SetSpriteData(texture, sourceRect);
}


void BorderSprite::SetSpriteData(Texture* texturePtr, const PackedRect& sourceRectangle)
{
	borderSize = Vector2(sourceRectangle.Size()) / 3.f;
	StaticSprite::SetSpriteData(texturePtr, sourceRectangle);
}


void BorderSprite::Render(SpriteBatch* spriteBatch, const Vector2& position, const Vector2& size)
{
	if( texture == null )
		return;

	// split into a "9-patch" structure.
	// 1 - 2    - 1 -
	// -   -    2   3
	// 3 - 4    - 4 -

	VertexColorTexture2D vertices[16];
	{
		const float minX = position.x;
		const float minY = position.y;
		const float maxX = position.x + size.x;
		const float maxY = position.y + size.y;
		const float borderX = borderSize.x;
		const float borderY = borderSize.y;

		const Vector2 d = uv.Size() / 3.f;

		float x[4], y[4];
		x[0] = minX;
		x[1] = minX + borderX;
		x[2] = maxX - borderX;
		x[3] = maxX;
		y[0] = minY;
		y[1] = minY + borderY;
		y[2] = maxY - borderY;
		y[3] = maxY;

		float u[4], v[4];
		u[0] = uv.min.x;
		u[1] = uv.min.x + d.x;
		u[2] = uv.max.x - d.x;
		u[3] = uv.max.x;
		v[0] = uv.min.y;
		v[1] = uv.min.y + d.y;
		v[2] = uv.max.y - d.y;
		v[3] = uv.max.y;

		Color vertexColor = color;

		vertices[0] = VertexColorTexture2D(Vector2(x[0], y[0]), Vector2(u[0], v[0]), vertexColor);
		vertices[1] = VertexColorTexture2D(Vector2(x[1], y[0]), Vector2(u[1], v[0]), vertexColor);
		vertices[2] = VertexColorTexture2D(Vector2(x[2], y[0]), Vector2(u[2], v[0]), vertexColor);
		vertices[3] = VertexColorTexture2D(Vector2(x[3], y[0]), Vector2(u[3], v[0]), vertexColor);

		vertices[4] = VertexColorTexture2D(Vector2(x[0], y[1]), Vector2(u[0], v[1]), vertexColor);
		vertices[5] = VertexColorTexture2D(Vector2(x[1], y[1]), Vector2(u[1], v[1]), vertexColor);
		vertices[6] = VertexColorTexture2D(Vector2(x[2], y[1]), Vector2(u[2], v[1]), vertexColor);
		vertices[7] = VertexColorTexture2D(Vector2(x[3], y[1]), Vector2(u[3], v[1]), vertexColor);

		vertices[8] = VertexColorTexture2D(Vector2(x[0], y[2]), Vector2(u[0], v[2]), vertexColor);
		vertices[9] = VertexColorTexture2D(Vector2(x[1], y[2]), Vector2(u[1], v[2]), vertexColor);
		vertices[10] = VertexColorTexture2D(Vector2(x[2], y[2]), Vector2(u[2], v[2]), vertexColor);
		vertices[11] = VertexColorTexture2D(Vector2(x[3], y[2]), Vector2(u[3], v[2]), vertexColor);

		vertices[12] = VertexColorTexture2D(Vector2(x[0], y[3]), Vector2(u[0], v[3]), vertexColor);
		vertices[13] = VertexColorTexture2D(Vector2(x[1], y[3]), Vector2(u[1], v[3]), vertexColor);
		vertices[14] = VertexColorTexture2D(Vector2(x[2], y[3]), Vector2(u[2], v[3]), vertexColor);
		vertices[15] = VertexColorTexture2D(Vector2(x[3], y[3]), Vector2(u[3], v[3]), vertexColor);
	}

	u32 textureID = texture->GetTextureID();
	spriteBatch->SetTextureID(textureID);

	// Draw the corners
	spriteBatch->DrawVertices(vertices[0], vertices[4], vertices[5], vertices[1]);
	spriteBatch->DrawVertices(vertices[2], vertices[6], vertices[7], vertices[3]);
	spriteBatch->DrawVertices(vertices[8], vertices[12], vertices[13], vertices[9]);
	spriteBatch->DrawVertices(vertices[10], vertices[14], vertices[15], vertices[11]);

	// Draw the sides
	if( isTiled )
	{
		// Draw the the sides so they are tiled across the w, h instead of stretched. Slower.
		spriteBatch->DrawTiled(textureID, vertices[1].position, vertices[6].position - vertices[1].position, borderSize, Rectf(vertices[1].uv, vertices[6].uv), color);
		spriteBatch->DrawTiled(textureID, vertices[4].position, vertices[9].position - vertices[4].position, borderSize, Rectf(vertices[4].uv, vertices[9].uv), color);
		spriteBatch->DrawTiled(textureID, vertices[6].position, vertices[11].position - vertices[6].position, borderSize, Rectf(vertices[6].uv, vertices[11].uv), color);
		spriteBatch->DrawTiled(textureID, vertices[9].position, vertices[14].position - vertices[9].position, borderSize, Rectf(vertices[9].uv, vertices[14].uv), color);
	}
	else
	{
		// Here the sprite is simply stretched to fit. Fastest method.
		spriteBatch->DrawVertices(vertices[1], vertices[5], vertices[6], vertices[2]);
		spriteBatch->DrawVertices(vertices[4], vertices[8], vertices[9], vertices[5]);
		spriteBatch->DrawVertices(vertices[6], vertices[10], vertices[11], vertices[7]);
		spriteBatch->DrawVertices(vertices[9], vertices[13], vertices[14], vertices[10]);
	}

	// Draw the center
	if(isSolid)
	{
		spriteBatch->DrawVertices(vertices[5], vertices[9], vertices[10], vertices[6]);
	}
}


CE_NAMESPACE_END
