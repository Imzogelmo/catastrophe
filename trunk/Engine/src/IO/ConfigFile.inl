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

#include <fc/tokenizer.h>

#include "IO/ConfigFile.h"
#include "IO/File.h"

CE_NAMESPACE_BEGIN


void ConfigFile::SetCurrentSection( const char* section )
{
	m_currentSection = section;
}


void ConfigFile::SetInt( const char* section, const char* entry, int value )
{
	ConfigSection* currentSection = AddSection(section);
	if( currentSection )
	{
		currentSection->configs[entry] = fc::to_string(value);
	}
	else
	{
		Log("ConfigFile error on section %s.", section);
	}
}


void ConfigFile::SetBool( const char* section, const char* entry, bool value )
{
	return SetInt(section, entry, value ? 1 : 0);
}


void ConfigFile::SetFloat( const char* section, const char* entry, float value )
{
	ConfigSection* currentSection = AddSection(section);
	if( currentSection )
	{
		currentSection->configs[entry] = fc::to_string(value);
	}
	else
	{
		Log("ConfigFile error on section %s.", section);
	}
}


void ConfigFile::SetString( const char* section, const char* entry, const char* value )
{
	ConfigSection* currentSection = AddSection(section);
	if( currentSection )
	{
		currentSection->configs[entry] = value;
	}
	else
	{
		Log("ConfigFile error on section %s.", section);
	}
}


void ConfigFile::SetInt( const char* entry, int value )
{
	SetInt(m_currentSection.c_str(), entry, value);
}


void ConfigFile::SetBool( const char* entry, bool value )
{
	SetBool(m_currentSection.c_str(), entry, value);
}


void ConfigFile::SetFloat( const char* entry, float value )
{
	SetFloat(m_currentSection.c_str(), entry, value);
}


void ConfigFile::SetString( const char* entry, const char* value )
{
	SetString(m_currentSection.c_str(), entry, value);
}


int ConfigFile::GetInt( const char* section, const char* entry, int value )
{
	int ret = value;
	ConfigSection* currentSection = Find(section);
	if( currentSection )
	{
		ConfigSection::map_type::iterator it = currentSection->configs.find(entry);
		if( it != currentSection->configs.end() )
		{
			ret = it->second.to_int();
		}
	}

	return ret;
}


bool ConfigFile::GetBool( const char* section, const char* entry, bool value )
{
	return GetInt(section, entry, value ? 1 : 0) == 0 ? false : true;
}


float ConfigFile::GetFloat( const char* section, const char* entry, float value )
{
	float ret = value;
	ConfigSection* currentSection = Find(section);
	if( currentSection )
	{
		ConfigSection::map_type::iterator it = currentSection->configs.find(entry);
		if( it != currentSection->configs.end() )
		{
			ret = it->second.to_float();
		}
	}

	return ret;
}


const char* ConfigFile::GetString( const char* section, const char* entry, const char* value )
{
	ConfigSection* currentSection = Find(section);
	if( currentSection )
	{
		ConfigSection::map_type::iterator it = currentSection->configs.find(entry);
		if( it != currentSection->configs.end() )
		{
			return it->second.c_str();
		}
	}

	return value;
}


int ConfigFile::GetInt( const char* entry, int value )
{
	return GetInt(m_currentSection.c_str(), entry, value);
}


bool ConfigFile::GetBool( const char* entry, bool value )
{
	return GetBool(m_currentSection.c_str(), entry, value);
}


float ConfigFile::GetFloat( const char* entry, float value )
{
	return GetFloat(m_currentSection.c_str(), entry, value);
}


const char* ConfigFile::GetString( const char* entry, const char* value )
{
	return GetString(m_currentSection.c_str(), entry, value);
}


ConfigSection* ConfigFile::Find( const char* section )
{
	ConfigSection* ret = 0;
	for( vec_type::iterator it = m_configurations.begin(); it != m_configurations.end(); ++it )
	{
		if( it->name == section )
		{
			ret = it;
			break;
		}
	}

	return ret;
}


ConfigSection* ConfigFile::AddSection( const char* section )
{
	ConfigSection* currentSection = Find(section);
	if( !currentSection )
	{
		m_configurations.push_back();
		m_configurations.back().name = section;
		currentSection = &m_configurations.back();
	}

	return currentSection;
}


bool ConfigFile::Read()
{
	File file(m_filename, FileRead);
	if( !file.IsOpen() )
	{
		file.Close();
		Log("Info: %s not found.", m_filename.c_str());
		return false;
	}

	fc::string key;
	fc::string value;
	fc::string line;
	fc::string data;
	fc::tokenizer tokenizer;
	tokenizer.set_delimiters( " \t\n\r=[]" );
	size_t size = file.Size();
	size_t index = 0;

	data.resize(size);
	file.Read( &data[0], file.Size() );
	ConfigSection* section = 0;

	while( index < size )
	{
		if( !fc::tokenizer::get_token(data, "\n", index, line) )
		{
			index += fc::max((size_t)1, line.size());
		}

		if( line.empty() )
		{
			++index;
			continue;
		}

		tokenizer.set_string(line);

		//skip over common whitespace and endlines.
		while( !line.empty() && (line[0] == 10 || line[0] == 13 || line[0] == ' ' || line[0] == '\t') )
		{
			line.erase( line.begin() );
		}

		if( line.empty() || line[0] == '#' ) continue;
		if( line[0] == 0 )
		{
			index = size;
			continue;
		}
		if( line[0] == '[' )
		{
			if( tokenizer.next(key) )
			{
				section = AddSection(key.c_str());
			}
		}

		if( section )
		{
			if( tokenizer.next(key) && tokenizer.next(value) )
			{
				fc::pair<ConfigSection::string_type, ConfigSection::string_type> configValue;
				configValue.first = key;
				configValue.second = value;

				section->configs.insert(configValue);
			}
			else
			{
				Log("ConfigFile error: Invalid identifier or value (%s), token will not be parsed!", key.c_str());
				continue;
			}
		}
	}

	file.Close();
	return true;
}


bool ConfigFile::Write()
{
	File file(m_filename, FileWriteText);
	if( !file.IsOpen() )
	{
		Log( "Error: Could not create a configuration file." );
		return false;
	}

	fc::string line;
	for( size_t i(0); i < m_configurations.size(); ++i )
	{
		line.clear();
		ConfigSection & section = m_configurations[i];

		// write an empty line before new sections.
		file.WriteLine("");
		line.append('[').append( section.name.c_str() ).append(']');
		file.WriteLine(line);

		ConfigSection::map_type & c = section.configs;
		for( ConfigSection::map_type::iterator it = c.begin(); it != c.end(); ++it )
		{
			line.clear();
			line.append(it->first.c_str()).append(" = ").append(it->second.c_str());
			file.WriteLine(line);
		}
	}

	file.Close();
	return true;
}



CE_NAMESPACE_END
