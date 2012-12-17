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

#include <fc/vector.h>
#include "asScriptTemplate.h"


class ScriptVectorTemplate : public ScriptTemplateClass
{
public:
	typedef ScriptTemplateClass::storage_type	storage_type;
	typedef fc::vector<storage_type>			vec_type;

	//there's no reason for this not to be public.
	vec_type m_vector;

	ScriptVectorTemplate( asIObjectType *objectType );
	ScriptVectorTemplate( asIObjectType *objectType, size_t size );
	~ScriptVectorTemplate();

	int Size() const;
	bool Empty() const;
	void PushBack( void* value );
	void PopBack();
	void PushFront( void* value );
	void PopFront();

	void* At( int index );
	void* Front();
	void* Back();

	void Insert1( int loc, void* value );
	void Insert2( int loc, int amount, void* value );
	void Erase1( int loc );
	void Erase2( int loc, int amount );
	void Clear();
	void Resize( int resizeAmount );

	// GC behaviour
	void EnumReferences( asIScriptEngine *engine );
	void ReleaseAllHandles( asIScriptEngine *engine );

};

