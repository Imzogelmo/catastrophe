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
#include "EquipmentItem.h"


EquipmentItem::EquipmentItem() :
	Item(),
	attributes()
{
}


void EquipmentItem::RegisterObject()
{
}


void EquipmentItem::SerializeXml( XmlWriter* xml )
{
	Item::SerializeXml(xml);
	attributes.SerializeXml(xml);
}


void EquipmentItem::DeserializeXml( XmlReader* xml )
{
	Item::DeserializeXml(xml);
	attributes.DeserializeXml(xml);
}


void EquipmentItem::Serialize( Serializer* f )
{
	//Item::Serialize(xml);
	//attributes.Serialize(xml);
}


void EquipmentItem::Deserialize( File* f )
{
	//Item::Deserialize(xml);
	//attributes.Deserialize(xml);
}


