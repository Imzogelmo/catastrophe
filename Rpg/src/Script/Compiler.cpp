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


#include <Catastrophe/IO/File.h>
#include "Compiler.h"



ScriptCompiler::ScriptCompiler() :
	m_script_directory(),
	m_debug_directory(),
	m_debug_output_scripts_to_file(false),
	m_debug_output_preprocessor_file(false) //TODO needs a compiler settings option.
{
}


void ScriptCompiler::SaveDebugFile( const fc::string& original_filename, const fc::string& debug_code )
{
	File f;
	fc::string debugfilename = "__" + original_filename;
	f.Open( debugfilename, FileWrite );
	if( f.IsOpen() )
	{
		f.WriteString(debug_code);
		f.Close();
	}
	else
	{
		Log("debug error: cannot open %s.", debugfilename.c_str());
	}
}


int ScriptCompiler::Compile(
	const fc::vector<fc::string>& _Args,
	const fc::string& filename,
	map_type *_Out_script_file_mem,
	int* preprocessor_Retval,
	int* compiler_Retval
	)
{
	int retval				= -1;
	*preprocessor_Retval	= 0;
	*compiler_Retval		= 0;
	map_type & scripts		= *_Out_script_file_mem;
	fc::vector<fc::string> args( _Args );
	fc::string processed_file;

	ASSERT(_Out_script_file_mem != 0);
	if( filename.empty() || !_Out_script_file_mem )
		return retval;

	// preprocessor
	CppPreprocessor cppPreprocessor;
	*preprocessor_Retval = cppPreprocessor.ProcessFile(args, filename, processed_file);

	if( processed_file.empty() )
		return 0; //file is empty, do nothing.


	// dump debug output to file
	if( m_debug_output_preprocessor_file )
	{
		fc::string ppdebugfilename(filename);
		Postprocessor::RemovePath(ppdebugfilename);
		SaveDebugFile( ppdebugfilename, processed_file );
	}


	// second pass compile
	Postprocessor postprocessor;
	postprocessor.Process( filename, processed_file, &scripts );

	if( m_debug_output_scripts_to_file )
	{
		map_type::iterator it = scripts.begin();
		for( ; it != scripts.end(); ++ it )
		{
			SaveDebugFile( (*it).first, (*it).second.code );
		}
	}

	retval = 0;

	return retval;

}

