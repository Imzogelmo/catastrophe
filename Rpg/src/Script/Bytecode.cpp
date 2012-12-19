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

#include "Bytecode.h"


BytecodeInStream::BytecodeInStream( const fc::string& filename )
	: m_filename(filename)
{
	m_file.Open( m_filename, FileRead );
}


BytecodeInStream::~BytecodeInStream()
{
	m_file.Close();
}


void BytecodeInStream::Read( void *data, size_t size )
{
	if( m_file.IsOpen() )
	{
		m_file.Read( data, size );
	}
}



BytecodeOutStream::BytecodeOutStream( const fc::string& filename )
	: m_filename(filename)
{
	m_file.Open( m_filename.c_str(), FileWrite );
}


BytecodeOutStream::~BytecodeOutStream()
{
	m_file.Close();
}


void BytecodeOutStream::Write( const void *data, size_t size )
{
	if( m_file.IsOpen() )
	{
		m_file.Write( data, size );
	}
}

