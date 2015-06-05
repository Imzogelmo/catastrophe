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


#include "Catastrophe/Core/Math/Rect.h"
#include "Catastrophe/Graphics/Texture.h"
#include "Catastrophe/Graphics/Sprite/SpriteBase.h"

CE_NAMESPACE_BEGIN



SpriteBase::SpriteBase() :
	texture(null),
	uv(Rectf::Zero),
	sourceRect(PackedRect::Zero)
{
}


SpriteBase::SpriteBase(Texture* texturePtr, const Rect& sourceRectangle) :
	texture(texturePtr),
	uv(Rectf::Zero),
	sourceRect()
{
	SetSourceRect(sourceRectangle);
}


SpriteBase::SpriteBase(Texture* texturePtr, const PackedRect& sourceRectangle) :
	texture(texturePtr),
	uv(Rectf::Zero),
	sourceRect()
{
	SetSourceRect(sourceRectangle);
}


void SpriteBase::SetTexture(Texture* texturePtr)
{
	texture = texturePtr;
	if(texture != null)
		uv = texture->GetUVRect(sourceRect);
}


u32 SpriteBase::GetTextureID() const
{
	return texture ? texture->GetTextureID() : 0;
}


void SpriteBase::SetSourceRect(const PackedRect& sourceRectangle)
{
	sourceRect = sourceRectangle;
	if(texture != null)
		uv = texture->GetUVRect(sourceRectangle);
}


void SpriteBase::SetSpriteData(Texture* texturePtr, const PackedRect& sourceRectangle)
{
	texture = texturePtr;
	SetSourceRect(sourceRectangle);
}




CE_NAMESPACE_END


