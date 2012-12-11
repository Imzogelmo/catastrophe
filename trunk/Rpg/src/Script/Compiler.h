
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


