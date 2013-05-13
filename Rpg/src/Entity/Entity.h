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

#include <Catastrophe/Math/Vector2.h>
#include <Catastrophe/Math/Rectf.h>

#include "Common.h"
#include "Collision/CollisionFilter.h"


enum EntityType
{
	EntityType_Entity, //null
	EntityType_ScriptEntity, //null
	EntityType_Object = 0x01,
	EntityType_Character = 0x10,
	EntityType_PlayerCharacter = EntityType_Character | 0x20,
	EntityType_MonsterCharacter = EntityType_Character | 0x40
	EntityType_MonsterCharacter = EntityType_Character | 0x40
	EntityType_Combatant = 0x10,

};


class Entity
{
public:
	enum EntityType
	{
		TypeEntity, //null
		TypeObject = 0x01,
		TypeCharacter = 0x10,
		TypePlayerCharacter = TypeCharacter | 0x20,
		TypeMonsterCharacter = TypeCharacter | 0x40
	};

	const int type;

	Vector2	pos;
	Rectf	hitbox;
	CollisionFilter	filter;
	bool	alive;

	Entity( EntityType derivedType );
	virtual ~Entity()
	{}

	virtual void Update() {}
	virtual void Render() {}


	inline bool CanCollide( Entity* entity )
	{
		return filter.CanCollide(entity->filter);
	}

	inline bool CollidesWith( Entity* entity )
	{
		bool intersects = GetBoundingRect().Intersects(entity->GetBoundingRect());
		return intersects;
	}

	inline Rectf GetBoundingRect()
	{
		return hitbox + pos;
	}

};


