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


class Entity
{
public:
	enum EntityType
	{
		TypeEntity, //null
		TypeObject
	};

	//this is much faster than dynamic_cast.
	const int type;

	Entity( EntityType derivedType = TypeEntity ) : type(derivedType) {}
	virtual ~Entity()
	{}

	virtual void Update() = 0;
	virtual void Render() = 0;

};


