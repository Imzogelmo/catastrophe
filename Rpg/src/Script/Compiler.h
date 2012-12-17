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

#include "Preprocessor.h"
//#include "PreprocessorSettings.h"
#include "Postprocessor.h"


class ScriptCompiler
{
public:
	typedef Postprocessor::pair_type	pair_type;
	typedef Postprocessor::map_type		map_type;

	ScriptCompiler();

	int Compile(
		const fc::vector<fc::string>& _Args,
		const fc::string& filename,
		map_type *_Out_script_file_mem,
		int* preprocessor_Retval,
		int* postprocessor_Retval
		);

	static void SaveDebugFile( const fc::string& original_filename, const fc::string& debug_code );

private:
	fc::string		m_script_directory;
	fc::string		m_debug_directory;
	bool			m_debug_output_scripts_to_file;
	bool			m_debug_output_preprocessor_file;

};


