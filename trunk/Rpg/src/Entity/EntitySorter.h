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

#include <fc/parallel.h>
#include "Common.h"
#include "Entity.h"


struct EntitySortY {
	inline bool operator()(const Entity* a, const Entity* b) const {
		return a->pos.y < b->pos.y;
	}
};

//todo:
struct EntitySortZ {
	inline bool operator()(const Entity* a, const Entity* b) const {
		return a->pos.y < b->pos.y;
	}
};


template <class SortType>
class EntitySorter
{
public:
	typedef fc::parallel< Entity*, fc::vector<size_t> >	vec_type;

	void Sort()
	{
		fc::insertion_sort(m_entities.begin(), m_entities.end(), SortType());
	}

	void RemoveEntity( Entity* e )
	{
		vec_type::iterator it = fc::find(m_entities.begin(), m_entities.end(), e);
		if( it != m_entities.end() )
		{
			m_entities.erase(it);
		}
	}

	void AddEntity( Entity* e )
	{
		vec_type::iterator it = fc::lower_bound(m_entities.begin(), m_entities.end(), e, SortType());
		m_entities.insert(it, e);
	}

	void RemoveDeadEntities()
	{
		for( vec_type::iterator it = m_entities.begin(); it != m_entities.end(); ++it )
		{
			if( !(*it)->IsAlive )
				m_entities.bind(it - m_entities.begin());
		}

		m_entities.execute;
	}

	vec_type m_entities;
};


