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
#include "DataList.h"


struct RPG_API Item : public AttributeData
{
	typedef AttributeData	base_type;

	Flags32			usage_flags;
	//size_t			effect_id;
	int				sfx;

	Sprite			icon;
	//AnimatedSprite	sprite;

	Item() : base_type()
	{}

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};



class RPG_API ItemList : public DataList<Item>
{
public:
	typedef DataList<Item>	base_type;

	ItemList() : base_type()
	{}

	Item& GetItem( size_t index ) { return base_type::operator [](index);  }
	const Item& GetItem( size_t index ) const { return base_type::operator [](index);  }

	NO_INLINE bool SerializeXml( const fc::string& filename );
	NO_INLINE bool DeserializeXml( const fc::string& filename );

};

