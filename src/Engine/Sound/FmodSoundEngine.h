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

#include <fc/vector.h>
#include <fc/string.h>

#include "SoundEngine.h"
#include "FmodSound.h"


CE_NAMESPACE_BEGIN


class CE_API FmodSoundEngine : public SoundEngine
{
public:
	typedef fc::vector<FmodSound*>	vec_type;

	FmodSoundEngine();
	~FmodSoundEngine()
	{}

	Sound* LoadFromFile( Sound::Type type, const fc::string& filename );
	Sound* LoadFromData( Sound::Type type, void* data, size_t n_bytes );
	void Initialize();
	void Shutdown();
	void StopAll();
	void PauseAll();
	void ResumeAll();
	void SetVolume( float volume );
	float GetVolume();
	void Update();

	FMOD::System* GetSystem() const { return m_system; }

protected:
	FMOD::System*	m_system;
	vec_type		m_sounds;

};


CE_NAMESPACE_END
