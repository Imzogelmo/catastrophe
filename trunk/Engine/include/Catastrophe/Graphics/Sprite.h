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

#include "Animation.h"
#include "AnimationSet.h"
#include "BlendMode.h"

#include "../Math/Vector2.h"
#include "../Math/Color.h"

CE_NAMESPACE_BEGIN


class SpriteBase
{
public:
	SpriteBase( const Vector2& size = Vector2::Zero,
				const Color& tint = Color::White(),
				const BlendMode& blendmode = BlendMode::Alpha,
				int layer = 0 );

	void SetSize(const Vector2& value) { size = value; }
	void SetTint(const Color& c) { tint = c; }
	void SetBlendMode(const BlendMode& value) { blendmode = value; }
	void SetLayer(int value) { layer = value; }
	void SetDepth(int value) { depth = value; }
	void SetAngle(float value) { angle = value; }
	void SetScale(const Vector2& value) { scale = value; }
	//void SetHotspot(const Vector2& hotspot) { m_hotspot = hotspot; }

	float Width() const { return size.x; }
	float Height() const { return size.y; }
	const Vector2& GetSize() const { return size; }
	Vector2 GetExtents() const { return size * 0.5f; }
	const Vector2& GetScale() const { return scale; }
	//const Vector2& GetHotspot() const { return m_hotspot; }
	const Color& GetTint() const { return tint; }
	const BlendMode& GetBlendMode() const { return blendmode; }
	int GetLayer() const { return layer; }
	int GetDepth() const { return depth; }
	float GetAngle() const { return angle; }

	//there's no good reason not to make these public.
	Vector2		size;
	Color		tint;
	BlendMode	blendmode;
	int			layer;
	int			depth;
	Vector2		scale;
	float		angle;
};

/**
 * @Sprite
 * 
 */
class CE_API Sprite : public SpriteBase
{
public:
	Sprite( const Texture* texture = 0, const Rect& sourceRect = Rect::Zero );
	Sprite( const Texture* texture, const Rectf& uv );

	void SetTexture( const Texture* texture );
	void SetSourceRect( const Rect& sourceRect );
	void SetUVRect( const Rectf& uv ) { m_uv = uv; }

	inline const Rectf& GetUVRect() const { return m_uv; }
	inline const Texture* GetTexture() const { return m_texture; }
	inline gluint GetTextureID() const { return m_texture->GetTextureID(); }

protected:
	const Texture*	m_texture;
	Rectf			m_uv;
};


class CE_API AnimatedSprite : public SpriteBase, public Animation
{
public:
	AnimatedSprite( const Texture* texture = 0, bool loopAnim = true, bool startPaused = false );
	AnimatedSprite(
		const Texture* texture,
		const Rect& sourceRect,
		int numberOfFrames = 1,
		int frameOffsetX = 0,
		int frameOffsetY = 0,
		bool loopAnim = true,
		bool startPaused = false
	);

	bool IsValid() const;

};



class AnimatedSpriteSet : public SpriteBase, public AnimationSet
{
public:
	//SpriteSet() {}


};



