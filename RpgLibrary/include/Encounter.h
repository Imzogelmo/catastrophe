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

#include <fc/fixed_vector.h>

#include "RpgCommon.h"


struct RPG_API EncounterData
{
	int	troop_id;
	int	rate;
	int	max_rate;

	EncounterData( int monsterPartyIndex = 0, int encounterRate = 0, int maxRate = 100 );

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );
};


/**
 * An encounter "group" simply consists of a collection of possible
 * random monster encounters within a given map region.
 */
struct RPG_API EncounterGroup 
{
	typedef fc::fixed_vector<EncounterData, 8>	vec_type;

	fc::string	name;
	vec_type	encounters;

	EncounterGroup();

	void SerializeXml( XmlWriter* xml );
	void DeserializeXml( XmlReader* xml );
};

