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

#include "Gui/Label.h"
#include "Graphics/SpriteBatch.h"

CE_NAMESPACE_BEGIN


Label::Label( const String& text, Font* font, TextAlignment alignment ) :
	Widget(),
	m_font(font),
	m_text(text),
	m_textAlignment(alignment),
	m_disabledColor(Color::DarkGray()),
	m_isHighlighted(false)
{
}


void Label::Render( SpriteBatch* spritebatch )
{
	if( !m_font || m_text.empty() )
		return;

	Color renderColor = GetCurrentTextColor();
	Vector2 pos = GetScreenPosition();
	pos.x += (float)GetTextAlignmentOffset();

	spritebatch->DrawString( m_font,
		m_text,
		pos,
		renderColor,
		m_textAlignment
	);
}


void Label::SetFont( Font* font )
{
	if(font)
		m_font = font;
}


void Label::SetText( const char* text )
{
	m_text = text;
}


void Label::SetText( const String& text )
{
	m_text = text;
}


float Label::GetTextAlignmentOffset() const
{
	float offset = 0;
	if( m_textAlignment == AlignCenter )
	{
		offset += m_size.x / 2.f;
	}
	else if( m_textAlignment == AlignRight )
	{
		offset += m_size.x;
	}

	return offset;
}


float Label::GetTextWidth() const
{
	return m_font ? m_font->GetTextWidth(m_text) : 0.f;
}


Color Label::GetCurrentTextColor() const
{
	return IsEnabled() ? //fixme
		(m_isHighlighted ? m_highlightedColor : m_color) : m_disabledColor;
}



CE_NAMESPACE_END
