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
#include "AttributeFlags.h"
#include "DataList.h"


/*
 * Stores information for a particular level.
 */
struct RPG_API LevelData
{
	AttributeFlags flags;

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );
};


/*
 * Stores information for a range of levels.
 */
struct RPG_API LevelInfo
{
	typedef fc::vector<LevelData>	vec_type;

	vec_type levels;
	int exp_table_id;

	LevelInfo() : levels(), exp_table_id(-1)
	{}

	void SetExpTableIndex( int id ) { exp_table_id = id; }
	int GetExpTableIndex() const { return exp_table_id; }

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );
};


/*
 * A collection of LevelData objects.
 */
class RPG_API LevelList : public DataList<LevelInfo>
{
public:
	typedef DataList<LevelInfo>	base_type;

	LevelList() : base_type()
	{}

	LevelInfo& GetLevelInfo( size_t index ) { return base_type::operator [](index);  }
	const LevelInfo& GetLevelInfo( size_t index ) const { return base_type::operator [](index);  }

	NO_INLINE bool SerializeXml( const fc::string& filename );
	NO_INLINE bool DeserializeXml( const fc::string& filename );
};

