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
	void Add( const T& object = T() )
	{
		m_items.push_back(object);
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

	vec_type& GetVector() { return m_items; }
	const vec_type& GetVector() const { return m_items; }
	
protected:
	vec_type m_items;

};


