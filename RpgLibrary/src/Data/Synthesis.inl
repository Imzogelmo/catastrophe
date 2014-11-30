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
#include "Synthesis.h"
#include "Serialization.h"



Synthesis::Synthesis() :
	item_id(0)
{
}


void Synthesis::Serialize( AttributeWriter* f )
{
	f->SetInt("item_id", item_id);

}


void Synthesis::Deserialize( AttributeReader* f )
{
	item_id = f->GetInt("item_id");

}


