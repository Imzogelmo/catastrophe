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
#include "MonsterTroop.h"



MonsterGroup::MonsterGroup() :
	monsterId(0),
	min(1),
	max(1)
{
}


MonsterGroup::MonsterGroup( u16 monsterIndex, u8 minNum, u8 maxNum ) :
	monsterId(monsterIndex),
	min(minNum),
	max(maxNum)
{
	Validate();
}


void MonsterGroup::Validate()
{
	if(max < min)
		max = min;
}


void MonsterGroup::Serialize( AttributeWriter* f )
{
	//f->BeginNode("Monster");
	f->SetShort("index", monsterId);
	f->SetByte("min", min);
	f->SetByte("max", max);
	//f->EndNode();

}


void MonsterGroup::Deserialize( AttributeReader* f )
{
	monsterId = f->GetShort("index", monsterId);
	min = f->GetByte("min", min);
	max = f->GetByte("max", max);

}





// MonsterTroop

MonsterTroop::MonsterTroop() :
	groups(),
	id(0),
	formation_id(0),
	max_monsters(9)
{
}


void MonsterTroop::Serialize( AttributeWriter* f )
{
	f->SetString("name", name);
	f->SetInt("formation", formation_id);
	f->SetInt("max", max_monsters);
	f->SetUInt("num_groups", groups.size());

	for( vec_type::iterator it = groups.begin(); it < groups.end(); ++it )
	{
		f->BeginNode("Monster");
		it->Serialize(f);
		f->EndNode();
	}
}


void MonsterTroop::Deserialize( AttributeReader* f )
{
	name = f->GetString("name", name);
	formation_id = f->GetInt("formation", formation_id);
	max_monsters = f->GetInt("max", max_monsters);

	u32 numGroups = f->GetInt("num_groups");
	groups.resize(numGroups);

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
	return (int)(groups.capacity() * sizeof(MonsterGroup));
}


