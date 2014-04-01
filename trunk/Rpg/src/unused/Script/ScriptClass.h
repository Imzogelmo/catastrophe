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
#include <Catastrophe/Util/NonCopyable.h>
#include "Common.h"
#include "ContextPool.h"
#include "ScriptClassDeclarations.h"


#define INFINITE_SUSPEND 2147483647
//#define STATUS_TERMINATE -2147483647



/*
 * @ScriptClass
 */
class ScriptClass : public NonCopyable
{
public:
	ScriptClass( ContextPool* contextPool = 0 );
	~ScriptClass();

	bool InitializeScript( const ScriptClassDeclarations& declarations, void* userData );
	asIScriptObject* CreateScriptObject();

	asIScriptEngine* GetScriptEngine();
	ContextPool* GetContextPool() const { return m_contextPool; }
	asIScriptObject* GetScriptObject() const { return m_object; }
	
	void UpdateScript();
	void Suspend( int frames );
	void DestroyScript();

	bool IsScriptDestroyed() const { return m_destroyed; }

protected:
	ContextPool*		m_contextPool;
	ScriptContext		m_ctx;
	asIScriptObject*	m_object;
	asIObjectType*		m_objectType;
	asIScriptFunction*	m_function;
	asIScriptFunction*	m_factory;
	int					m_suspend;
	int					m_script_status;

	bool				m_destroyed;
	bool				m_ref_counted;

};


