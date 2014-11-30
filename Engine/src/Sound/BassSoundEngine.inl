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


#if defined CE_SOUND_BASS

#include "Sound/BassSoundEngine.h"
#include <Bass.h>

CE_NAMESPACE_BEGIN


BassSoundEngine::BassSoundEngine()
{
}


void BassSoundEngine::Initialize()
{
	BASS_Init( -1, 44100, 0, 0, NULL);
}


void BassSoundEngine::Shutdown()
{
	StopAll();
	BASS_Free();
}


Sound* BassSoundEngine::LoadFromFile( Sound::Type type, const fc::string& filename )
{
		//dword handle(0);

		//handle = BASS_SampleLoad( FALSE, filename, 0, 0, 4, 0 );

		//handle = BASS_StreamCreateFile( FALSE, filename, 0, 0, 0 );

	return false;
}


Sound* BassSoundEngine::LoadFromData( Sound::Type type, void* data, u32 n_bytes )
{
	return false;
}


void BassSoundEngine::StopAll()
{
	for( vec_type::iterator it = m_sounds.begin(); it != m_sounds.end(); ++it )
	{
		//(*it)->Stop();
	}

	BASS_Stop();
}


void BassSoundEngine::PauseAll()
{
	BASS_Pause();
}


void BassSoundEngine::ResumeAll()
{
	BASS_Start();
}


void BassSoundEngine::SetVolume( float volume )
{
	m_volume = fc::clamp(volume, 0.f, 1.f);
	BASS_SetVolume( m_volume );
}


float BassSoundEngine::GetVolume()
{
	return BASS_GetVolume();
}


void BassSoundEngine::Update()
{
}


CE_NAMESPACE_END

#endif //CE_SOUND_BASS

