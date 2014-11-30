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
#include "BattleCommand.h"



BattleCommand::BattleCommand() :
	id(0),
	type(0),
	flags(0)
{
}


void BattleCommand::Serialize( AttributeWriter* f )
{
	f->SetString("name", name.c_str());
	f->SetString("description", description.c_str());
	f->SetInt("id", id);
	f->SetInt("type", type);
	f->SetInt("flags", flags);

}


void BattleCommand::Deserialize( AttributeReader* f )
{
	name = f->GetString("name");
	description = f->GetString("description");
	id = f->GetInt("id");
	type = f->GetInt("type");
	flags = f->GetInt("flags");

}


