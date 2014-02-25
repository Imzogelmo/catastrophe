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
#include "Modifier.h"


Modifier::Modifier() :
	value(0),
	index(0),
	target(0),
	type(0)
{
}


Attributes Modifier::ConvertToAttributes() const
{
	Attributes attributes;
	ApplyToAttributes(attributes);
	return attributes;
}


void Modifier::ApplyToAttributes( Attributes& attributes ) const
{
	if( type == BonusMalus )
	{
		switch(target)
		{
			case MaxParam:
			{
				if( index < MAX_PARAMS )
					attributes.max_params.AddAssignIndex<int>
						(index, value, -MAX_PARAM_VALUE, MAX_PARAM_VALUE);
			}
			break;
			case Stat:
			{
				if( index < MAX_STATS )
					attributes.stats.AddAssignIndex<int>
						(index, value, -MAX_STAT_VALUE, MAX_STAT_VALUE);
			}
			break;
			case ElementalDef:
			{
				if( index < MAX_ELEMENTS )
					attributes.elemental_def.AddAssignIndex<int>
						(index, value, -MAX_ELEMENT_VALUE, MAX_ELEMENT_VALUE);
			}
			break;
			case StatusAtk:
			{
				if( index < MAX_STATUS )
					attributes.status_atk.AddAssignIndex<int>
						(index, value, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
			}
			break;
			case StatusDef:
			{
				if( index < MAX_STATUS )
					attributes.status_atk.AddAssignIndex<int>
						(index, value, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
			}
			break;
		}
	}

	else if( type == Multiplier )
	{
		switch(target)
		{
			case MaxParam:
			{
				if( index < MAX_PARAMS )
					attributes.max_params.ApplyPercentageModifierToIndex<int>
						(index, value, -MAX_PARAM_VALUE, MAX_PARAM_VALUE);
			}
			break;
			case Stat:
			{
				if( index < MAX_STATS )
					attributes.max_params.ApplyPercentageModifierToIndex<int>
						(index, value, -MAX_STAT_VALUE, MAX_STAT_VALUE);
			}
			break;
			case ElementalDef:
			{
				if( index < MAX_ELEMENTS )
					attributes.elemental_def.ApplyPercentageModifierToIndex<int>
						(index, value, -MAX_ELEMENT_VALUE, MAX_ELEMENT_VALUE);
			}
			break;
			case StatusAtk:
			{
				if( index < MAX_STATUS )
					attributes.max_params.ApplyPercentageModifierToIndex<int>
						(index, value, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
			}
			break;
			case StatusDef:
			{
				if( index < MAX_STATUS )
					attributes.max_params.ApplyPercentageModifierToIndex<int>
						(index, value, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
			}
			break;
		}
	}
}


void Modifier::SerializeXml( AttributeWriter* f )
{
	f->SetInt("value", value);
	f->SetShort("index", index);
	f->SetByte("target", target);
	f->SetByte("type", type);
}


void Modifier::DeserializeXml( AttributeReader* f )
{
	value = f->GetInt("value");
	index = f->GetShort("index");
	target = f->GetInt("target");
	type = f->GetInt("type");
}

