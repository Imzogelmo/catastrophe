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
#include "FixedAttributeArray.h"
#include "AttributeFlags.h"


typedef FixedAttributeArray<int, MAX_PARAMS>		ParamValueArrayType;
typedef FixedAttributeArray<short, MAX_STATS>		StatisticsValueArrayType;
typedef FixedAttributeArray<short, MAX_ELEMENTS>	ElementalArrayType;
typedef FixedAttributeArray<char, MAX_STATUS>		StatusArrayType;
//typedef FixedAttributeArray<short, MAX_MISC>		MiscArrayType;


struct RPG_API Attributes
{
	typedef Attributes			this_type;

	ParamValueArrayType			max_params;
	StatisticsValueArrayType	stats;
	ElementalArrayType			elemental_def;
	StatusArrayType				status_atk;
	StatusArrayType				status_def;
	//MiscArrayType				misc;
	AttributeFlags				flags;

	//aggregate type

	this_type operator +(const this_type& rhs) const;
	this_type operator -(const this_type& rhs) const;
	this_type &operator +=(const this_type& rhs);
	this_type &operator -=(const this_type& rhs);


	inline void SetMaxParam( size_t index, int value )
	{
		max_params[index] = fc::clamp<int>
			(value, -MAX_PARAM_VALUE, MAX_PARAM_VALUE);
	}

	inline void SetStat( size_t index, int value )
	{
		stats[index] = (short)fc::clamp<int>
			(value, -MAX_STAT_VALUE, MAX_STAT_VALUE);
	}

	inline void SetElementalDef( size_t index, short value )
	{
		elemental_def[index] = (char)fc::clamp<int>
			(value, -MAX_ELEMENT_VALUE, MAX_ELEMENT_VALUE);
	}

	inline void SetStatusAtk( size_t index, int value )
	{
		status_atk[index] = (char)fc::clamp<int>
			(value, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
	}

	inline void SetStatusDef( size_t index, int value )
	{
		status_def[index] = (char)fc::clamp<int>
			(value, -MAX_STATUS_VALUE, MAX_STATUS_VALUE);
	}


/*
	void ApplyPercentageModifier(const this_type& modifier);
	void Clamp(const this_type& min, const this_type& max);
*/
	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};


