
#pragma once

#include <Catastrophe/FileIO.h>
#include "ItemData.h"


void ItemData::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Item");

	xml->SetString("name", name.c_str());
	xml->SetString("description", description.c_str());

	attributes.SerializeXml(xml);
	attribute_flags.SerializeXml(xml);

	xml->EndNode();
}


void ItemData::DeserializeXml( XmlReader* xml )
{
	name = xml->GetString("name");
	description = xml->GetString("description");

	attributes.DeserializeXml(xml);
	attribute_flags.DeserializeXml(xml);
}

