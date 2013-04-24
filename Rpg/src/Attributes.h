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

#include "Common.h"
#include "Defs.h"
#include "FixedAttributeArray.h"


typedef FixedAttributeArray<int, MAX_STATS>			StatisticsValueArrayType;
typedef FixedAttributeArray<short, MAX_ELEMENTS>	ElementalArrayType;
typedef FixedAttributeArray<ubyte, MAX_STATUS>		StatusArrayType;
typedef FixedAttributeArray<short, MAX_MISC>		MiscArrayType;


struct RPG_API Attributes
{
	typedef Attributes			this_type;

	StatisticsValueArrayType	stats;
	//ElementalArrayType			elements;
	StatusArrayType				status_atk;
	StatusArrayType				status_def;
	MiscArrayType				misc;

	//aggregate type

	this_type operator +(const this_type& rhs) const;
	this_type operator -(const this_type& rhs) const;
	this_type &operator +=(const this_type& rhs);
	this_type &operator -=(const this_type& rhs);


/*
	void ApplyPercentageModifier(const this_type& modifier);
	void Clamp(const this_type& min, const this_type& max);
*/
	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};

