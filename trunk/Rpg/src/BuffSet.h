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
#include <fc/string.h>

#include "Common.h"
#include "Attributes.h"
#include "Buff.h"


/*
 * A collection of active buffs on an entity
 */
class BuffSet
{
public:
	typedef fc::vector<Buff>	vec_type;

	BuffSet();

	bool AddBuff( const Buff& buff );
	void RemoveBuff( size_t index );

	bool Contains( int buff_id )
	{
		return Count(buff_id) > 0;
	}

	int Count( int buff_id )
	{
		int count = 0;
		for( vec_type::iterator it = m_buffs.begin(); it != m_buffs.end(); ++it)
			if( it->id == buff_id )
				count++;

		return count;
	}

	void Update();
	void CalculateModifiers() const;
	bool IsDirty() const { return m_is_dirty; }

	const Attributes& GetCombinedAttributes() const;

	Buff& operator []( size_t index );
	const Buff& operator []( size_t index ) const;
	Buff& GetBuff( size_t index ) { return operator[](index); }
	const Buff& GetBuff( size_t index ) const { return operator[](index); }

protected:
	vec_type			m_buffs;
	mutable Attributes	m_combinedBuffAttributes;
	mutable bool		m_is_dirty;

};



