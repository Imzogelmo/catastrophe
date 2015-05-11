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
					attributes.maxParams.AddAssignIndex<int>
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
					attributes.elementalDefense.AddAssignIndex<int>
						(index, value, -MAX_ELEMENT_VALUE, MAX_ELEMENT_VALUE);
			}
			break;
			case StatusAtk:
			{
				if( index < MAX_STATUS )
					attributes.statusAttack.AddAssignIndex<int>
						(index, value, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
			}
			break;
			case StatusDef:
			{
				if( index < MAX_STATUS )
					attributes.statusDefense.AddAssignIndex<int>
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
					attributes.maxParams.ApplyPercentageModifierToIndex<int>
						(index, value, -MAX_PARAM_VALUE, MAX_PARAM_VALUE);
			}
			break;
			case Stat:
			{
				if( index < MAX_STATS )
					attributes.stats.ApplyPercentageModifierToIndex<int>
						(index, value, -MAX_STAT_VALUE, MAX_STAT_VALUE);
			}
			break;
			case ElementalDef:
			{
				if( index < MAX_ELEMENTS )
					attributes.elementalDefense.ApplyPercentageModifierToIndex<int>
						(index, value, -MAX_ELEMENT_VALUE, MAX_ELEMENT_VALUE);
			}
			break;
			case StatusAtk:
			{
				if( index < MAX_STATUS )
					attributes.statusAttack.ApplyPercentageModifierToIndex<int>
						(index, value, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
			}
			break;
			case StatusDef:
			{
				if( index < MAX_STATUS )
					attributes.statusDefense.ApplyPercentageModifierToIndex<int>
						(index, value, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
			}
			break;
		}
	}
}


void Modifier::Serialize( AttributeWriter* f )
{
	f->SetAttribute("value", value);
	f->SetAttribute("index", index);
	f->SetAttribute("target", target);
	f->SetAttribute("type", type);
}


void Modifier::Deserialize( AttributeReader* f )
{
	f->GetAttribute("value", value);
	f->GetAttribute("index", index);
	f->GetAttribute("target", target);
	f->GetAttribute("type", type);
}

