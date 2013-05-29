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
#include "ScriptClass.h"
#include "ScriptEngine.h"


ScriptClass::ScriptClass( ContextPool* contextPool ) :
	m_contextPool(contextPool),
	m_ctx(),
	m_object(0),
	m_objectType(0),
	m_function(0),
	m_suspend(0),
	m_script_status(0),
	m_destroyed(false),
	m_ref_counted(false)
{
	if( !m_contextPool )
		m_contextPool = gGetScriptEngine()->GetContextPool();
}


ScriptClass::~ScriptClass()
{
	DestroyScript();
	m_ctx->SetUserData((void*)0);
	m_contextPool->ReleaseContext(&m_ctx);
}


asIScriptEngine* ScriptClass::GetScriptEngine()
{
	return m_contextPool->GetScriptEngine();
}


bool ScriptClass::InitializeScript( const ScriptClassDeclarations& declarations, void* userData )
{
	m_ctx = m_contextPool->AquireContext();
	if(!m_ctx)
	{
		m_destroyed = true;
		Log( "Error: No script context could be created." );
		return false;
	}

	m_ctx->SetUserData(userData);
	//m_ctx->SetUserData(this);
	asIScriptEngine *engine = m_contextPool->GetScriptEngine();

	bool useBaseClassDecl = false;
	int typeID = engine->GetModule(0)->GetTypeIdByDecl(declarations.class_decl.c_str());
	if( typeID < 0 )
	{
		// debug info only.
		LogDebug("Info: Script class (%s) was not found.", declarations.class_decl.c_str());

		// If no specialization is given, we instantiate the base class.
		typeID = engine->GetModule(0)->GetTypeIdByDecl(declarations.base_class_decl.c_str());
		if( typeID < 0 )
		{
			m_destroyed = true;
			Log( "Error: Script class (%s) or base class (%s) could not be instantiated.",
				declarations.class_decl.c_str(), declarations.base_class_decl.c_str() );
			return false;
		}

		useBaseClassDecl = true;
	}

	m_objectType = engine->GetObjectTypeById(typeID);
	if( !m_objectType )
	{
		m_destroyed = true;
		Log( "Error: asIObjectType (%i) returned null.", typeID );
		return false;
	}

	m_function = m_objectType->GetMethodByDecl(declarations.method_decl.c_str());
	if( !m_function )
	{
		//class exists but no update method.
		m_script_status = asEXECUTION_SUSPENDED;
		m_suspend = INFINITE_SUSPEND;
	}

	// Get the full factory declaration.
	fc::string classString = useBaseClassDecl ? declarations.base_class_decl : declarations.class_decl;
	fc::string factoryString = classString;
	factoryString.append(" @").append(classString).append("()");

	m_factory = m_objectType->GetFactoryByDecl(factoryString.c_str());
	if( !m_factory )
	{
		Log("Error: No factory method (%s) found", factoryString.c_str());
	}

	return true;
}


asIScriptObject* ScriptClass::CreateScriptObject()
{
	ASSERT(!!m_ctx);

	if( m_factory )
	{
		m_ctx->Prepare(m_factory);
		m_ctx->Execute();
		m_object = *(asIScriptObject**)m_ctx->GetAddressOfReturnValue();
		m_object->AddRef();
	}
	else
	{
		m_object = (asIScriptObject*)m_contextPool->GetScriptEngine()->CreateScriptObject(m_objectType->GetTypeId());
	}


	//if the function does not exist we have to destroy the object.
	if( !m_function )
	{
		DestroyScript();
		Log("Error: Function does not exist.");
		return (asIScriptObject*)0;
	}

	return m_object;
}


void ScriptClass::UpdateScript()
{
	int status = m_script_status;

	if( status < 0 )
	{
		//m_object has been m_destroyed... or maybe an exception?
		//return status;
		return;
	}
	else if( status == asEXECUTION_SUSPENDED )
	{
		if( --m_suspend > 0)
			//return asEXECUTION_SUSPENDED;
			return;
	}
	else
	{
		m_ctx->Prepare( m_function );
	}

	m_ctx->SetObject(m_object);
	m_script_status = m_ctx->Execute();

	//Fucked up thing #1 -
	//it's possible that during the "Execute()" call
	//the script tries to destroy this m_object before
	//we even return from our update function.
	//TODO

	//return m_script_status;
}


void ScriptClass::Suspend( int frames )
{
	m_suspend = frames;
	m_ctx->Suspend();
}


void ScriptClass::DestroyScript()
{
	if( !m_destroyed )
	{
		m_destroyed = true;

		//if( m_ref_counted )
		if( m_object )
		{
			m_object->Release();
		}
		//else
		{
			if( m_object )
				m_contextPool->GetScriptEngine()->ReleaseScriptObject((void*)m_object, m_objectType->GetTypeId());
		}

		m_ctx->Unprepare();
	}
}




