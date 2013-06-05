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


#ifdef CE_SDL

#include "System/SDLSystem.h"
#include "Input/Input.h"

// we only link to static libs on windows.
#if defined (WIN32) || defined (_WIN32)
	#define SDL_STATIC
#endif

#include <SDL/SDL.h>

#ifdef _MSC_VER
	// Link againt standard SDL libraries.
	#ifdef CE_DEBUG
		#pragma comment ( lib, "sdl2d.lib" )
	#else
		#pragma comment ( lib, "sdl2.lib" )
	#endif

	#pragma comment ( lib, "winmm.lib" )
	#pragma comment ( lib, "imm32.lib" )
	#pragma comment ( lib, "version.lib" )
#endif

CE_NAMESPACE_BEGIN


bool SDLSystem::InternalInit()
{
	return SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) == 0;
}


void SDLSystem::InternalTerminate()
{
	SDL_Quit();
}


void SDLSystem::Sleep(int milliseconds)
{
	SDL_Delay((Uint32)milliseconds);
}



// Window

SDLWindow::SDLWindow() :
	Window(),
	m_window(0),
	m_glContext(0)
{
}


SDLWindow::~SDLWindow()
{
	Close();
	if( m_glContext )
	{
		SDL_GL_DeleteContext(m_glContext); //eh...
		m_glContext = 0;
	}
}


double SDLWindow::GetTime() const
{
	return 0.0;
}


Point SDLWindow::GetSize() const
{
	return m_size;
}


Point SDLWindow::GetPosition() const
{
	return m_position;
}


void SDLWindow::SetVSync( bool vsync )
{
	int interval = vsync ? 1 : 0;
	SDL_GL_SetSwapInterval(interval);
}


void SDLWindow::SetTitle( const fc::string& title )
{
	SDL_SetWindowTitle(m_window, title.c_str());
}


void SDLWindow::SetSize( int x, int y )
{
	SDL_SetWindowSize(m_window, x, y);
	SDL_GetWindowSize(m_window, &m_size.x, &m_size.y);
}


void SDLWindow::SetPosition( const Point& pos )
{ 
	SDL_SetWindowPosition(m_window, pos.x, pos.y);
	SDL_GetWindowPosition(m_window, &m_position.x, &m_position.y);
}


void SDLWindow::Iconify()
{
	SDL_MinimizeWindow(m_window);
	m_hasFocus = false;
}


void SDLWindow::Restore()
{
	SDL_MaximizeWindow(m_window);
	m_hasFocus = true;
}


bool SDLWindow::IsActive() const
{
    return true;
}


void SDLWindow::SetCursorVisible(bool visible)
{
	(void*)visible;
}


void SDLWindow::SwapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}


bool SDLWindow::HasFocus() const
{
	return m_hasFocus;
}


bool SDLWindow::Open(int w, int h, bool fullscreen, bool resizable,
	int depth_buffer_bits, int stencil_bits, int multisample_level)
{
	Close();

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, depth_buffer_bits);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, stencil_bits);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// by default multisample is disabled.
	if( multisample_level > 0 )
	{
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multisample_level);
	}

	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
	flags |= SDL_WINDOW_OPENGL;
	flags |= SDL_WINDOW_RESIZABLE;
	flags |= SDL_WINDOW_SHOWN;

	m_window = SDL_CreateWindow(
		m_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w,
		h,
		flags
	);

	if( !m_window )
	{
		//fullscreen is probably the lowest common denominator here
		if(fullscreen)
		{
			fullscreen = false;
			return Open(w, h, fullscreen, resizable, depth_buffer_bits, stencil_bits, multisample_level);
		}

		return false;
	}

	// Create GL context
	m_glContext = SDL_GL_CreateContext(m_window);

	// get position,size.
	SDL_GetWindowPosition(m_window, &m_position.x, &m_position.y);
	SDL_GetWindowSize(m_window, &m_size.x, &m_size.y);

	// we don't want key repeat.
	//m_window->setKeyRepeatEnabled(false);

	m_depth_bits	= 32;
	m_isOpen		= true;
	m_hasFocus		= m_isOpen;

	// set up default opengl states
	InternalResize(m_size);
	SetOrthographicProjection();
	SetDefaultOpenGLState();

	return true;
}


void SDLWindow::Close()
{
	if( m_window )
	{
		SDL_DestroyWindow(m_window);
		m_window = 0;
	}

	m_isOpen = false;
}


Point SDLWindow::GetDesktopSize() const
{
	Point size = Point::Zero;
	SDL_DisplayMode displayMode;
	if( SDL_GetDesktopDisplayMode(0, &displayMode) == 0 )
	{
		size.x = displayMode.w;
		size.y = displayMode.h;
	}

	return size;
}


void SDLWindow::Update()
{
	SDL_Event event;

	while( SDL_PollEvent(&event) )
	{
		if( event.type == SDL_WINDOWEVENT )
		{
			// All possible Window events.
			switch( event.window.type )
			{
				case SDL_WINDOWEVENT_SHOWN:
				{
					m_hasFocus = true;
					break;
				}

				case SDL_WINDOWEVENT_HIDDEN:
				{
					m_hasFocus = false;
					break;
				}

				case SDL_WINDOWEVENT_EXPOSED:
				{
					//todo
					break;
				}

				case SDL_WINDOWEVENT_MOVED:
				{
					m_position.x = event.window.data1;
					m_position.y = event.window.data2;
					break;
				}

				case SDL_WINDOWEVENT_RESIZED:
				case SDL_WINDOWEVENT_SIZE_CHANGED:
				{
					m_size.x = event.window.data1;
					m_size.y = event.window.data2;
					InternalResize(m_size);
					break;
				}

				case SDL_WINDOWEVENT_MINIMIZED:
				{
					m_hasFocus = false;
					break;
				}

				case SDL_WINDOWEVENT_MAXIMIZED:
				case SDL_WINDOWEVENT_RESTORED:
				{
					m_hasFocus = true;
					break;
				}

				case SDL_WINDOWEVENT_ENTER:
				case SDL_WINDOWEVENT_FOCUS_GAINED:
				{
					m_hasFocus = true;
					break;
				}

				case SDL_WINDOWEVENT_LEAVE:
				case SDL_WINDOWEVENT_FOCUS_LOST:
				{
					m_hasFocus = false;
					break;
				}

				case SDL_WINDOWEVENT_CLOSE:
				{
					SetRequestClose(true);
					break;
				}
			}
		}

		else if( event.type == SDL_KEYDOWN )
		{
			int key = event.key.keysym.sym;
			Input::GetKeyboard()->SetKeyPress(key);
		}

		else if( event.type == SDL_KEYUP )
		{
			int key = event.key.keysym.sym;
			Input::GetKeyboard()->SetKeyRelease(key);
		}

		else if( event.type == SDL_MOUSEMOTION )
		{
			Mouse* mouse = Input::GetMouse();
			mouse->SetPos( Point(event.motion.x, event.motion.y) );
		}

		else if( event.type == SDL_MOUSEBUTTONDOWN )
		{
			Mouse* mouse = Input::GetMouse();
			mouse->SetButton((int)event.button.button, true);
		}

		else if( event.type == SDL_MOUSEBUTTONUP )
		{
			Mouse* mouse = Input::GetMouse();
			mouse->SetButton((int)event.button.button, false);
		}

		else if( event.type == SDL_MOUSEWHEEL )
		{
			Mouse* mouse = Input::GetMouse();
			mouse->SetWheelPos( mouse->GetWheel() + event.wheel.y );
		}

		else if( event.type == SDL_QUIT )
		{
			SetRequestClose(true);
		}

		else
		{
			LogDebug("SDL: Unknown event.");
		}

	} //while(event)
}



/////////////////////////////////////
//         Joystick
/////////////////////////////////////

void Joystick::Update()
{
	// todo: hack.. fixme
	static SDL_Joystick* joystickDevice[MaxJoysticks] = { 0, 0, 0, 0};

	if( !m_exists || m_joyNumber >= MaxJoysticks )
		return;

	if( !joystickDevice[m_joyNumber] )
	{
		joystickDevice[m_joyNumber] = SDL_JoystickOpen(m_joyNumber);
		if( !joystickDevice[m_joyNumber] )
		{
			m_exists = false;
			return;
		}
	}

	SDL_Joystick* joystickPtr = joystickDevice[m_joyNumber];

	for( int i(0); i < 2; ++i )
	{
		m_previous_analog[i] = m_analog[i];

		const int axis = (i * 2);
		m_analog[i].x = (float)SDL_JoystickGetAxis(joystickPtr, axis) / 32767.f;
		m_analog[i].y = (float)SDL_JoystickGetAxis(joystickPtr, axis + 1) / 32767.f;
	}

	for( uint i(0); i < MaxButtons; ++i )
	{
		if( SDL_JoystickGetButton(joystickPtr, i) )
		{
			m_button[i]++;
			m_buttonReleaseFlags &= ~(1 << i);
		}
		else
		{
			if( m_button[i] != 0 )
			{
				m_button[i] = 0;
				m_buttonReleaseFlags |= (1 << i);
			}
		}
	}

	enum _Pov_Directions 
	{
		POV_UP = 0x01, POV_RIGHT = 0x02, POV_DOWN = 0x04, POV_LEFT = 0x08
	};

	// At least SDL has a sane POV function that matches ours. :)
	m_pov = (int)SDL_JoystickGetHat(joystickPtr, 0);
}



CE_NAMESPACE_END


#endif //CE_SDL



