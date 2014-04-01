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

#include <cassert>
#include <angelscript.h>
#include <Catastrophe/Input/Input.h>

#include "asBindUtil.h"
#include "ScriptEngine.h"
#include "Combatant.h"


namespace script
{

	void SuspendScript( int frames )
	{
		ScriptEntity* object = (ScriptEntity*)asGetActiveContext()->GetUserData();
		if(object)
			object->Suspend(frames);
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
/*
	void BindCombatant()( asIScriptObject* obj )
	{
		asIScriptContext* ctx = asGetActiveContext();
		void* p = ctx->GetUserData();
		if( p != 0 )
		{
			Combatant* combatant = dynamic_cast<Combatant*>(p);
			if( combatant != 0 )
			{
				//if( combatant->GetScriptObject() != obj )
				//	Log("WTF!! combatant->GetScriptObject() != obj");

				return combatant;
			}
		}

		// failed.
		ScriptEngine* engine = (ScriptEngine*)ctx->GetEngine()->GetUserData();
		engine->SetException(ctx, "BindCombatant() call failed with address (%i)", (int)p);
		return 0;
	}
*/
	void* BindCombatant( Combatant& c )
	{
		asIScriptContext* ctx = asGetActiveContext();
		void* p = ctx->GetUserData();
		if( p != 0 )
		{
			Entity* entity = (Entity*)p;
			Combatant* combatant = 0;
			combatant = dynamic_cast<Combatant*>(entity);

			int gh = (int)p;
			if(gh > 90 )
			{
				Log("debug");
			}

			if( combatant != 0 )
			{
				//if( combatant->GetScriptObject() != obj )
				//	Log("WTF!! combatant->GetScriptObject() != obj");

				return combatant;
			}
		}

		// failed.
		ScriptEngine* engine = (ScriptEngine*)ctx->GetEngine()->GetUserData();
		engine->SetException(ctx, "BindCombatant() call failed");
		return 0;
	}

} //namespace script


void ScriptEngine::RegisterScriptInterfaces()
{
	int r(0);
	using namespace script;
	r = engine->RegisterInterface("IGameEntity"); assert( r >= 0 );
}


void ScriptEngine::RegisterGlobalFunctions()
{
	int r(0);
	using namespace script;
	r = engine->RegisterGlobalFunction( "void wait(int i = 0)", asFUNCTIONPR(SuspendScript, (int), void), asCALL_CDECL); assert( r >= 0 );

	//r = engine->RegisterGlobalFunction( "void __print(const string &in)", asFUNCTIONPR(Print, (const std::string &), void), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "void throw(const string &in)", asFUNCTIONPR(ThrowException, (const fc::string &), void), asCALL_CDECL); assert( r >= 0 );
	//r = engine->RegisterGlobalFunction( "void assert(bool)", asFUNCTIONPR(Assert1, (bool), void), asCALL_CDECL); assert( r >= 0 );
	
	r = engine->RegisterGlobalFunction( "void __print(const string &in, const string &in, int)", asFUNCTIONPR(Print, (const fc::string &, const fc::string &, int), void), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "void __assert(bool, const string &in, const string &in, int)", asFUNCTIONPR(Assert, (bool, const fc::string &, const fc::string &, int), void), asCALL_CDECL); assert( r >= 0 );

	r = engine->RegisterGlobalFunction( "int get_class_id(const string &in)", asFUNCTIONPR(GetScriptClassTypeIDByDecl, (const fc::string &), int), asCALL_CDECL); assert( r >= 0 );

	//GC.
	r = engine->RegisterGlobalFunction( "void garbage_collect(int)", asFUNCTIONPR(GarbageCollect, (int), void), asCALL_CDECL); assert( r >= 0 );


	// combatant init callback
	//r = engine->RegisterGlobalFunction( "combatant@ __init_combatant(IGameEntity@)", asFUNCTION(BindCombatant), asCALL_CDECL); assert( r >= 0 );
	r = engine->RegisterGlobalFunction( "combatant@ __init_combatant(combatant@)", asFUNCTION(BindCombatant), asCALL_CDECL); assert( r >= 0 );

}

