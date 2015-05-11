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


#include <Catastrophe/Core/IO/AttributeWriter.h>
#include <Catastrophe/Core/IO/AttributeReader.h>
#include "LevelData.h"
#include "Serialization.h"




void LevelData::Serialize( AttributeWriter* f )
{
	flags.Serialize(f);
}


void LevelData::Deserialize( AttributeReader* f )
{
	flags.Deserialize(f);
}



void LevelInfo::Serialize( AttributeWriter* f )
{
	f->BeginNode("LevelInfo");
	f->SetAttribute("count", levels.Size());
	f->SetAttribute("exp_table", exp_table_id);

	for( u32 i(0); i < levels.Size(); ++i )
	{
		f->BeginNode("LevelData");
		levels[i].Serialize(f);
		f->EndNode();
	}

	f->EndNode();
}


void LevelInfo::Deserialize( AttributeReader* f )
{
	u32 n = 0;
	f->GetAttribute("count", n);

	f->GetAttribute("exp_table", exp_table_id);
	levels.Clear();
	levels.Reserve(n);

	while( f->NextChild("LevelData") )
	{
		levels.Add();
		levels.Back().Deserialize(f);
		f->SetToParent();
	}
}

