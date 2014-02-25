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
#include "AttributeSerializer.h"


Attributes Attributes::operator +(const Attributes& rhs) const
{
	Attributes ret;

	ret.max_params = max_params + rhs.max_params;
	ret.stats = stats + rhs.stats;
	ret.elemental_def = elemental_def.Add<int>(rhs.elemental_def, -MAX_ELEMENT_VALUE, MAX_ELEMENT_VALUE);
	ret.status_atk = status_atk.Add<int>(rhs.status_atk, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
	ret.status_def = status_def.Add<int>(rhs.status_def, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);

	return ret;
}


Attributes Attributes::operator -(const Attributes& rhs) const
{
	Attributes ret;

	ret.max_params = max_params - rhs.max_params;
	ret.stats = stats - rhs.stats;
	ret.elemental_def = elemental_def.Subtract<int>(rhs.elemental_def, -MAX_ELEMENT_VALUE, MAX_ELEMENT_VALUE);
	ret.status_atk = status_atk.Subtract<int>(rhs.status_atk, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
	ret.status_def = status_def.Subtract<int>(rhs.status_def, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);

	return ret;
}


Attributes& Attributes::operator +=(const Attributes& rhs)
{
	max_params += rhs.max_params;
	stats += rhs.stats;
	elemental_def.AddAssign<int>(rhs.elemental_def, -MAX_ELEMENT_VALUE, MAX_ELEMENT_VALUE);
	status_atk.AddAssign<int>(rhs.status_atk, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
	status_def.AddAssign<int>(rhs.status_def, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);

	flags |= rhs.flags;

	return *this;
}


Attributes& Attributes::operator -=(const Attributes& rhs)
{
	max_params -= rhs.max_params;
	stats -= rhs.stats;
	elemental_def.SubtractAssign<int>(rhs.elemental_def, -MAX_ELEMENT_VALUE, MAX_ELEMENT_VALUE);
	status_atk.SubtractAssign<int>(rhs.status_atk, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
	status_def.SubtractAssign<int>(rhs.status_def, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);

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

void Attributes::RegisterObject()
{
	/*
	REGISTER_ATTRIBUTE_FACTORY_TYPE(Attributes);
	REGISTER_ATTRIBUTE_ARRAY(Attributes, VAR_TYPE_INT_ARRAY, MAX_PARAMS, "MaxParams", max_params);
	REGISTER_ATTRIBUTE_ARRAY(Attributes, VAR_TYPE_SHORT_ARRAY, MAX_STATS, "Stats", stats);
	REGISTER_ATTRIBUTE_ARRAY(Attributes, VAR_TYPE_BYTE_ARRAY, MAX_STATUS, "StatusAtk", status_atk);
	REGISTER_ATTRIBUTE_ARRAY(Attributes, VAR_TYPE_BYTE_ARRAY, MAX_STATUS, "StatusDef", status_def);
	*/
}


void Attributes::SerializeXml( AttributeWriter* f )
{
	//SERIALIZE_OBJECT_ATTRIBUTES_XML(this, f);

	f->WriteIntArrayElement("MaxParams", &max_params[0], MAX_PARAMS);
	f->WriteShortArrayElement("Stats", &stats[0], MAX_STATS);
	f->WriteByteArrayElement("StatusAtk", (byte*)&status_atk[0], MAX_STATUS);
	f->WriteByteArrayElement("StatusDef", (byte*)&status_def[0], MAX_STATUS);

	/*
	f->BeginNode("MaxParams");
	f->WriteBlock(&max_params[0], MAX_PARAMS);
	f->EndNode();

	f->BeginNode("Stats");
	f->WriteBlock(&stats[0], MAX_STATS);
	f->EndNode();

	//f->BeginNode("ElementalDef");
	//f->WriteBlock((ubyte*)&elemental_def[0], MAX_ELEMENTS);
	//f->EndNode();

	f->BeginNode("StatusAtk");
	f->WriteBlock((ubyte*)&status_atk[0], MAX_STATUS);
	f->EndNode();

	f->BeginNode("StatusDef");
	f->WriteBlock((ubyte*)&status_def[0], MAX_STATUS);
	f->EndNode();
	*/

	//flags.SerializeXml(xml);

}


void Attributes::DeserializeXml( AttributeReader* f )
{
	//DESERIALIZE_OBJECT_ATTRIBUTES_XML(this, xml);

	f->ReadIntArrayElement("MaxParams", &max_params[0], MAX_PARAMS);
	f->ReadShortArrayElement("Stats", &stats[0], MAX_STATS);
	f->ReadByteArrayElement("StatusAtk", (byte*)&status_atk[0], MAX_STATUS);
	f->ReadByteArrayElement("StatusDef", (byte*)&status_def[0], MAX_STATUS);

/*
	if( f->FirstChild("MaxParams") )
	{
		f->ReadIntArray(&max_params[0], MAX_PARAMS);
		f->SetToParent();
	}

	if( f->FirstChild("Stats") )
	{
		f->ReadBlock(&stats[0], MAX_STATS);
		f->SetToParent();
	}

	if( f->FirstChild("ElementalDef") )
	{
		f->ReadBlock((ubyte*)&elemental_def[0], MAX_ELEMENTS);
		f->SetToParent();
	}

	if( f->FirstChild("StatusAtk") )
	{
		f->ReadBlock((ubyte*)&status_atk[0], MAX_STATUS);
		f->SetToParent();
	}

	if( f->FirstChild("StatusDef") )
	{
		f->ReadBlock((ubyte*)&status_def[0], MAX_STATUS);
		f->SetToParent();
	}
*/
	//flags.DeserializeXml(xml);

}


