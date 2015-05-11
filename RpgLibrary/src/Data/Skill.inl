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

#include <Catastrophe/Core/IO/AttributeWriter.h>
#include <Catastrophe/Core/IO/AttributeReader.h>
#include "Skill.h"



Skill::Skill()
{
}


void Skill::Serialize( AttributeWriter* f )
{
	f->SetString("name", name.CString());
	f->SetString("script", script.CString());
	f->SetString("description", description.CString());

	//attributes.Serialize(xml);
}


void Skill::Deserialize( AttributeReader* f )
{
	name = f->GetString("name");
	script = f->GetString("script");
	description = f->GetString("description");

	//attributes.Deserialize(xml);
}


int Skill::GetMemoryUsage() const
{
	return (int)(description.Capacity() + levelData.Capacity());
}

