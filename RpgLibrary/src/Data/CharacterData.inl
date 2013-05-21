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


#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/IO/XmlReader.h>
#include "CharacterData.h"
#include "Serialization.h"



CharacterData::CharacterData() :
	name(),
	script(),
	description(),
	id(0),
	portrait_id(0),
	map_spriteset_id(0),
	battle_spriteset_id(0),
	lv(0),
	exp(0),
	gold(0),
	attributes()
{
}


void CharacterData::SerializeXml( XmlWriter* xml )
{
	xml->SetString("name", name.c_str());
	xml->SetString("script", script.c_str());
	xml->SetString("description", description.c_str());

	xml->BeginNode("Data");
	xml->SetInt("lv", lv);
	xml->SetInt("exp", exp);
	xml->SetInt("gold", gold);
	xml->SetInt("class_id", class_id);
	xml->SetInt("portrait_id", portrait_id);
	xml->SetInt("map_spriteset_id", map_spriteset_id);
	xml->SetInt("battle_spriteset_id", battle_spriteset_id);
	xml->EndNode();

	attributes.SerializeXml(xml);

}


void CharacterData::DeserializeXml( XmlReader* xml )
{
	name = xml->GetString("name");
	script = xml->GetString("script");
	description = xml->GetString("description");
	
	if( xml->NextChild("Data") )
	{
		lv = xml->GetInt("lv");
		exp = xml->GetInt("exp");
		gold = xml->GetInt("gold");
		class_id = xml->GetInt("class_id");
		portrait_id = xml->GetInt("portrait_id");
		map_spriteset_id = xml->GetInt("map_spriteset_id");
		battle_spriteset_id = xml->GetInt("battle_spriteset_id");
		xml->SetToParent();
	}

	attributes.DeserializeXml(xml);

}


