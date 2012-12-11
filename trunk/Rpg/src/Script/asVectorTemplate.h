
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

