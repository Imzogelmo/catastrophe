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
#include "AttributeSerializer.h"



MonsterGroup::MonsterGroup( int monsterIndex, int minNum, int maxNum ) :
	monster_id(monsterIndex),
	min(minNum),
	max(maxNum)
{
}


void MonsterGroup::RegisterObject()
{
	REGISTER_ATTRIBUTE_FACTORY_TYPE(MonsterGroup);
	REGISTER_ATTRIBUTE(MonsterGroup, VAR_TYPE_INT, "index", monster_id);
	REGISTER_ATTRIBUTE(MonsterGroup, VAR_TYPE_INT, "min", min);
	REGISTER_ATTRIBUTE(MonsterGroup, VAR_TYPE_INT, "max", max);
}


void MonsterGroup::Validate()
{
	if(min < 0) min = 0;
	if(max < 0) max = 0;
	if(max < min) max = min;
}


void MonsterGroup::SerializeXml( XmlWriter* xml )
{
	SERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);
}


void MonsterGroup::DeserializeXml( XmlReader* xml )
{
	DESERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);
}


void MonsterGroup::Serialize( Serializer* f )
{
	SERIALIZE_OBJECT_ATTRIBUTES(this, f);
}


void MonsterGroup::Deserialize( File* f )
{
	DESERIALIZE_OBJECT_ATTRIBUTES(this, f);
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
	REGISTER_ATTRIBUTE_FACTORY_TYPE(MonsterTroop);
	REGISTER_ATTRIBUTE(MonsterTroop, VAR_TYPE_STRING, "name", name);
	REGISTER_ATTRIBUTE(MonsterTroop, VAR_TYPE_INT, "formation", formation_id);
	REGISTER_ATTRIBUTE(MonsterTroop, VAR_TYPE_INT, "max", max_monsters);
	REGISTER_ATTRIBUTE_OBJECT_ARRAY(MonsterTroop, "Monster", "num_groups", vec_type, groups);
}


void MonsterTroop::SerializeXml( XmlWriter* xml )
{
	SERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);
}


void MonsterTroop::DeserializeXml( XmlReader* xml )
{
	DESERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);
}


void MonsterTroop::Serialize( Serializer* f )
{
	SERIALIZE_OBJECT_ATTRIBUTES(this, f);
}


void MonsterTroop::Deserialize( File* f )
{
	DESERIALIZE_OBJECT_ATTRIBUTES(this, f);
}



