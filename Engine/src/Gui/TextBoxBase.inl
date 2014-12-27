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

#include "Gui/TextBoxBase.h"
#include "Graphics/SpriteBatch.h"

CE_NAMESPACE_BEGIN


TextBoxBase::TextBoxBase() :
	m_font(null),
	m_text(),
	m_pageLength(0),
	m_currentChar(0),
	m_fastForwardSpeed(4),
	m_textSpeed(1.f),
	m_textSpeedCounter(0.f),
	m_textDisplayFinished(false),
	m_isTextInstantaneous(false)
{
}


void TextBoxBase::SetFont( Font* font )
{
	CE_ASSERT(font != null);
	m_font = font;
}


void TextBoxBase::SetText( const char* text )
{
	m_text = text;
	m_pageLength = 0;
	m_currentChar = 0;
	m_textSpeedCounter = 0.f;
	m_textDisplayFinished = false;
}


void TextBoxBase::SetText( const String& text )
{
	SetText(text.c_str());
}


void TextBoxBase::SetTextSpeed( float textSpeed )
{
	m_textSpeed = textSpeed;
}


void TextBoxBase::SetFastForwardSpeed( u32 fastForwardSpeed )
{
	m_fastForwardSpeed = fastForwardSpeed;
}


void TextBoxBase::FastForward()
{
	m_currentChar += m_fastForwardSpeed;
	if( m_currentChar >= m_pageLength )
	{
		m_currentChar = m_pageLength;
		m_textDisplayFinished = true;
	}
}


void TextBoxBase::Update()
{
	if( !IsActive() )
		return;

	if( m_currentChar < m_pageLength )
	{
		if( IsTextInstantaneous() )
		{
			m_currentChar = m_pageLength;
			m_textDisplayFinished = true;
		}
		else
		{
			m_textSpeedCounter += m_textSpeed;
			int incrementAmount = (int)m_textSpeedCounter;
			m_textSpeedCounter -= (float)incrementAmount;

			m_currentChar += incrementAmount;
		}

		m_currentChar = fc::min( m_currentChar, m_pageLength );
	}
	else if( !m_textDisplayFinished )
	{
		// current page is already fully displayed, so do nothing.
		m_currentChar = 0; //test
		m_textDisplayFinished = true;
	}

	Widget::Update();
}


void TextBoxBase::Render( SpriteBatch* )
{
	// nothing to do
}



CE_NAMESPACE_END


