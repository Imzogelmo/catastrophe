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
#include "StyledText.h"

CE_NAMESPACE_BEGIN



class CE_API TextBoxBase : public Widget
{
public:
	TextBoxBase();

	virtual void SetFont( Font* font );
	virtual void SetText( const char* text );
	virtual void SetText( const String& text );

	void SetTextSpeed( float textSpeed );
	void SetFastForwardSpeed( u32 fastForwardSpeed );
	void SetIsTextInstantaneous( bool value ) { m_isTextInstantaneous = value; }

	/// Fast forward the current character position by an amount set to the fastForwardSpeed.
	void FastForward();

	u32 GetPageLength() const { return m_pageLength; }
	u32 GetFastForwardSpeed() const { return m_fastForwardSpeed; }
	float GetTextSpeed() const { return m_textSpeed; }

	Font* GetFont() const { return m_font; }
	const String& GetText() const { return m_text; }
	
	bool IsTextInstantaneous() const { return m_isTextInstantaneous; }
	bool IsTextDisplayFinished() const { return m_textDisplayFinished; }

	virtual void Update();
	virtual void Render( SpriteBatch* spritebatch );

protected:
	void SetPageLength( u32 value ) { m_pageLength = value; }

	Font*	m_font;
	String	m_text;

	u32		m_pageLength;
	u32		m_currentChar;
	u32		m_fastForwardSpeed;

	float	m_textSpeed;
	float	m_textSpeedCounter;

	bool	m_textDisplayFinished;
	bool	m_isTextInstantaneous;

};


CE_NAMESPACE_END
