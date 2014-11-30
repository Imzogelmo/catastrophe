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
#include "Graphics/Texture.h"


CE_NAMESPACE_BEGIN


SpriteBase::SpriteBase() :
	size(Vector2::Zero),
	scale(Vector2::One),
	color(Color::White()),
	blendmode(BlendMode::Alpha),
	angle(0.f)
{
}


SpriteBase::SpriteBase( const Vector2& size,
			const Vector2& scale, 
			const Color& color,
			const BlendMode& blendmode,
			float angle
	) :
	size(size),
	scale(scale),
	color(color),
	blendmode(blendmode),
	angle(angle)
{
}



// Sprite class

Sprite::Sprite() :
	SpriteBase(),
	m_texture(0),
	m_uv(Rectf::One)
{
}


Sprite::Sprite( Texture* texture, const Rect& sourceRect ) :
	SpriteBase(),
	m_texture(0),
	m_uv(Rectf::One)
{
	Create(texture, sourceRect);
}


Sprite::Sprite( Texture* texture, const Rectf& uv ) :
	SpriteBase(),
	m_texture(0),
	m_uv(Rectf::One)
{
	Create(texture, uv);
}


Sprite::Sprite( const AnimatedSprite& sprite )
{
	*this = sprite;
}

/*
Sprite::~Sprite()
{
	if(m_texture)
		m_texture->ReleaseRef();
}
*/

Sprite& Sprite::operator =( const AnimatedSprite& sprite )
{
	size		= sprite.size;
	scale		= sprite.scale;
	color		= sprite.color;
	blendmode	= sprite.blendmode;
	angle		= sprite.angle;
	m_uv		= sprite.GetUVRect();

	SetTexture(sprite.GetTexture());

	return *this;
}


void Sprite::Create( Texture* texture, const Rect& sourceRect )
{
	SetTexture(texture);
	SetSourceRect(sourceRect);

	// create methods also sets size to exact pixel-dimensions
	SetSize( Vector2(sourceRect.size) );
}


void Sprite::Create( Texture* texture, const Rectf& uv )
{
	SetTexture(texture);
	SetUVRect(uv);

	// create methods also sets size to exact pixel-dimensions
	if(texture)
	{
		Vector2 s(uv.max.x * (float)texture->Width(), uv.max.y * (float)texture->Height());
		SetSize(s);
	}
}


void Sprite::SetTexture( Texture* texture )
{
	if(m_texture)
		m_texture->ReleaseRef();

	m_texture = texture;

	if(texture)
		texture->AddRef();
}


void Sprite::SetSourceRect( const Rect& sourceRect )
{
	if( m_texture )
		m_uv = m_texture->GetUVRect(sourceRect);
}


gluint Sprite::GetTextureID() const
{
	return m_texture ? m_texture->GetTextureID() : 0;
}




// Animated Sprite class

AnimatedSprite::AnimatedSprite() :
	SpriteBase(),
	SpriteAnimation()
{
}


AnimatedSprite::AnimatedSprite(
	Texture* texture,
	const Rect& sourceRect,
	int numberOfFrames,
	int frameOffsetX,
	int frameOffsetY
) :
	SpriteBase(),
	SpriteAnimation(texture, sourceRect, numberOfFrames, frameOffsetX, frameOffsetY)
{
	SetSize( Vector2((float)sourceRect.size.x, (float)sourceRect.size.y) );
}


AnimatedSprite::AnimatedSprite( const Sprite& sprite )
{
	*this = sprite;
}


AnimatedSprite& AnimatedSprite::operator =( const Sprite& sprite )
{
	size		= sprite.size;
	scale		= sprite.scale;
	color		= sprite.color;
	blendmode	= sprite.blendmode;
	angle		= sprite.angle;

	Texture* texture = sprite.GetTexture();
	Rect sourceRect = texture ? texture->GetSourceRect(sprite.GetUVRect()) : Rect::Zero;
	Create( texture, sourceRect, 1, sourceRect.Width(), sourceRect.Height() );

	return *this;
}


bool AnimatedSprite::IsValid() const
{
	//if any of these fail, so does the rendering of the sprite.
	return (m_texture && m_texture->IsValid() && GetNumFrames() > 0);
}





CE_NAMESPACE_END
