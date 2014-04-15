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


#include <mono/metadata/object.h>
#include <mono/metadata/loader.h>

#include <fc/math.h>
#include <fc/rand.h>
#include <Catastrophe/Math/Vector2.h>
#include <Catastrophe/Math/Vector3.h>
#include <Catastrophe/Math/Math.h>

#include "Script/MonoEngineBinding.h"


float MonoEngineBinding::Collision_DistanceToLineSegment2D( Vector2 a, Vector2 b, Vector2 point )
{
	return Math::DistancetoLineSegment(a, b, point);
}


float MonoEngineBinding::Collision_DistanceToLineSegment3D( Vector3 a, Vector3 b, Vector3 point )
{
	return Math::DistancetoLineSegment(a, b, point);
}


void MonoEngineBinding::BindCollision()
{
	SetNamespace("CatastropheEngine.Collision::");

	AddInternalCall("DistancetoLineSegment(Vector2, Vector2, Vector2)", Collision_DistanceToLineSegment2D);
	AddInternalCall("DistancetoLineSegment(Vector3, Vector3, Vector3)", Collision_DistanceToLineSegment3D);

}

