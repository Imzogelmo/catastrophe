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

#include "Graphics/Sprite.h"


CE_NAMESPACE_BEGIN


SpriteBase::SpriteBase( const Vector2& size, const Color& tint, const BlendMode& blendmode, int layer) :
	size(size),
	tint(tint),
	blendmode(blendmode),
	layer(layer),
	depth(0),
	scale(Vector2::One),
	angle(0.f)
{
}


Sprite::Sprite( const Texture* texture, const Rect& sourceRect )
: SpriteBase(), m_uv(Rectf::Zero)
{
	if(texture)
	{
		Init(texture, sourceRect);
	}
}


Sprite::Sprite( const Texture* texture, const Rectf& uv )
{
	SetTexture(texture);
	SetUVRect(uv);
	if(texture)
	{
		//set the size to the actual pixel size from the texture.
		SetSize( Vector2(
			uv.Width() * (float)texture->Width(),
			uv.Height() * (float)texture->Height())
		);
	}
}


void Sprite::Init( const Texture* texture, const Rect& sourceRect )
{
	SetTexture(texture);
	SetSourceRect(sourceRect);
	SetSize( Vector2(sourceRect.size) );
}


void Sprite::SetTexture( const Texture* texture )
{
	m_texture = texture;
}


void Sprite::SetSourceRect( const Rect& sourceRect )
{
	CE_ASSERT(m_texture != 0);
	if(m_texture)
		m_uv = m_texture->GetUVRect(sourceRect);
}


AnimatedSprite::AnimatedSprite( const Texture* texture, bool loopAnim, bool startPaused )
	: SpriteBase(), Animation(texture, loopAnim, startPaused)
{
	if(texture)
	{
		SetSize( Vector2((float)texture->Width(), (float)texture->Height()) );
	}
}


AnimatedSprite::AnimatedSprite(
	const Texture* texture,
	const Rect& sourceRect,
	int numberOfFrames,
	int frameOffsetX,
	int frameOffsetY,
	bool loopAnim,
	bool startPaused
) :
	SpriteBase(),
	Animation(texture, sourceRect, numberOfFrames, frameOffsetX, frameOffsetY, loopAnim, startPaused)
{
	SetSize( Vector2((float)sourceRect.size.x, (float)sourceRect.size.y) );
}


bool AnimatedSprite::IsValid() const
{
	//if any of these fail, so does the rendering of the sprite.
	return (m_texture && m_texture->IsValid() && NumFrames() > 0);
}





CE_NAMESPACE_END
