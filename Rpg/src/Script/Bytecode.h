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

