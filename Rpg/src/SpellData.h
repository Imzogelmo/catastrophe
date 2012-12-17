
#pragma once

#include <fc/string.h>

#include "Common.h"
#include "AttributeData.h"
#include "DataList.h"


struct SpellData : public AttributeData
{
	typedef AttributeData	base_type;

	//effect..

	SpellData() : base_type()
	{}

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};



class SpellList : public DataList<SpellData>
{
public:
	typedef DataList<SpellData>	base_type;

	SpellList() : base_type()
	{}

	SpellData& GetSpell( size_t index ) { return base_type::operator [](index);  }
	const SpellData& GetSpell( size_t index ) const { return base_type::operator [](index);  }

	bool SerializeXml( const fc::string& filename );
	bool DeserializeXml( const fc::string& filename );

};

