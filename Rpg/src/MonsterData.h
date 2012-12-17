
#pragma once

#include <fc/vector.h>

#include "Common.h"
#include "AttributeData.h"
#include "ItemDrop.h"
#include "DataList.h"



struct MonsterData : public AttributeData
{
	typedef AttributeData	base_type;

	//int sprite_index;
	//Sprite			sprite;
	ItemDropSet		item_dropset;

	MonsterData() : base_type()
	{}

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};


/*
 * A collection of stored MonsterData objects.
 */
class MonsterList : public DataList<MonsterData>
{
public:
	typedef DataList<MonsterData>	base_type;

	MonsterList() : base_type()
	{}

	MonsterData& GetMonster( size_t index ) { return base_type::operator [](index);  }
	const MonsterData& GetMonster( size_t index ) const { return base_type::operator [](index);  }

	bool SerializeXml( const fc::string& filename );
	bool DeserializeXml( const fc::string& filename );

};


