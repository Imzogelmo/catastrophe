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

#include "../Common.h"
#include "Keys.h"

#include <fc/vector_set.h>
#include <fc/vector_map.h>

CE_NAMESPACE_BEGIN


class CE_API Keyboard
{
public:

	enum
	{
		MaxKeys = MAX_KEYS
	};

	Keyboard();

	bool IsKeyDown( int key ) const;
	bool IsKeyPressed( int key ) const;
	bool IsKeyReleased( int key ) const;

	//returns the total number of frames this key has been down.
	int KeyFrames( int key ) const;

	void SetKeyPress( int key );
	void SetKeyRelease( int key );

	void Update();
	void AnnulKey( int key );
	void Annul();

protected:
	fc::vector_map<int, int>	m_keyDown;
	fc::vector_set<int>			m_keyReleased;
	fc::vector_set<int>			m_keyPressedQueue;
	fc::vector_set<int>			m_keyReleasedQueue;

};


CE_NAMESPACE_END
