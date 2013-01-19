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

#include "Sound/SoundEngine.h"

#if defined CE_FMOD
	#include "Sound/FmodSound.h"
	#include "Sound/FmodSoundEngine.h"
	#define CE_SOUND_TYPE			FmodSound
	#define CE_SOUND_ENGINE_TYPE	FmodSoundEngine
#elif defined CE_BASS
	#include "Sound/BassSound.h"
	#include "Sound/BassSoundEngine.h"
	#define CE_SOUND_TYPE			BassSound
	#define CE_SOUND_ENGINE_TYPE	BassSoundEngine
#else
	#include "Sound/FmodSound.h"
	#include "Sound/FmodSoundEngine.h"
	#define CE_SOUND_TYPE			FmodSound
	#define CE_SOUND_ENGINE_TYPE	FmodSoundEngine
#endif

CE_NAMESPACE_BEGIN


SoundEngine* SoundEngine::CreateSoundEngine()
{
	return new CE_SOUND_ENGINE_TYPE;
}


void SoundEngine::DeleteSoundEngine( SoundEngine* instance )
{
	delete instance;
}

//TODO pool sounds.
//fc::fixed_block_allocator<CE_SOUND_TYPE, 64> gSoundPool;

Sound* SoundEngine::CreateSound( Sound::Type type )
{
	Sound* sound = new CE_SOUND_TYPE(type, (CE_SOUND_ENGINE_TYPE*)this);
	//gSoundPool.allocate(1);
	return sound;
}


void SoundEngine::DestroySound( Sound** sound )
{
	//gSoundPool.destroy(*sound);
	delete *sound;
}


CE_NAMESPACE_END

