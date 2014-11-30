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

#include "../Math/Vector2.h"
#include "../Math/Color.h"
#include "../Math/Rectf.h"
#include "../Math/Rect.h"

#include "BlendMode.h"
#include "SpriteAnimation.h"

CE_NAMESPACE_BEGIN


enum SpriteAnimationType
{
	SpriteAnimationType_Loop,
	SpriteAnimationType_OneTime,
	SpriteAnimationType_PingPong
};


class SpriteBase
{
public:
	Vector2		size;
	Vector2		scale;
	Color		color;
	BlendMode	blendmode;
	float		angle;
	//u16			animationType;
	bool		flipX;
	bool		flipY;

	SpriteBase();
	SpriteBase( const Vector2& size,
				const Vector2& scale, 
				const Color& color,
				const BlendMode& blendmode,
				float angle
				);

	// set methods
	inline void SetSize( const Vector2& value ) { size = value; }
	inline void SetColor( const Color& c ) { color = c; }
	inline void SetBlendMode( const BlendMode& value ) { blendmode = value; }
	inline void SetScale( const Vector2& value ) { scale = value; }
	inline void SetAngle( float value ) { angle = value; }
	inline void SetFlipX( bool value ) { flipX = value; }
	inline void SetFlipY( bool value ) { flipY = value; }

	// get methods
	inline float Width() const { return size.x; }
	inline float Height() const { return size.y; }
	inline const Vector2& GetSize() const { return size; }
	inline const Vector2& GetScale() const { return scale; }
	inline const Color& GetColor() const { return color; }
	inline const BlendMode& GetBlendMode() const { return blendmode; }
	inline float GetAngle() const { return angle; }
	inline bool GetFlipX() const { return flipX; }
	inline bool GetFlipY() const { return flipY; }

};



/**
 * @Sprite
 * 
 */
class CE_API Sprite : public SpriteBase
{
public:
	Sprite();
	Sprite( Texture* texture, const Rect& sourceRect );
	Sprite( Texture* texture, const Rectf& uv );
	Sprite( const AnimatedSprite& sprite );

	Sprite& operator =( const AnimatedSprite& sprite );

	void SetTexture( Texture* texture );
	void SetSourceRect( const Rect& sourceRect );
	void SetUVRect( const Rectf& uv ) { m_uv = uv; }
	void Create( Texture* texture, const Rect& sourceRect );
	void Create( Texture* texture, const Rectf& uv );

	inline const Rectf& GetUVRect() const { return m_uv; }
	inline Texture* GetTexture() const { return m_texture; }
	gluint GetTextureID() const;

protected:
	Texture*	m_texture;
	Rectf		m_uv;
};



/**
 * @AnimatedSprite
 * 
 */
class CE_API AnimatedSprite : public SpriteBase, public SpriteAnimation
{
public:
	AnimatedSprite();
	AnimatedSprite( const Sprite& sprite );
	AnimatedSprite(
		Texture* texture,
		const Rect& sourceRect,
		int numberOfFrames = 1,
		int frameOffsetX = 0,
		int frameOffsetY = 0
	);

	AnimatedSprite& operator =( const Sprite& sprite );

	bool IsValid() const; //depricated

};




