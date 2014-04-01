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

#include "Common.h"
#include "Preprocessor.h"

#include <mcpp.h>
#include <direct.h>
#include <cstdlib>

#include <fc/string.h>
#include <fc/vector_map.h>

#include <Catastrophe/Util/GarbageCollect.h>


#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )
#endif


int CppPreprocessor::ProcessFile(
		int argc,
		char *argv[],
		fc::string& out_file
		)
{
	fc::string filename;
	fc::vector<fc::string> args;

	for( int i(0); i < argc; ++i )
	{
		if( i == argc - 1 )
		{
			filename = argv[ argc - 1 ];
			break;
		}
		args.push_back( argv[ i ] );
	}

	return ProcessFile( args, filename, out_file );
}


int CppPreprocessor::ProcessFile
	(
	const fc::vector<fc::string>& _Args,
	const fc::string& filename,
	fc::string& out_file
	)
{
	GarbageCollector gc;
	fc::vector<fc::string> args( _Args );

	if( args.empty() )
	{
		// all that is required is a valid path/file, so just set defaults.
		char buf[ 260 ];
		args.push_back( _getcwd( buf, 260 ) );
		args.push_back( "-W17" );
		args.push_back( "-+" );
		args.push_back( "-k" );
		args.push_back( "-D__DEFINED__" );
		args.push_back( "-Iscript/" );
		args.push_back( "-Iscript/std" );
	}

	int		num_args		= args.size() + 1;
	int		return_value	= 0;
	char*	error_string	= 0;
	char**	arg				= gc[ new char*[ num_args ] ];

	out_file.clear();

	//allocate memory for null-terminated strings
	for( size_t i(0); i < args.size(); ++i )
	{
		arg[ i ] = gc[ new char[ args[ i ].size() + 1 ] ];
		strcpy( arg[ i ], args[ i ].c_str() );
	}
	arg[ args.size() ] = gc[ new char[ filename.size() + 1 ] ];
	strcpy( arg[ args.size() ], filename.c_str() );

	BasicTimer timer;
	timer.StartTimer();

	mcpp::use_mem_buffers( 1 );
	return_value	= mcpp::lib_main( num_args, &arg[0] );
	out_file		= mcpp::get_mem_buffer( OUT );
	error_string	= mcpp::get_mem_buffer( ERR );

	timer.StopTimer();

	if( out_file.empty() )
	{
		//...
	}

	if( error_string )
	{
		Log("%s", error_string);
	}

	// free the memory allocated by mcpp, and log output.
	// the value must be 1 here, due to a "double free" bug in mcpp.
	mcpp::use_mem_buffers( 1 );
	Log( "Preprocessor finished with status: %d. Elapsed time: %d minutes, %.2f seconds.\n",
		return_value, timer.GetMinutes(), timer.GetSeconds() );

	return return_value;
}



#ifdef _MSC_VER
	#pragma warning ( pop )
#endif


