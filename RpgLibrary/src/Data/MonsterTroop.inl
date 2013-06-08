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
#include "MonsterTroop.h"
#include "Serialization.h"



MonsterGroup::MonsterGroup( int monsterIndex, int minNum, int maxNum ) :
	monster_id(monsterIndex),
	min(minNum),
	max(maxNum)
{
}


void MonsterGroup::Validate()
{
	if(min < 0) min = 0;
	if(max < 0) max = 0;
	if(max < min) max = min;
}


void MonsterGroup::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Monster");
	xml->SetInt("index", monster_id);
	xml->SetInt("min", min);
	xml->SetInt("max", max);
	xml->EndNode();
}


void MonsterGroup::DeserializeXml( XmlReader* xml )
{
	monster_id = xml->GetInt("index");
	min = xml->GetInt("min");
	max = xml->GetInt("max");
}




MonsterTroop::MonsterTroop() :
	groups(),
	id(0),
	formation_id(0),
	max_monsters(9)
{
}


void MonsterTroop::SerializeXml( XmlWriter* xml )
{
	xml->SetString("name", name);
	xml->SetInt("formation", formation_id);
	xml->SetInt("max", max_monsters);
	xml->SetUInt("num_groups", groups.size());

	for( vec_type::iterator it = groups.begin(); it < groups.end(); ++it )
	{
		it->SerializeXml(xml);
	}
}


void MonsterTroop::DeserializeXml( XmlReader* xml )
{
	name = xml->GetString("name");
	formation_id = xml->GetInt("formation");
	max_monsters = xml->GetInt("max", 9);
	size_t n = xml->GetInt("num_groups");
	groups.resize(n);

	bool nested = false;
	for( size_t i(0); i < groups.size(); ++i )
	{
		if( xml->NextChild("Monster") )
		{
			groups[i].DeserializeXml(xml);
			nested = true;
		}
		else
		{
		}
	}

	if( nested )
		xml->SetToParent();
}


