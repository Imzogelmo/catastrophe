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
#include "IO/Log.h"
#include "Graphics/OpenGL.h"


#if defined CE_SFML
	#include "System/SFMLSystem.h"
	#define CE_SYSTEM_TYPE			SFMLSystem
	#define CE_SYSTEM_WINDOW_TYPE	SFMLWindow
#elif defined CE_GLFW
	#include "System/GLFWSystem.h"
	#define CE_SYSTEM_TYPE			GLFWSystem
	#define CE_SYSTEM_WINDOW_TYPE	GLFWWindow
#else
	#include "System/GLFWSystem.h"
	#define CE_SYSTEM_TYPE			GLFWSystem
	#define CE_SYSTEM_WINDOW_TYPE	GLFWWindow
#endif


CE_NAMESPACE_BEGIN

System* System::m_instance = 0;


System::System() :
	m_window(0),
	m_gl_major_version(2),
	m_gl_minor_version(0),
	m_has_fbo(false)
{
}


System* System::GetInstance()
{
	CE_ASSERT(m_instance);
	return m_instance;
}


Window* System::CreateWindow(int w, int h, bool fullscreen, bool resizable,
	int depth_buffer_bits, int stencil_bits, int multisample_level)
{
	System* s = GetInstance();
	s->m_window->Open(w, h, fullscreen, resizable, depth_buffer_bits, stencil_bits, multisample_level);
	if(s->m_window->IsOpen())
	{
		s->InitOpenGL();
	}

	return s->m_window;
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


bool System::InitLogging( const fc::string& filename, bool debug_console )
{
	bool ret = Logger::GetInstance().Open(filename, debug_console);
	Log("Logging Initialized");
	return ret;
}


void System::Terminate()
{
	CE_ASSERT(m_instance);
	m_instance->InternalTerminate();

	delete m_instance->m_window;
	m_instance->m_window = 0;

	delete m_instance;
	m_instance = 0;
}


void System::InitOpenGL()
{
	if( int glew_init_success = glewInit() != GLEW_OK )
	{
		Log((char*)glewGetErrorString(glew_init_success));
		return;
	}

	Log("OpenGL Initialized,");
	Log("Card:    %s", glGetString(GL_RENDERER));
	Log("Vendor:  %s", glGetString(GL_VENDOR));
	Log("Version: %s", glGetString(GL_VERSION));

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

	m_gl_major_version = maj_ver;
	m_gl_minor_version = min_ver;

	Log("Glew version: %i, %i", m_gl_major_version, m_gl_minor_version);

	m_has_fbo = GLEW_EXT_framebuffer_object != 0;
	if(!m_has_fbo)
		LogWarning("Warning: GL_EXT_framebuffer_object is not supported -- Render to texture will not be available.");

	if(maj_ver < 2)
		LogError("Error: Shader objects require an OpenGL 2.0 context. Shaders will not be available.");

}




// Win32 main entry point defined, for portability.
#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>

extern int main(int argc, char* argv[]);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	return main(__argc, __argv);
}

#endif

CE_NAMESPACE_END

