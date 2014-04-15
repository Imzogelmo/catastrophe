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


#include <Catastrophe/Math/Vector2.h>
#include <Catastrophe/Math/Math.h>

#include "Script/MonoEngineBinding.h"


void MonoEngineBinding::Vector2_Rotate( Vector2* self, float angle )
{
	self->Rotate(angle);
}


void MonoEngineBinding::Vector2_RotateOrigin( Vector2* self, float angle, Vector2 origin )
{
	self->Rotate(angle, origin);
}


Vector2 MonoEngineBinding::Vector2_Rotated( Vector2* self, float angle )
{
	return self->Rotated(angle);
}


Vector2 MonoEngineBinding::Vector2_RotatedOrigin( Vector2* self, float angle, Vector2 origin )
{
	return self->Rotated(angle, origin);
}


void MonoEngineBinding::BindVector2()
{
	SetNamespace("CatastropheEngine.Vector2::");
	AddInternalCall("Rotate(float)", Vector2_Rotate);
	AddInternalCall("Rotate(float, Vector2)", Vector2_RotateOrigin);
	AddInternalCall("Rotated(float)", Vector2_Rotated);
	AddInternalCall("Rotated(float, Vector2)", Vector2_RotatedOrigin);
}

