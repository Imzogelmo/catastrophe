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

#include "Catastrophe/Sound.h"

CE_NAMESPACE_BEGIN


class CE_API SoundEngine
{
public:
	SoundEngine() : m_volume(1.f) {}
	virtual ~SoundEngine()
	{}

	/// Loads an audio file from disk and returns a pointer to the newly created sound.
	virtual Sound* LoadFromFile( Sound::Type type, const char* filename ) = 0;

	/// Loads an audio file from memory and returns a pointer to the newly created sound.
	virtual Sound* LoadFromData( Sound::Type type, void* data, u32 nBytes ) = 0;

	/// Loads a sound plugin, if supported.
	virtual bool LoadPlugin(const char* filename) = 0;

	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual void StopAll() = 0;
	virtual void PauseAll() = 0;
	virtual void ResumeAll() = 0;
	virtual void SetVolume( float volume ) = 0;
	virtual float GetVolume() = 0;
	virtual void Update() = 0;

	/// Creates a sound engine type. returns null if no sound back-end is defined.
	/// The caller is responsible for deleting this pointer when finished with it.
	static SoundEngine* CreateSoundEngine();

	/// Deletes a SoundEngine instance and all objects that were created by it.
	static void DeleteSoundEngine( SoundEngine* instance );

	// All sounds that are created here must be destroyed here.
	// You should never have to call these, as they are done by the sound engine.
	Sound* CreateSound( Sound::Type type );

	/// Destroys a sound instance.
	void DestroySound( Sound** sound );

protected:
	float m_volume;

};


CE_NAMESPACE_END
