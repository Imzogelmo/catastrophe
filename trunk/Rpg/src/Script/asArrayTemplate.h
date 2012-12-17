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

#include <fc/multi_array.h>
#include "asScriptTemplate.h"


class ScriptArrayTemplate : public ScriptTemplateClass
{
public:
	typedef ScriptTemplateClass::storage_type	storage_type;
	typedef fc::multi_array<storage_type>		array_type;

	//there's no reason for this not to be public.
	array_type m_array;

	ScriptArrayTemplate( asIObjectType *objectType );
	ScriptArrayTemplate( asIObjectType *objectType, int size );
	ScriptArrayTemplate( asIObjectType *objectType, int y, int x );
	ScriptArrayTemplate( asIObjectType *objectType, int z, int y, int x );
	~ScriptArrayTemplate();

	bool Empty() const;
	int Size() const;

	void* At1( int x );
	void* At2( int y, int x );
	void* At3( int z, int y, int x );

	int Offset1( int y, int x );
	int Offset2( int z, int y, int x );

	void Assign1( void* value );
	void Assign2( int start, int end, void* value );
	void Clear();
	void Resize1( int x );
	void Resize2( int y, int x );
	void Resize3( int z, int y, int x );

	// GC behaviour
	void EnumReferences( asIScriptEngine *engine );
	void ReleaseAllHandles( asIScriptEngine *engine );

};



