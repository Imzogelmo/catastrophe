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

#include "Screen.h"
#include "Camera.h"


/*
 * GameScreen
 * base screen class for screens which can contain
 * scripts, camera movement, collisions, sprites, 
 * and other normal game mechanics;
 */
class GameScreen : public Screen
{
public:
	GameScreen();
	virtual ~GameScreen()
	{}
	
	virtual void Update();
	virtual void Render();


protected:

	Camera	m_camera;
	//list of	m_entities;
	//other stuff.

};

