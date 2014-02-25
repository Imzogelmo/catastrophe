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

#include <Catastrophe/IO/AttributeWriter.h>
#include <Catastrophe/IO/AttributeReader.h>
#include "Spell.h"


Spell::Spell()
{
}


void Spell::SerializeXml( AttributeWriter* f )
{
	f->SetString("name", name.c_str());
	f->SetString("script", script.c_str());
	f->SetString("description", description.c_str());

	attributes.SerializeXml(f);
}


void Spell::DeserializeXml( AttributeReader* f )
{
	name = f->GetString("name");
	script = f->GetString("script");
	description = f->GetString("description");

	attributes.DeserializeXml(f);
}

