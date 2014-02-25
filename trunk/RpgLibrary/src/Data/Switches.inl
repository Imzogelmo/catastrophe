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
#include "Switches.h"
#include "Serialization.h"


Switches::Switches() :
	bits()
{
}


void Switches::Reset()
{
	bits.reset();
}


void Switches::FlipBit( int bit )
{
	if( bit < 4096 )
		bits.flip(bit);
}


void Switches::SetBit( int bit, bool value )
{
	if( bit < 4096 )
		bits.set(bit, value);
}


bool Switches::GetBit( int bit )
{
	bool ret = false;
	if( bit < 4096 )
		ret = bits.get(bit);

	return ret;
}


void Switches::SerializeXml( AttributeWriter* f )
{
	f->BeginNode("Switches");
	//f->WriteIntBlock((int*)bits.data(), bit_array_type::NWords);
	f->EndNode();
}


void Switches::DeserializeXml( AttributeReader* f )
{
	if( f->FirstChild("MaxParams") )
	{
		//f->ReadIntBlock((int*)bits.data(), bit_array_type::NWords);
		f->SetToParent();
	}
}


