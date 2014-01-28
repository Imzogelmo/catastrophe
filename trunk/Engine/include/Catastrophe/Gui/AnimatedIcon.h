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

#include "Widget.h"
#include "../Graphics/Sprite.h"

CE_NAMESPACE_BEGIN


class AnimatedIcon : public Widget
{
public:
	AnimatedIcon();

	virtual void Update();
	virtual void Render( SpriteBatch* spritebatch );

	virtual void SetSprite( const AnimatedSprite& sprite );
	virtual void SetAutoFitSprite( bool stretch = true );
	virtual void SetAutoCenterSprite( bool center = true );

	bool GetAutoFitSprite() const { return m_stretchSprite; }
	bool GetAutoCenterSprite() const { return m_centerSprite; }

	AnimatedSprite& GetSprite() { return m_sprite; }
	const AnimatedSprite& GetSprite() const { return m_sprite; }

protected:
	AnimatedSprite	m_sprite;
	bool			m_stretchSprite;
	bool			m_centerSprite;

};


CE_NAMESPACE_END
