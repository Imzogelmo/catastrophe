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

#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/IO/XmlReader.h>
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
						(index, value, MAX_PARAM_VALUE, -MAX_PARAM_VALUE);
			}
			break;
			case Stat:
			{
				if( index < MAX_STATS )
					attributes.stats.AddAssignIndex<int>
						(index, value, MAX_STAT_VALUE, -MAX_STAT_VALUE);
			}
			break;
			case StatusAtk:
			{
				if( index < MAX_STATUS )
					attributes.status_atk.AddAssignIndex<int>
						(index, value, MAX_STATUS_VALUE, -MAX_STATUS_VALUE);
			}
			break;
			case StatusDef:
			{
				if( index < MAX_STATUS )
					attributes.status_atk.AddAssignIndex<int>
						(index, value, MAX_STATUS_VALUE, -MAX_STATUS_VALUE);
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
						(index, value, MAX_PARAM_VALUE, -MAX_PARAM_VALUE);
			}
			break;
			case Stat:
			{
				if( index < MAX_STATS )
					attributes.max_params.ApplyPercentageModifierToIndex<int>
						(index, value, MAX_STAT_VALUE, -MAX_STAT_VALUE);
			}
			break;
			case StatusAtk:
			{
				if( index < MAX_STATUS )
					attributes.max_params.ApplyPercentageModifierToIndex<int>
						(index, value, MAX_STATUS_VALUE, -MAX_STATUS_VALUE);
			}
			break;
			case StatusDef:
			{
				if( index < MAX_STATUS )
					attributes.max_params.ApplyPercentageModifierToIndex<int>
						(index, value, MAX_STATUS_VALUE, -MAX_STATUS_VALUE);
			}
			break;
		}
	}
}


void Modifier::SerializeXml( XmlWriter* xml )
{
	xml->SetInt("value", value);
	xml->SetShort("index", index);
	xml->SetByte("target", target);
	xml->SetByte("type", type);
}


void Modifier::DeserializeXml( XmlReader* xml )
{
	value = xml->GetInt("value");
	index = xml->GetInt("index");
	target = xml->GetInt("target");
	type = xml->GetInt("type");
}

