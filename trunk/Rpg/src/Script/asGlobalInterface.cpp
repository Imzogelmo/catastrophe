
#pragma once

#include <cassert>
#include <angelscript.h>
#include <Catastrophe/Input/Input.h>

#include "asBindUtil.h"
#include "ScriptEngine.h"


namespace script
{

	void SuspendScript( int frames )
	{
		//ScriptObject* object = asGetActiveContext()->GetUserData();
		//if(object)
		//	object->Suspend(frames);
	}

	void ThrowException( const fc::string &message )
	{
		asIScriptContext* ctx = asGetActiveContext();
		ScriptEngine* engine = (ScriptEngine*)ctx->GetEngine()->GetUserData();
		if(engine)
		{
			engine->SetException(ctx, message);
		}
	}

	void Print( const fc::string &message, const fc::string &file, int line )
	{
		//Log(message);
		Log( fc::string(file + " line " + fc::to_string(line) + message).c_str() );
	}

	void Assert( bool condition, const fc::string &str, const fc::string &file, int line )
	{
		if(!condition)
		{
			//LogError("assertion failed! " + file + " line " + fc::to_string(line));
			ThrowException(str);
		}
	}

	int GetScriptClassTypeIDByDecl( const fc::string &class_decl )
	{
		int typeID = asGetActiveContext()->GetEngine()->GetModule(0)->GetTypeIdByDecl(class_decl.c_str());
		return typeID;
	}

	int LoadTexture( const fc::string& filename )
	{
		return 0;
	}

	bool RegisterCallback( const fc::string& func, int type )
	{
		return false;
	}

	bool UnregisterCallback( int type )
	{
		return false;
	}

	void GarbageCollect( int gcFlags )
	{
		asGetActiveContext()->GetEngine()->GarbageCollect(gcFlags);
		//ScriptEngine* engine = asGetActiveContext()->GetEngine()->GetUserData();
		//engine->GarbageCollect(gcFlags);
	}


} //namespace script


void ScriptEngine::RegisterScriptInterfaces()
{
	int r = engine->RegisterInterface( "IGameObject" );
	assert( r >= 0 );
}


void ScriptEngine::RegisterGlobalFunctions()
{
	int r(0);
	using namespace script;
	r = engine->RegisterGlobalFunction( "void wait(int)", asFUNCTIONPR(SuspendScript, (int), void), asCALL_CDECL); assert( r >= 0 );

	//r = engine->RegisterGlobalFunction( "void __print(const string &in)", asFUNCTIONPR(Print, (const std::string &), void), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "void throw(const string &in)", asFUNCTIONPR(ThrowException, (const fc::string &), void), asCALL_CDECL); assert( r >= 0 );
	//r = engine->RegisterGlobalFunction( "void assert(bool)", asFUNCTIONPR(Assert1, (bool), void), asCALL_CDECL); assert( r >= 0 );
	
	r = engine->RegisterGlobalFunction( "void __print(const string &in, const string &in, int)", asFUNCTIONPR(Print, (const fc::string &, const fc::string &, int), void), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "void __assert(bool, const string &in, const string &in, int)", asFUNCTIONPR(Assert, (bool, const fc::string &, const fc::string &, int), void), asCALL_CDECL); assert( r >= 0 );

	r = engine->RegisterGlobalFunction( "int get_class_id(const string &in)", asFUNCTIONPR(GetScriptClassTypeIDByDecl, (const fc::string &), int), asCALL_CDECL); assert( r >= 0 );
	//r = engine->RegisterGlobalFunction( "int load_texture(const String& in)", asFUNCTIONPR(LoadTilesheet, (const std::string &), int), asCALL_CDECL); assert( r >= 0 );
	//GC.
	r = engine->RegisterGlobalFunction( "void garbage_collect(int)", asFUNCTIONPR(GarbageCollect, (int), void), asCALL_CDECL); assert( r >= 0 );

}

