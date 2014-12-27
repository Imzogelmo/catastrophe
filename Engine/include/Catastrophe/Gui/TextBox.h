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

#include "Label.h"
#include "TextBoxBase.h"

CE_NAMESPACE_BEGIN


struct CE_API TextPage
{
	typedef fc::vector<String> StringVector;

	StringVector lines;

	StringVector& GetLines() { return lines; }
	const StringVector& GetLines() const { return lines; }

	TextPage();

	void AddNewLine( const String& str );
	void Render( Font* font, SpriteBatch* spriteBatch, const Vector2& position, Color color, u32 numCharsToDraw );

	u32 GetNumTextLines() const { return lines.size(); }
	u32 Length() const;

};


class CE_API TextBox : public TextBoxBase
{
public:
	typedef fc::vector<TextPage*> vec_type;

	TextBox();
	
	virtual void SetFont( Font* font );
	virtual void SetText( const char* text );
	virtual void SetText( const String& text );

	virtual void Update();
	virtual void Render( SpriteBatch* spriteBatch );
	virtual void IncrementPage();

	TextPage* AddNewPage();
	TextPage* GetPage( u32 pageNumber );
	TextPage* GetCurrentPage();

	void ClearPages();
	void SetCurrentPage( u32 pageNumber );
	u32 GetNumPages() const;

	bool IsTextDisplayFinished();
	bool IsPagesFinished();

protected:
	virtual void UpdateText();
	bool GetNextToken( const String& str, String& token, u32& index, const String& delimiters = " \t\r" );

	vec_type	m_pages;
	u32			m_currentPageNumber;

};




CE_NAMESPACE_END
