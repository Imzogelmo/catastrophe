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

#include <fc/vector.h>
#include "Screen.h"



class ScreenManager
{
public:
	typedef fc::vector<Screen*> vec_type;

	ScreenManager();

	void Clear();
	void Update();
	void Render();

	Screen* GetTop() const;
	Screen* GetActive() const;
	bool IsEmpty() const;

	void Add( Screen* screen );
	//void Exit( Screen* screen );
	void Remove( Screen* screen );

private:
	vec_type		m_screens;

	//vec_type		m_queue;

};

