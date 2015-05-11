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

#include "Catastrophe/Core/Containers/String.h"
//#include "Catastrophe/Core/Containers/Vector.h"

#include "RpgCommon.h"


struct RPG_API CharacterData
{
	StaticString<32>	name;
	StaticString<32>	script;
	String				description;

	u16				id;
	u8				raceId;
	u8				classId;
	Gender			gender;
	Handedness		handedness;
	Alignment		alignment;

	u16				portraitId;
	u16				mapSpritesetId;
	u16				battleSpritesetId;
	u32				flags; //todo

	int				startingLv;
	int				startingExp;
	int				startingGold;
	Attributes		attributes;

	//levelupLearning { id, lv } ..?
	//Vector<int>		spells;

	CharacterData();

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

	int GetMemoryUsage() const;

};

