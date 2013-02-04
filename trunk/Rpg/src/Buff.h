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
#include "DataList.h"


class Buff
{
public:
	enum BuffType
	{
		TypeConstant,
		TypeModifier,
		TypeMultiplier
	};

	BuffType type;
	Attributes attributes;
	fc::string name;
	int id;
	int	lifetime;
	int stack_count; //the number of times this buff can stack.
	int flags; //todo effect length, type etc..
	int type_flags;

	Buff( BuffType type = TypeConstant ) : 
		type(type),
		attributes(),
		id(0),
		lifetime(0),
		stack_count(1)
	{}

	int GetStackCount() const
	{
		return stack_count;
	}

	bool IsTimedOut() const
	{
		return (type != TypeConstant && lifetime <= 0);
	}

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};


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

	bool Contains( int id )
	{
		return Count(id) > 0;
	}

	int Count( int id )
	{
		int count = 0;
		for( vec_type::iterator it = m_buffs.begin(); it != m_buffs.end(); ++it)
			if( it->id == id )
				count++;

		return count;
	}

	void Update();
	void CalculateModifiers();
	bool IsDirty() const { return m_is_dirty; }

	const Attributes& GetCombinedAttributes();

	Buff& operator []( size_t index );
	const Buff& operator []( size_t index ) const;
	Buff& GetBuff( size_t index ) { return operator[](index); }
	const Buff& GetBuff( size_t index ) const { return operator[](index); }

protected:
	vec_type	m_buffs;
	Attributes	m_combinedBuffAttributes;

	//bool		m_stackMultiplierPolicy;
	bool		m_is_dirty;

};


/*
 * A collection of stored Buff objects.
 */
class RPG_API BuffList : public DataList<Buff>
{
public:
	typedef DataList<Buff>	base_type;

	BuffList() : base_type()
	{}

	Buff& GetBuff( size_t index ) { return base_type::operator [](index);  }
	const Buff& GetBuff( size_t index ) const { return base_type::operator [](index);  }

	NO_INLINE bool SerializeXml( const fc::string& filename );
	NO_INLINE bool DeserializeXml( const fc::string& filename );

};


