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

	ret.max_params = max_params + rhs.max_params;
	ret.stats = stats + rhs.stats;
	//ret.elements = elements + rhs.elements;
	ret.status_atk = status_atk.Add<int>(rhs.status_atk, 0, 100);
	ret.status_def = status_def.Add<int>(rhs.status_def, 0, 100);

	return ret;
}


Attributes Attributes::operator -(const Attributes& rhs) const
{
	Attributes ret;

	ret.max_params = max_params - rhs.max_params;
	ret.stats = stats - rhs.stats;
	//ret.elements = elements - rhs.elements;
	ret.status_atk = status_atk.Subtract<int>(rhs.status_atk, 0, 100);
	ret.status_def = status_def.Subtract<int>(rhs.status_def, 0, 100);

	return ret;
}


Attributes& Attributes::operator +=(const Attributes& rhs)
{
	max_params += rhs.max_params;
	stats += rhs.stats;

	//elements += rhs.elements;
	status_atk.AddAssign<int>(rhs.status_atk, 0, 100);
	status_def.AddAssign<int>(rhs.status_def, 0, 100);

	//flags |= rhs.flags;

	return *this;
}


Attributes& Attributes::operator -=(const Attributes& rhs)
{
	max_params -= rhs.max_params;
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
	xml->BeginNode("MaxParams");
	xml->WriteBlock(&max_params[0], MAX_PARAMS);
	xml->EndNode();

	xml->BeginNode("Stats");
	xml->WriteBlock(&stats[0], MAX_STATS);
	xml->EndNode();

	xml->BeginNode("StatusAtk");
	xml->WriteBlock((ubyte*)&status_atk[0], MAX_STATUS);
	xml->EndNode();

	xml->BeginNode("StatusDef");
	xml->WriteBlock((ubyte*)&status_def[0], MAX_STATUS);
	xml->EndNode();

	//attribute_flags.SerializeXml(xml);

}


void Attributes::DeserializeXml( XmlReader* xml )
{

	if( xml->FirstChild("MaxParams") )
	{
		xml->ReadBlock(&max_params[0], MAX_PARAMS);
		xml->SetToParent();
	}

	if( xml->FirstChild("Stats") )
	{
		xml->ReadBlock(&stats[0], MAX_STATS);
		xml->SetToParent();
	}

	if( xml->FirstChild("StatusAtk") )
	{
		xml->ReadBlock((ubyte*)&status_atk[0], MAX_STATUS);
		xml->SetToParent();
	}

	if( xml->FirstChild("StatusDef") )
	{
		xml->ReadBlock((ubyte*)&status_def[0], MAX_STATUS);
		xml->SetToParent();
	}

	//attribute_flags.DeserializeXml(xml);

}

/*
void Attributes::DeserializeXml( XmlReader* xml )
{
	temp[0] = temp[1] = temp[2] = 0;

	int a[32];
	xml->FirstChild("Attributes");
	xml->ReadBlock(&a[0], 32);
	xml->SetToParent();

	temp[0] = a[0];
	temp[1] = a[1];
	temp[2] = a[2];

	max_params[0] = a[4];

	for(int i(0); i<16; ++i)
	{
		stats[i] = a[i + 8];
	}

	//xml->FirstChild("Attributes");
	//xml->ReadBlock(&stats[0], MAX_STATS);
	//xml->SetToParent();

	//attribute_flags.DeserializeXml(xml);

}
*/
