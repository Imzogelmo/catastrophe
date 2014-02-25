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

#include "RpgCommon.h"


struct RPG_API ExpCurve
{
	typedef fc::vector<int>		vec_type;

	vec_type	values;
	int			max_levels;
	int			start_exp;
	int			end_exp;

	ExpCurve( int maxLevels = 50, int startExp = 40, int endExp = 989641 )
		: values(), max_levels(maxLevels), start_exp(startExp), end_exp(endExp)
	{}

	int& operator []( size_t i ) { return values.at(i); }
	const int& operator []( size_t i ) const { return values.at(i); }

	void GenerateCurve();

};


struct RPG_API ExpTable
{
	typedef fc::vector<int>		vec_type;

	// valid exp table indices start at 1.
	// zero is equivelent to lv 0. (0 exp)
	vec_type table;

	int& operator []( int lv ) { return table.at(lv); }
	const int& operator []( int lv ) const { return table.at(lv); }

	int GetExpForLevel( int lv );
	int GetExpDeltaForLevel( int lv );
	void Resize( int maxLv );

	void SerializeXml( AttributeWriter* f );
	void DeserializeXml( AttributeReader* f );

};


