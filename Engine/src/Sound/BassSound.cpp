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


#if defined CE_BASS

#include "Sound/BassSound.h"
#include "Sound/BassSoundEngine.h"
#include <Bass.h>

CE_NAMESPACE_BEGIN



BassSound::BassSound( Type type, BassSoundEngine* parent ) :
	Sound(type),
	m_parent(parent),
	m_handle(0)
{
}

		//	gBass->BASS_StreamFree(aMusicInfo->mHStream);
		//else if (aMusicInfo->mHMusic)
		//	gBass->BASS_MusicFree(aMusicInfo->mHMusic);



void BassSound::Play( bool restart )
{
	BASS_ChannelStop(m_handle);
	BASS_ChannelPlay( m_handle, (restart ? 1 : 0) );
}


void BassSound::Pause()
{
	if( IsPlaying() )
		BASS_ChannelPause(m_handle);
}

void BassSound::Resume()
{
	//if( IsPaused() )
	//	BASS_ChannelResume(m_handle);
}

bool BassSound::IsPlaying() const
{
	return (BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_PLAYING);
}

bool BassSound::IsPaused() const
{
	return (BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_PAUSED);
}

bool BassSound::IsStopped() const
{
	return (BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_STOPPED);
}

bool BassSound::IsLooping() const
{
	return (BASS_ChannelIsActive(m_handle) == BASS_ACTIVE_STOPPED);
}


void BassSound::SetVolume( float vol )
{
	m_volume = fc::clamp(vol, 0.f, 1.f);
	BASS_ChannelSetAttribute( m_handle, BASS_ATTRIB_VOL, m_volume );
}

float BassSound::GetVolume() const
{
	return m_volume;
}


void BassSound::SetPan( float pan )
{
	pan = fc::clamp(pan, -1.f, 1.f);
	BASS_ChannelSetAttribute( m_handle, BASS_ATTRIB_PAN, pan );
}

float BassSound::GetPan() const
{
	float pan = 0.f;
	BASS_ChannelGetAttribute( m_handle, BASS_ATTRIB_PAN, &pan );
	return pan;
}


void BassSound::SetLooping( bool enable )
{
	m_loop = enable;
	BASS_ChannelFlags( m_handle, (m_loop ? 1 : 0), BASS_SAMPLE_LOOP );
}


void BassSound::SetPosition( int pos )
{
	BASS_ChannelSetPosition( m_handle, (QWORD)pos, BASS_POS_BYTE );
}

int BassSound::GetPosition() const
{
	int position = (int)BASS_ChannelGetPosition( m_handle, BASS_POS_BYTE );
	return position;
}

int BassSound::GetLength() const
{
	int length = (int)BASS_ChannelGetLength( m_handle, BASS_POS_BYTE );
	return length;
}


CE_NAMESPACE_END

#endif //CE_BASS

