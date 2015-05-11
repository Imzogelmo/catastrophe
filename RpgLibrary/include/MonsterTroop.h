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

#include "Catastrophe/Core/Containers/StaticVector.h"
#include "Catastrophe/Core/Containers/String.h"

#include "RpgCommon.h"


/*
 * @MonsterGroup
 * class that represents data on how to instantiate
 * monsters.
 */
struct RPG_API MonsterGroup
{
	/// The id of the monster in this Group
	u16	monsterId;

	/// The minimum number of monsters that may appear in this group.
	u8	minimum;

	/// The maximum number of monsters that may appear in this group.
	u8	maximum;

	MonsterGroup();
	MonsterGroup( u16 monsterId, u8 minNum, u8 maxNum );

	void Validate();
	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

};

CE_MAKE_TRAIT(MonsterGroup, is_pod);



/*
 * @MonsterTroop
 * class that holds an array of monster groups.
 */
struct RPG_API MonsterTroop
{
	typedef StaticVector<MonsterGroup, 8> vec_type;

	String	name; //this is editor only....
	vec_type	groups;
	u16			id;
	u16			formationId;
	u8			maxMonsters;

	MonsterTroop();

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

	int GetMemoryUsage() const;

};

//MAKE_TRAIT(MonsterTroop, is_pod);



