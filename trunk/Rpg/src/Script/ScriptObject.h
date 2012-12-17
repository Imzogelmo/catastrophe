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

#include <fc/string.h>

#include "Common.h"
#include "ContextPool.h"


#define INFINITE_SUSPEND 2147483647
//#define STATUS_TERMINATE -2147483647


//..don't copy this right now...
class ScriptObject : public Indexable<size_t>//, public NonCopyable
{
public:
	ScriptObject( ContextPool* contextPool );
	~ScriptObject();

	void Initialize( const fc::string& class_decl, const fc::string& method_decl = "void run()" );

	asIScriptEngine* GetScriptEngine()
	{
		return m_contextPool->GetScriptEngine();
	}

	asIScriptObject *CreateObject();
	

	/*
	asIScriptObject *CreateObject( const Vector2& pos )
	{
		this->pos = pos;
		return CreateObject();
	}
	*/

	int	Update();
	void Suspend( int frames );
	void Destroy();

	//void DeepCopy( ScriptObject* &_out );

protected:
	//ScriptContext* m_ctx;
	ContextPool*		m_contextPool;
	ScriptContext		m_ctx;

	asIScriptObject*	m_object;
	asIObjectType*		m_objectType;
	asIScriptFunction*	m_function;
	//asIScriptContext*	context;
	int					m_suspend;
	int					m_script_status; //todo: don't need this as a class method
	//int					m_function_id;

	bool				m_destroyed;
	bool				m_ref_counted;

};


