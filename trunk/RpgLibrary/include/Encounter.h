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

#include "Catastrophe/Core/Containers/Vector.h"

#include "RpgCommon.h"


struct RPG_API EncounterData
{
	u16	troopId;
	u8	rate;
	u8	maxRate;

	EncounterData( u16 monsterTroopIndex = 0, u8 encounterRate = 0, u8 maxRate = 128 );

	//simply to ensure data is sane before saving.
	void Validate();

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );
};


/**
 * An encounter "group" simply consists of a collection of possible
 * random monster encounters within a given map region.
 */
struct RPG_API EncounterGroup 
{
	typedef Vector<EncounterData>	VectorType;

	String		name;
	VectorType	encounters;
	u16 id;

	EncounterGroup();

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

	int GetMemoryUsage() const;
};

