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

#include <Catastrophe/Graphics/Sprite.h>
#include "Common.h"
#include "DataList.h"

/*
class RPG_API SpriteList : public DataList<Sprite>
{
public:
	typedef DataList<Sprite>	base_type;

	SpriteList() : base_type()
	{}

	Sprite& GetSprite( size_t index ) { return base_type::operator [](index);  }
	const Sprite& GetSprite( size_t index ) const { return base_type::operator [](index);  }

	NO_INLINE bool SerializeXml( const fc::string& filename );
	NO_INLINE bool DeserializeXml( const fc::string& filename );

};
*/

class RPG_API AnimatedSpriteList : public DataList<AnimatedSprite>
{
public:
	typedef DataList<AnimatedSprite>	base_type;

	AnimatedSpriteList() : base_type()
	{}

	AnimatedSprite& GetSprite( size_t index ) { return base_type::operator [](index);  }
	const AnimatedSprite& GetSprite( size_t index ) const { return base_type::operator [](index);  }

	NO_INLINE bool SerializeXml( const fc::string& filename );
	NO_INLINE bool DeserializeXml( const fc::string& filename );

};

