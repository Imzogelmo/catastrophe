
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



