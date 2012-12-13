//////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify //
// it under the terms of the GNU General Public License as published by //
// the Free Software Foundation, either version 3 of the License, or    //
// (at your option) any later version.                                  //
//                                                                      //
// This program is distributed in the hope that it will be useful,      //
// but WITHOUT ANY WARRANTY; without even the implied warranty of       //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        //
// GNU General Public License for more details.                         //
//////////////////////////////////////////////////////////////////////////

#include "Precompiled.h"


#include "Tokenizer.h"
#include <sstream>


const wxString Tokenizer::default_delimiters(" \t\n\r");


Tokenizer::Tokenizer()
	:
	_index(0),
	_string(),
	_delimiters(default_delimiters)
{}


Tokenizer::Tokenizer( const wxString& str )
	:
	_index(0),
	_string(str),
	_delimiters(default_delimiters)
{}


Tokenizer::Tokenizer( const wxString& str, const wxString& delimiters )
	:
	_index(0),
	_string(str),
	_delimiters(delimiters)
{}


Tokenizer::Tokenizer( const Tokenizer& t )
	:
	_index(t._index),
	_string(t._string),
	_delimiters(t._delimiters)
{}


Tokenizer::size_type Tokenizer::GetPosition() const
	{
		return _index;
	}


void Tokenizer::SetString( const wxString& str )
	{
		_index = 0;
		_string = str;
	}


void Tokenizer::SetString( const char* cstr )
	{
		_index = 0;
		_string = cstr;
	}


void Tokenizer::SetDelimiters( const wxString& delimiters )
	{
		_delimiters = delimiters;
	}


void Tokenizer::SetDelimiters( const char* delimiters )
	{
		_delimiters = delimiters;
	}


void Tokenizer::SetPosition( size_type pos )
	{
		if( pos < _string.size() )
			_index = pos;
	}


bool Tokenizer::GetNextToken( wxString& token ) 
	{
		return GetToken( _string, _delimiters, _index, token );
	}


bool Tokenizer::GetToken( const wxString& str, const wxString& delimiters, size_type& index, wxString& token ) 
	{
		size_type count;
		size_type begin_index;
		size_type end_index;

		begin_index = str.find_first_not_of( delimiters, index );

		if( begin_index == wxString::npos ) 
			return false;

		if( str[ begin_index ] == '"' ) //string can contain delimiters
		{
			end_index = str.find_first_of( '"', begin_index + 1 );
		}
		else
		{
			end_index = str.find_first_of( delimiters, begin_index + 1 );
		}

		if( end_index == wxString::npos )
		{
			index = str.size();
			count = index - begin_index;
		}
		else
		{
			index = end_index;
			count = end_index - begin_index;
		}

		token.assign( &str[ begin_index ], count );

		return true;
	}


void Tokenizer::GetTokens( const wxString& str, const wxString& delimiters, fc::vector<wxString> &tokens )
{
	wxString token;
	const size_type size = str.size();

	for( size_type index(0); index < size; )
	{
		if( !GetToken( str, delimiters, index, token ) )
			break;

		tokens.push_back( token );
	}
}


int Tokenizer::ToInt( const char* str )
	{
		return atoi( str );
	}


int Tokenizer::ToInt( const wxString& str )
	{
		return ToInt( str.c_str() );
	}

int Tokenizer::ToInt( const wxString& str, size_type offset )
	{
		return atoi( &str[offset] );
	}


float Tokenizer::ToFloat( const char* str )
	{
		return (float)atof( str );
	}


float Tokenizer::ToFloat( const wxString& str )
	{
		return ToFloat( str.c_str() );
	}


float Tokenizer::ToFloat( const wxString& str, size_type offset )
	{
		return (float)atof( &str[offset] );
	}




