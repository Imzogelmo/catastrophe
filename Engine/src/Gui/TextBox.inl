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

#include "Gui/TextBox.h"
#include "Graphics/SpriteBatch.h"

CE_NAMESPACE_BEGIN


TextBox::TextBox( const fc::string& text, Font* font, TextAlignment alignment, int rowHeight ) :
	Label(text, font, alignment),
	m_rowHeight(rowHeight),
	m_fastForwardSpeed(4),
	m_textSpeed(3.f)
{
}


void TextBox::SetFastForwardSpeed( int speed )
{
	m_fastForwardSpeed = (size_t)speed;
}


void TextBox::FastForward()
{
	m_currentChar += (size_t)m_fastForwardSpeed;
	if( m_currentChar >= m_text.size() )
	{
		m_currentChar = m_text.size();
		m_textDisplayFinished = true;
	}
}


bool TextBox::IsTextInstantaneous() const
{
	return Math::EpsilonCompare(m_textSpeed, 0.f, 0.001f);
}


void TextBox::Update()
{
	if( !IsActive() )
		return;

	if( m_currentChar < m_text.size() )
	{
		if( IsTextInstantaneous() )
		{
			m_currentChar = m_text.size();
			m_textDisplayFinished = true;
		}
		else
		{
			++m_textSpeedCounter;
			while( m_textSpeedCounter > m_textSpeed )
			{
				m_textSpeedCounter -= m_textSpeed;
				++m_currentChar;
			}
		}

		m_currentChar = fc::min( m_currentChar, m_text.size() );
	}
	else
	{
		m_currentChar = 0; //test
		m_textDisplayFinished = true;
	}

	Widget::Update();
}


void TextBox::Render( SpriteBatch* spritebatch )
{
	if( !IsVisible() )
		return;

	if( m_font || !m_text.empty() )
	{
		Vector2 pos = GetScreenPosition();
		pos.x += (float)GetTextAlignmentOffset();

		size_t size = m_textRows.size();
		for( size_t i(0); i < size; ++i )
		{
			if( (int)m_currentChar < m_textRows[i].x )
				break;

			int amount = abs(m_textRows[i].y - m_textRows[i].x);
			if( (int)m_currentChar < m_textRows[i].x + amount )
				amount -= m_textRows[i].x + amount - m_currentChar;

			spritebatch->DrawString( m_font,
				m_text,
				//m_text.begin() + m_textRows[i].x,
				//m_text.begin() + m_textRows[i].y,
				m_textRows[i].x,
				amount,
				pos,
				m_color,
				m_textAlignment
			);

			pos.y += m_font->GetLineHeight();

		}
	}

	Widget::Render(spritebatch);
}


void TextBox::SetFont( Font* font )
{
	if(font)
	{
		m_font = font;
		UpdateText();
	}
}


void TextBox::SetText( const fc::string& text )
{
	m_text = text;
	m_currentChar = 0;
	m_textSpeedCounter = 0.f;
	UpdateText();
}


void TextBox::UpdateText()
{
	// Here we have to generate all our line information for the
	// current text. By caching this data we can speed up font rendering.
	m_textRows.clear();

	float textWidth = 0.f;
	float textWidthBeforeCurrentWord = 0.f;

	int rowStartIndex = 0;
	int lastWordStartIndex = 0;
	int currentWordSize = 0;
	int numWordsInRow = 0;
	int textSize = (int)m_text.size();

	for( int i(0); i < textSize; ++i )
	{
		const char c = m_text[i];
		const Glyph & glyph = m_font->GetGlyph(c);

		if( c == '\n' || i == textSize - 1 )
		{
			int index = i;
			if( i == textSize - 1 )
				index++;

			m_textRows.push_back( Point(rowStartIndex, index) );

			rowStartIndex = i + 1;
			while( rowStartIndex < textSize && m_text[ rowStartIndex ] == ' ' )
				++rowStartIndex;

			currentWordSize = 0;
			numWordsInRow = 0;
			textWidth = 0;
			continue;
		}
		else if( c == ' ' )
		{
			if( currentWordSize > 0 )
			{
				numWordsInRow++;
				currentWordSize = 0;
			}
		}
		else
		{
			if( currentWordSize == 0 )
			{
				lastWordStartIndex = i;
				textWidthBeforeCurrentWord = textWidth;
			}

			currentWordSize++;
		}

		textWidth += glyph.advance;
		if( textWidth > GetWidth() )
		{
			if( numWordsInRow == 0 )
			{
				//width is not enough - barf on it.
				//w = textWidth;
			}
			else
			{
				//rewind to start of last word, removing the trailing space if needed.
				if( lastWordStartIndex > 0 && m_text[ lastWordStartIndex - 1 ] == ' ' )
					--lastWordStartIndex;

				//m_textRows.push_back( Point(rowStartIndex, lastWordStartIndex) );

				//rowStartIndex = lastWordStartIndex;


				m_textRows.push_back( Point(rowStartIndex, lastWordStartIndex) );

				rowStartIndex = lastWordStartIndex;
				//don't start a new row with a leftover space from the last row.
				while( rowStartIndex < textSize && m_text[ rowStartIndex ] == ' ' )
					++rowStartIndex;

				textWidth = textWidth - textWidthBeforeCurrentWord;

			}
		}
	}
}


/*
void TextBox::UpdateText()
{
	//Here we have to generate all our row information for the
	//current text. By caching this data we can speed up font rendering.
	m_textRows.clear();

	float textWidth = 0.f;
	float textWidthBeforeCurrentWord = 0.f;

	int rowStartIndex = 0;
	int lastWordStartIndex = 0;
	int currentWordSize = 0;
	int numWordsInRow = 0;
	int textSize = (int)m_text.size();

	for( int i(0); i < textSize; ++i )
	{
		const char c = m_text[i];
		const Glyph & glyph = m_font->GetGlyph(c);

		if( c == '\n' || i == textSize - 1 )
		{
			int index = i;
			if( i == textSize - 1 )
				index++;

			m_textRows.push_back( Point(rowStartIndex, index) );
			
			rowStartIndex = i + 1;
			while( rowStartIndex < textSize && m_text[ rowStartIndex ] == ' ' )
				++rowStartIndex;

			currentWordSize = 0;
			numWordsInRow = 0;
			textWidth = 0;
			continue;
		}
		else if( c == ' ' )
		{
			if( currentWordSize > 0 )
			{
				numWordsInRow++;
				currentWordSize = 0;
			}
		}
		else
		{
			if( currentWordSize == 0 )
			{
				lastWordStartIndex = i;
				textWidthBeforeCurrentWord = textWidth;
			}

			currentWordSize++;
		}

		textWidth += glyph.advance;
		if( textWidth > GetWidth() )
		{
			if( numWordsInRow == 0 )
			{
				//width is not enough - barf on it.
				//w = textWidth;
			}
			else
			{
				//rewind to start of last word, removing the trailing space if needed.
				if( lastWordStartIndex > 0 && m_text[ lastWordStartIndex - 1 ] == ' ' )
					--lastWordStartIndex;

				//m_textRows.push_back( Point(rowStartIndex, lastWordStartIndex) );

				//rowStartIndex = lastWordStartIndex;

			
				m_textRows.push_back( Point(rowStartIndex, lastWordStartIndex) );

				rowStartIndex = lastWordStartIndex;
				//don't start a new row with a leftover space from the last row.
				while( rowStartIndex < textSize && m_text[ rowStartIndex ] == ' ' )
					++rowStartIndex;

				textWidth = textWidth - textWidthBeforeCurrentWord;

			}
		}
	}
}
*/



CE_NAMESPACE_END
