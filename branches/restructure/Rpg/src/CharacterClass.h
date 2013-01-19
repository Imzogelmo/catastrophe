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
#include <Catastrophe/Graphics/AnimationSet.h>

#include "Common.h"
#include "AttributeData.h"
#include "DataList.h"



struct RPG_API CharacterClass : public AttributeData
{
	typedef AttributeData	base_type;

	int				exp_table_index;
	//Sprite		sprite;
	//SpellBook		spells;
	AnimationSet	animation_set;

	CharacterClass();

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};


/*
 * A collection of stored character classes.
 */
class RPG_API CharacterClassList : public DataList<CharacterClass>
{
public:
	typedef DataList<CharacterClass>	base_type;

	CharacterClassList() : base_type()
	{}

	CharacterClass& GetCharacterClass( size_t index ) { return base_type::operator [](index);  }
	const CharacterClass& GetCharacterClass( size_t index ) const { return base_type::operator [](index);  }

	NO_INLINE bool SerializeXml( const fc::string& filename );
	NO_INLINE bool DeserializeXml( const fc::string& filename );

};

