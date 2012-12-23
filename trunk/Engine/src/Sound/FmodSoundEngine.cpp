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


#include <Fmod/fmod.hpp>
#include <Fmod/fmod_dsp.h>
#include <Fmod/fmod_errors.h>

#include "Sound/FmodSound.h"
#include "Sound/FmodSoundEngine.h"

#ifdef _MSC_VER
	#pragma comment(lib, "fmodex_vc.lib")
#endif

#define ERRCHECK(result) { \
	if( result != FMOD_OK ) { \
		Log( "FMOD error (%d) %s", result, FMOD_ErrorString(result) ); \
	}}

CE_NAMESPACE_BEGIN


FmodSoundEngine::FmodSoundEngine() :
	SoundEngine(),
	m_system(0),
	m_sounds()
{
}


void FmodSoundEngine::Initialize()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&m_system);
	ERRCHECK(result);

	result = m_system->init(128, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);
}


void FmodSoundEngine::Shutdown()
{
	StopAll();
	FMOD_RESULT result;

	//release all
	for( vec_type::iterator it = m_sounds.begin(); it != m_sounds.end(); ++it )
	{
		(*it)->Release();
		DestroySound((Sound**)it);
	}

	m_sounds.clear();
	result = m_system->close();
	ERRCHECK(result);

	result = m_system->release();
	ERRCHECK(result);
}


Sound* FmodSoundEngine::LoadFromFile( Sound::Type type, const fc::string& filename )
{
	FmodSound* sound = 0;
	FMOD::Sound* fmodSound = 0;
	FMOD_RESULT result;

	if( type == Sound::TypeSfx )
	{
		result = m_system->createSound( filename.c_str(), FMOD_DEFAULT, 0, &fmodSound );
	}
	else //if( type == Sound::TypeMidi || type == Sound::TypeStream )
	{
		result = m_system->createStream( filename.c_str(), FMOD_DEFAULT, 0, &fmodSound );
	}

	if( result == FMOD_OK )
	{
		sound = (FmodSound*)CreateSound(type);
		sound->m_sound = fmodSound;
		sound->m_sound->setUserData(sound);
		m_sounds.push_back(sound);
	}
	else
	{
		//log it as an error.
		Log( "FMOD error (%d) %s", result, FMOD_ErrorString(result) );
	}

	return sound;
}


Sound* FmodSoundEngine::LoadFromData( Sound::Type type, void* data, size_t n_bytes )
{
	return 0; //todo
}


void FmodSoundEngine::StopAll()
{
	for( vec_type::iterator it = m_sounds.begin(); it != m_sounds.end(); ++it )
	{
		(*it)->Stop();
	}
}


void FmodSoundEngine::PauseAll()
{
	for( vec_type::iterator it = m_sounds.begin(); it != m_sounds.end(); ++it )
	{
		(*it)->Pause();
	}
}


void FmodSoundEngine::ResumeAll()
{
	for( vec_type::iterator it = m_sounds.begin(); it != m_sounds.end(); ++it )
	{
		(*it)->Resume();
	}
}


void FmodSoundEngine::SetVolume( float volume )
{
	m_volume = fc::clamp(volume, 0.f, 1.f);
	//FMOD_RESULT result = m_system->setVolume(m_volume);
	//ERRCHECK(result);
}


float FmodSoundEngine::GetVolume()
{
	return m_volume;
}


void FmodSoundEngine::Update()
{
	FMOD_RESULT result = m_system->update();
	ERRCHECK(result);
}



#undef ERRCHECK

CE_NAMESPACE_END

