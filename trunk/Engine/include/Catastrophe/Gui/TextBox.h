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
#include "Frame.h"
#include "TextLine.h"

#include <fc/fixed_vector.h>

CE_NAMESPACE_BEGIN

/*
class CE_API IntrusiveTextSegment
{
public:
	typedef const char*	iterator;
	TextSegment() : m_textBegin(0), m_textEnd(0), m_scale(Vector2::One), m_color(Color::White)
	{}

	TextSegment( iterator first, iterator last, const Vector2& scale, const Color& color)
		: m_textBegin(first), m_textEnd(last), m_scale(scale), m_color(color)
	{}

	iterator Begin() const { return m_textBegin; }
	iterator End() const { return m_textEnd; }

	virtual float GetLineWidth( Font* );
	virtual float GetLineHeight();

protected:
	Font*		m_font;
	iterator	m_textBegin;
	iterator	m_textEnd;
	Vector2		m_scale;
	Color		m_color;

};


// represents a line of text
class CE_API TextLine
{
public:
	virtual TextSegment* GetTextSegment( int i );
	virtual int GetNumTexts();
	virtual int GetLineWidth();
	virtual int GetLineHeight();



protected:
	fc::vector<TextSegment*> m_textSegments;

};


// represents a page of text
class CE_API TextPage
{
public:
	virtual TextSegment* GetTextSegment( int i );
	virtual int GetNumTexts();
	virtual int GetLineWidth();
	virtual int GetLineHeight();



protected:
	fc::vector<TextSegment*> m_textSegments;

};


*/

class CE_API TextBox : public Label
{
public:
	typedef fc::fixed_vector<Point, 16>		row_vec_type;
	enum MessageConstants
	{
		DefaultFastForwardSpeed = 4,
	};

	TextBox( const fc::string& text = "", Font* font = 0, TextAlignment alignment = AlignLeft, int rowHeight = -1 );
	
	virtual void Update();
	virtual void Render( SpriteBatch* spritebatch );

	virtual void SetFont( Font* font );
	virtual void SetText( const fc::string& text );
	//virtual void SetRowHeight( int height );
	virtual void SetFastForwardSpeed( int speed );
	virtual void FastForward();

	u32 GetNumberOfRows() const;
	int GetRowHeight() const { return m_rowHeight; }
	int GetFastForwardSpeed() const { return m_fastForwardSpeed; }

	bool IsTextDisplayFinished() const { return m_textDisplayFinished; }
	bool IsTextInstantaneous() const;

	void UpdateText();

protected:
	int				m_rowHeight;
	row_vec_type	m_textRows; 

	int				m_fastForwardSpeed;
	float			m_textSpeed;
	float			m_textSpeedCounter;
	u32			m_currentChar;

	bool			m_textDisplayFinished;
	bool			m_autoUpdateFastForwardSpeed;

};





CE_NAMESPACE_END
