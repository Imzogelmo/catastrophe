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
#include "MonsterTroop.h"



MonsterGroup::MonsterGroup() :
	monsterId(0),
	minimum(1),
	maximum(1)
{
}


MonsterGroup::MonsterGroup( u16 monsterIndex, u8 minNum, u8 maxNum ) :
	monsterId(monsterIndex),
	minimum(minNum),
	maximum(maxNum)
{
	Validate();
}


void MonsterGroup::Validate()
{
	if(maximum < minimum)
		minimum = maximum;
}


void MonsterGroup::Serialize( AttributeWriter* f )
{
	//f->BeginNode("Monster");
	f->SetAttribute("index", monsterId);
	f->SetAttribute("min", minimum);
	f->SetAttribute("max", maximum);
	//f->EndNode();

}


void MonsterGroup::Deserialize( AttributeReader* f )
{
	f->GetAttribute("index", monsterId);
	f->GetAttribute("min", minimum);
	f->GetAttribute("max", maximum);
}





// MonsterTroop

MonsterTroop::MonsterTroop() :
	groups(),
	id(0),
	formationId(0),
	maxMonsters(9)
{
}


void MonsterTroop::Serialize( AttributeWriter* f )
{
	f->SetString("name", name);
	f->SetAttribute("formation", formationId);
	f->SetAttribute("max", maxMonsters);
	f->SetAttribute("num_groups", groups.size());

	for( vec_type::Iterator it = groups.begin(); it < groups.end(); ++it )
	{
		f->BeginNode("Monster");
		it->Serialize(f);
		f->EndNode();
	}
}


void MonsterTroop::Deserialize( AttributeReader* f )
{
	f->GetString("name", name);
	f->GetAttribute("formation", formationId);
	f->GetAttribute("max", maxMonsters);

	u32 numGroups = 0;
	f->GetAttribute("num_groups", numGroups);
	groups.Resize(numGroups);

	for( u32 i(0); i < numGroups; ++i )
	{
		if( f->NextChild("Monster") )
			groups[i].Deserialize(f);
	}

	if( f->GetCurrentNodeName() == "Monster" )
		f->SetToParent();

}


int MonsterTroop::GetMemoryUsage() const
{
	return (int)(groups.Capacity() * sizeof(MonsterGroup));
}


