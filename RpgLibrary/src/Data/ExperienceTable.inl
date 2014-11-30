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


#include <fc/math.h>
#include <Catastrophe/IO/AttributeWriter.h>
#include <Catastrophe/IO/AttributeReader.h>
#include "ExperienceTable.h"



void ExpCurve::GenerateCurve()
{
	values.resize( (u32)maxLevels + 1 );
	values[0] = 1;

	for( u32 i(1); i < values.size(); i++ )
	{
		values[i] = values[i - 1] + fc::iround(39.f * powf((float)fc::min<u32>(i, 29), 2.f));
	}

	int y = 0;
}



int ExperienceTable::GetExpForLevel( int lv )
{
	int ret = 0x7fffffff;
	if( (u32)lv < table.size() )
		ret = table[lv];

	return ret;
}


int ExperienceTable::GetExpDeltaForLevel( int lv )
{
	if( lv == 0 )
		return 0; //special case (0 exp = 0 lv)

	if( (u32)lv < table.size() )
		return table[lv] - table[lv - 1];

	return 0x7fffffff;
}


void ExperienceTable::Resize( u32 maxLv )
{
	u32 oldSize = table.size();
	u32 newSize = fc::min<u32>(maxLv + 1, MAX_LEVEL);

	table.resize(newSize);
	if( oldSize < table.size() )
	{
		if( oldSize == 0 )
			table[0] = 0;

		fc::fill_n(table.begin() + oldSize, table.size() - oldSize, 0x7fffffff);
	}
}


void ExperienceTable::Serialize( AttributeWriter* f )
{
	f->SetUInt("count", table.size());
	f->WriteIntArray("array", &table[0], table.size());
}


void ExperienceTable::Deserialize( AttributeReader* f )
{
	u32 n = f->GetUInt("count");
	Resize(n);

	f->ReadIntArray("array", &table[0], table.size());
}


int ExperienceTable::GetMemoryUsage() const
{
	return (int)(table.size() * sizeof(int));
}
