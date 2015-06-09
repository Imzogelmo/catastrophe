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

#include "System/System.h"
#include "Core/IO/Log.h"
#include "Graphics/OpenGL.h"

#include <stdio.h>


#if defined CE_SFML
	#include "System/SFMLSystem.h"
	#define CE_SYSTEM_TYPE			SFMLSystem
	#define CE_SYSTEM_WINDOW_TYPE	SFMLWindow
#elif defined CE_GLFW
	#include "System/GLFWSystem.h"
	#define CE_SYSTEM_TYPE			GLFWSystem
	#define CE_SYSTEM_WINDOW_TYPE	GLFWWindow
#elif defined CE_SDL
	#include "System/SDLSystem.h"
	#define CE_SYSTEM_TYPE			SDLSystem
	#define CE_SYSTEM_WINDOW_TYPE	SDLWindow
#else
	// By default, we have to include something.
	#include "System/GLFWSystem.h"
	#define CE_SYSTEM_TYPE			GLFWSystem
	#define CE_SYSTEM_WINDOW_TYPE	GLFWWindow
#endif


CE_NAMESPACE_BEGIN

System* System::m_instance = 0;


System::System() :
	m_window(0),
	m_glMajorVersion(2),
	m_glMinorVersion(0),
	m_hasFBO(false),
	m_console(false)
{
}


System* System::GetInstance()
{
	CE_ASSERT(m_instance != null);
	return m_instance;
}


Window* System::CreateWindow(int w, int h, bool fullscreen, bool resizable,
	int depth_buffer_bits, int stencil_bits, int multisample_level)
{
	System* systemImpl = GetInstance();
	systemImpl->m_window->Open(w, h, fullscreen, resizable, depth_buffer_bits, stencil_bits, multisample_level);
	if(systemImpl->m_window->IsOpen())
	{
		systemImpl->InitOpenGL();
	}

	return systemImpl->m_window;
}


Window* System::GetWindow()
{
	return GetInstance()->m_window;
}


bool System::Init()
{
	if(!m_instance)
		m_instance = new CE_SYSTEM_TYPE;
	if(!m_instance->m_window)
		m_instance->m_window = new CE_SYSTEM_WINDOW_TYPE;

	return m_instance->InternalInit();
}


bool System::InitLogging( const String& filename, bool debug_console )
{
	bool ret = Logger::GetInstance()->Open(filename, debug_console);
	Log("Logging Initialized");

	if( debug_console )
	{
		OpenDebugConsole();
		printf("DEBUG CONSOLE\n" );
	}

	return ret;
}


void System::Terminate()
{
	CE_ASSERT(m_instance != null);
	m_instance->InternalTerminate();

	delete m_instance->m_window;
	m_instance->m_window = null;

	delete m_instance;
	m_instance = null;
}


void System::InitOpenGL()
{
	if( int glew_init_success = glewInit() != GLEW_OK )
	{
		Log((char*)glewGetErrorString(glew_init_success));
		return;
	}

	LogInfo("OpenGL Initialized,");
	LogInfo("Card:    %s", glGetString(GL_RENDERER));
	LogInfo("Vendor:  %s", glGetString(GL_VENDOR));
	LogInfo("Version: %s", glGetString(GL_VERSION));

	int maj_ver = 1;
	int min_ver = 1;
	if(!GLEW_VERSION_1_2) maj_ver = 1, min_ver = 1;
	else if(!GLEW_VERSION_1_3) maj_ver = 1, min_ver = 2;
	else if(!GLEW_VERSION_1_4) maj_ver = 1, min_ver = 3;
	else if(!GLEW_VERSION_1_5) maj_ver = 1, min_ver = 4;
	else if(!GLEW_VERSION_2_0) maj_ver = 1, min_ver = 5;
	else if(!GLEW_VERSION_2_1) maj_ver = 2, min_ver = 0;
	else if(!GLEW_VERSION_3_0) maj_ver = 2, min_ver = 1;
	else maj_ver = 3, min_ver = 0;

	m_glMajorVersion = maj_ver;
	m_glMinorVersion = min_ver;

	//Log("Glew version: %i, %i", m_gl_major_version, m_gl_minor_version);

	m_hasFBO = GLEW_EXT_framebuffer_object != 0;
	if(!m_hasFBO)
		LogWarning("Warning: GL_EXT_framebuffer_object is not supported -- Render to texture will not be available.");

	if(maj_ver < 2)
		LogError("Warning: Shader objects require an OpenGL 2.0 context. Shaders will not be available.");

}


void System::SetOpenGLVersion( int major, int minor )
{
	GetInstance()->m_glMajorVersion = major;
	GetInstance()->m_glMinorVersion = minor;
}


void System::Sleep(int milliseconds)
{
	CE_SYSTEM_TYPE* systemImpl = (CE_SYSTEM_TYPE*)m_instance;
	systemImpl->Sleep(milliseconds);
}


// Win32 main entry point defined, for portability.
#if defined(_WIN32) || defined(WIN32)

//windows crap
#if !defined(_68K_) && !defined(_MPPC_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && defined(_M_IX86)
#define _X86_
#endif

//more windows crap
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#define NOGDI

// add any compilers that need to include the full windows.h here
#if (_MSC_VER > 1500)
	#include <windows.h>
#else
	#include <windef.h>
	#include <winbase.h>
	#include <wincon.h>
#endif

#include <fcntl.h>
#include <io.h>
#include <iostream>



extern int main(int argc, char* argv[]);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	return main(__argc, __argv);
}


void System::OpenDebugConsole()
{
	const int MAX_CONSOLE_LINES = 256;

	CONSOLE_SCREEN_BUFFER_INFO console_info;
	int hConHandle;
	long lStdHandle;

	AllocConsole();

	// set the screen buffer to be big enough to scroll text
	GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &console_info );
	console_info.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize( GetStdHandle(STD_OUTPUT_HANDLE), console_info.dwSize );

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle( STD_OUTPUT_HANDLE );
	hConHandle = _open_osfhandle( lStdHandle, _O_TEXT );
	*stdout = *_fdopen( hConHandle, "w" );
	setvbuf( stdout, NULL, _IONBF, 0 );

	// redirect unbuffered STDIN to the console
	lStdHandle = (long)GetStdHandle( STD_INPUT_HANDLE );
	hConHandle = _open_osfhandle( lStdHandle, _O_TEXT );
	*stdin = *_fdopen( hConHandle, "r" );
	setvbuf( stdin, NULL, _IONBF, 0 );

	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle( STD_ERROR_HANDLE );
	hConHandle = _open_osfhandle( lStdHandle, _O_TEXT );
	*stderr = *_fdopen( hConHandle, "w" );
	setvbuf( stderr, NULL, _IONBF, 0 );

	//for cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	std::ios::sync_with_stdio();

	GetInstance()->m_console = true;
}


void System::CloseDebugConsole()
{
	FreeConsole();
	GetInstance()->m_console = false;
}

#else

void System::OpenDebugConsole() {}
void System::CloseDebugConsole() {}

#endif //_WIN32

CE_NAMESPACE_END

