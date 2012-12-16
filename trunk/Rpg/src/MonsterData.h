
#pragma once

#include <fc/vector.h>
#include "Common.h"
#include "Attributes.h"
#include "AttributeFlags.h"
#include "ItemDrop.h"
#include "DataList.h"



struct MonsterData
{
	fc::string		name;
	fc::string		script;
	fc::string		description;
	Attributes		attributes;
	AttributeFlags	attribute_flags;

	//int sprite_index;
	//Sprite			sprite;
	ItemDropSet		item_dropset;

	MonsterData(const fc::string& name = "", const fc::string& scriptName = "", const fc::string& description = "") :
		name(name), 
		script(scriptName),
		description(description)
	{}

	Attributes& GetAttributes() { return attributes; }
	AttributeFlags& GetAttributeFlags() { return attribute_flags; }

	void SerializeXml(XmlWriter* xml);
	void DeserializeXml(XmlReader* xml);

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


