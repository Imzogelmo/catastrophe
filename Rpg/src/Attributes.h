
#pragma once

#include "Common.h"
#include "FixedAttributeArray.h"


#define MAX_ATTRIBUTES	32
#define MAX_ELEMENTS	32
#define MAX_STATUS		32

typedef FixedAttributeArray<int, MAX_ATTRIBUTES>	StatisticsValueArrayType;
typedef FixedAttributeArray<short, MAX_ELEMENTS>	ElementalArrayType;
typedef FixedAttributeArray<short, MAX_STATUS>		StatusArrayType;


struct Attributes
{
	typedef Attributes			this_type;

	StatisticsValueArrayType	attributes;
	ElementalArrayType			elements;
	StatusArrayType				status;

	//aggregate type

	this_type operator +(const this_type& rhs)
	{
		this_type ret;
		ret.attributes = attributes + rhs.attributes;
		ret.elements = elements + rhs.elements;
		ret.status = status + rhs.status;

		return ret;
	}

	this_type operator -(const this_type& rhs)
	{
		this_type ret;
		ret.attributes = attributes - rhs.attributes;
		ret.elements = elements - rhs.elements;
		ret.status = status - rhs.status;

		return ret;
	}

	this_type &operator +=(const this_type& rhs)
	{
		attributes += rhs.attributes;
		elements += rhs.elements;
		status += rhs.status;

		return *this;
	}

	this_type &operator -=(const this_type& rhs)
	{
		attributes -= rhs.attributes;
		elements -= rhs.elements;
		status -= rhs.status;

		return *this;
	}

	void ApplyPercentageModifier(const this_type& modifier);
	void ApplyMin(const this_type& value);
	void ApplyMax(const this_type& value);
	void Clamp(const this_type& min, const this_type& max);

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};


