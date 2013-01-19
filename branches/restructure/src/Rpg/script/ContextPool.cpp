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

//#include "ScriptObject.h"
#include "ContextPool.h"


ContextPool::ContextPool( asIScriptEngine *engine )
: m_engine(engine)
{
	m_pool.reserve( DefaultPoolSize );
	m_free_store.reserve( DefaultStoreSize );
}


ContextPool::~ContextPool()
{
	Dispose();
}


void ContextPool::Dispose()
{
	for( pool_type::iterator it = m_pool.begin(); it != m_pool.end(); ++it )
		(*it).context->Release();

	m_pool.clear();
	m_free_store.clear();
}


void ContextPool::ReleaseContext( ScriptContext* instance )
{
#ifdef _DEBUG
	size_t val = instance->GetIndex();
	store_type::iterator it = fc::upper_bound( m_free_store.begin(), m_free_store.end(), val, ReverseIndexSorter() );
	ASSERT(it != m_free_store.end());
	m_free_store.insert( it, val );
#else
	m_free_store.push_back(instance->GetIndex());
#endif
}


ScriptContext ContextPool::AquireContext()
{
	ScriptContext ctx;

	if( m_free_store.empty() )
	{
		const size_t current_index = m_pool.size();
		if( current_index < MaxPoolSize )
		{
			asIScriptContext* context = m_engine->CreateContext();
			if(context)
			{
				ctx.context = context;
				ctx.SetIndex(current_index);
				m_pool.push_back(ctx);
			}
		}
	}
	else
	{
		ctx = m_pool.at(m_free_store.back());
		m_free_store.pop_back();
	}

	return ctx;
}



