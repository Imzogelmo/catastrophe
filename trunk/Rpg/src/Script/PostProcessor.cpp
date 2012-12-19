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


#include <fc/tokenizer.h>

#include "Common.h"
#include "PostProcessor.h"



Postprocessor::Postprocessor()
{
}


Postprocessor::~Postprocessor()
{
}


bool Postprocessor::GetNextLine( fc::string& code, size_t& index, int& line, fc::string& currentLine )
{
	currentLine.clear();
	for( const size_t size = code.size(); index < size; )
	{
		const char c = code[ index++ ];

		currentLine.push_back( c );
		if( c == '\n' )
		{
			++line;
			return true;
		}
	}

	return false; //eof
}


void Postprocessor::ExpandScriptBehaviors( fc::string& code )
{
	// Implement custom script behavior
	size_t offset(0);
	fc::string token;

	while( offset != fc::string::npos )
	{
		const char c = code[ offset ];

		// ignore strings
		if( c == '"' )
		{
			offset = code.find_first_of( '"', offset + 1 );
			if( offset != fc::string::npos )
				++offset;
		}
/*
		// expand '[]' subscript to full function declaration.
		else if( c == '[' )
		{
			static const fc::string opindex( "opArray(" );

			code[ offset++ ] = '.';
			code.insert( offset, "opArray(" );
			offset += opindex.size();
		}
		else if( c == ']' )
		{
			code[ offset++ ] = ')';
		}
*/

		// remove "new" keyword.
		else if( c == 'n' )
		{
			char previous = code[ offset - 1 ];
			if( previous == ' ' || previous == '\t' )
			{
				size_t index = offset;
				fc::tokenizer::get_token( code, FC_DEFAULT_DELIMITERS, index, token );

				if( token == "new" )
				{
					code.replace( offset, 3, "   " );
				}
			}
			++offset;
		}

		// remove "public" keyword.
		else if( c == 'p' )
		{
			char previous = code[ offset - 1 ];
			if( previous == ' ' || previous == '\t' ) //what about \n ??
			{
				size_t index = offset;
				fc::tokenizer::get_token( code, FC_DEFAULT_DELIMITERS, index, token );

				if( token == "public" )
				{
					code.replace( offset, 6, "      " );
				}
			}
			++offset;
		}

		// overload dereferencing operators '.', '->'.
		else if( c == '-' )
		{
			if( offset < code.size() - 1 )
			{
				const char next = code[ offset + 1 ];
				if( next == '>' )
				{
					code.replace( offset, 2, ". " );
					++offset;
				}
			}
			++offset;
		}

		/*
		// overload scope operators '::', '.'.
		else if( c == ':' )
		{
			if( offset < code.size() - 1 )
			{
				const char next = code[ offset + 1 ];
				if( next == ':' )
				{
					code.replace( offset, 2, ". " );
					++offset;
				}
			}
			++offset;
		}
		*/

		//fixme;
		size_t offpos = offset;
		offset = code.find_first_of( "\"[]np-", offset );
		if( offpos == offset )
		{
			offset++;
			offset = code.find_first_of( "\"[]np-", offset );
		}
	}
}


void Postprocessor::RemovePath( fc::string& filepath )
{
	for( int i(int(filepath.size() - 1)); i >= 0 ; --i )
	{
		const char c = filepath[ i ];

		if( c == '"' )
		{
			filepath.erase( i, 1 );
		}
		else if( c == '/' || c == '\\' )
		{
			filepath.erase( 0, i + 1 );
			break;
		}
	}
}


void Postprocessor::GetNextToken( fc::string& code, size_t& index, fc::string& token )
{
	token.clear();
	bool is_string = false;
	bool token_found = false;

	for( const size_t size = code.size(); index < size; ++index )
	{
		const char c = code[ index ];

		if( c == '\n' )
			break;

		// path may contain spaces
		else if( c == '"' )
		{
			if( is_string )
				break;

			is_string = true;
		}

		// whitespace
		else if( c == ' ' || c == '\t' )
		{
			if( token_found )
			{
				if( !is_string )
					break;

				token.push_back( c );
			}
		}

		// valid character
		else if( 
			(c >= 'a' && c <= 'z') || 
			(c >= 'A' && c <= 'Z') || 
			(c >= '0' && c <= '9') ||
			(c == '_')
			)
		{
			token.push_back( c );
			token_found = true;
		}

		else if( is_string )
		{
			token.push_back( c );
			token_found = true;
		}

		// error
		else Log("Error: invalid token on '#' directive.");
	}
}


void Postprocessor::RemoveLine( fc::string& code, size_t index, bool remove_line_ending )
{
	size_t starting_index = index;
	size_t amount_to_remove = 0;

	while( index < code.size() && code[ index ] != '\n')
	{
		++amount_to_remove;
		++index;
	}

	if( remove_line_ending && index < code.size() && code[ index ] == '\n' )
		++amount_to_remove;

	code.erase( starting_index, amount_to_remove );
}


void Postprocessor::ProcessLineDirective( fc::string& code, size_t& index, fc::string& filename, int& line_number )
{
	filename.clear();
	fc::string token;

	// get the line number
	//GetNextToken( code, index, token );
	fc::tokenizer::get_token( code, FC_DEFAULT_DELIMITERS, index, token );

	line_number = (size_t) atoi( token.c_str() );

	// get the filename
	//GetNextToken( code, index, filename );
	fc::tokenizer::get_token( code, FC_DEFAULT_DELIMITERS, index, filename );
	RemovePath( filename );
}


void Postprocessor::Process( const fc::string& code_filename, fc::string& code, map_type *out_script_sections )
{
	map_type &scripts = *out_script_sections;

	fc::string fname_noPath( code_filename );
	RemovePath( fname_noPath );

	scripts.clear();
	scripts.insert( pair_type( fname_noPath, Script() ) );

	Script *current_script			= &scripts[ fname_noPath ];
	int line						= 1;
	size_t c						= 0;
	size_t cur_section_start_index	= 0;
	int cur_section_line_start		= 0;
	bool eof						= false;

	fc::string token;
	fc::string filename;
	fc::string currentline;


	// Pass 2 - Implement our own custum script behaviors
	ExpandScriptBehaviors( code ); //todo: do each section seperately

	// Pass 3 - Clean up the preprocessed file and re-format our line-endings
	while( !eof )
	{
		// process the directive, if any
		if( c < code.size() && code[ c ] == '#' )
		{
			size_t temp_index = c + 1;
			//GetNextToken( code, temp_index, token );
			fc::tokenizer::get_token( code, FC_DEFAULT_DELIMITERS, temp_index, token );

			// get info and append to scripts
			if( token == "line" )
			{
				int line_number = 0;

				//Tokenizer::GetToken( code, Tokenizer::default_delimiters, temp_index, filename );
				ProcessLineDirective( code, temp_index, filename, line_number );
				RemoveLine( code, c, (line_number == 1 ? true : false) );

				current_script = &scripts[ filename ];

				int line_diff = line_number - 1 - current_script->line;
				if( line_diff > 0 )
				{
					current_script->code.append( line_diff, '\n' );
					current_script->line += line_diff;
				}
			}
			else if( token == "include" )
			{
				//delete the current line
				RemoveLine( code, c );
			}
			else
			{
				Log("Postprocessor: unknown token found.");
			}

		}

		// we can be assured any '#' info has already been resolved
		else if( GetNextLine( code, c, line, currentline ) )
		{
			current_script->code += currentline;
			current_script->line++;
		}
		else eof = true;

	}

	// and last but not least, make sure files end with a new line.
	for( map_type::iterator it = scripts.begin(); it != scripts.end(); ++ it )
	{
		//...maybe not.
		//(*it).second.code.push_back('\n');
	}

}
