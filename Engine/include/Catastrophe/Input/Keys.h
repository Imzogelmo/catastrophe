// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

CE_NAMESPACE_BEGIN


//namespace Key
enum Keys
{
	KEY_A					= 'A',
	KEY_B					= 'B',
	KEY_C					= 'C',
	KEY_D					= 'D',
	KEY_E					= 'E',
	KEY_F					= 'F',
	KEY_G					= 'G',
	KEY_H					= 'H',
	KEY_I					= 'I',
	KEY_J					= 'J',
	KEY_K					= 'K',
	KEY_L					= 'L',
	KEY_M					= 'M',
	KEY_N					= 'N',
	KEY_O					= 'O',
	KEY_P					= 'P',
	KEY_Q					= 'Q',
	KEY_R					= 'R',
	KEY_S					= 'S',
	KEY_T					= 'T',
	KEY_U					= 'U',
	KEY_V					= 'V',
	KEY_W					= 'W',
	KEY_X					= 'X',
	KEY_Y					= 'Y',
	KEY_Z					= 'Z',
	KEY_0					= '0',
	KEY_1					= '1',
	KEY_2					= '2',
	KEY_3					= '3',
	KEY_4					= '4',
	KEY_5					= '5',
	KEY_6					= '6',
	KEY_7					= '7',
	KEY_8					= '8',
	KEY_9					= '9',
	KEY_BACKTICK			= '`',
	KEY_TILDE				= '~',
	KEY_BANG				= '!',
	KEY_RIGHTBRACE			= '[',
	KEY_LEFTBRACE			= ']',
	KEY_SEMICOLON			= ';',
	KEY_QUOTE				= '\'',
	KEY_BACKSLASH			= '\\',
	KEY_PIPE				= '|',
	KEY_EQUAL				= '= ',
	KEY_PLUS				= '+',
	KEY_MINUS				= '-',
	KEY_SPACE				= 32,
	KEY_ESC					= 257,
	KEY_F1					= 258,
	KEY_F2					= 259,
	KEY_F3					= 260,
	KEY_F4					= 261,
	KEY_F5					= 262,
	KEY_F6					= 263,
	KEY_F7					= 264,
	KEY_F8					= 265,
	KEY_F9					= 266,
	KEY_F10					= 267,
	KEY_F11					= 268,
	KEY_F12					= 269,
	KEY_F13					= 270,
	KEY_F14					= 271,
	KEY_F15					= 272,

	KEY_UP					= 283,
	KEY_DOWN				= 284,
	KEY_LEFT				= 285,
	KEY_RIGHT				= 286,
	KEY_LSHIFT				= 287,
	KEY_RSHIFT				= 288,
	KEY_LCTRL				= 289,
	KEY_RCTRL				= 290,
	KEY_LALT				= 291,
	KEY_RALT				= 292,
	KEY_TAB					= 293,
	KEY_ENTER				= 294,
	KEY_BACKSPACE			= 295,
	KEY_INSERT				= 296,
	KEY_DEL					= 297,
	KEY_PAGEUP				= 298,
	KEY_PAGEDOWN			= 299,
	KEY_HOME				= 300,
	KEY_END					= 301,
	KEY_KP_0				= 302,
	KEY_KP_1				= 303,
	KEY_KP_2				= 304,
	KEY_KP_3				= 305,
	KEY_KP_4				= 306,
	KEY_KP_5				= 307,
	KEY_KP_6				= 308,
	KEY_KP_7				= 309,
	KEY_KP_8				= 310,
	KEY_KP_9				= 311,
	KEY_KP_ADD				= 315,
	KEY_KP_SUBTRACT			= 314,
	KEY_KP_DIVIDE			= 312,
	KEY_KP_MULTIPLY			= 313,
	KEY_KP_DECIMAL			= 316,
	KEY_KP_EQUAL			= 317,
	KEY_KP_ENTER			= 318,
	MAX_KEYS				//always last
};


#ifdef CE_SFML
//namespace Key
enum Keys
{
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_ESCAPE,
	KEY_LCONTROL,
	KEY_LSHIFT,
	KEY_LALT,
	KEY_LSYSTEM,
	KEY_RCONTROL,
	KEY_RSHIFT,
	KEY_RALT,
	KEY_RSYSTEM,
	KEY_MENU,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_QUOTE,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_TILDE,
	KEY_EQUAL,
	KEY_DASH,
	KEY_SPACE,
	KEY_RETURN,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_END,
	KEY_HOME,
	KEY_INSERT,
	KEY_DELETE,
	KEY_ADD,
	KEY_SUBTRACT,
	KEY_MULTIPLY,
	KEY_DIVIDE,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_KP_0,
	KEY_KP_1,
	KEY_KP_2,
	KEY_KP_3,
	KEY_KP_4,
	KEY_KP_5,
	KEY_KP_6,
	KEY_KP_7,
	KEY_KP_8,
	KEY_KP_9,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_F13,
	KEY_F14,
	KEY_F15,
	KEY_PAUSE,
	MAX_KEYS
};

#endif //CE_SFML


CE_NAMESPACE_END

