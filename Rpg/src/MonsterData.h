
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



struct MonsterGroupData
{
	int		monster_index;
	int		min;
	int		max;

	MonsterGroupData(int monsterIndex = 0, int minNum = 1, int maxNum = 1) :
		monster_index(monsterIndex),
		min(minNum),
		max(maxNum)
	{}

	//simply to ensure data is sane before saving.
	void Validate();

	void SerializeXml(XmlWriter* xml);
	void DeserializeXml(XmlReader* xml);

};



/**
 * A Monster Party is simply a collection of Monster Groups
 * together which form a complete party.
 */
class MonsterPartyData
{
public:
	typedef fc::vector<MonsterGroupData> vec_type;

	MonsterPartyData();

	bool Empty() const { return m_groups.empty(); }
	size_t NumGroups() const { return m_groups.size(); }

	void AddGroup( const MonsterGroupData& group );
	void RemoveGroup(size_t index);

	MonsterGroupData& GetGroup(size_t index);
	const MonsterGroupData& GetGroup(size_t index) const;

	//direct access is useful for editor functions
	vec_type& GetGroups() { return m_groups; }
	const vec_type& GetGroups() const { return m_groups; }
	
	void SerializeXml(XmlWriter* xml);
	void DeserializeXml(XmlReader* xml);

protected:
	vec_type	m_groups;
};



/**
 * A collection of all stored MonsterData objects.
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


