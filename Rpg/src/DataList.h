
#pragma once

#include <fc/vector.h>
#include "Common.h"


#define DATALIST_ASSERT(x) ASSERT(x)

/**
 * Base collection class for database list objects.
 * These objects are stored in a tight array (not a list) and
 * are only accessible by index.
 */
template <class T>
class DataList
{
public:
	typedef DataList<T>			this_type;
	typedef fc::vector<T>		vec_type;

	DataList() : m_items()
	{}

	bool Empty() const { return m_items.empty(); }
	size_t Size() const { return m_items.size(); }

	void Add( const T& object )
	{
		m_items.push_back(object);
	}

	void Remove()
	{
		if( !m_items.empty() )
			m_items.erase_at(index);
	}

	void Remove( size_t index )
	{
		if( index < m_items.size() )
			m_items.erase_at(index);
	}

	T& operator []( size_t i )
	{
		DATALIST_ASSERT(i < m_items.size());
		return m_items[i];
	}

	const T& operator []( size_t i ) const
	{
		DATALIST_ASSERT(i < m_items.size());
		return m_items[i];
	}

protected:
	vec_type m_items;

};


