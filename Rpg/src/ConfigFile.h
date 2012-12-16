
#pragma once

#include <fc/string.h>
#include <fc/vector.h>

#include "Common.h"


class ConfigSetting
{
public:
	enum ConfigurationSetting
	{
		Vsync,
		LimitFps,
		HighResTimer,
		FrameSkip,
		ResX,
		ResY,
		Fullscreen,
		KeepAspect,
		KeepScale,
		Scale,
		OpenGLVersion,
		Multisample,
		Antialiasing,
		ForceMipmaps,
		NumJoysticks,
		Console,
		Debug,
		MaxSettings //always last
	};

	ConfigSetting(const fc::string& str = "", int val = 0)
		: str(str), value(val) {}

	void Set( const fc::string& s, int val )
	{
		str	= s;
		value = val;
	}

	fc::string str;
	int value;
};


class ConfigFile
{
public:
	ConfigFile();

	void SetFilename( const fc::string& filename ) { m_filename = filename; }
	const fc::string& GetFilename() { return m_filename; }

	ConfigSetting &operator [] ( size_t index ) { return m_settings[ index ]; }
	const ConfigSetting &operator [] ( size_t index ) const { return m_settings[ index ]; }

	void InitDefaultValues();
	ConfigSetting* Find( const fc::string& key );
	ConfigSetting* GetSettings() { return &m_settings[0]; }

	bool Read();
	bool Write();

private:
	fc::string m_filename;
	ConfigSetting m_settings[ ConfigSetting::MaxSettings ];

};



