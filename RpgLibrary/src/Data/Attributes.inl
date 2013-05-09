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


Attributes Attributes::operator +(const Attributes& rhs) const
{
	Attributes ret;

	ret.params = params + rhs.params;
	ret.stats = stats + rhs.stats;
	//ret.elements = elements + rhs.elements;
	ret.status_atk = status_atk.Add<int>(rhs.status_atk, 0, 100);
	ret.status_def = status_def.Add<int>(rhs.status_def, 0, 100);

	return ret;
}


Attributes Attributes::operator -(const Attributes& rhs) const
{
	Attributes ret;

	ret.params = params - rhs.params;
	ret.stats = stats - rhs.stats;
	//ret.elements = elements - rhs.elements;
	ret.status_atk = status_atk.Subtract<int>(rhs.status_atk, 0, 100);
	ret.status_def = status_def.Subtract<int>(rhs.status_def, 0, 100);

	return ret;
}


Attributes& Attributes::operator +=(const Attributes& rhs)
{
	params += rhs.params;
	stats += rhs.stats;

	//elements += rhs.elements;
	status_atk.AddAssign<int>(rhs.status_atk, 0, 100);
	status_def.AddAssign<int>(rhs.status_def, 0, 100);

	//flags |= rhs.flags;

	return *this;
}


Attributes& Attributes::operator -=(const Attributes& rhs)
{
	params -= rhs.params;
	stats -= rhs.stats;
	//elements -= rhs.elements;
	status_atk.SubtractAssign<int>(rhs.status_atk, 0, 100);
	status_def.SubtractAssign<int>(rhs.status_def, 0, 100);

	//flags -= rhs.flags;

	return *this;
}


/*
void Attributes::ApplyPercentageModifier(const Attributes& modifier)
{
	stats.ApplyPercentageModifier(modifier.stats);
	//elements.ApplyPercentageModifier(modifier.elements);
	status_atk.ApplyPercentageModifier(modifier.status_atk);
}


void Attributes::Clamp(const Attributes& min, const Attributes& max)
{
	stats.Clamp(min.stats, max.stats);
	//elements.Clamp(min.elements, max.elements);
	status_atk.Clamp(min.status_atk, max.status_atk);
}
*/

void Attributes::SerializeXml( XmlWriter* xml )
{
	xml->BeginNode("Attributes");
	xml->WriteBlock(&stats[0], MAX_STATS);
	xml->EndNode();

	xml->BeginNode("Status Atk");
	xml->WriteBlock((ubyte*)&status_atk[0], MAX_STATUS);
	xml->EndNode();

	xml->BeginNode("Status Def");
	xml->WriteBlock((ubyte*)&status_def[0], MAX_STATUS);
	xml->EndNode();

	//attribute_flags.SerializeXml(xml);

}


void Attributes::DeserializeXml( XmlReader* xml )
{
	xml->FirstChild("Attributes");
	xml->ReadBlock(&stats[0], MAX_STATS);
	xml->SetToParent();

	xml->FirstChild("Status Atk");
	xml->ReadBlock((ubyte*)&status_atk[0], MAX_STATUS);
	xml->SetToParent();

	xml->FirstChild("Status Def");
	xml->ReadBlock((ubyte*)&status_def[0], MAX_STATUS);
	xml->SetToParent();

	//attribute_flags.DeserializeXml(xml);

}
