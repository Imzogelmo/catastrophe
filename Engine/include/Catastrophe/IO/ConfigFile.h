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
#include <fc/static_string.h>
#include <fc/vector.h>
#include <fc/vector_map.h>
#include "../Common.h"

CE_NAMESPACE_BEGIN


struct ConfigFileSection
{
	typedef fc::static_string<32> string_type;
	typedef fc::vector_map<string_type, string_type> map_type;

	string_type name;
	map_type configs;
};

// Declare fast storage type.
FC_MAKE_TRAIT(ConfigFileSection::string_type, is_pod);


class ConfigFile
{
public:
	typedef fc::vector<ConfigFileSection> vec_type;

	ConfigFile( const char* filename )
		: m_filename(filename), m_currentSection(), m_configurations()
	{}

	bool Read();
	bool Write();
	void SetCurrentSection( const char* section );

	void SetInt( const char* section, const char* entry, int value );
	void SetBool( const char* section, const char* entry, bool value );
	void SetFloat( const char* section, const char* entry, float value );
	void SetString( const char* section, const char* entry, const char* value );

	void SetInt( const char* entry, int value );
	void SetBool( const char* entry, bool value );
	void SetFloat( const char* entry, float value );
	void SetString( const char* entry, const char* value );

	int GetInt( const char* section, const char* entry, int value );
	bool GetBool( const char* section, const char* entry, bool value );
	float GetFloat( const char* section, const char* entry, float value );
	const char* GetString( const char* section, const char* entry, const char* value );

	int GetInt( const char* entry, int value );
	bool GetBool( const char* entry, bool value );
	float GetFloat( const char* entry, float value );
	const char* GetString( const char* entry, const char* value );

protected:
	// these pointers are not long living.
	ConfigFileSection* Find( const char* section );
	ConfigFileSection* AddSection( const char* section );

	String	m_filename;
	String	m_currentSection;
	vec_type	m_configurations;
};


CE_NAMESPACE_END
