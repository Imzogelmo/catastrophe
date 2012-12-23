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

CE_NAMESPACE_BEGIN


class Sound
{
public:
	enum Type
	{
		TypeStream,
		TypeSfx,
		TypeMidi
	};

	Sound( Type type ) :
		m_type(type), m_volume(1.f), m_loop(true)
		{
			if( type == TypeSfx )
				m_loop = false;
		}

	virtual ~Sound()
	{}

	virtual void Play( bool restart = true ) = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Stop() = 0;
	virtual void Release() = 0;

	virtual bool IsPlaying() const = 0;
	virtual bool IsPaused() const = 0;
	virtual bool IsStopped() const = 0;
	virtual bool IsLooping() const = 0;

	virtual void SetVolume( float vol ) = 0;
	virtual void SetPan( float pan ) = 0;
	virtual void SetPosition( int pos ) = 0;
	virtual void SetLooping( bool enable = true ) = 0;

	virtual float GetVolume() const = 0;
	virtual float GetPan() const = 0;
	virtual int GetPosition() const = 0;
	virtual int GetLength() const = 0;

	Type GetType() { return m_type; }

protected:
	Type	m_type;
	float	m_volume;
	bool	m_loop;

};


CE_NAMESPACE_END

