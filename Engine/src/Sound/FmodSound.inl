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


#ifdef CE_SOUND_FMOD

#include <Fmod/fmod.hpp>
#include <Fmod/fmod_dsp.h>
#include <Fmod/fmod_errors.h>

#include "Sound/FmodSound.h"
#include "Sound/FmodSoundEngine.h"

CE_NAMESPACE_BEGIN


FMOD_RESULT F_CALLBACK ChannelCallback( FMOD_CHANNEL *fmodChannel, FMOD_CHANNEL_CALLBACKTYPE type, void *commanddata1, void *commanddata2 )
{
	if( type == FMOD_CHANNEL_CALLBACKTYPE_END )
	{
		//TODO: this does not take into account what happens when the sound has played twice.. hmm....
		void* data;
		FMOD_Channel_GetUserData(fmodChannel, &data);
		(*(void**)data) = 0;
	}

	return FMOD_OK;
}


FmodSound::FmodSound( Type type, FmodSoundEngine* parent ) :
	Sound(type),
	m_parent(parent),
	m_sound(0),
	m_channel(0)
{
}


void FmodSound::Release()
{
	Stop();
	if(m_sound)
	{
		FMOD_RESULT result = m_sound->release();
		FMOD_ERRCHECK(result);

		m_channel = 0;
	}
}


void FmodSound::Play( bool restart )
{
	if(m_sound)
	{
		//TODO channel gets lost and recycled by FMOD.
		//we could set a callback here so that we can respond accordingly.
		//if(restart)
		//	Stop();

		FMOD_CHANNELINDEX channelID = FMOD_CHANNEL_FREE;
		if( m_channel && (m_type != TypeSfx || restart) )
		{
			channelID = FMOD_CHANNEL_REUSE;
		}

		FMOD_RESULT result = m_parent->GetSystem()->playSound(channelID, m_sound, true, &m_channel);
		FMOD_ERRCHECK(result);

		//store the pointer to our channel. -evil-
		m_channel->setUserData((void*)&m_channel);
		m_channel->setCallback(ChannelCallback);
		m_channel->setVolume(m_volume);
		m_channel->setPaused(false);
		SetLooping(m_loop);
	}
}


void FmodSound::Pause()
{
	if(m_channel)
	{
		FMOD_RESULT result = m_channel->setPaused(true);
		FMOD_ERRCHECK(result);
	}
}


void FmodSound::Stop()
{
	if(m_channel)
	{
		FMOD_RESULT result = m_channel->stop();
		FMOD_ERRCHECK(result);
	}
}


void FmodSound::Resume()
{
	if(m_channel)
	{
		FMOD_RESULT result = m_channel->setPaused(false);
		FMOD_ERRCHECK(result);
	}
}


bool FmodSound::IsPlaying() const
{
	bool playing = false;
	if(m_channel)
	{
		FMOD_RESULT result = m_channel->isPlaying(&playing);
		FMOD_ERRCHECK(result);
	}
	return playing;
}


bool FmodSound::IsPaused() const
{
	bool paused = false;
	if(m_channel)
	{
		FMOD_RESULT result = m_channel->getPaused(&paused);
		FMOD_ERRCHECK(result);
	}
	return paused;
}


bool FmodSound::IsStopped() const
{
	bool stopped = true;
	if(m_channel)
	{
		//FMOD_RESULT result = m_channel->getStopped(&stopped);
		//FMOD_ERRCHECK(result);
	}
	return stopped;
}


bool FmodSound::IsLooping() const
{
	//todo loop_begin; loop_end;
	return m_loop;
}


void FmodSound::SetVolume( float vol )
{
	m_volume = fc::clamp(vol, 0.f, 1.f);
	if(m_channel)
	{
		FMOD_RESULT result = m_channel->setVolume(m_volume);
		FMOD_ERRCHECK(result);
	}
}


float FmodSound::GetVolume() const
{
	return m_volume;
}


void FmodSound::SetPan( float pan )
{
	pan = fc::clamp(pan, -1.f, 1.f);
	if(m_channel)
	{
		FMOD_RESULT result = m_channel->setPan(pan);
		FMOD_ERRCHECK(result);
	}
}


float FmodSound::GetPan() const
{
	float pan = 0.f;
	if(m_channel)
	{
		FMOD_RESULT result = m_channel->getPan(&pan);
		FMOD_ERRCHECK(result);
	}
	return pan;
}


void FmodSound::SetLooping( bool enable )
{
	m_loop = enable;
	if(m_channel)
	{
		FMOD_RESULT result = m_channel->setLoopCount( (m_loop ? -1 : 0) );
		FMOD_ERRCHECK(result);
	}
}


void FmodSound::SetPosition( int pos )
{
	if(m_channel)
	{
		int length = GetLength();
		int time = fc::clamp( pos, 0, length );
		FMOD_RESULT result = m_channel->setPosition( time, FMOD_TIMEUNIT_MS );
		FMOD_ERRCHECK(result);
	}
}


int FmodSound::GetPosition() const
{
	int pos = 0;
	if(m_channel)
	{
		FMOD_RESULT result = m_channel->getPosition( (size_t*)&pos, FMOD_TIMEUNIT_MS );
		FMOD_ERRCHECK(result);
	}
	return pos;
}


int FmodSound::GetLength() const
{
	int length = 0;
	if(m_sound)
	{
		FMOD_RESULT result = m_sound->getLength( (size_t*)&length, FMOD_TIMEUNIT_MS );
		FMOD_ERRCHECK(result);
	}
	return length;
}


CE_NAMESPACE_END


#endif // CE_SOUND_FMOD
