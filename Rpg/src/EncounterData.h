
#pragma once

#include <fc/vector.h>

#include "Common.h"
#include "DataList.h"


/**
 * EncounterData - holds an ID to a monster party and an encounter rate.
 */
struct EncounterData
{
	int	troop_index;
	int	rate;
	int	max_rate;

	EncounterData( int monsterPartyIndex = 0, int encounterRate = 0, int maxRate = 100 ) :
		troop_index(monsterPartyIndex),
		rate(encounterRate),
		max_rate(maxRate)
	{}

	void SetMonsterTroopIndex( int index ) { troop_index = index; }
	void SetEncounterRate( int encounterRate ) { rate = encounterRate; }
	void SetMaxRate( int rate ) { max_rate = rate; }

	int GetMaxRate() const { return max_rate; }
	int GetEncounterRate() const { return rate; }
	int GetMonsterTroopIndex() const { return troop_index; }

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

};


/**
 * An encounter "group" simply consists of a collection of possible
 * random monster party encounters within a given map region.
 */
class EncounterGroupData 
{
public:
	typedef fc::vector<EncounterData>	vec_type;

	EncounterGroupData( const fc::string& name = "" );

	bool Empty() const { return m_encounters.empty(); }
	size_t Size() const { return m_encounters.size(); }

	void SetName( const fc::string& str ) { m_name = str; }
	void AddEncounter( const EncounterData& data );
	void RemoveEncounter( size_t index );

	const fc::string&		GetName() const { return m_name; }
	EncounterData&			GetEncounter( size_t index );
	const EncounterData&	GetEncounter( size_t index ) const;
	vec_type&				GetEncounters() { return m_encounters; }
	const vec_type&			GetEncounters() const { return m_encounters; }

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );

protected:
	fc::string	m_name;
	vec_type	m_encounters;

};



class EncounterGroupList : public DataList<EncounterGroupData>
{
public:
	typedef DataList<EncounterGroupData>	base_type;

	EncounterGroupList() : base_type()
	{}

	EncounterGroupData& GetEncounterGroup( size_t index ) { return base_type::operator [](index);  }
	const EncounterGroupData& GetEncounterGroup( size_t index ) const { return base_type::operator [](index);  }

	bool SerializeXml( const fc::string& filename );
	bool DeserializeXml( const fc::string& filename );

};
