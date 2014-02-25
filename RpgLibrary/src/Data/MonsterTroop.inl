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
#include "AttributeSerializer.h"



MonsterGroup::MonsterGroup( int monsterIndex, int minNum, int maxNum ) :
	monster_id(monsterIndex),
	min(minNum),
	max(maxNum)
{
}


void MonsterGroup::RegisterObject()
{
	/*
	REGISTER_ATTRIBUTE_FACTORY_TYPE(MonsterGroup);
	REGISTER_ATTRIBUTE(MonsterGroup, VAR_TYPE_INT, "index", monster_id);
	REGISTER_ATTRIBUTE(MonsterGroup, VAR_TYPE_INT, "min", min);
	REGISTER_ATTRIBUTE(MonsterGroup, VAR_TYPE_INT, "max", max);
	*/
}


void MonsterGroup::Validate()
{
	if(min < 0) min = 0;
	if(max < 0) max = 0;
	if(max < min) max = min;
}


void MonsterGroup::SerializeXml( AttributeWriter* f )
{
	//SERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);

	f->BeginNode("Monster");
	f->SetInt("index", monster_id);
	f->SetInt("min", min);
	f->SetInt("max", max);
	f->EndNode();

}


void MonsterGroup::DeserializeXml( AttributeReader* f )
{
	//DESERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);

	monster_id = f->GetInt("index", monster_id);
	min = f->GetInt("min", min);
	max = f->GetInt("max", max);

}





// MonsterTroop

MonsterTroop::MonsterTroop() :
	groups(),
	id(0),
	formation_id(0),
	max_monsters(9)
{
}


void MonsterTroop::RegisterObject()
{
	/*
	REGISTER_ATTRIBUTE_FACTORY_TYPE(MonsterTroop);
	REGISTER_ATTRIBUTE(MonsterTroop, VAR_TYPE_STRING, "name", name);
	REGISTER_ATTRIBUTE(MonsterTroop, VAR_TYPE_INT, "formation", formation_id);
	REGISTER_ATTRIBUTE(MonsterTroop, VAR_TYPE_INT, "max", max_monsters);
	REGISTER_ATTRIBUTE_OBJECT_ARRAY(MonsterTroop, "Monster", "num_groups", vec_type, groups);
	*/
}


void MonsterTroop::SerializeXml( AttributeWriter* f )
{
	//SERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);

	f->SetString("name", name);
	f->SetInt("formation", formation_id);
	f->SetInt("max", max_monsters);
	f->SetUInt("num_groups", groups.size());

	for( vec_type::iterator it = groups.begin(); it < groups.end(); ++it )
	{
		f->BeginNode("Monster");
		it->SerializeXml(f);
		f->EndNode();
	}
}


void MonsterTroop::DeserializeXml( AttributeReader* f )
{
	//DESERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);

	name = f->GetString("name", name);
	formation_id = f->GetInt("formation", formation_id);
	max_monsters = f->GetInt("max", max_monsters);

	size_t numGroups = f->GetInt("num_groups");
	groups.resize(numGroups);

	for( size_t i(0); i < numGroups; ++i )
	{
		if( f->NextChild("Monster") )
			groups[i].DeserializeXml(f);
	}

	if( f->GetCurrentNodeName() == "Monster" )
		f->SetToParent();

}



