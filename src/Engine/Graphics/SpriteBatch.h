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

#include <fc/vector.h>

#include "../Common.h"
#include "../Math/Common.h"
#include "../Math/Vector2.h"
#include "../Math/Rect.h"
#include "../Math/Color.h"

#include "Blendmode.h"
#include "SpriteSort.h"
#include "Shader.h"
#include "Font.h"

CE_NAMESPACE_BEGIN


/*
class Renderer
{
public:
	virtual void Begin() = 0;
	virtual void Render() = 0;
	virtual void End() = 0;
};
*/

struct VertexTextureSpriteData2D
{
	Vector2 pos, uv;
	Color color;

	//contains all possible rendering states of a sprite.
	union
	{
		gluint	texture;
		size_t	blendmode;
		int		depth;
		float	y_pos;
	};
};

FC_MAKE_TRAIT(VertexTextureSpriteData2D, is_pod);


struct SpriteData
{
	// aggregate type
	VertexTextureSpriteData2D data[4];

	inline void SetTexture( gluint texture ) { data[0].texture = texture; }
	inline void SetBlendMode( const BlendMode& blendmode ) { data[1].blendmode = blendmode.value; }
	inline void SetDepth( int depth ) { data[2].depth = depth; }
	inline void SetYPosition( float pos ) { data[3].y_pos = pos; }

	inline gluint GetTexture() const { return data[0].texture; }
	inline size_t GetBlendMode() const { return data[1].blendmode; }
	inline int GetDepth() const { return data[2].depth; }
	inline float GetYPosition() const { return data[3].y_pos; }
};

FC_MAKE_TRAIT(SpriteData, is_pod);


class CE_API SpriteBatch
{
public:
	typedef fc::vector<SpriteData> vec_type;

	 SpriteBatch( size_t reserve = 256 );
	~SpriteBatch();

	void Reserve( size_t reserve );
	void Clear();

	void SetBlendMode( const BlendMode& blendmode = BlendMode() ) { m_current_blendmode = blendmode; }
	void SetClippingRect( const Rect& rect ) { m_clip_rect = rect; }
	void SetSortMode( SpriteSortMode mode = Deferred ) { m_sortmode = mode; }
	void SetShader( Shader* shader = 0 ) { m_attached_shader = shader; }
	void SetMaxHardwareBatchSize( size_t maxHardwareBatch = size_t(-1) );

	void EnableClipping( bool enable = true ) { m_enable_clipping = enable; }
	void EnableSorting( bool enable = true ) { m_enable_sorting = enable; }
	void EnableShader( bool enable = true ) { m_enable_shader = enable; }

	bool IsClippingEnabled() const { return m_enable_clipping; }
	bool IsSortingEnabled() const { return m_enable_sorting; }
	bool IsShaderEnabled() const { return m_enable_shader; }

	BlendMode GetCurrentBlendMode() const { return m_current_blendmode; }
	Rect GetClippingRect() const { return m_clip_rect; }
	SpriteSortMode GetSortMode() const { return m_sortmode; }
	size_t GetMaxHardwareBatchSize() const { return m_max_batch_usage; }

	Shader* GetShader() { return m_attached_shader; }
	const Shader* GetShader() const { return m_attached_shader; }

	size_t GetSpriteCount() const { return m_queue.size(); }
	size_t GetVertexCount() const { return m_queue.size() * 4; }
	size_t GetCapacity() const { return m_queue.capacity(); }

	//sort usually never needs to be called by the user.
	void Sort();
	void Begin();

	//void Draw( Texture* tex, const Vector2& pos, const Rectf& uv = Rectf(0.f, 0.f, 1.f, 1.f), const Color& c = Color::White(), int depth = 0 );
	//void Draw( Texture* tex, const Vector2& pos, const Vector2& size, const Rectf& uv = Rectf(0.f, 0.f, 1.f, 1.f), const Color& c = Color::White(), int depth = 0 );

	void Draw( gluint texture, const Rectf& vertices, const Rectf& uv, const Color& c = Color::White(), int depth = 0 );
	void DrawRotated( gluint texture, float rotation, const Rectf& vertices, const Rectf& uv, const Color& c = Color::White(), int depth = 0 );
	void DrawRotated( gluint texture, float rotation, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& c = Color::White(), int depth = 0 );
	void DrawScaled( gluint texture, const Vector2& scale, const Rectf& vertices, const Rectf& uv, const Color& c = Color::White(), int depth = 0 );
	void DrawScaled( gluint texture, const Vector2& scale, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& c = Color::White(), int depth = 0 );
	void DrawRotatedScaled( gluint texture, float rotation, const Vector2& scale, const Rectf& vertices, const Rectf& uv, const Color& c = Color::White(), int depth = 0 );
	void DrawRotatedScaled( gluint texture, float rotation, const Vector2& scale, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& c = Color::White(), int depth = 0 );

	void Draw( gluint texture, const Vector2* vtx, const Vector2* uv, const Color* c, size_t numQuads, int depth = 0 );
	void DrawRotated( gluint texture, float rotation, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, size_t numQuads, int depth = 0 );
	void DrawScaled( gluint texture, const Vector2& scale, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, size_t numQuads, int depth = 0 );
	void DrawRotatedScaled( gluint texture, float rotation, const Vector2& scale, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, size_t numQuads, int depth = 0 );

	void Draw( gluint texture, const Vector2* vtx, const Vector2* uv, const Color* c, const ushort *quadsIndices, size_t numQuads, int depth = 0 );
	void DrawRotated( gluint texture, float rotation, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, const ushort *quadsIndices, size_t numQuads, int depth = 0 );
	void DrawScaled( gluint texture, const Vector2& scale, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, const ushort *quadsIndices, size_t numQuads, int depth = 0 );
	void DrawRotatedScaled( gluint texture, float rotation, const Vector2& scale, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, const ushort *quadsIndices, size_t numQuads, int depth = 0 );

	void DrawString( Font* font, const fc::string& text, const Vector2& pos, const Color& c = Color::White(), TextAlignment alignment = AlignLeft, int face_size = Font::DefaultFaceSize, int depth = 0 );
	void DrawString( Font* font, const fc::string& text, size_t textPos, size_t amount, const Vector2& pos, const Color& c = Color::White(), TextAlignment alignment = AlignLeft, int face_size = Font::DefaultFaceSize, int depth = 0 );
	void DrawString( Font* font, const fc::string& text, const Vector2& scale, const Vector2& pos, const Color& c = Color::White(), TextAlignment alignment = AlignLeft, int face_size = Font::DefaultFaceSize, int depth = 0 );

	void DrawSprite( const Sprite& sprite, const Vector2& pos );
	void DrawAnimatedSprite( const AnimatedSprite& sprite, const Vector2& pos );
	void DrawTexture( const Texture* texture, const Vector2& pos );
	void DrawSpriteData( const SpriteData& data );

	void Render();
	void Render( const Matrix& transformation );
	void End();

	void TransformSprite( float rotation, const Vector2& scale, const Vector2& origin, SpriteData& s );

private:
	void InternalQueueSprite( gluint texture, float rotation, const Vector2& scale, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& c, int depth );
	void InternalQueueSprite( gluint texture, float rotation, const Vector2& scale, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, size_t numQuads, int depth );
	void InternalQueueSprite( gluint texture, float rotation, const Vector2& scale, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, const ushort *quadsIndices, size_t numQuads, int depth );
	void InternalQueueString( Font* font, const char* first, const char* last, const Vector2& scale, Vector2 pos, const Color& c, TextAlignment alignment, int face_size, int depth );

	void InternalFlush( gluint texture, size_t blendmodevalue, size_t first, size_t count );

	vec_type		m_queue;
	BlendMode		m_current_blendmode;
	Rect			m_clip_rect;
	SpriteSortMode	m_sortmode;
	Shader*			m_attached_shader;
	size_t			m_max_batch_usage;
	bool			m_enable_clipping;
	bool			m_enable_sorting;
	bool			m_enable_shader;
};


CE_NAMESPACE_END

