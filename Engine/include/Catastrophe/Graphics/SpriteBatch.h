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

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/PlatformMath.h"
#include "Catastrophe/Core/Math/MathUtil.h"
#include "Catastrophe/Core/Math/Vector2.h"
#include "Catastrophe/Core/Math/Rect.h"
#include "Catastrophe/Core/Math/Rectf.h"
#include "Catastrophe/Core/Math/Color.h"
#include "Catastrophe/Core/Containers/Vector.h"

#include "Catastrophe/Graphics/TextAlignment.h"
#include "Catastrophe/Graphics/Common.h"
#include "Catastrophe/Graphics/Blendmode.h"
#include "Catastrophe/Graphics/Vertex.h"
#include "Catastrophe/Graphics/Quad2D.h"


CE_NAMESPACE_BEGIN

struct SpriteData
{};

#define RENDERSTATE_FLAG_TEXTURE	1
#define RENDERSTATE_FLAG_BLENDMODE	2

struct RenderState2D
{
	/// The handle of the gpu texture for this batch.
	u32 textureID;

	/// The blending parameters to use for this batch.
	BlendMode blendMode;

	/// The number of vertices we are rendering in this batch.
	u32 vertexCount;

	/// Flags that describe what state changes need to be applied when rendering.
	u8 stateChangedFlags;

	/// Index of clipping stack.
	u8 clipRectIndex;

	/// Set all states to default values
	void SetToDefaultValues()
	{
		textureID = 0;
		blendMode = BlendMode::Alpha;
		vertexCount = 0;
		stateChangedFlags = 0;
		clipRectIndex = 0;
	}
};


class CE_API SpriteBatch
{
public:

	/// Constructs a new spritebatch with default capacity.
	SpriteBatch(u32 initialCapacity = 256);

	/// Destructor
	~SpriteBatch();

	/// Sets a blendmode value for all future calls to Draw().
	/// SpriteBatch is capable of a seperate BlendMode state for each individual element.
	void SetBlendMode(const BlendMode& blendmode);

	/// Sets a texture id value for all future calls to Draw() that contain no texture ID parameter.
	void SetTextureID(u32 textureID);

	void PushClipRect(const Rect& clipRect);
	void PopClipRect();

	/// Gets the total number of Quad2D that are currently batched.
	u32 GetBatchSize() const { return m_queue.Size(); }

	/// Gets the total number of vertices that are currently batched.
	u32 GetVertexCount() const { return m_queue.Size() * 4; }

	/// The current capacity of the allocated buffer that holds elements of type Quad2D.
	/// If the capacity becomes too large, it may be a good indication that calls to Flush()
	/// should be used after rendering each pool of game components to keep memory usage down.
	u32 GetCapacity() const { return m_queue.Capacity(); }

	/// Set the current capacity of the render queue.
	/// This does nothing if the input capacity is less than GetQuadCount(). 
	void SetCapacity(u32 capacity);

	/// Reserves the internal capacity enough to hold number of quads without any reallocation.
	void Reserve(u32 capacity);

	/// Begins a new batch. This must be called only once for each call to End();
	void Begin();

	/// Ends and flushes the current batch. A call to Begin() is then required to render another batch.
	void End();

	/// Flushes the queue and any reamining vertices to the gpu.
	void Flush();

	void Draw(u32 textureID, const Vector2& position, const Vector2& size, const Rectf& uv, const Color& color = Color::White());
	void Draw(u32 textureID, const Rectf& vertices, const Rectf& uv, const Color& color = Color::White());
	void DrawRotated(u32 textureID, float rotation, const Rectf& vertices, const Rectf& uv, const Color& color = Color::White());
	void DrawRotated(u32 textureID, float rotation, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& color = Color::White());
	void DrawScaled(u32 textureID, const Vector2& scale, const Rectf& vertices, const Rectf& uv, const Color& color = Color::White());
	void DrawScaled(u32 textureID, const Vector2& scale, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& color = Color::White());
	void DrawRotatedScaled(u32 textureID, float rotation, const Vector2& scale, const Rectf& vertices, const Rectf& uv, const Color& color = Color::White());
	void DrawRotatedScaled(u32 textureID, float rotation, const Vector2& scale, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& color = Color::White());

	void DrawSprite(const Sprite& sprite, const Vector2& position);
	void DrawAnimatedSprite(const AnimatedSprite& animatedSprite, const Vector2& position);
	void DrawAnimatedSpriteSet(const AnimatedSpriteSet& spriteset, const Vector2& position);

	/// Draws a quad using the previously set renderstate.
	void DrawQuad(const Quad2D& quad);

	/// Add a quad to this batch.
	void DrawQuad(u32 textureID, const Quad2D& quad);

	/// Add any number of quads to this batch.
	void DrawQuads(u32 textureID, const Quad2D* quads, u32 numQuads);

	void DrawVertices(const VertexColorTexture2D& tl, const VertexColorTexture2D& bl,
		const VertexColorTexture2D& br, const VertexColorTexture2D& t);

	void DrawVertices(u32 textureID,
		const VertexColorTexture2D& tl, const VertexColorTexture2D& bl,
		const VertexColorTexture2D& br, const VertexColorTexture2D& tr);

	/// Draws part of a quad.
	//void DrawPartialQuad(u32 textureID, const Quad2D& quad, const Vector2& delta, Align alignment);

	/// Tiles a sprite of size 'tileSize' across a given area defined by position and size.
	/// If tileSize is not equally divisible by the total size then the last
	/// tile will be clamped appropriately, and only partially drawn.
	void DrawTiled(u32 textureID, const Vector2& position, const Vector2& size, const Vector2& tileSize, const Rectf& uv, const Color& color);

	// Font rendering
	void DrawString(Font* font, const String& text, const Vector2& position, const Color& color, TextAlignment alignment = AlignLeft );
	void DrawString(Font* font, const String& text, u32 textPos, u32 amount, const Vector2& position, const Color& color, TextAlignment alignment = AlignLeft );
	void DrawString(Font* font, const char* first, const char* last, Vector2 position, const Color& color, TextAlignment alignment = AlignLeft );

	void Render();
	void Render(const Matrix& transformation);

private:
	void InternalDraw(u32 textureID, const Rectf& vertices, const Rectf& uv, const Color& color);
	void InternalDrawTransformed(u32 textureID, float rotation, const Vector2& scale, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& color);
	void CheckRenderState(u32 textureID);
	void CheckRenderState(BlendMode blendMode);
	void CheckQueueRenderState();
	void InternalFlush();

	u32						m_currentOffset;
	RenderState2D			m_currentRenderState;
	Vector<RenderState2D>	m_renderStates;
	Vector<Quad2D>			m_queue;
	Vector<Rect>			m_clipStack;

};


CE_NAMESPACE_END

