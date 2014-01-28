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


#include "Input/Keyboard.h"

CE_NAMESPACE_BEGIN


Keyboard::Keyboard()
{
	Annul();
}


bool Keyboard::IsKeyDown( int key ) const
{
	return m_keyDown.contains(key);
}


bool Keyboard::IsKeyPressed( int key ) const
{
	fc::vector_map<int, int>::const_iterator it = m_keyDown.find(key);
	return (it != m_keyDown.end() && it->second == 1);
}


bool Keyboard::IsKeyReleased( int key ) const
{
	return m_keyReleased.contains(key);
}


int Keyboard::KeyFrames( int key ) const
{
	fc::vector_map<int, int>::const_iterator it = m_keyDown.find(key);
	if(it != m_keyDown.end())
		return it->second;

	return 0;
}


void Keyboard::SetKeyPress( int key )
{
	m_keyPressedQueue.insert(key);
}


void Keyboard::SetKeyRelease( int key )
{
	m_keyReleasedQueue.insert(key);
}


void Keyboard::Update()
{
	m_keyReleased.clear();

	//erase keys that were released.
	for( fc::vector_set<int>::iterator it = m_keyReleasedQueue.begin(); it != m_keyReleasedQueue.end(); ++it )
	{
		m_keyDown.erase(*it);
		m_keyReleased.insert(*it);
	}

	//increment the frame count for keys that are being held down.
	for( fc::vector_map<int, int>::iterator it = m_keyDown.begin(); it != m_keyDown.end(); ++it )
	{
		it->second++;
	}

	//add keys that were pressed this frame.
	for( fc::vector_set<int>::iterator it = m_keyPressedQueue.begin(); it != m_keyPressedQueue.end(); ++it )
	{
		m_keyDown[*it] = 1;
	}

	m_keyPressedQueue.clear();
	m_keyReleasedQueue.clear();
}


void Keyboard::AnnulKey( int key )
{
	m_keyDown.erase(key);
}


void Keyboard::Annul()
{
	m_keyDown.clear();
	m_keyPressedQueue.clear();
	m_keyReleasedQueue.clear();
}


CE_NAMESPACE_END
