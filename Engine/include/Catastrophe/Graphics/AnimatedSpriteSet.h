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

CE_NAMESPACE_BEGIN


class AnimatedSpriteSet
{
public:
	typedef fc::vector<SpriteAnimation> vec_type;

	Vector2		size;
	Vector2		scale;
	Color		color;
	BlendMode	blendmode;
	float		angle;

	AnimatedSpriteSet( const Vector2& size = Vector2::Zero,
				const Color& c = Color::White(),
				const BlendMode& blendmode = BlendMode::Alpha,
				int layer = 0 );

	// set methods
	inline void SetSize( const Vector2& value ) { size = value; }
	inline void SetColor( const Color& c ) { color = c; }
	inline void SetBlendMode( const BlendMode& value ) { blendmode = value; }
	inline void SetScale( const Vector2& value ) { scale = value; }
	inline void SetAngle( float value ) { angle = value; }
	inline void SetCurrentAnimation( size_t index ) { m_currentAnimation = index; }

	void AddAnimation( const SpriteAnimation& anim ) { InsertAnimation(anim, m_animations.size()); }
	void InsertAnimation( const SpriteAnimation& anim, size_t index );
	void RemoveAnimation( size_t index );
	void Reserve( size_t capacity );
	void Resize( size_t newSize );
	void Update();

	// get methods
	inline float Width() const { return size.x; }
	inline float Height() const { return size.y; }
	inline const Vector2& GetSize() const { return size; }
	inline const Vector2& GetScale() const { return scale; }
	inline const Color& GetColor() const { return color; }
	inline const BlendMode& GetBlendMode() const { return blendmode; }
	inline float GetAngle() const { return angle; }

	// sprite animation index methods
	inline SpriteAnimation& operator []( size_t index ) { return m_animations.at(index); }
	inline const SpriteAnimation& operator []( size_t index ) const { return m_animations.at(index); }
	inline SpriteAnimation& GetAnimation( size_t index ) { return operator[](index); }
	inline const SpriteAnimation& GetAnimation( size_t index ) const { return operator[](index); }
	inline SpriteAnimation& GetCurrentAnimation() { return operator[](m_currentAnimation); }
	inline const SpriteAnimation& GetCurrentAnimation() const { return operator[](m_currentAnimation); }

protected:
	vec_type	m_animations;
	size_t		m_currentAnimation;

};



CE_NAMESPACE_END
