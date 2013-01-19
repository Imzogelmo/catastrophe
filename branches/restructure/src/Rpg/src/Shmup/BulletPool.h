
#pragma once

#include <fc/vector.h>
#include "Bullet.h"


class BulletPool
{
public:
	typedef fc::vector<Bullet>		pool_type;
	typedef fc::vector<size_t>		store_type;

	BulletPool( size_t numToAllocate, size_t maxAllocationReserve )
	{
		Initialize(numToAllocate, maxAllocationReserve);
	}

	void Initialize( size_t numToAllocate, size_t maxAllocationReserve )
	{
		m_pool.set_capacity( maxAllocationReserve );
		m_free_store.set_capacity( maxAllocationReserve );

		for( size_t i(numToAllocate); i > 0; )
		{
			--i;
			m_pool.push_back();
			m_free_store.push_back( i );
		}
	}

	void ReleaseBullet( Bullet* b )
	{
		m_free_store.push_back(b->GetIndex());
	}

	Bullet* AquireBullet()
	{
		Bullet* b = 0;

		if( m_free_store.empty() )
		{
			const size_t current_index = m_pool.size();
			if( current_index < m_pool.capacity() )
			{
				m_pool.push_back();
				b = &m_pool.back();
			}
		}
		else
		{
			b = &m_pool.at(m_free_store.back());
			m_free_store.pop_back();
		}

		return b;
	}


private:
	pool_type	m_pool;
	store_type	m_free_store;

};




