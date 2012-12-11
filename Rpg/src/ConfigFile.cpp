
#include <fc/tokenizer.h>

#include <Catastrophe/IO/File.h>
#include "ConfigFile.h"

#define DEFAULT_CONFIG_FILE_NAME "settings.cfg"


ConfigFile::ConfigFile()
{
	m_filename = DEFAULT_CONFIG_FILE_NAME;
	InitDefaultValues();
}


void ConfigFile::InitDefaultValues()
{
	ConfigSetting* cfg = &m_settings[0];

	//Framerate settings
	cfg[ ConfigSetting::Vsync			].Set( "vsync"			, 0 );
	cfg[ ConfigSetting::LimitFps		].Set( "limit_fps"		, 1 );
	cfg[ ConfigSetting::HighResTimer	].Set( "highres_timer"	, 1 );
	cfg[ ConfigSetting::FrameSkip		].Set( "frame_skip"		, 0 );

	cfg[ ConfigSetting::ResX			].Set( "resx"			, 640 );
	cfg[ ConfigSetting::ResY			].Set( "resy"			, 480 );
	cfg[ ConfigSetting::Windowed		].Set( "windowed"		, 1 );
	cfg[ ConfigSetting::KeepAspect		].Set( "keep_aspect"	, 0 );
	cfg[ ConfigSetting::KeepScale		].Set( "keep_scale"		, 0 );
	cfg[ ConfigSetting::Scale			].Set( "scale"			, 0 );

	cfg[ ConfigSetting::OpenGLVersion	].Set( "opengl_version"	, 20 );
	cfg[ ConfigSetting::Multisample		].Set( "multisample"	, 0 );
	cfg[ ConfigSetting::Antialiasing	].Set( "antialias"		, 1 );
	cfg[ ConfigSetting::ForceMipmaps	].Set( "mipmaps"		, 0 );

	cfg[ ConfigSetting::NumJoysticks	].Set( "numjoysticks"	, 4 );

	cfg[ ConfigSetting::Console			].Set( "console"		, 1 );
	cfg[ ConfigSetting::Debug			].Set( "debug"			, 0 );

}


ConfigSetting* ConfigFile::Find( const fc::string& key )
{
	for( size_t i(0); i < ConfigSetting::MaxSettings; ++i )
	{
		if( m_settings[ i ].str == key )
			return &m_settings[ i ];
	}

	return 0;
}


bool ConfigFile::Read()
{
	File file(m_filename, FileReadText);
	if( !file.IsOpen() )
	{
		file.Close();
		Log("Info: %s not found. Writing default configuration...", m_filename.c_str());
		Write();

		return false;
	}

	/*
		The config file is stored as a simple text file
		so that it is easily editable by users that
		may have no idea just what they are doing. :P
	*/

	fc::string key;
	fc::string token;
	fc::string line;

	fc::tokenizer tokenizer;
	tokenizer.set_delimiters( " ;\t=:()[]<>,./" );

	while( !file.IsEof() )
	{
		file.ReadLine(line);
		if( line.empty() )
			continue;

		tokenizer.set_string(line);

		//Get the key type
		if( tokenizer.next(token) )
		{
			key = token;
			ConfigSetting *cfg = Find(token);

			//Get the value type
			if( !cfg || !tokenizer.next(token) )
			{
				Log("ConfigFile error: Invalid identifier or value (%s), token will not be parsed!", key.c_str());
				continue;
			}

			cfg->value = token.to_int();
		}
	}
	file.Close();

	return true;
}


bool ConfigFile::Write()
{
	const size_t MaxKeyLength = 15;

	// avoids extra allocations and other screwyness.
	for( int i(0); i < ConfigSetting::MaxSettings; ++i )
		ASSERT( m_settings[ i ].str.size() < MaxKeyLength );

	File file(m_filename, FileWriteText);
	if( !file.IsOpen() )
	{
		Log( "Error: Could not create a configuration file." );
		return false;
	}

	fc::string line;
	for( int i(0); i < ConfigSetting::MaxSettings; ++i )
	{
		const ConfigSetting *cfg = &m_settings[ i ];

		line.assign( cfg->str );
		line.append( MaxKeyLength - cfg->str.size(), ' ' );
		file.WriteLine( line + fc::to_string(cfg->value) );
	}

	file.Close();
	return true;
}



