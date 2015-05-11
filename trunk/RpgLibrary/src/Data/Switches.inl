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
#include "Switches.h"
#include "Serialization.h"


Switches::Switches() :
	bits()
{
}


void Switches::Reset()
{
	bits.Reset();
}


void Switches::ToggleBit( u32 position )
{
	if( position < MaxBits )
		bits.FlipBit(position);
}


void Switches::SetBit( u32 position, bool value )
{
	if( position < MaxBits )
		bits.SetBit(position, value);
}


bool Switches::GetBit( u32 position )
{
	return (position < MaxBits ? bits.GetBit(position) : false);
}


void Switches::Serialize( AttributeWriter* f )
{
	f->BeginNode("Switches");
	f->WriteIntArrayElement("Bits", (int*)bits.data(), bit_array_type::NWords);
	f->EndNode();
}


void Switches::Deserialize( AttributeReader* f )
{
	if( f->FirstChild("Switches") )
	{
		f->ReadIntArrayElement("Bits", (int*)bits.data(), bit_array_type::NWords);
		f->SetToParent();
	}
}


