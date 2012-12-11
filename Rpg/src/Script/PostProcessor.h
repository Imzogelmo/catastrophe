
#pragma once

#include <Catastrophe/Util/BasicTimer.h>

#include <fc/string.h>
#include <fc/vector_map.h>


/*
	Preprocessor - final pass: 
	Remove the unwanted cpp processor 
	information, incuded files, line information, 
	and other directives so it can be compiled
	sucessfully.
*/

class Postprocessor
{
public:
	struct Script
	{
		fc::string code;
		int line;

		Script(const fc::string& code = "", int line = 1) : code(code), line(line)
		{}
	};

	typedef fc::pair<fc::string, Script>			pair_type;
	typedef fc::vector_map<fc::string, Script>		map_type;

	Postprocessor();
	~Postprocessor();

	void Process( const fc::string& code_filename, fc::string& code, map_type *out_script_sections );
	void ProcessLineDirective( fc::string& code, size_t& index, fc::string& filename, int& line_number );
	void RemoveLine( fc::string& code, size_t index, bool remove_line_ending = false );
	static void RemovePath( fc::string& filepath );
	void GetNextToken( fc::string& code, size_t& index, fc::string& _Token );
	void ExpandScriptBehaviors( fc::string& code );
	bool GetNextLine( fc::string& code, size_t& index, int& line, fc::string& _currentLine );

};


