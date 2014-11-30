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

#include "RpgCommon.h"
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
	String name;
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

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

};



