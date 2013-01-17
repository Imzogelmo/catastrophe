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

#include "Common.h"
#include "DataList.h"


struct RPG_API ExpTable
{
	typedef fc::vector<int>		vec_type;

	// valid exp table indices start at 1.
	// zero is equivelent to lv 0. (0 exp)
	vec_type table;

	int& operator []( int lv ) { return table.at(lv); }
	const int& operator []( int lv ) const { return table.at(lv); }

	int GetExpForLevel( int lv );
	int GetExpDeltaForLevel( int lv ); // get the difference of lv and previous lv.
	void Resize( int maxLv );

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};


/*
 * A collection of experience tables.
 */
class RPG_API ExpTableList : public DataList<ExpTable>
{
public:
	typedef DataList<ExpTable>	base_type;

	ExpTableList() : base_type()
	{}

	ExpTable& GetExpTable( size_t index ) { return base_type::operator [](index);  }
	const ExpTable& GetExpTable( size_t index ) const { return base_type::operator [](index);  }

	NO_INLINE bool SerializeXml( const fc::string& filename );
	NO_INLINE bool DeserializeXml( const fc::string& filename );

};

