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

#include <Engine/Graphics/Sprite.h>
#include "Common.h"
#include "AttributeData.h"
#include "ItemDrop.h"
#include "DataList.h"



struct RPG_API Monster : public AttributeData
{
	typedef AttributeData	base_type;

	//int sprite_index;
	ItemDropSet		item_dropset;
	AnimatedSprite	sprite;

	Monster() : base_type()
	{}

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};


/*
 * A collection of stored Monster objects.
 */
class RPG_API MonsterList : public DataList<Monster>
{
public:
	typedef DataList<Monster>	base_type;

	MonsterList() : base_type()
	{}

	Monster& GetMonster( size_t index ) { return base_type::operator [](index);  }
	const Monster& GetMonster( size_t index ) const { return base_type::operator [](index);  }

	NO_INLINE bool SerializeXml( const fc::string& filename );
	NO_INLINE bool DeserializeXml( const fc::string& filename );

};


