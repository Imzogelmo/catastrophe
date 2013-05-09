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



MonsterGroup::MonsterGroup( int monsterIndex, int minNum, int maxNum, int x, int y ) :
	monster_id(monsterIndex),
	min(minNum),
	max(maxNum),
	x(x),
	y(y)
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
	xml->SetInt("x", x);
	xml->SetInt("y", y);
	xml->EndNode();
}


void MonsterGroup::DeserializeXml( XmlReader* xml )
{
	monster_id = xml->GetInt("index");
	min = xml->GetInt("min");
	max = xml->GetInt("max");
	x = xml->GetInt("x");
	y = xml->GetInt("y");
}




MonsterTroop::MonsterTroop() :
	groups()
{
}


void MonsterTroop::SerializeXml( XmlWriter* xml )
{
	xml->SetString("name", name);
	xml->SetUInt("num_groups", groups.size());

	for( vec_type::iterator it = groups.begin(); it < groups.end(); ++it )
	{
		it->SerializeXml(xml);
	}
}


void MonsterTroop::DeserializeXml( XmlReader* xml )
{
	name = xml->GetString("name");
	size_t n = xml->GetUInt("num_groups");
	groups.reserve(n);

	bool hasChild = false;
	while( xml->NextChild("Monster") )
	{
		groups.push_back();
		groups.back().DeserializeXml(xml);
		hasChild = true;
	}

	if( hasChild )
		xml->SetToParent();
}

