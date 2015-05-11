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

#include "RpgCommon.h"
#include "FixedAttributeTypeArray.h"
#include "AttributeFlags.h"


typedef FixedAttributeTypeArray<s32, MAX_PARAMS>	MaxParamValueArrayType;
typedef FixedAttributeTypeArray<s16, MAX_STATS>		StatisticsValueArrayType;
//typedef FixedAttributeTypeArray<s16, MAX_ELEMENTS>	ElementalArrayType;
//typedef FixedAttributeTypeArray<s8, MAX_STATUS>		StatusArrayType;

typedef FixedAttributeTypeArray<s8, MAX_ELEMENTS>	ElementalArrayType;
typedef FixedAttributeTypeArray<s8, MAX_STATS>		StatusArrayType;

//typedef FixedAttributeTypeArray<s16, MAX_MISC>	MiscArrayType;


struct RPG_API Attributes
{
	typedef Attributes			this_type;

	MaxParamValueArrayType		maxParams;
	StatisticsValueArrayType	stats;
	ElementalArrayType			elementalDefense;
	StatusArrayType				statusAttack;
	StatusArrayType				statusDefense;
	//MiscArrayType				misc;
	AttributeFlags				flags;

	//aggregate type

	this_type operator +(const this_type& rhs) const;
	this_type operator -(const this_type& rhs) const;
	this_type &operator +=(const this_type& rhs);
	this_type &operator -=(const this_type& rhs);


	inline void SetMaxParam( u32 index, int value )
	{
		maxParams[index] = Clamp<int>
			(value, -MAX_PARAM_VALUE, MAX_PARAM_VALUE);
	}

	inline void SetStat( u32 index, s16 value )
	{
		stats[index] = (s16)Clamp<int>
			(value, -MAX_STAT_VALUE, MAX_STAT_VALUE);
	}

	inline void SetElementalDef( u32 index, s16 value )
	{
		elementalDefense[index] = (char)Clamp<int>
			(value, -MAX_ELEMENT_VALUE, MAX_ELEMENT_VALUE);
	}

	inline void SetStatusAtk( u32 index, int value )
	{
		statusAttack[index] = (char)Clamp<int>
			(value, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
	}

	inline void SetStatusDef( u32 index, int value )
	{
		statusDefense[index] = (char)Clamp<int>
			(value, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
	}


/*
	void ApplyPercentageModifier(const this_type& modifier);
	void Clamp(const this_type& min, const this_type& max);
*/

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

};


