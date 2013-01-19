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

#include <fc/vector.h>
#include <Catastrophe/Util/Indexable.h>
#include "Common.h"


class ScriptContext : public Indexable<size_t>
{
public:
	asIScriptContext* context;
	ScriptContext( asIScriptContext* c = 0 ) : context(c) {}

	operator bool() const { return context != 0; }
	asIScriptContext& operator*() const { return *context; }
	asIScriptContext* operator->() const { return context; }

};


class ContextPool
{
public:
	typedef fc::vector<ScriptContext>		pool_type;
	typedef fc::vector<size_t>				store_type;

	enum : size_t
	{
		MaxPoolSize = 2048,
		DefaultPoolSize = 64,
		DefaultStoreSize = 64
	};

	ContextPool( asIScriptEngine *engine );
	~ContextPool();

	void Dispose();
	asIScriptEngine *GetScriptEngine() { return m_engine; }

	ScriptContext AquireContext();
	void ReleaseContext( ScriptContext* instance );

	struct ReverseIndexSorter
	{
		bool operator() (size_t a, size_t b) const { return a > b; }
	};

private:
	asIScriptEngine*	m_engine;
	pool_type			m_pool;
	store_type			m_free_store;

};




