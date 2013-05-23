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
	xml->SetInt("elem_atk", element_atk);
	xml->SetInt("elem_absorb", element_absorb);
	xml->SetInt("elem_nullify", element_nullify);
	xml->SetInt("elem_resist", element_resist);
	xml->SetInt("elem_weak", element_weak);
	xml->SetInt("family", family_flags);
	xml->SetInt("class", class_flags);
	xml->SetInt("misc", misc_flags);
	xml->EndNode();
}


void AttributeFlags::DeserializeXml( XmlReader* xml )
{
	if( xml->FirstChild("Flags") )
	{
		element_atk = xml->GetInt("elem_atk");
		element_absorb = xml->GetInt("elem_absorb");
		element_nullify = xml->GetInt("elem_nullify");
		element_resist = xml->GetInt("elem_resist");
		element_weak = xml->GetInt("elem_weak");
		family_flags = xml->GetInt("family");
		class_flags = xml->GetInt("class");
		misc_flags = xml->GetInt("misc");
		xml->SetToParent();
	}
}


