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
#include "BattleCommand.h"
#include "Serialization.h"



BattleCommand::BattleCommand() :
	id(0),
	flags(0)
{
}


void BattleCommand::SerializeXml( XmlWriter* xml )
{
	xml->SetString("name", name.c_str());
	xml->SetString("description", description.c_str());

	xml->SetInt("id", id);

}


void BattleCommand::DeserializeXml( XmlReader* xml )
{
	name = xml->GetString("name");
	description = xml->GetString("description");

	id = xml->GetInt("id");

}


