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

#include <fc/fixed_vector.h>

#include "../Common.h"
#include "../Math/Vector2.h"
#include "../Math/Color.h"
#include "../Math/Rectf.h"
#include "../Math/Rect.h"

#include "Sprite.h"
#include "SpriteAnimation.h"

CE_NAMESPACE_BEGIN


class AnimatedSpriteSet : public SpriteBase
{
public:
	typedef fc::vector<SpriteAnimation> vec_type;

	AnimatedSpriteSet();
	AnimatedSpriteSet(	const Vector2& size,
						const Vector2& scale, 
						const Color& color,
						const BlendMode& blendmode,
						float angle
					);

	void AddAnimation( const Rect& sourceRect, float animationDelay, int numberOfFrames = 1, int frameOffsetX = 0, int frameOffsetY = 0 );
	void AddAnimation( const Rect& sourceRect, int numberOfFrames = 1, int frameOffsetX = 0, int frameOffsetY = 0 );
	void AddAnimation( const SpriteAnimation& anim );
	void InsertAnimation( const SpriteAnimation& anim, size_t index );
	void RemoveAnimation( size_t index );

	void SetTexture( Texture* texture );
	void SetCurrentAnimation( size_t index );
	void Reserve( size_t capacity );
	void Resize( size_t newSize );
	void Update();

	inline bool Empty() const { return m_animations.empty(); }
	inline size_t GetNumAnimations() const { return m_animations.size(); }
	inline size_t GetCurrentAnimationIndex() const { return m_currentAnimation; }
	inline Texture* GetTexture() const { return m_texture; }
	gluint GetTextureID() const;

	// sprite animation index methods
	inline SpriteAnimation& operator []( size_t index ) { return m_animations.at(index); }
	inline const SpriteAnimation& operator []( size_t index ) const { return m_animations.at(index); }
	inline SpriteAnimation& GetAnimation( size_t index ) { return operator[](index); }
	inline const SpriteAnimation& GetAnimation( size_t index ) const { return operator[](index); }
	inline SpriteAnimation& GetCurrentAnimation() { return operator[](m_currentAnimation); }
	inline const SpriteAnimation& GetCurrentAnimation() const { return operator[](m_currentAnimation); }

	const vec_type& GetAnimationsVector() const { return m_animations; }

protected:
	Texture*	m_texture;
	vec_type	m_animations;
	size_t		m_currentAnimation;

};



CE_NAMESPACE_END
