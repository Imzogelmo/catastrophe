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

#include "ScriptObject.h"


ScriptObject::ScriptObject( ContextPool* contextPool ) :
	m_contextPool(contextPool)
{
}


ScriptObject::~ScriptObject()
{
	Destroy();
	m_contextPool->ReleaseContext(&m_ctx);
}


void ScriptObject::Initialize( const fc::string& class_decl, const fc::string& method_decl )
{
	m_ctx = m_contextPool->AquireContext();
	if(!m_ctx)
	{
		m_destroyed = true;
		Log( "Error: No script context could be created." );
		return;
	}

	asIScriptEngine *engine = m_contextPool->GetScriptEngine();

	int typeID = engine->GetModule(0)->GetTypeIdByDecl(class_decl.c_str());
	if( typeID < 0 )
	{
		m_destroyed = true;
		Log("Error: Script class (%s) could not be instantiated.", class_decl.c_str());
		return;
	}

	m_objectType = engine->GetObjectTypeById(typeID);
	if( !m_objectType )
	{
		m_destroyed = true;
		Log( "Internal error: asIObjectType (%i) returned null.", typeID );
		return;
	}

	m_function = m_objectType->GetMethodByDecl(method_decl.c_str());
	if( !m_function )
	{
		//class exists but no update method.
		m_script_status = asEXECUTION_SUSPENDED;
		m_suspend = INFINITE_SUSPEND;
	}
	/*
	m_function_id = m_objectType->GetMethodIdByDecl(method_decl.c_str());
	if( m_function_id < 0 )
	{
		//class exists but no update method.
		m_script_status = asEXECUTION_SUSPENDED;
		m_suspend = INFINITE_SUSPEND;
	}
	*/

	//m_ctx->SetClassName( class_decl );
	m_ctx->SetUserData(this);

}


asIScriptObject* ScriptObject::CreateObject()
{
	if( m_destroyed )
		return 0;

	//gGetContextPool()->PushObjectPropertyBindStack( &m_ctx->obj_p );
	m_object = (asIScriptObject*)m_contextPool->GetScriptEngine()->CreateScriptObject(m_objectType->GetTypeId());

	return m_object;
}


/*
asIScriptObject *ScriptObject::CreateObject( Vector2 pos )
{
	if( m_ctx->m_destroyed )
		return (asIScriptObject*)0;

	// create m_object at position
	int funcId = m_ctx->m_objectType->GetFactoryIdByDecl( gGetContextPool()->ClassDeclToCtor( m_ctx->GetClassName().c_str(), "(const Vector2 &in)" ) );
	if( funcId < 0 )
	{
		// invalid, use default constructor
		CreateObject();
	}
	else
	{
		m_ctx->m_ref_counted = true;

		gGetContextPool()->PushInstance( this );
			gGetContextPool()->PushObjectPropertyBindStack( &m_ctx->obj_p );
			m_ctx->context->Prepare( funcId );
			*(Vector2**)m_ctx->context->GetAddressOfArg(0) = &pos;
			m_ctx->context->Execute();
			m_ctx->m_object = *(void**)m_ctx->context->GetAddressOfReturnValue();
			if( !m_ctx->m_object )
			{
				throw( "*(void**)m_ctx->context->GetAddressOfReturnValue() returned null!\n" );
				return 0;
			}
			((asIScriptObject*)m_ctx->m_object)->AddRef();
		gGetContextPool()->PopInstance();
	}

	return (asIScriptObject*)m_ctx->m_object;
}
*/

int	ScriptObject::Update()
{
	int status = m_script_status;

	if( status < 0 )
	{
		//m_object has been m_destroyed... or maybe an exception?
		return status;
	}
	else if( status == asEXECUTION_SUSPENDED )
	{
		if( --m_suspend > 0)
			return asEXECUTION_SUSPENDED;
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

	return m_script_status;
}


void ScriptObject::Suspend( int frames )
{
	m_suspend = frames;
	m_ctx->Suspend();
}


void ScriptObject::Destroy()
{
	if( !m_destroyed )
	{
		m_destroyed = true;

		if( m_ref_counted )
		{
			m_object->Release();
		}
		else
		{
			m_contextPool->GetScriptEngine()->ReleaseScriptObject((void*)m_object, m_objectType->GetTypeId());
		}

		m_ctx->Unprepare();
	}
}




