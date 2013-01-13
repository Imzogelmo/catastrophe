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
#include <fc/vector.h>
#include <fc/vector_map.h>
#include "../Common.h"

CE_NAMESPACE_BEGIN


struct ConfigSection
{
	typedef fc::vector_map<fc::string, fc::string>	map_type;

	fc::string name;
	map_type configs;
};


class ConfigFile
{
public:
	typedef fc::vector<ConfigSection>		vec_type;

	ConfigFile( const fc::string& filename )
		: m_filename(filename)
	{}

	bool Read();
	bool Write();
	void SetCurrentSection( const fc::string& section );

	void SetInt( const fc::string& section, const fc::string& entry, int value );
	void SetBool( const fc::string& section, const fc::string& entry, bool value );
	void SetFloat( const fc::string& section, const fc::string& entry, float value );
	void SetString( const fc::string& section, const fc::string& entry, const fc::string& value );

	void SetInt( const fc::string& entry, int value );
	void SetBool( const fc::string& entry, bool value );
	void SetFloat( const fc::string& entry, float value );
	void SetString( const fc::string& entry, const fc::string& value );

	int GetInt( const fc::string& section, const fc::string& entry, int value );
	bool GetBool( const fc::string& section, const fc::string& entry, bool value );
	float GetFloat( const fc::string& section, const fc::string& entry, float value );
	const fc::string& GetString( const fc::string& section, const fc::string& entry, const fc::string& value );

	int GetInt( const fc::string& entry, int value );
	bool GetBool( const fc::string& entry, bool value );
	float GetFloat( const fc::string& entry, float value );
	const fc::string& GetString( const fc::string& entry, const fc::string& value );

protected:
	// these pointers are not long living.
	ConfigSection* Find( const fc::string& section );
	ConfigSection* AddSection( const fc::string& section );

	fc::string	m_filename;
	vec_type	m_configurations;
	fc::string	m_currentSection;
};


CE_NAMESPACE_END
