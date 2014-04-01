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

#include "asVectorTemplate.h"
#include "ScriptEngine.h"


ScriptVectorTemplate::ScriptVectorTemplate( asIObjectType *objectType ) :
	ScriptTemplateClass( objectType ),
	m_vector()
{
}


ScriptVectorTemplate::ScriptVectorTemplate( asIObjectType *objectType, size_t size ) :
	ScriptTemplateClass( objectType ),
	m_vector()
{
	Resize(int(size));
}


ScriptVectorTemplate::~ScriptVectorTemplate()
{
	Clear();
}


bool ScriptVectorTemplate::Empty() const
{
	return m_vector.empty();
}


int ScriptVectorTemplate::Size() const
{
	return (int)m_vector.size();
}


void ScriptVectorTemplate::PushBack( void* value )
{
	m_vector.push_back( storage_type() );
	this->ConstructObject( &m_vector.back() );
	this->SetValue( &m_vector.back(), value );
}


void ScriptVectorTemplate::PopBack()
{
	if( !m_vector.empty() )
	{
		this->DestructObject( &m_vector.back() );
		m_vector.pop_back();
	}
}


void ScriptVectorTemplate::PushFront( void* value )
{
	Insert1( 0, value );
}


void ScriptVectorTemplate::PopFront()
{
	Erase1(0);
}


void* ScriptVectorTemplate::At( int index )
{
	return this->GetReturnObjectPtr( &m_vector[index] );
}


void* ScriptVectorTemplate::Front()
{
	if( m_vector.empty() )
		return 0;

	return this->GetReturnObjectPtr( &m_vector.front() );
}


void* ScriptVectorTemplate::Back()
{
	if( m_vector.empty() )
		return 0;

	return this->GetReturnObjectPtr( &m_vector.back() );
}


void ScriptVectorTemplate::Insert1( int loc, void* value )
{
	m_vector.insert( m_vector.begin() + loc, storage_type() );
	this->ConstructObject( &m_vector[ loc ] );
	this->SetValue( &m_vector[ loc ], value );
}


void ScriptVectorTemplate::Insert2( int loc, int amount, void* value )
{
	if( size_t(loc + amount) > m_vector.size() )
		return; //todo

	m_vector.insert_at( (size_t)loc, (size_t)amount, storage_type() );

	vec_type::iterator begin = m_vector.begin() + loc;
	vec_type::iterator end = begin + amount;
	for( ; begin != end; ++begin )
	{
		this->ConstructObject( &(*begin) );
		this->SetValue( &(*begin), value );
	}
}


void ScriptVectorTemplate::Erase1( int loc )
{
	if( size_t(loc) > m_vector.size() )
		return; //todo

	this->DestructObject( &m_vector[ loc ] );
	m_vector.erase( m_vector.begin() + loc );
}


void ScriptVectorTemplate::Erase2( int loc, int amount )
{
	size_t last = size_t(loc) + size_t(amount);

	if( last > m_vector.size() )
		return; //todo

	for( size_t i((size_t)loc); i < last; ++i )
	{
		this->DestructObject( &m_vector[ i ] );
	}

	m_vector.erase( m_vector.begin() + loc, m_vector.begin() + last );
}


void ScriptVectorTemplate::Clear()
{
	const size_t size = m_vector.size();
	for( size_t i(0); i < size; ++i )
	{
		this->DestructObject( &m_vector[ i ] );
	}

	m_vector.clear();
}


void ScriptVectorTemplate::Resize( int resizeAmount )
{
	size_t newSize = (size_t)resizeAmount;
	if( newSize > m_vector.size() )
		return; //todo

	const size_t size = m_vector.size();

	if( newSize == 0 )
	{
		Clear();
	}
	else if( size < newSize )
	{
		const size_t amount = newSize - m_vector.size();

		m_vector.reserve( newSize );
		m_vector.insert( m_vector.end(), amount, storage_type() );

		for( size_t i(0); i < amount; ++i )
		{
			const size_t index = size + i;
			this->ConstructObject( &m_vector[ index ] );
		}
	}
	else if( size > newSize )
	{
		const size_t amount = m_vector.size() - newSize;

		for( size_t i(0); i < amount; ++i )
		{
			this->DestructObject( &m_vector[ size - amount + i ] );
		}

		m_vector.resize( newSize );
	}
}


void ScriptVectorTemplate::EnumReferences( asIScriptEngine *engine )
{
	// If the array is holding handles, then we need to notify the GC of them
	int subtypeId = m_objType->GetSubTypeId();
	if( subtypeId & asTYPEID_MASK_OBJECT )
	{
		if( m_isHandle )
		{
			vec_type::iterator it = m_vector.begin();
			for( ; it != m_vector.end(); ++it )
			{
				if( (*it).ptr )
					engine->GCEnumCallback( *(void**)it->ptr );
			}
		}
	}
}


void ScriptVectorTemplate::ReleaseAllHandles( asIScriptEngine *engine )
{
	Clear();
}



namespace script
{

	ScriptVectorTemplate* ScriptVectorFactory( asIObjectType *ot, int size )
	{
		// It's possible the constructor raised a script exception, in which case we 
		// need to free the memory and return null instead, else we get a memory leak.
		asIScriptContext *ctx = asGetActiveContext();
		if( ctx && ctx->GetState() == asEXECUTION_EXCEPTION )
		{
			return 0;
		}

		ScriptVectorTemplate *a = new ScriptVectorTemplate(ot, size);
		return a;
	}

	ScriptVectorTemplate* ScriptVectorFactory( asIObjectType *ot )
	{
		return ScriptVectorFactory(ot, 0);
	}

} //scriptvector


void ScriptEngine::RegisterVectorTemplate()
{
	int r;
	using namespace script;
	r = engine->RegisterObjectType("vector<class T>", 0, asOBJ_REF | asOBJ_GC | asOBJ_TEMPLATE); assert( r >= 0 );

	// Register a callback for validating the subtype before it is used
	r = engine->RegisterObjectBehaviour("vector<T>", asBEHAVE_TEMPLATE_CALLBACK, "bool f(int &in, bool &out)", asFUNCTION(ScriptTemplateClass::TemplateContainerCallback), asCALL_CDECL); assert( r >= 0 );

	// Templates receive the object type as the first parameter. To the script writer this is hidden
	r = engine->RegisterObjectBehaviour("vector<T>", asBEHAVE_FACTORY, "vector<T>@ f(int&in)", asFUNCTIONPR(ScriptVectorFactory, (asIObjectType*), ScriptVectorTemplate*), asCALL_CDECL); assert( r >= 0 );

	// Register the factory that will be used for initialization lists
	//r = engine->RegisterObjectBehaviour("vector<T>", asBEHAVE_LIST_FACTORY, "vector<T>@ f(int&in, int)", asFUNCTIONPR(ScriptVectorFactory, (asIObjectType*, int), ScriptVectorTemplate*), asCALL_CDECL); assert( r >= 0 );

	// The memory management methods
	r = engine->RegisterObjectBehaviour("vector<T>", asBEHAVE_ADDREF, "void f()", asMETHOD(ScriptVectorTemplate,AddRef), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("vector<T>", asBEHAVE_RELEASE, "void f()", asMETHOD(ScriptVectorTemplate,Release), asCALL_THISCALL); assert( r >= 0 );

	// Index methods
	//r = engine->RegisterObjectMethod("vector<T>", "T &opArray(int)", asMETHOD(ScriptVectorTemplate, At), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod("vector<T>", "const T &opArray(int) const", asMETHOD(ScriptVectorTemplate, At), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "T &opIndex(int)", asMETHOD(ScriptVectorTemplate, At), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "const T &opIndex(int) const", asMETHOD(ScriptVectorTemplate, At), asCALL_THISCALL); assert( r >= 0 );
	
	r = engine->RegisterObjectMethod("vector<T>", "T& at(int)", asMETHOD(ScriptVectorTemplate, At), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "const T& at(int) const", asMETHOD(ScriptVectorTemplate, At), asCALL_THISCALL); assert( r >= 0 );

	r = engine->RegisterObjectMethod("vector<T>", "T& front()", asMETHOD(ScriptVectorTemplate, Front), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "const T& front() const", asMETHOD(ScriptVectorTemplate, Front), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "T& back()", asMETHOD(ScriptVectorTemplate, Back), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "const T& back() const", asMETHOD(ScriptVectorTemplate, Back), asCALL_THISCALL); assert( r >= 0 );

	// The assignment operator
	//r = engine->RegisterObjectMethod("vector<T>", "vector<T> &opAssign(const vector<T>&in)", asMETHOD(CScriptArray, operator=), asCALL_THISCALL); assert( r >= 0 );

	// Other methods
	r = engine->RegisterObjectMethod("vector<T>", "bool empty() const", asMETHODPR(ScriptVectorTemplate, Empty, (void) const, bool), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "int size() const", asMETHODPR(ScriptVectorTemplate, Size, (void) const, int), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "void push_back(const T& in)", asMETHODPR(ScriptVectorTemplate, PushBack, (void*), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "void pop_back()", asMETHODPR(ScriptVectorTemplate, PopBack, (void), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "void push_front(const T& in)", asMETHODPR(ScriptVectorTemplate, PushFront, (void*), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "void pop_front()", asMETHODPR(ScriptVectorTemplate, PopFront, (void), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "void insert(int, const T& in)", asMETHODPR(ScriptVectorTemplate, Insert1, (int, void*), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "void insert(int, int, const T& in)", asMETHODPR(ScriptVectorTemplate, Insert2, (int, int, void*), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "void erase(int)", asMETHODPR(ScriptVectorTemplate, Erase1, (int), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "void erase(int, int)", asMETHODPR(ScriptVectorTemplate, Erase2, (int, int), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "void resize(int)", asMETHODPR(ScriptVectorTemplate, Resize, (int), void), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector<T>", "void clear()", asMETHODPR(ScriptVectorTemplate, Clear, (void), void), asCALL_THISCALL); assert( r >= 0 );

	// Register GC behaviours in case the array needs to be garbage collected
	r = engine->RegisterObjectBehaviour("vector<T>", asBEHAVE_GETREFCOUNT, "int f()", asMETHOD(ScriptVectorTemplate, GetRefCount), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("vector<T>", asBEHAVE_SETGCFLAG, "void f()", asMETHOD(ScriptVectorTemplate, SetFlag), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("vector<T>", asBEHAVE_GETGCFLAG, "bool f()", asMETHOD(ScriptVectorTemplate, GetFlag), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("vector<T>", asBEHAVE_ENUMREFS, "void f(int&in)", asMETHOD(ScriptVectorTemplate, EnumReferences), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("vector<T>", asBEHAVE_RELEASEREFS, "void f(int&in)", asMETHOD(ScriptVectorTemplate, ReleaseAllHandles), asCALL_THISCALL); assert( r >= 0 );
}

