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

#include "Catastrophe/Core/Math/Matrix.h"
#include "Catastrophe/Core/Math/Rectf.h"
#include "Catastrophe/Core/PlatformMath.h"
#include "Catastrophe/Core/Math/MathUtil.h"

#include "Graphics/SpriteBatch.h"
#include "Graphics/Sprite.h"
#include "Graphics/AnimatedSpriteSet.h"
#include "Graphics/OpenGL.h"

CE_NAMESPACE_BEGIN



SpriteBatch::SpriteBatch(u32 initialCapacity) :
	m_currentOffset(0),
	m_currentRenderState(),
	m_renderStates(),
	m_queue(),
	m_clipStack()
{
	m_currentRenderState.SetToDefaultValues();
	Reserve(initialCapacity);
}


SpriteBatch::~SpriteBatch()
{
}


void SpriteBatch::SetBlendMode(const BlendMode& blendmode)
{
	CheckRenderState(blendmode);
}


void SpriteBatch::SetTextureID(u32 textureID)
{
	CheckRenderState(textureID);
}


void SpriteBatch::SetCapacity(u32 capacity)
{
	// If we're losing memory we have to flush to prevent possible buffer overflow.
	if(capacity >= m_queue.Size())
		Flush();

	m_queue.SetCapacity(capacity);
}


void SpriteBatch::Reserve(u32 reserve )
{
	m_queue.Reserve(reserve);
}


void SpriteBatch::Begin()
{
	m_queue.Clear();
}


void SpriteBatch::End()
{
	//if(m_shader)
	//	m_shader->Unbind();
}


void SpriteBatch::PushClipRect(const Rect& clipRect )
{
}


void SpriteBatch::PopClipRect()
{
}


void SpriteBatch::Flush()
{
	InternalFlush();
}


void SpriteBatch::Draw(u32 textureID, const Vector2& position, const Vector2& size, const Rectf& uv, const Color& color)
{
	InternalDraw(textureID, Rectf(position, position + size), uv, color);
}


void SpriteBatch::Draw(u32 textureID, const Rectf& vertices, const Rectf& uv, const Color& color)
{
	InternalDraw(textureID, vertices, uv, color);
}


void SpriteBatch::DrawRotated(u32 textureID, float rotation, const Rectf& vertices, const Rectf& uv, const Color& color)
{
	InternalDrawTransformed(textureID, rotation, 1.f, vertices.Center(), vertices, uv, color);
}


void SpriteBatch::DrawRotated(u32 textureID, float rotation, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& color)
{
	InternalDrawTransformed(textureID, rotation, 1.f, origin, vertices, uv, color);
}


void SpriteBatch::DrawScaled(u32 textureID, const Vector2& scale, const Rectf& vertices, const Rectf& uv, const Color& color)
{
	InternalDrawTransformed(textureID, 0.f, scale, vertices.Center(), vertices, uv, color);
}


void SpriteBatch::DrawScaled(u32 textureID, const Vector2& scale, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& color)
{
	InternalDrawTransformed(textureID, 0.f, scale, origin, vertices, uv, color);
}


void SpriteBatch::DrawRotatedScaled(u32 textureID, float rotation, const Vector2& scale, const Rectf& vertices, const Rectf& uv, const Color& color)
{
	InternalDrawTransformed(textureID, rotation, scale, vertices.Center(), vertices, uv, color);
}


void SpriteBatch::DrawRotatedScaled(u32 textureID, float rotation, const Vector2& scale, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& color)
{
	InternalDrawTransformed(textureID, rotation, scale, origin, vertices, uv, color);
}


void SpriteBatch::DrawSprite(const Sprite& sprite, const Vector2& position )
{
	if(sprite.GetTexture() != null)
	{
		CheckRenderState(sprite.GetBlendMode());

		const Vector2 halfSize = sprite.size * 0.5f;
		InternalDrawTransformed(
			sprite.GetTextureID(),
			sprite.angle,
			sprite.scale,
			position,
			Rectf(position - halfSize, position + halfSize),
			sprite.GetUVRect(),
			sprite.color
		);
	}
}


void SpriteBatch::DrawAnimatedSprite(const AnimatedSprite& sprite, const Vector2& position )
{
	if(sprite.GetTexture() != null)
	{
		Rectf uv = sprite.GetUVRect();
		if(sprite.GetFlipX() )
			uv.FlipX();
		if(sprite.GetFlipY() )
			uv.FlipY();

		CheckRenderState(sprite.GetBlendMode());

		const Vector2 halfSize = sprite.size * 0.5f;
		InternalDrawTransformed(
			sprite.GetTextureID(),
			sprite.angle,
			sprite.scale,
			position,
			Rectf(position - halfSize, position + halfSize),
			uv,
			sprite.color
		);
	}
}


void SpriteBatch::DrawAnimatedSpriteSet(const AnimatedSpriteSet& spriteset, const Vector2& position )
{
	if(spriteset.Empty() || spriteset.GetTexture() == null)
		return;

	CheckRenderState(spriteset.GetBlendMode());

	const Vector2 halfSize = spriteset.size * 0.5f;
	InternalDrawTransformed(
		spriteset.GetTextureID(),
		spriteset.angle,
		spriteset.scale,
		position,
		Rectf(position - halfSize, position + halfSize),
		spriteset.GetCurrentAnimation().GetUVRect(),
		spriteset.color
	);
}


void SpriteBatch::DrawQuad(const Quad2D& quad)
{
	*m_queue.AddUninitialized() = quad;
}


void SpriteBatch::DrawQuad(u32 textureID, const Quad2D& quad)
{
	CheckRenderState(textureID);

	*m_queue.AddUninitialized() = quad;
}


void SpriteBatch::DrawQuads(u32 textureID, const Quad2D* quads, u32 numQuads)
{
	CheckRenderState(textureID);

	// Fastest method; binary copy of raw, uninitialized memory.
	Quad2D* p = m_queue.AddUninitialized(numQuads);
	Memory::Memcpy(p, quads, numQuads * sizeof(Quad2D));
}


void SpriteBatch::DrawVertices(const VertexColorTexture2D& tl, const VertexColorTexture2D& bl,
							   const VertexColorTexture2D& br, const VertexColorTexture2D& tr)
{
	Quad2D* quad = m_queue.AddUninitialized();
	quad->vertices[0] = tl;
	quad->vertices[1] = bl;
	quad->vertices[2] = br;
	quad->vertices[3] = tr;
}


void SpriteBatch::DrawVertices(u32 textureID, const VertexColorTexture2D& tl, const VertexColorTexture2D& bl,
							   const VertexColorTexture2D& br, const VertexColorTexture2D& tr)
{
	CheckRenderState(textureID);

	Quad2D* quad = m_queue.AddUninitialized();
	quad->vertices[0] = tl;
	quad->vertices[1] = bl;
	quad->vertices[2] = br;
	quad->vertices[3] = tr;
}


void SpriteBatch::DrawTiled(u32 textureID, const Vector2& position, const Vector2& size, const Vector2& tileSize, const Rectf& uv, const Color& color )
{
	CheckRenderState(textureID);

	Quad2D currentQuad;
	currentQuad.SetUVData(uv);
	currentQuad.SetColorData(color);

	float maxTileWidth = tileSize.x;
	float maxTileHeight = tileSize.y;
	float width = size.x;
	float height = size.y;

	for(float y = 0.f; y < height; y += maxTileHeight)
	{
		float tileHeight = Math::Min(height - y, maxTileHeight);

		if(Math::EpsilonCompare(y, height) )
			break;

		for(float x = 0.f; x < width; x += maxTileWidth)
		{
			if(Math::EpsilonCompare(x, width) )
				break;

			float tileWidth = Math::Min(width - x, maxTileWidth);
			float positionX = position.x + x;
			float positionY = position.y + y;

			currentQuad.SetVertexData(positionX, positionY, positionX + tileWidth, positionY + tileHeight);
			Quad2D* p = m_queue.AddUninitialized();
			*p = currentQuad;

			// If rendering a partial tile then we have to clamp the uv.
			if(!Math::EpsilonCompare(tileWidth, maxTileWidth) || !Math::EpsilonCompare(tileHeight, maxTileHeight) )
			{
				Vector2 d = Vector2(tileWidth / maxTileWidth ,tileHeight / maxTileHeight);
				Rectf clampedUV = Rectf(uv.min, uv.max * d);
				p->SetUVData(clampedUV);
			}
		}
	}
}


// Text rendering

void SpriteBatch::DrawString( Font* font, const String& text, const Vector2& position, const Color& color, TextAlignment alignment )
{
	DrawString( font, text.begin(), text.end(), position, color, alignment );
}


void SpriteBatch::DrawString( Font* font, const String& text, u32 textPos, u32 amount, const Vector2& position, const Color& color, TextAlignment alignment )
{
	DrawString( font, text.begin() + textPos, text.begin() + textPos + amount, position, color, alignment );
}


void SpriteBatch::DrawString( Font* font, const char* first, const char* last, Vector2 position, const Color& color, TextAlignment alignment )
{
	CE_ASSERT(first <= last);

	Vector2 originalPos = position;

	if(alignment == AlignCenter)
	{
		position.x += (float)(font->GetTextWidth(first, last) / 2.f);
	}
	else if(alignment == AlignRight)
	{
		position.x -= (float)font->GetTextWidth(first, last);
	}

	Quad2D quad;
	quad.SetColorData(color);

	if(first != last)
		CheckRenderState(font->GetTextureID());

	for( ; first != last; ++first )
	{
		const Glyph* glyph = &font->GetGlyph(*first);
		if(*first == '\n')
		{
			position.x = originalPos.x;
			position.y += (float)font->GetLineHeight();
			continue;
		}

		if(*first != ' ')
		{
			const Vector2 minPosition = position + glyph->translation;
			const Vector2 maxPosition = minPosition + glyph->size;

			quad.SetVertexUVData(minPosition, maxPosition, glyph->uv);
			m_queue.Add(quad);
		}

		position.x += glyph->advance;
	}
}


void SpriteBatch::InternalDraw(u32 textureID, const Rectf& vertices, const Rectf& uv, const Color& color)
{
	CheckRenderState(textureID);

	Quad2D* quad = m_queue.AddUninitialized();
	quad->SetVertexUVColorData((const float*)&vertices, (const float*)&uv, color);
}


void SpriteBatch::InternalDrawTransformed
(u32 textureID, float rotation, const Vector2& scale, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& color)
{
	CheckRenderState(textureID);

	Quad2D* quad = m_queue.AddUninitialized();
	quad->SetVertexUVColorData((const float*)&vertices, (const float*)&uv, color);
	quad->Transform(rotation, scale, origin);
}


void SpriteBatch::CheckRenderState(u32 textureID)
{
	if(m_currentRenderState.textureID != textureID)
	{
		CheckQueueRenderState();

		m_currentRenderState.textureID = textureID;
		m_currentRenderState.stateChangedFlags |= RENDERSTATE_FLAG_TEXTURE;
	}
}


void SpriteBatch::CheckRenderState(BlendMode blendMode)
{
	if(m_currentRenderState.blendMode != blendMode)
	{
		CheckQueueRenderState();

		m_currentRenderState.blendMode = blendMode;
		m_currentRenderState.stateChangedFlags |= RENDERSTATE_FLAG_BLENDMODE;
	}
}


void SpriteBatch::CheckQueueRenderState()
{
	const u32 queueSize = m_queue.Size();

	// If this is not the first render state then queue it
	if(m_currentOffset != queueSize)
	{
		m_currentRenderState.vertexCount = (queueSize - m_currentOffset) * 4;
		m_currentOffset = queueSize;

		m_renderStates.Add(m_currentRenderState);

		// Reset flags
		m_currentRenderState.stateChangedFlags = 0;
		//m_currentRenderState.clipRectIndex = 0;
	}
}


void SpriteBatch::Render()
{
	// Simply flush the remaining vertices.
	InternalFlush();
}


void SpriteBatch::Render(const Matrix& transformation )
{
	glPushMatrix();
	glMultMatrixf(&transformation.m[0]);
	Render();
	glPopMatrix();
}


void SpriteBatch::InternalFlush()
{
	if(m_queue.Empty() )
		return;

	bool used_scissor = false;
	//if(m_clippingEnabled && !m_clipRect.Empty() )
	//{
	//	used_scissor = true;
	//	const Rect& r = m_clipRect;

	//	int viewport[4];
	//	glGetIntegerv(GL_VIEWPORT, viewport);

	//	glEnable(GL_SCISSOR_TEST);
	//	glScissor(r.position.x , viewport[3] - r.position.y - r.size.y, r.size.x, r.size.y);
	//}

	//if(m_shader)
	//	m_shader->Bind(); //fixme:

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	const VertexColorTexture2D* vertexPointer = (const VertexColorTexture2D*)&m_queue[0];
	glVertexPointer(2, GL_FLOAT, sizeof(VertexColorTexture2D), &vertexPointer->position);
	glTexCoordPointer(2, GL_FLOAT, sizeof(VertexColorTexture2D), &vertexPointer->uv);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(VertexColorTexture2D), &vertexPointer->color);


	// Make sure that we flush the current state if there are vertices pending.
	CheckQueueRenderState();

	u32 vertexOffset = 0;
	for(const RenderState2D* renderStates = m_renderStates.begin(); renderStates != m_renderStates.end(); ++renderStates)
	{
		const u32 vertexCount = (u32)renderStates->vertexCount;
		const u32 renderStateFlags = (u32)renderStates->stateChangedFlags;

		if((renderStateFlags & RENDERSTATE_FLAG_TEXTURE) != 0)
		{
			glBindTexture(GL_TEXTURE_2D, renderStates->textureID);
		}

		if((renderStateFlags & RENDERSTATE_FLAG_BLENDMODE) != 0)
		{
			renderStates->blendMode.Apply();
		}

		glDrawArrays(GL_QUADS, vertexOffset, vertexCount);

		vertexOffset += vertexCount;
	}

	//if(used_scissor)
	//	glDisable(GL_SCISSOR_TEST);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	// Reset offset to vertex buffer and empty queue.
	m_currentOffset = 0;
	m_queue.Clear();
	m_renderStates.Clear();

}



CE_NAMESPACE_END

