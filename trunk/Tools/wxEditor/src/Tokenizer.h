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

#pragma once


#include <fc/vector.h>
#include <sstream>


//TODO: Make template for wxString types.
class Tokenizer 
{
public:
	static const wxString default_delimiters;
	typedef unsigned int size_type;

	Tokenizer();
	Tokenizer( const wxString& str );
	Tokenizer( const wxString& str, const wxString& delimiters );
	Tokenizer( const Tokenizer& t );
	~Tokenizer()
	{}

	size_type GetPosition() const;
	bool GetNextToken( wxString& token );
	void SetString( const char* cstr );
	void SetString( const wxString& str );
	void SetDelimiters( const char* delimiters );
	void SetDelimiters( const wxString& delimiters );
	void SetPosition( size_type pos );

	static bool GetToken( const wxString& str, const wxString& delimiters, size_type& index, wxString& token );
	static void GetTokens( const wxString& str, const wxString& delimiters, fc::vector<wxString> &tokens );


	template<class T> static void ToString( wxString& outstr, T value );
	template<class T> static wxString ToString( T value );

	static int ToInt( const char* str );
	static int ToInt( const wxString& str );
	static int ToInt( const wxString& str, size_type offset );
	static float ToFloat( const char* str );
	static float ToFloat( const wxString& str );
	static float ToFloat( const wxString& str, size_type offset );

protected:
	size_type _index;
	wxString _string;
	wxString _delimiters;
};










template <class T> inline
wxString Tokenizer::ToString( T value )
	{
		std::ostringstream stringstream;
		stringstream << value;

		return wxString( stringstream.str() );
	}


template<class T> inline
void Tokenizer::ToString( wxString& outstr, T value )
	{
		std::ostringstream stringstream;
		stringstream << value;

		outstr.assign( stringstream.str() );
	}
