
#include <Catastrophe/Math/Color.h>
#include <Catastrophe/Math/Vector2.h>
#include <angelscript.h>

#include "asArray.h"
#include "ScriptEngine.h"



namespace script
{

	template <class T>
	ScriptArray<T>* ScriptArrayConstruct()
	{
		ScriptArray<T> *a = new ScriptArray<T>();
		return a;
	}

	template <class T>
	ScriptArray<T>* ScriptArrayFactory1( int x )
	{
		ScriptArray<T> *a = new ScriptArray<T>( x );
		return a;

		fc::multi_array<int> b;
		b.at(1) = 7;
	}

	template <class T>
	ScriptArray<T>* ScriptArrayFactory2( int y, int x )
	{
		ScriptArray<T> *a = new ScriptArray<T>( y, x );
		return a;
	}

	template <class T>
	ScriptArray<T>* ScriptArrayFactory3( int z, int y, int x )
	{
		ScriptArray<T> *a = new ScriptArray<T>( z, y, x );
		return a;
	}

	template <class T>
	ScriptArray<T>* ScriptArrayFactoryCopy( const ScriptArray<T>& arr )
	{
		ScriptArray<T> *a = new ScriptArray<T>( arr );
		return a;
	}

} //namespace script


void ScriptEngine::RegisterScriptArrayTemplateSpecializations()
{
	/* template class MUST be registered first */

	RegisterArrayTemplateSpecialization<int>( "array<int>", "int" );
	//RegisterArrayTemplateSpecialization<int>( "array<uint>", "uint" );
	RegisterArrayTemplateSpecialization<float>( "array<float>", "float" );
	RegisterArrayTemplateSpecialization<Vector2>( "array<vec2>", "vec2" );

	//register the Array<T> object for default [] arrays.
	engine->RegisterDefaultArrayType( "array<T>" );
}


template <class T>
void ScriptEngine::RegisterArrayTemplateSpecialization( const fc::string decl, const fc::string type )
{
	int r(0);
	using namespace script;
	const fc::string const_ref( (fc::string("const ") + type) + " &in" );


	// register the array type
	r = engine->RegisterObjectType( decl.c_str(), 0, asOBJ_REF ); assert( r >= 0 );

	// constructors
	r = engine->RegisterObjectBehaviour( decl.c_str(), asBEHAVE_FACTORY, 
		( decl + " @f()" ).c_str(), 
		asFUNCTION(ScriptArrayConstruct<T>), asCALL_CDECL ); assert( r >= 0 );
	
	r = engine->RegisterObjectBehaviour( decl.c_str(), asBEHAVE_FACTORY,
		(((decl + " @f(") + const_ref) + ")" ).c_str(),
		asFUNCTION(ScriptArrayFactory1<T>), asCALL_CDECL ); assert( r >= 0 );
	
	r = engine->RegisterObjectBehaviour( decl.c_str(), asBEHAVE_FACTORY,
		(((((decl + " @f(") + const_ref) + "," ) + const_ref ) + ")" ).c_str(),
		asFUNCTION(ScriptArrayFactory2<T>), asCALL_CDECL ); assert( r >= 0 );

	r = engine->RegisterObjectBehaviour( decl.c_str(), asBEHAVE_FACTORY,
		(((((((decl + " @f(") + const_ref) + "," ) + const_ref ) + "," ) + const_ref ) + ")" ).c_str(),
		asFUNCTION(ScriptArrayFactory3<T>), asCALL_CDECL ); assert( r >= 0 );

	r = engine->RegisterObjectBehaviour( decl.c_str(), asBEHAVE_FACTORY,
		(((decl + " @f(const ") + decl) + " &in)" ).c_str(),
		asFUNCTION(ScriptArrayFactoryCopy<T>), asCALL_CDECL ); assert( r >= 0 );

	// index methods
	r = engine->RegisterObjectMethod( decl.c_str(),
		( fc::string("const ") + type + "& at(int) const" ).c_str(),
		asMETHOD(ScriptArray<T>, At1), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		( fc::string("const ") + type + "& at(int, int) const" ).c_str(),
		asMETHOD(ScriptArray<T>, At2), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		( fc::string("const ") + type + "& at(int, int, int) const" ).c_str(),
		asMETHOD(ScriptArray<T>, At3), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		( type + "& at(int)" ).c_str(),
		asMETHOD(ScriptArray<T>, At1), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		( type + "& at(int, int)" ).c_str(),
		asMETHOD(ScriptArray<T>, At2), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		( type + "& at(int, int, int)" ).c_str(),
		asMETHOD(ScriptArray<T>, At3), asCALL_THISCALL ); assert( r >= 0 );

	// resize methods
	r = engine->RegisterObjectMethod( decl.c_str(),
		"void resize(int)",
		asMETHOD(ScriptArray<T>, Resize1), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		"void resize(int, int)",
		asMETHOD(ScriptArray<T>, Resize2), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		"void resize(int, int, int)",
		asMETHOD(ScriptArray<T>, Resize3), asCALL_THISCALL ); assert( r >= 0 );

	// operators
	r = engine->RegisterObjectMethod( decl.c_str(),
		( decl + "& opAssign(const " + decl + " &in)" ).c_str(),
		asMETHOD(ScriptArray<T>, operator=), asCALL_THISCALL ); assert( r >= 0 );

	// methods
	r = engine->RegisterObjectMethod( decl.c_str(),
		"bool empty() const",
		asMETHOD(ScriptArray<T>, Empty), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		"int size() const",
		asMETHOD(ScriptArray<T>, Size), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		"int offset(int, int)",
		asMETHOD(ScriptArray<T>, Offset2), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		"int offset(int, int, int)",
		asMETHOD(ScriptArray<T>, Offset3), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		(( fc::string( "void assign(" ) + const_ref ) + ")" ).c_str(),
		asMETHOD(ScriptArray<T>, AssignAll), asCALL_THISCALL ); assert( r >= 0 );

	r = engine->RegisterObjectMethod( decl.c_str(),
		(( fc::string( "void assign(int, int, " ) + const_ref ) + ")" ).c_str(),
		asMETHOD(ScriptArray<T>, Assign), asCALL_THISCALL ); assert( r >= 0 );

	// memory management
	r = engine->RegisterObjectBehaviour( decl.c_str(), asBEHAVE_ADDREF, "void f()", asMETHOD(ScriptArray<T>, AddRef), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour( decl.c_str(), asBEHAVE_RELEASE, "void f()", asMETHOD(ScriptArray<T>, Release), asCALL_THISCALL); assert( r >= 0 );

}



