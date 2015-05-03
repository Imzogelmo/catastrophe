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

#include "Catastrophe/Core/StringUtils.h"
#include "Catastrophe/Core/IO/ConfigFile.h"
#include "Catastrophe/Core/IO/File.h"

CE_NAMESPACE_BEGIN


ConfigFile::ConfigFile( const char* filename ) :
	m_filename(filename),
	m_currentSection(),
	m_configurations()
{
}


void ConfigFile::SetCurrentSection( const char* section )
{
	m_currentSection = section;
}


void ConfigFile::SetInt( const char* section, const char* entry, int value )
{
	ConfigFileSection* currentSection = AddSection(section);
	if( currentSection )
	{
		currentSection->configs[entry] = ToString(value);
	}
}


void ConfigFile::SetBool( const char* section, const char* entry, bool value )
{
	return SetInt(section, entry, value ? 1 : 0);
}


void ConfigFile::SetFloat( const char* section, const char* entry, float value )
{
	ConfigFileSection* currentSection = AddSection(section);
	if( currentSection )
	{
		currentSection->configs[entry] = ToString(value);
	}
}


void ConfigFile::SetString( const char* section, const char* entry, const char* value )
{
	ConfigFileSection* currentSection = AddSection(section);
	if( currentSection )
	{
		currentSection->configs[entry] = value;
	}
}


void ConfigFile::SetInt( const char* entry, int value )
{
	SetInt(m_currentSection.CString(), entry, value);
}


void ConfigFile::SetBool( const char* entry, bool value )
{
	SetBool(m_currentSection.CString(), entry, value);
}


void ConfigFile::SetFloat( const char* entry, float value )
{
	SetFloat(m_currentSection.CString(), entry, value);
}


void ConfigFile::SetString( const char* entry, const char* value )
{
	SetString(m_currentSection.CString(), entry, value);
}


int ConfigFile::GetInt( const char* section, const char* entry, int value )
{
	int ret = value;
	ConfigFileSection* currentSection = Find(section);
	if( currentSection )
	{
		ConfigFileSection::MapType::ConstIterator it = currentSection->configs.Find(entry);
		if( it != currentSection->configs.end() )
		{
			ret = it->value.ToInt();
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
	ConfigFileSection* currentSection = Find(section);
	if( currentSection )
	{
		ConfigFileSection::MapType::ConstIterator it = currentSection->configs.Find(entry);
		if( it != currentSection->configs.end() )
		{
			ret = it->value.ToFloat();
		}
	}

	return ret;
}


const char* ConfigFile::GetString( const char* section, const char* entry, const char* value )
{
	ConfigFileSection* currentSection = Find(section);
	if( currentSection )
	{
		ConfigFileSection::MapType::ConstIterator it = currentSection->configs.Find(entry);
		if( it != currentSection->configs.end() )
		{
			return it->value.CString();
		}
	}

	return value;
}


int ConfigFile::GetInt( const char* entry, int value )
{
	return GetInt(m_currentSection.CString(), entry, value);
}


bool ConfigFile::GetBool( const char* entry, bool value )
{
	return GetBool(m_currentSection.CString(), entry, value);
}


float ConfigFile::GetFloat( const char* entry, float value )
{
	return GetFloat(m_currentSection.CString(), entry, value);
}


const char* ConfigFile::GetString( const char* entry, const char* value )
{
	return GetString(m_currentSection.CString(), entry, value);
}


ConfigFileSection* ConfigFile::Find( const char* section )
{
	for( ConfigFileSection* it = m_configurations.begin(); it != m_configurations.end(); ++it )
		if( it->name == section )
			return it;

	return null;
}


ConfigFileSection* ConfigFile::AddSection( const char* section )
{
	ConfigFileSection* currentSection = Find(section);
	if( !currentSection )
	{
		currentSection = m_configurations.AddUninitialized();
		Memory::Construct(currentSection);
		currentSection->name = section;
	}

	return currentSection;
}


bool ConfigFile::Read()
{
	File file(m_filename, FileRead);
	if( !file.IsOpen() )
		return false;

	String key;
	String value;
	String line;
	String data;
	StringTokenizer<String> lineTokenizer("", " \t\n\r=[]");

	u32 size = file.Size();
	u32 index = 0;

	data.Resize(size);
	file.Read( &data[0], file.Size() );
	ConfigFileSection* section = null;

	while( index < size )
	{
		index = data.GetToken(line, index, "\n\r");
		if(index == String::npos)
			break;

		// skip over whitespace
		line.TrimStart();

		// needs to hold at least '[]' or ' = '
		if( line.size() < 3 )
		{
			++index;
			continue;
		}

		if(line[0] == '#') //comment
			continue;

		lineTokenizer.SetString(line);

		// Start a new section
		if( line[0] == '[' )
		{
			if( lineTokenizer.Next(key) )
				section = AddSection(key.CString());
		}

		// Parse the key-value pairs.
		else if(section != null)
		{
			if( lineTokenizer.Next(key) && lineTokenizer.Next(value) )
			{
				section->configs.Add(key, value);
			}
			else
			{
				Log("ConfigFile error: Invalid identifier or value (%s), token will not be parsed!", key.CString());
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

	String line;
	for( u32 i(0); i < m_configurations.Size(); ++i )
	{
		line.Clear();
		ConfigFileSection & section = m_configurations[i];

		// write an empty line before new sections.
		file.WriteLine("");
		line.Append('[').Append( section.name.CString() ).Append(']');
		file.WriteLine(line);

		ConfigFileSection::MapType & c = section.configs;
		for( ConfigFileSection::MapType::Iterator it = c.begin(); it != c.end(); ++it )
		{
			line.Clear();
			line.Append(it->key.CString()).Append(" = ").Append(it->value.CString());
			file.WriteLine(line);
		}
	}

	file.Close();
	return true;
}



CE_NAMESPACE_END
