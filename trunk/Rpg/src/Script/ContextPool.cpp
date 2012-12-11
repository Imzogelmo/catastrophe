
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



