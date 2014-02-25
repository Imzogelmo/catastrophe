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


#include <Catastrophe/IO/AttributeWriter.h>
#include <Catastrophe/IO/AttributeReader.h>
#include "LevelData.h"
#include "Serialization.h"




void LevelData::SerializeXml( AttributeWriter* f )
{
	flags.SerializeXml(f);
}


void LevelData::DeserializeXml( AttributeReader* f )
{
	flags.DeserializeXml(f);
}



void LevelInfo::SerializeXml( AttributeWriter* f )
{
	f->BeginNode("LevelInfo");
	f->SetUInt("count", levels.size());
	f->SetInt("exp_table", exp_table_id);

	for( size_t i(0); i < levels.size(); ++i )
	{
		f->BeginNode("LevelData");
		levels[i].SerializeXml(f);
		f->EndNode();
	}

	f->EndNode();
}


void LevelInfo::DeserializeXml( AttributeReader* f )
{
	size_t n = f->GetUInt("count");
	exp_table_id = f->GetInt("exp_table");
	levels.clear();
	levels.reserve(n);

	while( f->NextChild("LevelData") )
	{
		levels.push_back();
		levels.back().DeserializeXml(f);
		f->SetToParent();
	}
}

