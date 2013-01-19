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

#include "Math/Matrix.h"
#include "Math/Rectf.h"
#include "Math/Math.h"

#include "Graphics/SpriteBatch.h"
#include "Graphics/Sprite.h"
#include "Graphics/OpenGL.h"

CE_NAMESPACE_BEGIN


SpriteBatch::SpriteBatch( size_t reserve ) :
	m_queue(),
	m_current_blendmode(),
	m_clip_rect(Rect(0, 0, 0, 0)),
	m_sortmode(Deferred),
	m_attached_shader(0),
	m_max_batch_usage(size_t(-1)),
	m_enable_clipping(true),
	m_enable_sorting(true),
	m_enable_shader(true)
{
	Reserve(reserve);
}


SpriteBatch::~SpriteBatch()
{}


void SpriteBatch::Reserve( size_t reserve )
{
	m_queue.reserve( reserve );
}


void SpriteBatch::Clear()
{
	m_queue.clear_uninitialized();
}


void SpriteBatch::Begin()
{
	Clear();
}


void SpriteBatch::End()
{
	if(m_attached_shader)
		m_attached_shader->Unbind();
}

void SpriteBatch::SetMaxHardwareBatchSize( size_t maxHardwareBatch )
{
	if(maxHardwareBatch < 512)
		maxHardwareBatch = 512;

	m_max_batch_usage = maxHardwareBatch;
}

// Sprite rendering
void SpriteBatch::Draw( gluint texture, const Rectf& vertices, const Rectf& uv, const Color& c, int depth )
{
	InternalQueueSprite( texture, 0.f, 1.f, 0.f, vertices, uv, c, depth );
}

void SpriteBatch::DrawRotated( gluint texture, float rotation, const Rectf& vertices, const Rectf& uv, const Color& c, int depth )
{
	InternalQueueSprite( texture, rotation, 1.f, vertices.Center(), vertices, uv, c, depth );
}

void SpriteBatch::DrawRotated( gluint texture, float rotation, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& c, int depth )
{
	InternalQueueSprite( texture, rotation, 1.f, origin, vertices, uv, c, depth );
}

void SpriteBatch::DrawScaled( gluint texture, const Vector2& scale, const Rectf& vertices, const Rectf& uv, const Color& c, int depth )
{
	InternalQueueSprite( texture, 0.f, scale, vertices.Center(), vertices, uv, c, depth );
}

void SpriteBatch::DrawScaled( gluint texture, const Vector2& scale, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& c, int depth )
{
	InternalQueueSprite( texture, 0.f, scale, origin, vertices, uv, c, depth );
}

void SpriteBatch::DrawRotatedScaled( gluint texture, float rotation, const Vector2& scale, const Rectf& vertices, const Rectf& uv, const Color& c, int depth )
{
	InternalQueueSprite( texture, rotation, scale, vertices.Center(), vertices, uv, c, depth );
}

void SpriteBatch::DrawRotatedScaled( gluint texture, float rotation, const Vector2& scale, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& c, int depth )
{
	InternalQueueSprite( texture, rotation, scale, origin, vertices, uv, c, depth );
}


// Quad batch rendering
void SpriteBatch::Draw( gluint texture, const Vector2* vtx, const Vector2* uv, const Color* c, size_t numQuads, int depth )
{
	InternalQueueSprite( texture, 0.f, 1.f, 0.f, vtx, uv, c, numQuads, depth );
}

void SpriteBatch::DrawRotated( gluint texture, float rotation, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, size_t numQuads, int depth )
{
	InternalQueueSprite( texture, rotation, 1.f, origin, vtx, uv, c, numQuads, depth );
}

void SpriteBatch::DrawScaled( gluint texture, const Vector2& scale, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, size_t numQuads, int depth )
{
	InternalQueueSprite( texture, 0.f, scale, origin, vtx, uv, c, numQuads, depth );
}

void SpriteBatch::DrawRotatedScaled( gluint texture, float rotation, const Vector2& scale, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, size_t numQuads, int depth )
{
	InternalQueueSprite( texture, rotation, scale, origin, vtx, uv, c, numQuads, depth );
}


// Quad indices batch rendering
void SpriteBatch::Draw( gluint texture, const Vector2* vtx, const Vector2* uv, const Color* c, const ushort *quadsIndices, size_t numQuads, int depth )
{
	InternalQueueSprite( texture, 0.f, 1.f, 0.f, vtx, uv, c, quadsIndices, numQuads, depth );
}

void SpriteBatch::DrawRotated( gluint texture, float rotation, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, const ushort *quadsIndices, size_t numQuads, int depth )
{
	InternalQueueSprite( texture, rotation, 1.f, origin, vtx, uv, c, quadsIndices, numQuads, depth );
}

void SpriteBatch::DrawScaled( gluint texture, const Vector2& scale, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, const ushort *quadsIndices, size_t numQuads, int depth )
{
	InternalQueueSprite( texture, 0.f, scale, origin, vtx, uv, c, quadsIndices, numQuads, depth );
}

void SpriteBatch::DrawRotatedScaled( gluint texture, float rotation, const Vector2& scale, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, const ushort *quadsIndices, size_t numQuads, int depth )
{
	InternalQueueSprite( texture, rotation, scale, origin, vtx, uv, c, quadsIndices, numQuads, depth );
}


void SpriteBatch::DrawSprite( const Sprite& sprite, const Vector2& pos )
{
	InternalQueueSprite(
		sprite.GetTextureID(),
		sprite.angle,
		sprite.scale,
		pos + sprite.GetExtents(),
		Rectf(pos, pos + sprite.size),
		sprite.GetUVRect(),
		sprite.tint,
		sprite.depth
		);
}


void SpriteBatch::DrawAnimatedSprite( const AnimatedSprite& sprite, const Vector2& pos )
{
	InternalQueueSprite(
		sprite.GetTextureID(),
		sprite.angle,
		sprite.scale,
		pos + sprite.GetExtents(),
		Rectf(pos, pos + sprite.size),
		sprite.GetFrameUVRect(),
		sprite.tint,
		sprite.depth
		);
}


void SpriteBatch::DrawTexture( const Texture* texture, const Vector2& pos )
{
	InternalQueueSprite( texture->GetTextureID(), 0.f, 1.f, 0.f, 
		Rectf(pos.x, pos.y, (float)texture->Width(), (float)texture->Height()), Rectf::One, Color::White(), 0 );
}


void SpriteBatch::DrawSpriteData( const SpriteData& data )
{
	//it doesn't get any faster than this.
	m_queue.push_back_uninitialized() = data;
}


// Text rendering
void SpriteBatch::DrawString( Font* font, const fc::string& text, const Vector2& pos, const Color& c, TextAlignment alignment, int face_size, int depth )
{
	InternalQueueString( font, text.begin(), text.end(),  Vector2::One, pos, c, alignment, face_size, depth );
}

void SpriteBatch::DrawString( Font* font, const fc::string& text, size_t textPos, size_t amount, const Vector2& pos, const Color& c, TextAlignment alignment, int face_size, int depth )
{
	InternalQueueString( font, text.begin() + textPos, text.begin() + textPos + amount, Vector2::One, pos, c, alignment, face_size, depth );
}

void SpriteBatch::DrawString( Font* font, const fc::string& text, const Vector2& scale, const Vector2& pos, const Color& c, TextAlignment alignment, int face_size, int depth )
{
	InternalQueueString( font, text.begin(), text.end(), scale, pos, c, alignment, face_size, depth );
}


void SpriteBatch::InternalQueueString
( Font* font, const char* first, const char* last, const Vector2& scale, Vector2 pos, const Color& c, TextAlignment alignment, int face_size, int depth )
{
	CE_ASSERT(first <= last);

	Vector2 originalPos = pos;

	if(alignment == AlignCenter)
	{
		pos.x += (float)(font->GetTextWidth(first, last) / 2.f) * scale.x;
	}
	else if(alignment == AlignRight)
	{
		pos.x -= (float)font->GetTextWidth(first, last) * scale.x;
	}

	//Vector2 origin = pos;
	//Vector2 scale = (float)font->GetFaceSize() / (float)faceSize;

	//for( fc::string::const_iterator it = text.begin(); it != text.end(); ++it )
	for( ; first != last; ++first )
	{
		const Glyph* glyph = &font->GetGlyph(*first);
		if(*first == '\n')
		{
			pos.x = originalPos.x;
			pos.y += (float)font->GetLineHeight();
			continue;
		}

		if(*first != ' ')
		{
			Vector2 translation = pos + Vector2( float(glyph->translation.x), float(glyph->translation.y) );
			Vector2 size( float(glyph->size.x), float(glyph->size.y) );

			if( !scale.Equals(Vector2::One) )
				size *= scale;

			InternalQueueSprite( font->GetTextureID(), 0.f, 1.f, 0.f, Rectf(translation, translation + size), glyph->uv, c, depth );
		}

		pos.x += (float(glyph->advance) * scale.x);
	}
}


void SpriteBatch::InternalQueueSprite
( gluint texture, float rotation, const Vector2& scale, const Vector2& origin, const Rectf& vertices, const Rectf& uv, const Color& c, int depth )
{
	Vector2 v[4], t[4];
	vertices.GetCorners( v );
	uv.GetCorners( t );

	SpriteData & s = m_queue.push_back_uninitialized();
	for( size_t i(0); i < 4; ++i )
	{
		s.data[i].pos = v[i];
		s.data[i].uv = t[i];
		s.data[i].color = c;
	}

	s.SetTexture(texture);
	s.SetBlendMode(m_current_blendmode.value);
	s.SetDepth(depth);
	s.SetYPosition(v[1].y);
	TransformSprite( rotation, scale, origin, s );
}


void SpriteBatch::InternalQueueSprite
( gluint texture, float rotation, const Vector2& scale, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, size_t numQuads, int depth )
{
	SpriteData * s = m_queue.push_back_uninitialized( numQuads );

	for( size_t i(0); i < numQuads; ++i )
	{
		for( size_t j(0); j < 4; ++j )
		{
			const size_t index = i * 4 + j;
			s[i].data[j].pos = vtx[ index ];
			s[i].data[j].uv = uv[ index ];
			s[i].data[j].color = c[ index ];
		}

		s[i].SetTexture(texture);
		s[i].SetBlendMode(m_current_blendmode.value);
		s[i].SetDepth(depth);
		s[i].SetYPosition(vtx[1].y);
	}

	if( scale != Vector2::One && rotation != 0.f )
	{
		for( size_t i(0); i < numQuads; ++i )
			TransformSprite( rotation, scale, origin, s[i] );
	}
}


void SpriteBatch::InternalQueueSprite
( gluint texture, float rotation, const Vector2& scale, const Vector2& origin, const Vector2* vtx, const Vector2* uv, const Color* c, const ushort *quadsIndices, size_t numQuads, int depth )
{
	SpriteData * s = m_queue.push_back_uninitialized( numQuads );

	size_t element(0);
	for( size_t i(0); i < numQuads; ++i )
	{
		for( size_t j(0); j < 4; ++j )
		{
			s[i].data[j].pos = vtx[ quadsIndices[element] ];
			s[i].data[j].uv = uv[ quadsIndices[element] ];
			s[i].data[j].color = c[ quadsIndices[element] ];
			++element;
		}

		s[i].SetTexture(texture);
		s[i].SetBlendMode(m_current_blendmode.value);
		s[i].SetDepth(depth);
		s[i].SetYPosition(vtx[ quadsIndices[element-3] ].y);
	}

	if( scale != Vector2::One && rotation != 0.f )
	{
		for( size_t i(0); i < numQuads; ++i )
			TransformSprite( rotation, scale, origin, s[i] );
	}
}


void SpriteBatch::TransformSprite( float rotation, const Vector2& scale, const Vector2& origin, SpriteData& s )
{
	if( rotation != 0.f )
	{
		const Vector2 rot = Math::SinCos(rotation);
		Math::RotateScalePoint( rot, scale, origin, s.data[0].pos );
		Math::RotateScalePoint( rot, scale, origin, s.data[1].pos );
		Math::RotateScalePoint( rot, scale, origin, s.data[2].pos );
		Math::RotateScalePoint( rot, scale, origin, s.data[3].pos );
	}
	else if( scale != Vector2::One )
	{
		Math::ScalePoint( scale, origin, s.data[0].pos );
		Math::ScalePoint( scale, origin, s.data[1].pos );
		Math::ScalePoint( scale, origin, s.data[2].pos );
		Math::ScalePoint( scale, origin, s.data[3].pos );
	}
}


void SpriteBatch::Render()
{
	if( m_queue.empty() )
		return;

	//_SortQueue();

	bool used_scissor = false;
	if( m_enable_clipping && !m_clip_rect.Empty() )
	{
		used_scissor = true;
		const Rect& r = m_clip_rect;

		int viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );

		glEnable( GL_SCISSOR_TEST );
		glScissor( r.pos.x , viewport[3] - r.pos.y - r.size.y, r.size.x, r.size.y );
	}

	if(m_attached_shader)
		m_attached_shader->Bind(); //fixme:


	glEnable( GL_TEXTURE_2D );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );

	glVertexPointer( 2, GL_FLOAT, sizeof(VertexTextureSpriteData2D), &m_queue[0].data[0].pos );
	glTexCoordPointer( 2, GL_FLOAT, sizeof(VertexTextureSpriteData2D), &m_queue[0].data[0].uv );
	glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(VertexTextureSpriteData2D), &m_queue[0].data[0].color );

	size_t	first	= 0,
			last	= 0,
			size	= m_queue.size();

	size_t n_batched = 0;
	gluint current_texture = m_queue[0].GetTexture();
	size_t current_blender = m_queue[0].GetBlendMode();

	for( ; last < size; ++last )
	{
		const SpriteData& spriteData = m_queue[last];
		const gluint next_texture = spriteData.GetTexture();
		const size_t next_blender = spriteData.GetBlendMode();

		++n_batched; //todo: optimize this via a prefetch flush (begin, end = m_max_batch_usage)
		if( current_texture != next_texture || current_blender != next_blender || n_batched > m_max_batch_usage )
		{
			InternalFlush( current_texture, current_blender, first, last - first );
			current_texture = next_texture;
			current_blender = next_blender;
			first = last;
		}
	}

	//flush the remaining sprites.
	InternalFlush( current_texture, current_blender, first, last - first );

	if(used_scissor)
		glDisable( GL_SCISSOR_TEST );

	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}


void SpriteBatch::InternalFlush( gluint texture, size_t blendmodevalue, size_t first, size_t count )
{
	if(count == 0)
		return;

	BlendMode blendmode = blendmodevalue;
	blendmode.Apply();

	glBindTexture( GL_TEXTURE_2D, texture );
	glDrawArrays( GL_QUADS, (first * 4), (count * 4) );
}


void SpriteBatch::Render( const Matrix& transformation )
{
	glPushMatrix();
		glMultMatrixf( &transformation.m[0] );
		Render();
	glPopMatrix();
}



CE_NAMESPACE_END

