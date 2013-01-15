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
#include "Attributes.h"


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
	int	lifetime;
	int flags; //todo effect length, type etc..
	int type_flags;

	Buff( BuffType type = TypeConstant ) : 
		type(type),
		attributes(),
		lifetime(0)
	{}

	bool IsTimedOut()
	{
		return (type != TypeConstant && lifetime <= 0);
	}
};


class BuffList
{
public:
	typedef fc::vector<Buff>	vec_type;

	BuffList();

	void AddBuff( const Buff& buff );
	void RemoveBuff( size_t index );

	void Update();
	void CalculateModifiers();
	bool IsDirty() const { return m_is_dirty; }

	const Attributes& GetCombinedAttributes();

protected:
	vec_type	m_buffs;
	Attributes	m_combinedBuffAttributes;

	//bool		m_stackMultiplierPolicy;
	bool		m_is_dirty;

};



