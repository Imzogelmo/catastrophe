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

#ifdef CE_GLFW

#include "System/GLFWSystem.h"
#include "Input/Input.h"

#include <GL/glfw.h>

#ifdef _MSC_VER
	// Link againt standard GLFW libraries.
	#ifdef CE_DEBUG
		#pragma comment ( lib, "glfwd.lib" )
	#else
		#pragma comment ( lib, "glfw.lib" )
	#endif
#endif

CE_NAMESPACE_BEGIN


bool GLFWSystem::InternalInit()
{
	if( !glfwInit() )
		return false;

	return true;
}


void GLFWSystem::InternalTerminate()
{
	glfwTerminate();
}


void GLFWSystem::Sleep( int milliseconds )
{
	glfwSleep( (double)milliseconds / 1000.0 );
}



// Window

GLFWWindow::GLFWWindow() :
	Window()
{
}


GLFWWindow::~GLFWWindow()
{
	Close();
}


double GLFWWindow::GetTime() const
{
	return glfwGetTime();
}


Point GLFWWindow::GetSize() const
{
	return m_size;
}


Point GLFWWindow::GetPosition() const
{
	return m_position;
}


void GLFWWindow::SetVSync( bool vsync )
{
	glfwSwapInterval( vsync ? 1 : 0 );
}


void GLFWWindow::SetTitle( const fc::string& title )
{
	glfwSetWindowTitle(title.c_str());
}


void GLFWWindow::SetSize( int w, int h )
{ 
	glfwSetWindowSize(w, h);
	glfwGetWindowSize(&m_size.x, &m_size.y);
}


void GLFWWindow::SetPosition( const Point& pos )
{ 
	m_position = pos;
	glfwSetWindowPos(pos.x, pos.y);
}


void GLFWWindow::Iconify()
{
	glfwIconifyWindow();
}


void GLFWWindow::Restore()
{
	glfwRestoreWindow();
}


bool GLFWWindow::IsActive() const
{
    return glfwGetWindowParam( GLFW_ACTIVE ) != 0;
}


void GLFWWindow::SetCursorVisible( bool visible )
{
	if(visible)
	{
		glfwEnable(GLFW_MOUSE_CURSOR);
	}
	else
	{
		glfwEnable(GLFW_MOUSE_CURSOR);
	}
}


void GLFWWindow::SwapBuffers()
{
	glfwSwapBuffers();
}


bool GLFWWindow::Open(int w, int h, bool fullscreen, bool resizable,
	int depth_buffer_bits, int stencil_bits, int multisample_level)
{
	if( IsOpen() )
		Close();

	if(!resizable)
		glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, 1);

	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 2 );
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 0 );
	glfwOpenWindowHint( GLFW_FSAA_SAMPLES, multisample_level );

	int mode = fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW;
	m_isOpen = glfwOpenWindow(w, h, 8, 8, 8, 8, depth_buffer_bits, stencil_bits, mode) != 0;
	if(!m_isOpen)
	{
		return false;
	}

	//center the window.
	if(!fullscreen)
	{
		Point desktopSize = GetDesktopSize();
		Point winPos = (desktopSize - Point(w, h)) / 2;
		winPos.Clamp( Point::Zero, desktopSize / 2 );
		SetPosition(winPos);
	}

	m_size = Point(w, h);
	if(m_pixelResolution.IsZero())
	{
		m_pixelResolution = m_size;
	}

	//if(m_viewport.Empty())
	//	m_viewport.size = m_pixelResolution;

	//SetViewport( m_viewport );
	InternalResize( Rect(Point(0, 0), m_size) );
	SetOrthographicProjection();

	//glfwGetWindowSize( &m_size.x, &m_size.y );
	m_hasFocus		= glfwGetWindowParam( GLFW_ACTIVE ) != 0;
	m_depth_bits	= glfwGetWindowParam( GLFW_DEPTH_BITS ) != 0;
	m_isOpen		= glfwGetWindowParam( GLFW_OPENED ) != 0;

	SetTitle("Catastrophe");
	SetCallbacks();
	SetDefaultOpenGLState();

	return true;
}


Point GLFWWindow::GetDesktopSize() const
{
	GLFWvidmode desktop;
	glfwGetDesktopMode( &desktop );

	return Point(desktop.Width, desktop.Height);
}


void GLFWWindow::Close()
{
	glfwCloseWindow();
	m_isOpen = false;
}


void GLFWWindow::Update() 
{
	glfwPollEvents();
}


void GLFWWindow::SetCallbacks() 
{
	glfwSetKeyCallback( &glfwKeyboardCallback );
	glfwSetCharCallback( &glfwCharacterCallback );
	glfwSetMouseButtonCallback( &glfwMouseButtonCallback );
	glfwSetMousePosCallback( &glfwMousePosCallback );
	glfwSetMouseWheelCallback( &glfwMouseWheelPosCallback );
	glfwSetWindowSizeCallback( &glfwWindowResizeCallback );
	glfwSetWindowCloseCallback( &glfwWindowCloseCallback );
}


void GLFWWindow::glfwWindowResizeCallback( int width, int height )
{
	GLFWWindow* w = (GLFWWindow*)System::GetWindow();
	w->m_size = Point(width, height);
	w->InternalResize( Rect(0, 0, width, height) );
}


void GLFWWindow::glfwKeyboardCallback( int key, int action )
{
	if( action == GLFW_PRESS )
	{
		//todo bind keys
		Keyboard* k = Input::GetInstance()->GetKeyboard(); 
		k->SetKeyPress(key);
	}
	else
	{
		Keyboard* k = Input::GetInstance()->GetKeyboard();
		k->SetKeyRelease(key);
	}
}


void GLFWWindow::glfwCharacterCallback( int key, int action )
{
	key = action; //todo
}


void GLFWWindow::glfwMousePosCallback( int x, int y )
{
	Mouse* m = Input::GetInstance()->GetMouse(); 
	m->SetPos( Point(x, y) );
}

void GLFWWindow::glfwMouseWheelPosCallback( int pos )
{
	Mouse* m = Input::GetInstance()->GetMouse(); 
	m->SetWheelPos( pos );
}

void GLFWWindow::glfwMouseButtonCallback( int button, int action )
{
	Mouse* m = Input::GetInstance()->GetMouse(); 
	m->SetButton( button, action == GLFW_PRESS ? true : false );
}

int GLFWWindow::glfwWindowCloseCallback()
{
	System::GetWindow()->SetRequestClose(true);
	return GL_FALSE;
}



/////////////////////////////////////
//         Joystick
/////////////////////////////////////

void Joystick::Update()
{
	if( !Exists() )
		return;

	if( glfwGetJoystickParam(GetJoystickNumber(), GLFW_PRESENT) == GL_FALSE )
	{
		Log("Joystick (%i) not detected.", GetJoystickNumber());
		m_exists = false;
		return;
	}

	for( int i(0); i < MaxAnalogs; ++i )
	{
		m_previous_analog[i] = m_analog[i];
	}

	glfwGetJoystickPos( GetJoystickNumber(), &m_analog[0].x, 4 ); //MaxAxes );

	//glfw bug...
	m_analog[0].y = -m_analog[0].y;
	//m_analog[1].y = -m_analog[1].y;

	uchar b[MaxButtons];
	glfwGetJoystickButtons( GetJoystickNumber(), b, MaxButtons );

	for( uint i(0); i < MaxButtons; ++i )
	{
		if( b[i] != 0 )
		{
			m_button[i]++;
			m_buttonReleaseFlags &= ~( (uint)(1 << i) );
		}
		else
		{
			if( m_button[i] != 0 )
			{
				m_button[i] = 0;
				m_buttonReleaseFlags |= ( (uint)(1 << i) );
			}
		}
	}

	//todo:
	m_pov = (0x00000000);
}



CE_NAMESPACE_END


#endif //CE_GLFW
