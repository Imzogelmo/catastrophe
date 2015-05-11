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

#include "RpgCommon.h"
#include "Attributes.h"
#include "ItemDropSet.h"
#include "Factor.h"

#include "Catastrophe/Core/Containers/String.h"
#include "Catastrophe/Core/Containers/StaticString.h"



struct RPG_API MonsterData
{
	StaticString<32>	name;
	StaticString<32>	script;
	String				description;

	u16			id;
	u16			portraitId;
	u16			mapSpritesetId;
	u16			battleSpritesetId;
	//u16			backgroundId;

	int				lv;
	int				exp;
	int				gold;
	Attributes		attributes;
	//FactorSet		factors;
	FixedFactorList	factors;
	ItemDropSet		itemDropset;
	u32				familyFlags;

	MonsterData();

	static void RegisterObject();

	void Serialize( AttributeWriter* f );
	void Deserialize( AttributeReader* f );

	int GetMemoryUsage() const;

};


typedef MonsterData Monster; //just in case it gets changed...again..
