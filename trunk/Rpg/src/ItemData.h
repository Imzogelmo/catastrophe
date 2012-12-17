
#pragma once

#include <Catastrophe/Graphics/Sprite.h>

#include "Common.h"
#include "AttributeData.h"
#include "DataList.h"


struct ItemData : public AttributeData
{
	typedef AttributeData	base_type;

	Flags32			usage_flags;

	//int sprite_index;
	AnimatedSprite	sprite; //icon?

	ItemData() : base_type()
	{}

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};



class ItemList : public DataList<ItemData>
{
public:
	typedef DataList<ItemData>	base_type;

	ItemList() : base_type()
	{}

	ItemData& GetItem( size_t index ) { return base_type::operator [](index);  }
	const ItemData& GetItem( size_t index ) const { return base_type::operator [](index);  }

	bool SerializeXml( const fc::string& filename );
	bool DeserializeXml( const fc::string& filename );

};

