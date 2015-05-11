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
#include "CharacterClass.h"
#include "Serialization.h"



CharacterClass::CharacterClass() :
	name(),
	script(),
	description(),
	id(0),
	portraitId(0),
	mapSpritesetId(0),
	battleSpritesetId(0),
	exp_table_id(0),
	attributes()
{
}


void CharacterClass::Serialize( AttributeWriter* f )
{
	f->SetString("name", name.CString());
	f->SetString("script", script.CString());
	f->SetString("description", description.CString());

	f->BeginNode("Data");
	f->SetAttribute("portraitId", portraitId);
	f->SetAttribute("mapSpritesetId", portraitId);
	f->SetAttribute("battleSpritesetId", portraitId);
	f->EndNode();

	attributes.Serialize(f);

}


void CharacterClass::Deserialize( AttributeReader* f )
{
	name = f->GetString("name");
	script = f->GetString("script");
	description = f->GetString("description");

	if( f->NextChild("Data") )
	{
		f->GetAttribute("portraitId", portraitId);
		f->GetAttribute("mapSpritesetId", mapSpritesetId);
		f->GetAttribute("battleSpritesetId", battleSpritesetId);
		f->SetToParent();
	}

	attributes.Deserialize(f);

}


int CharacterClass::GetMemoryUsage() const
{
	return (int)(description.Capacity());
}

