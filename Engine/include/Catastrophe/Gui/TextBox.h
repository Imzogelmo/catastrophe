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

CE_NAMESPACE_BEGIN


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

	void SetFrame( Frame* frame );
	void SetFont( Font* font );
	void SetText( const fc::string& text );
	void SetRowHeight( int height );
	void SetFastForwardSpeed( int speed );
	void FastForward();

	Frame* GetFrame() const { return m_frame; }
	size_t GetNumberOfRows() const;
	int GetRowHeight() const { return m_rowHeight; }
	int GetFastForwardSpeed() const { return m_fastForwardSpeed; }

	bool IsTextDisplayFinished() const { return m_textDisplayFinished; }
	bool IsTextInstantaneous() const;

	void UpdateText();

protected:
	Frame*			m_frame;
	int				m_rowHeight;
	row_vec_type	m_textRows; 

	int				m_fastForwardSpeed;
	float			m_textSpeed;
	float			m_textSpeedCounter;
	size_t			m_currentChar;

	bool			m_textDisplayFinished;
	bool			m_autoUpdateFastForwardSpeed;

};





CE_NAMESPACE_END
