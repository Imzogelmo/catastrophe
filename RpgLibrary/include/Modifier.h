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

#pragma once

#include <fc/string.h>

#include "RpgCommon.h"
#include "Attributes.h"


struct Modifier
{
	enum Target
	{
		MaxParam,
		Stat,
		ElementalDef,
		StatusAtk,
		StatusDef
	};

	enum Type
	{
		BonusMalus,
		Multiplier
	};

	int		value;
	short	index;
	byte	target;
	byte	type;

	Modifier();

	Attributes ConvertToAttributes() const;
	void ApplyToAttributes( Attributes& attributes ) const;

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );
};

