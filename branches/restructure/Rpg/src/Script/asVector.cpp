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

#include <Catastrophe/Math/Color.h>
#include <Catastrophe/Math/Vector2.h>
#include <angelscript.h>

#include "asVector.h"
#include "ScriptEngine.h"


namespace script
{

	template <class T>
	ScriptVector<T>* ScriptVectorFactory()
	{
		ScriptVector<T> *ptr = new ScriptVector<T>();
		return ptr;
	}

	template <class T>
	ScriptVector<T>* ScriptVectorFactory1( int x )
	{
		ScriptVector<T> *ptr = new ScriptVector<T>( x );
		return ptr;
	}

	template <class T>
	ScriptVector<T>* ScriptVectorFactoryCopy( const ScriptVector<T>& v )
	{
		ScriptVector<T> *ptr = new ScriptVector<T>( v );
		return ptr;
	}

} //namespace script


void ScriptEngine::RegisterScriptVectorTemplateSpecializations()
{
	// template class MUST be registered first.

	RegisterVectorTemplateSpecialization<int>( "vector<int>", "int" );
	//RegisterVectorTemplateSpecialization<size_t>( "vector<uint>", "uint" );
	RegisterVectorTemplateSpecialization<float>( "vector<float>", "float" );
	//RegisterVectorTemplateSpecialization<Color>( "vector<color>", "color" );
	RegisterVectorTemplateSpecialization<Vector2>( "vector<vec2>", "vec2" );
	RegisterVectorTemplateSpecialization<fc::string>( "vector<string>", "string" );

}


template <class T>
void ScriptEngine::RegisterVectorTemplateSpecialization( const fc::string decl, const fc::string type )
{
	int r(0);
	using namespace script;
	const fc::string const_ref( (fc::string("const ") + type) + " &in" );

	// register the array type
	r = engine->RegisterObjectType( decl.c_str(), 0, asOBJ_REF ); assert( r >= 0 );

	// constructors
	r = engine->RegisterObjectBehaviour( decl.c_str(), asBEHAVE_FACTORY, 
		( decl + " @f()" ).c_str(), 
		asFUNCTION(ScriptVectorFactory<T>), asCALL_CDECL ); assert( r >= 0 );
	
	r = engine->RegisterObjectBehaviour( decl.c_str(), asBEHAVE_FACTORY,
		(((decl + " @f(") + const_ref) + ")" ).c_str(),
		asFUNCTION(ScriptVectorFactory1<T>), asCALL_CDECL ); assert( r >= 0 );

	r = engine->RegisterObjectBehaviour( decl.c_str(), asBEHAVE_FACTORY,
		(((decl + " @f(const ") + decl) + " &in)" ).c_str(),
		asFUNCTION(ScriptVectorFactoryCopy<T>), asCALL_CDECL ); assert( r >= 0 );

	// index methods
	r = engine->RegisterObjectMethod( decl.c_str(),
		( fc::string("const ") + type + "& at(int) const" ).c_str(),
		asMETHOD(ScriptVector<T>, At), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		( fc::string("const ") + type + "& opIndex(int) const" ).c_str(),
		asMETHOD(ScriptVector<T>, At), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		( type + "& at(int)" ).c_str(),
		asMETHOD(ScriptVector<T>, At), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		( type + "& opIndex(int)" ).c_str(),
		asMETHOD(ScriptVector<T>, At), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		( fc::string("const ") + type + "& front() const" ).c_str(),
		asMETHOD(ScriptVector<T>, Front), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		( type + "& front()" ).c_str(),
		asMETHOD(ScriptVector<T>, Front), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		( fc::string("const ") + type + "& back() const" ).c_str(),
		asMETHOD(ScriptVector<T>, Back), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		( type + "& back()" ).c_str(),
		asMETHOD(ScriptVector<T>, Back), asCALL_THISCALL ); assert( r >= 0 );

	// resize methods
	r = engine->RegisterObjectMethod( decl.c_str(),
		"void resize(int)",
		asMETHOD(ScriptVector<T>, Resize), asCALL_THISCALL ); assert( r >= 0 );

	// operators
	r = engine->RegisterObjectMethod( decl.c_str(),
		( decl + "& opAssign(const " + decl + " &in)" ).c_str(),
		asMETHOD(ScriptVector<T>, operator=), asCALL_THISCALL ); assert( r >= 0 );

	// methods
	r = engine->RegisterObjectMethod( decl.c_str(),
		"bool empty() const",
		asMETHOD(ScriptVector<T>, Empty), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		"int size() const",
		asMETHOD(ScriptVector<T>, Size), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		(( fc::string( "void push_back(" ) + const_ref ) + ")" ).c_str(),
		asMETHOD(ScriptVector<T>, PushBack), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		"void pop_back()",
		asMETHOD(ScriptVector<T>, PopBack), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		(( fc::string( "void push_front(" ) + const_ref ) + ")" ).c_str(),
		asMETHOD(ScriptVector<T>, PushFront), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		"void pop_front()",
		asMETHOD(ScriptVector<T>, PopFront), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		(( fc::string( "void insert(int," ) + const_ref ) + ")" ).c_str(),
		asMETHOD(ScriptVector<T>, Insert1), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		(( fc::string( "void insert(int, int," ) + const_ref ) + ")" ).c_str(),
		asMETHOD(ScriptVector<T>, Insert2), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		fc::string( "void erase(int)" ).c_str(),
		asMETHOD(ScriptVector<T>, Erase1), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		fc::string( "void erase(int, int)" ).c_str(),
		asMETHOD(ScriptVector<T>, Erase2), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		"void clear()",
		asMETHOD(ScriptVector<T>, Clear), asCALL_THISCALL ); assert( r >= 0 );


	// memory management
	r = engine->RegisterObjectBehaviour( decl.c_str(), asBEHAVE_ADDREF, "void f()", asMETHOD(ScriptVector<T>, AddRef), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( decl.c_str(), asBEHAVE_RELEASE, "void f()", asMETHOD(ScriptVector<T>, Release), asCALL_THISCALL); assert( r >= 0 );

}

