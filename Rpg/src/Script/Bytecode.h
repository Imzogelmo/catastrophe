
#pragma once

#include <angelscript.h>

#include <fc/string.h>
#include <Catastrophe/IO/File.h>


class BytecodeInStream : public asIBinaryStream
{
public:
	BytecodeInStream( const fc::string& filename );
	~BytecodeInStream();

	void Write( const void *, size_t ) {}
	void Read( void *data, size_t size );

protected:
	fc::string	m_filename;
	File		m_file;

};


class BytecodeOutStream : public asIBinaryStream
{
public:
	BytecodeOutStream( const fc::string& filename );
	~BytecodeOutStream();

	void Write( const void *data, size_t size );
	void Read( void *, size_t ) {}

protected:
	fc::string	m_filename;
	File		m_file;

};

