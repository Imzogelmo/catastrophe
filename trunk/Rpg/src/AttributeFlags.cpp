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
	xml->SetInt("element", element.bits);
	xml->SetInt("element_absorb", element_absorb.bits);
	xml->SetInt("element_nullify", element_nullify.bits);
	xml->SetInt("element_resist", element_resist.bits);
	xml->SetInt("element_weak", element_weak.bits);
	xml->SetInt("family", family_flags.bits);
	xml->SetInt("class", class_flags.bits);
	xml->SetInt("misc", misc_flags.bits);
	xml->EndNode();
}


void AttributeFlags::DeserializeXml( XmlReader* xml )
{
	xml->FirstChild("Flags");
	element.bits = xml->GetInt("element");
	element_absorb.bits = xml->GetInt("element_absorb");
	element_nullify.bits = xml->GetInt("element_nullify");
	element_resist.bits = xml->GetInt("element_resist");
	element_weak.bits = xml->GetInt("element_weak");
	family_flags.bits = xml->GetInt("family");
	class_flags.bits = xml->GetInt("class");
	misc_flags.bits = xml->GetInt("misc");
	xml->SetToParent();
}


