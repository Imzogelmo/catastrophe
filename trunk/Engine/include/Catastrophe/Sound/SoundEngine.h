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

#include <fc/string.h>
#include "Sound.h"

CE_NAMESPACE_BEGIN


class SoundEngine
{
public:
	SoundEngine() : m_volume(1.f) {}
	virtual ~SoundEngine()
	{}

	virtual Sound* LoadFromFile( Sound::Type type, const fc::string& filename ) = 0;
	virtual Sound* LoadFromData( Sound::Type type, void* data, size_t n_bytes ) = 0;
	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual void StopAll() = 0;
	virtual void PauseAll() = 0;
	virtual void ResumeAll() = 0;
	virtual void SetVolume( float volume ) = 0;
	virtual float GetVolume() = 0;
	virtual void Update() = 0;

	//creates a sound engine type. returns null if no sound back-end is defined.
	//the caller is responsible for deleting this pointer when finished with it.
	static SoundEngine* CreateSoundEngine();
	static void DeleteSoundEngine( SoundEngine* instance );

	//all sounds that are created here must be destroyed here.
	//you should never have to call these, as they are done by the sound engine.
	Sound* CreateSound( Sound::Type type );
	void DestroySound( Sound** sound );

protected:
	float			m_volume;

};


CE_NAMESPACE_END
