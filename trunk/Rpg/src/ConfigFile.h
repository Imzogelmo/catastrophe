// catastrophe rpg engine
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

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



