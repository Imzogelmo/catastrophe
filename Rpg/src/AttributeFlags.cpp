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


#include <Catastrophe/FileIO.h>

#include "AttributeFlags.h"


void AttributeFlags::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Flags");
	xml->SetInt("stats", stat_flags.bits);
	xml->SetInt("elements", element_flags.bits);
	xml->SetInt("status", status_flags.bits);
	xml->SetInt("family", family_flags.bits);
	xml->SetInt("class", class_flags.bits);
	xml->SetInt("misc", misc_flags.bits);
	xml->EndNode();
}


void AttributeFlags::DeserializeXml( XmlReader* xml )
{
	xml->FirstChild("Flags");
	stat_flags.bits = xml->GetInt("stats");
	element_flags.bits = xml->GetInt("elements");
	status_flags.bits = xml->GetInt("status");
	family_flags.bits = xml->GetInt("family");
	class_flags.bits = xml->GetInt("class");
	misc_flags.bits = xml->GetInt("misc");
	xml->SetToParent();
}


