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

#include "Sound.h"

CE_NAMESPACE_BEGIN

class SoundEngine;
class FmodSoundEngine;

//forward declarations
namespace FMOD
{
    class System;
    class Sound;
    class Channel;
    class ChannelGroup;
    class SoundGroup;
    class Reverb;
    class DSP;
    class DSPConnection;
    class Geometry;
}


class CE_API FmodSound : public Sound
{
public:
	friend class FmodSoundEngine;

	FmodSound( Type type, FmodSoundEngine* parent );

	void Play( bool restart = true );
	void Pause();
	void Resume();
	void Stop();
	void Release();

	bool IsPlaying() const;
	bool IsPaused() const;
	bool IsStopped() const;
	bool IsLooping() const;

	void SetVolume( float vol );
	void SetPan( float pan );
	void SetPosition( int pos );
	void SetLooping( bool enable = true );

	float GetVolume() const;
	float GetPan() const;
	int GetPosition() const;
	int GetLength() const;

protected:
	FmodSoundEngine*	m_parent;
	FMOD::Sound*		m_sound;
	FMOD::Channel*		m_channel;

};


#ifndef FMOD_ERRCHECK
#define FMOD_ERRCHECK(result) { \
	if( result != FMOD_OK ) { \
		Log( "FMOD error (%d) %s", result, FMOD_ErrorString(result) ); \
	}}
#endif


CE_NAMESPACE_END

