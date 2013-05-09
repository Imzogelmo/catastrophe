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

#include <Catastrophe/IO/XmlWriter.h>
#include <Catastrophe/IO/XmlReader.h>
#include <Catastrophe/Math/Point.h>
#include <Catastrophe/Math/Rect.h>
#include <Catastrophe/Graphics/SpriteAnimation.h>
#include <Catastrophe/Graphics/AnimatedSpriteSet.h>
#include <Catastrophe/Graphics/Sprite.h>
#include <fc/math.h>

#include "Serialization.h"
#include "TextureManager.h"

#include "SerializeObject.inl"
#include "DeserializeObject.inl"



void test()
{
	Point p;
	SerializeObject(0,p);
	SerializeObject("test",0,p);

	DeserializeObject(0,p);
	DeserializeObject("test",0,p);

	Rect r;
	SerializeObject(0,r);
	SerializeObject("test",0,r);

	DeserializeObject(0,r);
	DeserializeObject("test",0,r);


}