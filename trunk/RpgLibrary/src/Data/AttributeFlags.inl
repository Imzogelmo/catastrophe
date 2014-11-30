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
	f->SetInt("elemAtk", elementAtk);
	f->SetInt("familyStrong", familyStrong);
	f->SetInt("familyWeak", familyWeak);
	f->SetInt("class", classFlags);
	f->SetInt("misc", miscFlags);
	f->EndNode();
}


void AttributeFlags::Deserialize( AttributeReader* f )
{
	if( f->FirstChild("Flags") )
	{
		elementAtk = f->GetInt("elem_atk");
		familyStrong = f->GetInt("familyStrong");
		familyWeak = f->GetInt("familyWeak");
		classFlags = f->GetInt("class");
		miscFlags = f->GetInt("misc");
		f->SetToParent();
	}
}


