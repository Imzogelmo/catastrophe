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
#include "CharacterData.h"



CharacterData::CharacterData() :
	name(),
	script(),
	description(),
	id(0),
	portraitId(0),
	mapSpritesetId(0),
	battleSpritesetId(0),
	startingLv(1),
	startingExp(0),
	startingGold(0),
	attributes()
{
}


void CharacterData::Serialize( AttributeWriter* f )
{
	f->SetString("name", name.CString());
	f->SetString("script", script.CString());
	f->SetString("description", description.CString());

	f->BeginNode("Data");
	f->SetAttribute("lv", startingLv);
	f->SetAttribute("exp", startingExp);
	f->SetAttribute("gold", startingGold);
	f->SetAttribute("class_id", classId);
	f->SetAttribute("portraitId", portraitId);
	f->SetAttribute("mapSpritesetId", mapSpritesetId);
	f->SetAttribute("battleSpritesetId", battleSpritesetId);
	f->EndNode();

	attributes.Serialize(f);
}


void CharacterData::Deserialize( AttributeReader* f )
{
	name = f->GetString("name");
	script = f->GetString("script");
	description = f->GetString("description");
	
	if( f->NextChild("Data") )
	{
		f->GetAttribute("lv", startingLv);
		f->GetAttribute("exp", startingExp);
		f->GetAttribute("gold", startingGold);
		f->GetAttribute("class_id", classId);
		f->GetAttribute("portraitId", portraitId);
		f->GetAttribute("mapSpritesetId", mapSpritesetId);
		f->GetAttribute("battleSpritesetId", battleSpritesetId);
		f->SetToParent();
	}

	attributes.Deserialize(f);
}


int CharacterData::GetMemoryUsage() const
{
	return (int)(description.Capacity());
}


