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

#include <fc/vector.h>
#include <fc/string.h>
#include "Common.h"
#include "DataList.h"


struct MonsterGroupData
{
	int		monster_index;
	int		min;
	int		max;

	MonsterGroupData(int monsterIndex = 0, int minNum = 1, int maxNum = 1) :
		monster_index(monsterIndex), min(minNum), max(maxNum)
	{}

	//simply to ensure data is sane before saving.
	void Validate();

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};


/*
 * A MonsterParty (aka Monster Troop)
 * is simply a collection of Monster Groups.
 */
class MonsterPartyData
{
public:
	typedef fc::vector<MonsterGroupData> vec_type;

	MonsterPartyData();

	size_t NumGroups() const { return m_groups.size(); }
	void AddGroup( const MonsterGroupData& group );
	void RemoveGroup( size_t index );
	void SetName( const fc::string& str ) { m_name = str; }

	const fc::string& GetName() const { return m_name; }
	MonsterGroupData& GetGroup( size_t index );
	const MonsterGroupData& GetGroup( size_t index ) const;
	
	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

protected:
	fc::string	m_name;
	vec_type	m_groups;
};



/*
 * A collection of stored MonsterPartyData objects.
 */
class MonsterPartyList : public DataList<MonsterPartyData>
{
public:
	typedef DataList<MonsterPartyData>	base_type;

	MonsterPartyList() : base_type()
	{}

	MonsterPartyData& GetMonsterParty( size_t index ) { return base_type::operator [](index);  }
	const MonsterPartyData& GetMonsterParty( size_t index ) const { return base_type::operator [](index);  }

	NO_INLINE bool SerializeXml( const fc::string& filename );
	NO_INLINE bool DeserializeXml( const fc::string& filename );

};

