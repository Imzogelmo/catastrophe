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
#include "Graphics/Font.h"
#include "Graphics/SpriteBatch.h"

CE_NAMESPACE_BEGIN


// TextPage

TextPage::TextPage() :
	lines()
{
	lines.reserve(4);
}


void TextPage::AddNewLine( const String& str )
{
	lines.push_back(str);
}


void TextPage::Render( Font* font, SpriteBatch* spriteBatch, const Vector2& position, Color color, u32 numCharsToDraw )
{
	CE_ASSERT(spriteBatch);
	if( font == null || numCharsToDraw == 0 )
		return;

	SpriteData sd;
	::memset(&sd, 0, sizeof(SpriteData));

	sd.SetBlendMode(BlendMode::Alpha);
	sd.SetTexture(font->GetTextureID());
	sd.data[0].color = color;
	sd.data[1].color = color;
	sd.data[2].color = color;
	sd.data[3].color = color;

	Vector2 currentPosition = position;
	u32 charsRendered = numCharsToDraw;

	for( StringVector::const_iterator line = lines.begin(); line != lines.end(); ++line )
	{
		//const String& str = *line;
		for( String::const_iterator it = line->begin(); it != line->end(); ++it )
		{
			const char c = *it;
			const Glyph& glyph = font->GetGlyph(c);

			// don't render any whitespace.
			if( c != ' ' )
			{
				const Vector2 minPosition = currentPosition + glyph.translation;
				const Vector2 maxPosition = minPosition + glyph.size;
				const Rectf uv = glyph.uv;

				sd.SetVertexUVData(minPosition, maxPosition, uv);
				spriteBatch->DrawSpriteData(sd);
			}

			currentPosition.x += glyph.advance;

			// if we've already rendered the specified amount of characters we're done.
			if( --charsRendered == 0 )
				return;
		}

		// reset position and add line height to the current position.
		currentPosition.x = position.x;
		currentPosition.y += font->GetLineHeight();
	}
}


u32 TextPage::Length() const
{
	u32 length = 0;
	for( StringVector::const_iterator it = lines.begin(); it != lines.end(); ++it )
		length += it->length();

	return length;
}


// TextBox

TextBox::TextBox() :
	TextBoxBase(),
	m_pages(),
	m_currentPageNumber(0)
{
}


void TextBox::SetFont( Font* font )
{
	if( font != null )
	{
		m_font = font;
		UpdateText();
	}
}


void TextBox::SetText( const String& text )
{
	SetText(text.c_str());
}


void TextBox::SetText( const char* text )
{
	TextBoxBase::SetText(text);
	UpdateText();
}


void TextBox::Update()
{
	TextBoxBase::Update();
}


void TextBox::Render( SpriteBatch* spriteBatch )
{
	TextPage* currentTextPage = GetCurrentPage();
	if( currentTextPage != null )
	{
		u32 numCharsToDraw = m_currentChar;
		Color color = GetColor();
		Vector2 screenPosition = GetScreenPosition();

		currentTextPage->Render(m_font, spriteBatch, screenPosition, color, numCharsToDraw);
	}

	Widget::Render(spriteBatch);
}


void TextBox::IncrementPage()
{
	if( !m_pages.empty() && m_currentPageNumber < m_pages.size() - 1 )
		m_currentPageNumber++;
}


void TextBox::UpdateText()
{
	if( m_font == null )
		return;

	ClearPages();

	TextPage* currentPage = AddNewPage();
	String currentWord;
	String currentLine;
	currentWord.reserve(64);
	currentLine.reserve(128);

	u32 spaceWidth = (u32)m_font->GetGlyph(' ').advance;
	u32 maxLineWidth = (u32)(fc::max<int>((int)GetWidth(), 64));
	u32 maxNumLines = (u32)(fc::max<int>((int)GetHeight(), 32) / m_font->GetLineHeight());
	u32 currentLineWidth = 0;
	u32 currentIndex = 0;
	u32 currentPageLength = 0;

	while( GetNextToken(m_text, currentWord, currentIndex, " \t\r") )
	{
		u32 wordWidth = (u32)m_font->GetTextWidth(currentWord);
		if( (currentLineWidth + wordWidth) > maxLineWidth )
		{
			// out of room, start a new line
			currentPage->AddNewLine(currentLine);
			currentLineWidth = 0;
			currentLine.clear();

			// add a new page if the next line won't fit inside the textbox.
			if( currentPage->GetNumTextLines() >= maxNumLines )
				currentPage = AddNewPage();
		}

		currentLine += currentWord;
		currentLine += ' ';
		currentLineWidth += (wordWidth + spaceWidth);

		if( currentWord[0] == '\n' )
		{
		}

	}

	// add the remainder to the final text line
	if( !currentLine.empty() )
		currentPage->AddNewLine(currentLine);

	SetCurrentPage(0);
}


TextPage* TextBox::AddNewPage()
{
	TextPage* page = new TextPage();
	m_pages.push_back(page);
	page->lines.reserve(8); //fixme
	return page;
}


TextPage* TextBox::GetPage( u32 pageNumber )
{
	return (pageNumber < m_pages.size() ? m_pages[pageNumber] : null);
}


TextPage* TextBox::GetCurrentPage()
{
	return (m_currentPageNumber < m_pages.size() ? m_pages[m_currentPageNumber] : null);
}


void TextBox::ClearPages()
{
	for( vec_type::iterator it = m_pages.begin(); it != m_pages.end(); ++it )
		delete *it;

	m_pages.clear();
}


void TextBox::SetCurrentPage( u32 pageNumber )
{
	if( pageNumber < m_pages.size() )
	{
		m_currentPageNumber = pageNumber;
		SetPageLength(GetCurrentPage() ? GetCurrentPage()->Length() : 0);
	}
}


u32 TextBox::GetNumPages() const
{
	return m_pages.size();
}


bool TextBox::IsTextDisplayFinished()
{
	return m_textDisplayFinished;
}


bool TextBox::IsPagesFinished()
{
	return (m_textDisplayFinished && m_currentPageNumber == m_pages.size() - 1);
}


bool TextBox::GetNextToken( const String& str, String& token, u32& index, const String& delimiters )
{
	u32 beginIndex;
	u32 endIndex;

	beginIndex = str.find_first_not_of( delimiters, index );

	if( beginIndex == String::npos ) 
		return false;

	endIndex = str.find_first_of( delimiters, beginIndex + 1 );
	if( endIndex == String::npos )
		endIndex = str.size();

	CE_ASSERT(endIndex >= beginIndex);

	index = endIndex;
	token.assign( &str[ beginIndex ], endIndex - beginIndex );

	return true;
}






















/*
void AddSpace( u32& index )
{
	if( m_text[index] == ' ' )
}

void AddWord( const StringRef& str, u32& index )
{
	float lineWidth = 0.f;
	if( fc::is_whitespace(token[index]) )
		lineWidth += m_font->GetGlyph(' ').advance;

	return lineWidth;
}

const char* TextBox::AddNewWord( const char* first, const char* last, StyledTextLineRef& currentLine )
{
	// Start a new line
	first = StripLeadingWhiteSpace(first, last);
	if( first != last )
	{
		for( float lineWidth = 0.f; lineWidth < maxLineWidth; ++lineWidth )
		{
			const char c = *first;
			const Glyph& glyph = m_font->GetGlyph(c);

			if( c == '\n' )
				return first;
		
			lineWidth += glyph.advance;
		}
	}
}

const char* TextBox::StripLeadingWhiteSpace( const char* first, const char* last )
{
	while( first != last && (first == ' ' || first == '\t') )
		++first;

	return first;
}


const char* TextBox::StripTrailingWhiteSpace( const char* first, const char* last )
{
	while( first != last-- && (last == ' ' || last == '\t') )
		;

	return last;
}

*/



CE_NAMESPACE_END
