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

#pragma once

#include "Common.h"



class ScriptFunction
{
public:
	ScriptFunction( ContextPool* contextPool );
	~ScriptFunction();

protected:
	//ScriptContext* m_ctx;
	ContextPool*		m_contextPool;
	ScriptContext		m_ctx;

	asIScriptFunction*	m_function;


};


ScriptFunction::ScriptFunction( ContextPool* contextPool ) :
	m_contextPool(contextPool),
	m_ctx()
{
	m_ctx = m_contextPool->AquireContext();
	m_ctx->SetUserData(this);
}


ScriptFunction::~ScriptFunction()
{
	m_ctx->SetUserData((void*)0);
	m_contextPool->ReleaseContext(&m_ctx);
}


void ScriptFunction::SetArg( int argIndex, void* object )
{
	m_ctx->SetArgObject( argIndex, object );
}


void ScriptFunction::SetArg( int argIndex, int value )
{
	m_ctx->SetArgDWORD( argIndex, value );
}


void ScriptFunction::SetArg( int argIndex, float value )
{
	m_ctx->SetArgFloat( argIndex, value );
}


void ScriptFunction::Execute()
{
	if( m_ctx->Prepare(func_id) < 0 )
	{
	}

	int executionStatus = m_ctx->Execute();
	if( executionStatus != asEXECUTION_FINISHED )
	{
		ScriptEngine* scriptEngine = m_contextPool->GetScriptEngine()->GetUserData();
		scriptEngine->SetException(m_ctx);
	}
}



