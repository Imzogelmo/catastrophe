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

#include "../Common.h"
#include "../Math/Color.h"

#include "Window.h"

CE_NAMESPACE_BEGIN


class CE_API System
{
public:
	friend class Window;
	static System* GetInstance();

	static bool Init();
	static bool InitLogging( const fc::string& filename, bool debug_console = false );
	static void Terminate();

	static void SetOpenGLVersion( int major, int minor );

	static Window* CreateWindow(int w = 640, int h = 480, bool fullscreen = false, bool resizable = true,
		int depth_buffer_bits = 8, int stencil_bits = 0, int multisample_level = 0);
	static Window* GetWindow();

	static void OpenDebugConsole();
	static void CloseDebugConsole();
	//static void Update();

protected:
	System();
	void InitOpenGL();

	virtual bool InternalInit() = 0;
	virtual void InternalTerminate() = 0;

	Window*			m_window;
	int				m_gl_major_version;
	int				m_gl_minor_version;
	bool			m_has_fbo;
	bool			m_console;
	bool			mUnused2;
	bool			mUnused3;

	static System*	m_instance;

};


CE_NAMESPACE_END

