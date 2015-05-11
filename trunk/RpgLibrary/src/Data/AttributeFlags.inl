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


void AttributeFlags::Serialize( AttributeWriter* f )
{
	f->BeginNode("Flags");
	f->SetAttribute("elemAtk", elementAtk);
	f->SetAttribute("familyStrong", familyStrong);
	f->SetAttribute("familyWeak", familyWeak);
	f->SetAttribute("class", classFlags);
	f->SetAttribute("misc", miscFlags);
	f->EndNode();
}


void AttributeFlags::Deserialize( AttributeReader* f )
{
	if( f->FirstChild("Flags") )
	{
		f->GetAttribute("elem_atk", elementAtk);
		f->GetAttribute("familyStrong", familyStrong);
		f->GetAttribute("familyWeak", familyWeak);
		f->GetAttribute("class", classFlags);
		f->GetAttribute("misc", miscFlags);
		f->SetToParent();
	}
}


