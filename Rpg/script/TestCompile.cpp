
#pragma once

/*
#include "defines.h"
#include "script_classes.h"
#include "class_namespaces.h"
#include "keycodes.h"
#include "opengl.h"
#include "color.h"
*/

//include scripts here

//#define assert(x) __assert((x), #x, __FILE__, __LINE__)
#define assert(x)



//#include "main.cpp"
//#include "test.cpp"


void test_keyboard()
{
	keyboard key;
	key = input::keyboard;
	bool p = key.pressed[0];
	bool r = key.released[0];
	bool d = key.down[0];
	int frames = key[0];
	key = keyboard(); // test assignment

	if( input::key.pressed[32] ||
		input::key.released[32] ||
		input::key.down[32] ||
		input::key[32] != 0 )
	{
		input::key.annul();
	}
}

void test_mouse()
{
	mouse m;
	m = input::mouse;

	point pos = m.pos;
	point prev = m.previous;
	int x = m.x;
	int y = m.y;
	assert(pos.x == x);
	assert(pos.y == y);

	bool p = m.pressed[0];
	bool r = m.released[0];
	int frames = m.button[0];
	m = mouse(); // test assignment

}

void test_joystick()
{
	joystick joy;
	joy = input::get_joystick(0);
	int n = joy.num_hats + joy.num_buttons + joy.num_axes;
	if( joy.pressed[0] || joy.released[0] ) {}
	joy.button[0];
	//joy.frames[0];

	//input::joystick[0].down[6];


}


class Main
{
	//Test test;

	point point;

	Main()
	{
/*
		int id = game::load_texture("null");
		texture tex = game::texture[id];
		id = game::load_font("null", 32);
		font fnt = game::font[id];
*/
		int id = game.load_texture("null");
		texture tex = game::get_texture(id);
		id = game::load_font("null", 32);
		font fnt = game::get_font(id);

		point a();
		point b(0,0);
		point c = a + b;

		this.point -= c * b * a;
		//test.Init();

		array<int> arr(32);
		arr.at(0) = 12;
		int fhu = arr.at(0);


		//joystick@ joyh = null;
		joystick joy;
		int yui = joy.button[0];

		//wwwwait(0);
		joystick joy2 = joy;
		int b6 = joy2.button[6];
		//mouse m = gat_mouse();

		test_mouse();
		test_keyboard();
		test_joystick();
	}

	void run()
	{
		//test.Update();
	}

};













