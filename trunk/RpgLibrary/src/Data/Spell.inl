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
#include "Spell.h"


Spell::Spell()
{
}


void Spell::Serialize( AttributeWriter* f )
{
	f->SetString("name", name.CString());
	f->SetString("script", script.CString());
	f->SetString("description", description.CString());

	attributes.Serialize(f);
}


void Spell::Deserialize( AttributeReader* f )
{
	name = f->GetString("name");
	script = f->GetString("script");
	description = f->GetString("description");

	attributes.Deserialize(f);
}


int Spell::GetMemoryUsage() const
{
	return (int)(description.Capacity() + levelData.Capacity());
}
