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


void AttributeFlags::SerializeXml( AttributeWriter* f )
{
	f->BeginNode("Flags");
	f->SetInt("elem_atk", element_atk);
	f->SetInt("elem_absorb", element_absorb);
	f->SetInt("elem_nullify", element_nullify);
	f->SetInt("elem_resist", element_resist);
	f->SetInt("elem_weak", element_weak);
	f->SetInt("family", family_flags);
	f->SetInt("class", class_flags);
	f->SetInt("misc", misc_flags);
	f->EndNode();
}


void AttributeFlags::DeserializeXml( AttributeReader* f )
{
	if( f->FirstChild("Flags") )
	{
		element_atk = f->GetInt("elem_atk");
		element_absorb = f->GetInt("elem_absorb");
		element_nullify = f->GetInt("elem_nullify");
		element_resist = f->GetInt("elem_resist");
		element_weak = f->GetInt("elem_weak");
		family_flags = f->GetInt("family");
		class_flags = f->GetInt("class");
		misc_flags = f->GetInt("misc");
		f->SetToParent();
	}
}


