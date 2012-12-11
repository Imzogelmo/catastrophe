
#pragma once

#include <fc/vector.h>
#include <Catastrophe/Util/Indexable.h>
#include "../Common.h"


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




