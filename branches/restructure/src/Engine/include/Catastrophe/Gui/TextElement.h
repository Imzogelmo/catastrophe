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
#include "../Graphics/Font.h"

CE_NAMESPACE_BEGIN


class CE_API TextElement : public Widget
{
public:
	TextElement( const fc::string& text = "", Font* font = 0, TextAlignment alignment = AlignLeft );

	void Render( SpriteBatch* spritebatch );

	void SetFont( Font* font );
	void SetText( const fc::string& text );
	void SetTextAlignment( TextAlignment alignment ) { m_textAlignment = alignment; }

	const Font* GetFont() const { return m_font; }
	const fc::string& GetText() const { return m_text; }
	TextAlignment GetTextAlignment() const { return m_textAlignment; }
	int GetTextAlignmentOffset() const;

protected:
	Font*			m_font;
	fc::string		m_text;
	TextAlignment	m_textAlignment;

};


CE_NAMESPACE_END
