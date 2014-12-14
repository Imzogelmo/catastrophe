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

#include <Catastrophe/IO/File.h>
#include <Catastrophe/IO/AttributeWriter.h>
#include <Catastrophe/IO/AttributeReader.h>

#include "Attributes.h"


Attributes Attributes::operator +(const Attributes& rhs) const
{
	Attributes ret;

	ret.maxParams = maxParams + rhs.maxParams;
	ret.stats = stats + rhs.stats;
	ret.elementalDefense = elementalDefense.Add<int>(rhs.elementalDefense, -MAX_ELEMENT_VALUE, MAX_ELEMENT_VALUE);
	ret.statusAttack = statusAttack.Add<int>(rhs.statusAttack, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
	ret.statusDefense = statusDefense.Add<int>(rhs.statusDefense, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);

	return ret;
}


Attributes Attributes::operator -(const Attributes& rhs) const
{
	Attributes ret;

	ret.maxParams = maxParams - rhs.maxParams;
	ret.stats = stats - rhs.stats;
	ret.elementalDefense = elementalDefense.Subtract<int>(rhs.elementalDefense, -MAX_ELEMENT_VALUE, MAX_ELEMENT_VALUE);
	ret.statusAttack = statusAttack.Subtract<int>(rhs.statusAttack, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
	ret.statusDefense = statusDefense.Subtract<int>(rhs.statusDefense, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);

	return ret;
}


Attributes& Attributes::operator +=(const Attributes& rhs)
{
	maxParams += rhs.maxParams;
	stats += rhs.stats;
	elementalDefense.AddAssign<int>(rhs.elementalDefense, -MAX_ELEMENT_VALUE, MAX_ELEMENT_VALUE);
	statusAttack.AddAssign<int>(rhs.statusAttack, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
	statusDefense.AddAssign<int>(rhs.statusDefense, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);

	flags |= rhs.flags;

	return *this;
}


Attributes& Attributes::operator -=(const Attributes& rhs)
{
	maxParams -= rhs.maxParams;
	stats -= rhs.stats;
	elementalDefense.SubtractAssign<int>(rhs.elementalDefense, -MAX_ELEMENT_VALUE, MAX_ELEMENT_VALUE);
	statusAttack.SubtractAssign<int>(rhs.statusAttack, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
	statusDefense.SubtractAssign<int>(rhs.statusDefense, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);

	//flags -= rhs.flags;

	return *this;
}


/*
void Attributes::ApplyPercentageModifier(const Attributes& modifier)
{
	stats.ApplyPercentageModifier(modifier.stats);
	//elements.ApplyPercentageModifier(modifier.elements);
	statusAttack.ApplyPercentageModifier(modifier.statusAttack);
}


void Attributes::Clamp(const Attributes& min, const Attributes& max)
{
	stats.Clamp(min.stats, max.stats);
	//elements.Clamp(min.elements, max.elements);
	statusAttack.Clamp(min.statusAttack, max.statusAttack);
}
*/

void Attributes::RegisterObject()
{
	/*
	REGISTER_ATTRIBUTE_FACTORY_TYPE(Attributes);
	REGISTER_ATTRIBUTE_ARRAY(Attributes, VAR_TYPE_INT_ARRAY, MAX_PARAMS, "MaxParams", maxParams);
	REGISTER_ATTRIBUTE_ARRAY(Attributes, VAR_TYPE_SHORT_ARRAY, MAX_STATS, "Stats", stats);
	REGISTER_ATTRIBUTE_ARRAY(Attributes, VAR_TYPE_BYTE_ARRAY, MAX_STATUS, "StatusAtk", statusAttack);
	REGISTER_ATTRIBUTE_ARRAY(Attributes, VAR_TYPE_BYTE_ARRAY, MAX_STATUS, "StatusDef", statusDefense);
	*/
}


void Attributes::Serialize( AttributeWriter* f )
{
	//SERIALIZE_OBJECT_ATTRIBUTES_XML(this, f);

	f->WriteIntArrayElement("MaxParams", &maxParams[0], MAX_PARAMS);
	f->WriteShortArrayElement("Stats", &stats[0], MAX_STATS);
	f->WriteByteArrayElement("StatusAtk", (u8*)&statusAttack[0], MAX_STATUS);
	f->WriteByteArrayElement("StatusDef", (u8*)&statusDefense[0], MAX_STATUS);

	/*
	f->BeginNode("MaxParams");
	f->WriteBlock(&maxParams[0], MAX_PARAMS);
	f->EndNode();

	f->BeginNode("Stats");
	f->WriteBlock(&stats[0], MAX_STATS);
	f->EndNode();

	//f->BeginNode("ElementalDef");
	//f->WriteBlock((u8*)&elementalDefense[0], MAX_ELEMENTS);
	//f->EndNode();

	f->BeginNode("StatusAtk");
	f->WriteBlock((u8*)&statusAttack[0], MAX_STATUS);
	f->EndNode();

	f->BeginNode("StatusDef");
	f->WriteBlock((u8*)&statusDefense[0], MAX_STATUS);
	f->EndNode();
	*/

	//flags.Serialize(xml);

}


void Attributes::Deserialize( AttributeReader* f )
{
	//DESERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);

	f->ReadIntArrayElement("MaxParams", &maxParams[0], MAX_PARAMS);
	f->ReadShortArrayElement("Stats", &stats[0], MAX_STATS);
	f->ReadByteArrayElement("StatusAtk", (u8*)&statusAttack[0], MAX_STATUS);
	f->ReadByteArrayElement("StatusDef", (u8*)&statusDefense[0], MAX_STATUS);

/*
	if( f->FirstChild("MaxParams") )
	{
		f->ReadIntArray(&maxParams[0], MAX_PARAMS);
		f->SetToParent();
	}

	if( f->FirstChild("Stats") )
	{
		f->ReadBlock(&stats[0], MAX_STATS);
		f->SetToParent();
	}

	if( f->FirstChild("ElementalDef") )
	{
		f->ReadBlock((u8*)&elementalDefense[0], MAX_ELEMENTS);
		f->SetToParent();
	}

	if( f->FirstChild("StatusAtk") )
	{
		f->ReadBlock((u8*)&statusAttack[0], MAX_STATUS);
		f->SetToParent();
	}

	if( f->FirstChild("StatusDef") )
	{
		f->ReadBlock((u8*)&statusDefense[0], MAX_STATUS);
		f->SetToParent();
	}
*/
	//flags.Deserialize(xml);

}


