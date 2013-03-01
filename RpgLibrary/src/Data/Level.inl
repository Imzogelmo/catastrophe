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


#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/IO/XmlReader.h>
#include "LevelData.h"
#include "Serialization.h"




void LevelData::SerializeXml( XmlWriter* xml )
{
	flags.SerializeXml(xml);
}


void LevelData::DeserializeXml( XmlReader* xml )
{
	flags.DeserializeXml(xml);
}



void LevelInfo::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("LevelInfo");
	xml->SetUInt("count", levels.size());
	xml->SetInt("exp_table", exp_table_id);

	for( size_t i(0); i < levels.size(); ++i )
	{
		xml->BeginNode("LevelData");
		levels[i].SerializeXml(xml);
		xml->EndNode();
	}

	xml->EndNode();
}


void LevelInfo::DeserializeXml( XmlReader* xml )
{
	size_t n = xml->GetUInt("count");
	exp_table_id = xml->GetInt("exp_table");
	levels.clear();
	levels.reserve(n);

	while( xml->NextChild("LevelData") )
	{
		levels.push_back();
		levels.back().DeserializeXml(xml);
		xml->SetToParent();
	}
}

