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
#include "MonsterFormation.h"
#include "AttributeSerializer.h"



MonsterFormationCellData::MonsterFormationCellData() :
	x(0),
	y(0)
{
}


MonsterFormationCellData::MonsterFormationCellData( short x, short y ) :
	x(x),
	y(y)
{
}


void MonsterFormationCellData::RegisterObject()
{
	REGISTER_ATTRIBUTE_FACTORY_TYPE(MonsterFormationCellData);
	REGISTER_ATTRIBUTE(MonsterFormationCellData, VAR_TYPE_SHORT, "x", x);
	REGISTER_ATTRIBUTE(MonsterFormationCellData, VAR_TYPE_SHORT, "y", y);
}


void MonsterFormationCellData::SerializeXml( XmlWriter* xml )
{
	SERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);
}


void MonsterFormationCellData::DeserializeXml( XmlReader* xml )
{
	DESERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);
}


void MonsterFormationCellData::Serialize( Serializer* f )
{
	SERIALIZE_OBJECT_ATTRIBUTES(this, f);
}


void MonsterFormationCellData::Deserialize( File* f )
{
	DESERIALIZE_OBJECT_ATTRIBUTES(this, f);
}





// MonsterFormation

MonsterFormation::MonsterFormation() :
	formations(),
	id(0)
{
}


void MonsterFormation::RegisterObject()
{
	REGISTER_ATTRIBUTE_FACTORY_TYPE(MonsterFormation);
	REGISTER_ATTRIBUTE_OBJECT_ARRAY(MonsterFormation, "Cell", "max", array_type, formations);
}


void MonsterFormation::SerializeXml( XmlWriter* xml )
{
	SERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);
}


void MonsterFormation::DeserializeXml( XmlReader* xml )
{
	DESERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);
}


void MonsterFormation::Serialize( Serializer* f )
{
	SERIALIZE_OBJECT_ATTRIBUTES(this, f);
}


void MonsterFormation::Deserialize( Deserializer* f )
{
	DESERIALIZE_OBJECT_ATTRIBUTES(this, f);
}



