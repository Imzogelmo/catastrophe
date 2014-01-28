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

#include <angelscript.h>

#include "asArrayTemplate.h"
#include "ScriptEngine.h"



ScriptArrayTemplate::ScriptArrayTemplate( asIObjectType *objectType ) :
	ScriptTemplateClass( objectType ), m_array()
{
}


ScriptArrayTemplate::ScriptArrayTemplate( asIObjectType *objectType, int size ) :
	ScriptTemplateClass( objectType ), m_array()
{
	Resize3( 0, 0, size );
}


ScriptArrayTemplate::ScriptArrayTemplate( asIObjectType *objectType, int y, int x ) :
	ScriptTemplateClass( objectType ), m_array()
{
	Resize3( 0, y, x );
}


ScriptArrayTemplate::ScriptArrayTemplate( asIObjectType *objectType, int z, int y, int x ) :
	ScriptTemplateClass( objectType ), m_array()
{
	Resize3( z, y, x );
}


ScriptArrayTemplate::~ScriptArrayTemplate()
{
	Clear();
}


bool ScriptArrayTemplate::Empty() const
{
	return m_array.empty();
}


int ScriptArrayTemplate::Size() const
{
	return (int)m_array.size();
}


void* ScriptArrayTemplate::At1( int x )
{
	return this->GetReturnObjectPtr( &m_array[ x ] );
}


void* ScriptArrayTemplate::At2( int y, int x )
{
	return this->GetReturnObjectPtr( &m_array( y, x ) );
}


void* ScriptArrayTemplate::At3( int z, int y, int x )
{
	return this->GetReturnObjectPtr( &m_array( z, y, x ) );
}


int ScriptArrayTemplate::Offset1( int y, int x )
{
	return m_array.offset( y, x );
}


int ScriptArrayTemplate::Offset2( int z, int y, int x )
{
	return m_array.offset( z, y, x );
}


void ScriptArrayTemplate::Assign1( void* value )
{
	for( size_t i(0); i < m_array.size(); ++i )
		this->SetValue( &m_array[ i ], value );
}


void ScriptArrayTemplate::Assign2( int start, int end, void* value )
{
	//this->Resize3( 0, y, x );
}


void ScriptArrayTemplate::Clear()
{
	for( size_t i(0); i < m_array.size(); ++i )
	{
		this->DestructObject( &m_array[ i ] );
		//this->ReleasePtr( (void*)&m_array[ i ] );
	}

	m_array.resize(0);
}


void ScriptArrayTemplate::Resize1( int x )
{
	Resize3( 0, 0, x );
}


void ScriptArrayTemplate::Resize2( int y, int x )
{
	Resize3( 0, y, x );
}


void ScriptArrayTemplate::Resize3( int z, int y, int x )
{
	const size_t size = m_array.size();
	const size_t newSize = (size_t)
		(z ? (x * y * z) : 
			(y ? (x * y) : 
				(x ? x : 0)
			)
		);

	if( newSize == 0 )
	{
		if( size != 0 )
			Clear();
	}
	else if( size < newSize )
	{
		m_array.resize( z, y, x );

		const size_t amount = newSize - size;
		for( size_t i(0); i < amount; ++i )
		{
			const size_t index = size + i;
			this->ConstructObject( &m_array[ index ] );
		}
	}
	else if( size > newSize )
	{
		const size_t amount = size - newSize;
		for( size_t i(0); i < amount; ++i )
		{
			this->DestructObject( &m_array[ size - amount + i ] );
		}

		m_array.resize( z, y, x );
	}
	else if( z != m_array.z() && y != m_array.y() && x != m_array.x() )
	{
		// Same size, different shape
		m_array.resize( z, y, x );
	}
}


void ScriptArrayTemplate::EnumReferences( asIScriptEngine *engine )
{
	// If the array is holding handles, then we need to notify the GC of them
	int subtypeId = m_objType->GetSubTypeId();
	if( subtypeId & asTYPEID_MASK_OBJECT )
	{
		array_type::iterator it = m_array.begin();
		for( ; it != m_array.end(); ++it )
		{
			if( (*it).ptr )
				engine->GCEnumCallback( *(void**)it->ptr );
		}
	}
}


void ScriptArrayTemplate::ReleaseAllHandles( asIScriptEngine *engine )
{
	Clear();
}



namespace script
{

	ScriptArrayTemplate* ScriptArrayFactory( asIObjectType *ot, int z, int y, int x )
	{
		ScriptArrayTemplate *a = new ScriptArrayTemplate( ot, z, y, x );

		// It's possible the constructor raised a script exception, in which case we 
		// need to free the memory and return null instead, else we get a memory leak.
		asIScriptContext *ctx = asGetActiveContext();
		if( ctx && ctx->GetState() == asEXECUTION_EXCEPTION )
		{
			delete a;
			return 0;
		}

		return a;
	}

	ScriptArrayTemplate* ScriptArrayFactory( asIObjectType *ot, int y, int x )
	{
		return ScriptArrayFactory(ot, 0, y, x);
	}

	ScriptArrayTemplate* ScriptArrayFactory( asIObjectType *ot, int x )
	{
		return ScriptArrayFactory(ot, 0, 0, x);
	}

	ScriptArrayTemplate* ScriptArrayFactory( asIObjectType *ot )
	{
		return ScriptArrayFactory(ot, 0, 0, 0);
	}

} //namespace script



void ScriptEngine::RegisterArrayTemplate()
{
	int r;
	using namespace script;
	r = engine->RegisterObjectType("array<class T>", 0, asOBJ_REF | asOBJ_GC | asOBJ_TEMPLATE); assert( r >= 0 );

	// Register a callback for validating the subtype before it is used
	r = engine->RegisterObjectBehaviour("array<T>", asBEHAVE_TEMPLATE_CALLBACK, "bool f(int &in, bool &out)", asFUNCTION(ScriptTemplateClass::TemplateContainerCallback), asCALL_CDECL); assert( r >= 0 );

	// Templates receive the object type as the first parameter. To the script writer this is hidden
	r = engine->RegisterObjectBehaviour("array<T>", asBEHAVE_FACTORY, "array<T>@ f(int&in)", asFUNCTIONPR(ScriptArrayFactory, (asIObjectType*), ScriptArrayTemplate*), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("array<T>", asBEHAVE_FACTORY, "array<T>@ f(int&in, int)", asFUNCTIONPR(ScriptArrayFactory, (asIObjectType*, int), ScriptArrayTemplate*), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("array<T>", asBEHAVE_FACTORY, "array<T>@ f(int&in, int, int)", asFUNCTIONPR(ScriptArrayFactory, (asIObjectType*, int, int), ScriptArrayTemplate*), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("array<T>", asBEHAVE_FACTORY, "array<T>@ f(int&in, int, int, int)", asFUNCTIONPR(ScriptArrayFactory, (asIObjectType*, int, int, int), ScriptArrayTemplate*), asCALL_CDECL); assert( r >= 0 );

	// Register the factory that will be used for initialization lists
	r = engine->RegisterObjectBehaviour("array<T>", asBEHAVE_LIST_FACTORY, "array<T>@ f(int&in, int)", asFUNCTIONPR(ScriptArrayFactory, (asIObjectType*, int), ScriptArrayTemplate*), asCALL_CDECL); assert( r >= 0 );

	// The memory management methods
	r = engine->RegisterObjectBehaviour("array<T>", asBEHAVE_ADDREF, "void f()", asMETHOD(ScriptArrayTemplate,AddRef), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("array<T>", asBEHAVE_RELEASE, "void f()", asMETHOD(ScriptArrayTemplate,Release), asCALL_THISCALL); assert( r >= 0 );

	// The index operator returns the template subtype
	r = engine->RegisterObjectMethod("array<T>", "T &at(int)", asMETHOD(ScriptArrayTemplate, At1), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("array<T>", "T &at(int,int)", asMETHOD(ScriptArrayTemplate, At2), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("array<T>", "T &at(int,int,int)", asMETHOD(ScriptArrayTemplate, At3), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("array<T>", "const T &at(int) const", asMETHOD(ScriptArrayTemplate, At1), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("array<T>", "const T &at(int,int) const", asMETHOD(ScriptArrayTemplate, At2), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("array<T>", "const T &at(int,int,int) const", asMETHOD(ScriptArrayTemplate, At3), asCALL_THISCALL); assert( r >= 0 );

	// assignment operator
	r = engine->RegisterObjectMethod("array<T>", "array<T> &opAssign(const array<T>&in)", asMETHOD(ScriptArrayTemplate, operator=), asCALL_THISCALL); assert( r >= 0 );

	// Other methods
	r = engine->RegisterObjectMethod("array<T>", "bool empty() const", asMETHOD(ScriptArrayTemplate, Empty), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("array<T>", "int size() const", asMETHOD(ScriptArrayTemplate, Size), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("array<T>", "void resize(int)", asMETHODPR(ScriptArrayTemplate, Resize1, (int), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("array<T>", "void resize(int,int)", asMETHODPR(ScriptArrayTemplate, Resize2, (int,int), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("array<T>", "void resize(int,int,int)", asMETHODPR(ScriptArrayTemplate, Resize3, (int,int,int), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("array<T>", "int offset(int,int)", asMETHODPR(ScriptArrayTemplate, Offset1, (int,int), int), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("array<T>", "int offset(int,int,int)", asMETHODPR(ScriptArrayTemplate, Offset2, (int,int,int), int), asCALL_THISCALL); assert( r >= 0 );

	//assign
	r = engine->RegisterObjectMethod("array<T>", "void assign(const T &in)", asMETHODPR(ScriptArrayTemplate, Assign1, (void*), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("array<T>", "void assign(int,int,const T &in)", asMETHODPR(ScriptArrayTemplate, Assign2, (int,int,void*), void), asCALL_THISCALL); assert( r >= 0 );

	// Register GC behaviours in case the array needs to be garbage collected
	r = engine->RegisterObjectBehaviour("array<T>", asBEHAVE_GETREFCOUNT, "int f()", asMETHOD(ScriptArrayTemplate, GetRefCount), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("array<T>", asBEHAVE_SETGCFLAG, "void f()", asMETHOD(ScriptArrayTemplate, SetFlag), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("array<T>", asBEHAVE_GETGCFLAG, "bool f()", asMETHOD(ScriptArrayTemplate, GetFlag), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("array<T>", asBEHAVE_ENUMREFS, "void f(int&in)", asMETHOD(ScriptArrayTemplate, EnumReferences), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("array<T>", asBEHAVE_RELEASEREFS, "void f(int&in)", asMETHOD(ScriptArrayTemplate, ReleaseAllHandles), asCALL_THISCALL); assert( r >= 0 );

}
