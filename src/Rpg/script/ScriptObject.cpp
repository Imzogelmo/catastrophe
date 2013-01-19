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
	ScriptClass(contextPool)
{
}


ScriptObject::~ScriptObject()
{
}


void ScriptObject::Initialize( const fc::string& class_decl, const fc::string& method_decl )
{
	ScriptClass::Initialize(class_decl, method_decl);
	if( !m_destroyed && !m_function )
	{
		Destroy();
	}
}


asIScriptObject* ScriptObject::CreateObject()
{
	if( m_destroyed )
		return 0;

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



