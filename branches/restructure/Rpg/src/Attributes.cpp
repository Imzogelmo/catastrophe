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

#include <Catastrophe/FileIO.h>

#include "Attributes.h"



void Attributes::ApplyPercentageModifier(const Attributes& modifier)
{
	stats.ApplyPercentageModifier(modifier.stats);
	elements.ApplyPercentageModifier(modifier.elements);
	status.ApplyPercentageModifier(modifier.status);
}


void Attributes::ApplyMin(const Attributes& value)
{
	stats.ApplyMin(value.stats);
	elements.ApplyMin(value.elements);
	status.ApplyMin(value.status);
}


void Attributes::ApplyMax(const Attributes& value)
{
	stats.ApplyMax(value.stats);
	elements.ApplyMax(value.elements);
	status.ApplyMax(value.status);
}


void Attributes::Clamp(const Attributes& min, const Attributes& max)
{
	stats.Clamp(min.stats, max.stats);
	elements.Clamp(min.elements, max.elements);
	status.Clamp(min.status, max.status);
}


void Attributes::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Attributes");
	xml->Write(&stats[0], MAX_STATS);
	xml->EndNode();

	xml->BeginNode("Elements");
	xml->Write(&elements[0], MAX_ELEMENTS);
	xml->EndNode();

	xml->BeginNode("Status");
	xml->Write(&status[0], MAX_STATUS);
	xml->EndNode();
}


void Attributes::DeserializeXml( XmlReader* xml )
{
	xml->FirstChild("Attributes");
	xml->ReadBlock(&stats[0], MAX_STATS);
	xml->SetToParent();

	xml->FirstChild("Elements");
	xml->ReadBlock(&elements[0], MAX_ELEMENTS);
	xml->SetToParent();

	xml->FirstChild("Status");
	xml->ReadBlock(&status[0], MAX_STATUS);
	xml->SetToParent();
}

