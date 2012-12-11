
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

