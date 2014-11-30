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
	int			maxLevels;
	int			startingExp;
	int			endingExp;

	ExpCurve( int maxLevels = 50, int startExp = 40, int endExp = 989641 )
		: values(), maxLevels(maxLevels), startingExp(startExp), endingExp(endExp)
	{}

	int& operator []( u32 i ) { return values.at(i); }
	const int& operator []( u32 i ) const { return values.at(i); }

	void GenerateCurve();

};


struct RPG_API ExperienceTable
{
	// Valid exp table indices start at 1, so
	// zero is equivilent to lv 0. (0 exp).
	fc::dynamic_array<int> table;

	int& operator []( u32 lv ) { return table.at(lv); }
	const int& operator []( u32 lv ) const { return table.at(lv); }

	int GetExpForLevel( int lv );
	int GetExpDeltaForLevel( int lv );
	void Resize( u32 maxLv );

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

	int GetMemoryUsage() const;

};


