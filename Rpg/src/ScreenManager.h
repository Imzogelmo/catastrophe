
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

