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
#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/IO/XmlReader.h>
#include "ExpTable.h"



void ExpCurve::GenerateCurve()
{
	values.resize( (size_t)max_levels + 1 );
	values[0] = 1;

	for( size_t i(1); i < values.size(); i++ )
	{
		values[i] = values[i - 1] + fc::iround(39.f * powf((float)fc::min<size_t>(i, 29), (float)2));
	}

	int y = 0;
}



int ExpTable::GetExpForLevel( int lv )
{
	int ret = 0x7fffffff;
	if( (size_t)lv < table.size() )
		ret = table[lv];

	return ret;
}


int ExpTable::GetExpDeltaForLevel( int lv )
{
	if( lv == 0 )
		return 0; //special case (0 exp = 0 lv)

	int previous = lv - 1;
	int ret = 0x7fffffff;
	if( (size_t)lv < table.size() )
	{
		ret = table[lv] - table[previous];
	}

	return ret;
}


void ExpTable::Resize( int maxLv )
{
	size_t oldSize = table.size();
	table.resize(maxLv + 1);
	if( oldSize < table.size() )
	{
		if( oldSize == 0 )
			table[0] = 0;

		fc::fill_n(table.begin() + oldSize, table.size() - oldSize, 0x7fffffff);
	}
}


void ExpTable::SerializeXml( XmlWriter* xml )
{
	xml->SetUInt("count", table.size());
	//xml->WriteIntBlock(&table[0], table.size());
}


void ExpTable::DeserializeXml( XmlReader* xml )
{
	size_t n = xml->GetUInt("count");
	this->Resize((int)n);
	//xml->ReadIntBlock(&table[0], n);
}

