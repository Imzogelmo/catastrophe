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

#include <Engine/Graphics/Sprite.h>
#include "Entity.h"
#include "Collision/CollisionFilter.h"


//todo; figure out what we need for entities; scripts, characters, objects...
class Object : public Entity
{
public:
	Vector2	pos, speed;
	Rectf	hitbox;
	CollisionFilter	filter;
	AnimatedSprite	sprite;

	//Object() : Entity(TypeObject)
	//{}

	virtual void Update()
	{
		pos += speed;
	}

	virtual void Render() {}

	inline Rectf GetBoundingRect()
	{
		return hitbox + pos;
	}

};




