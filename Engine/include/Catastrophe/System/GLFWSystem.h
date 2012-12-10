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

#include "System.h"
#include "Window.h"

CE_NAMESPACE_BEGIN


class GLFWSystem : public System
{
protected:
	bool InternalInit();
	void InternalTerminate();

};


class GLFWWindow : public Window
{
public:
	virtual ~GLFWWindow();

	virtual bool Open(int w = 640, int h = 480, bool fullscreen = false, bool resizable = true,
		const Color& bits = Color(8,8,8,8), int depth_buffer_bits = 8, int stencil_bits = 0, int multisample_level = 0);

	virtual void Close();
	virtual double GetTime() const;

	virtual void SetTitle( const fc::string& title );
	virtual void SetSize( int w, int h );
	virtual void SetPosition( const Point& size );

	virtual void SetVSync( bool vsync = true );

	virtual Point GetSize() const;
	virtual Point GetDesktopSize() const;
	virtual Point GetPosition() const;

	virtual void Sleep( int milliseconds );
	virtual void Iconify();
	virtual void Restore();
	virtual void SetCursorVisible( bool visible = true );

	virtual void Update();
	virtual void SwapBuffers();

	virtual bool HasFocus() const { return m_hasFocus; }
	virtual bool IsActive() const;

protected:
	void SetCallbacks();
	static void glfwWindowResizeCallback( int width, int height );
	static void glfwKeyboardCallback( int key, int action );
	static void glfwCharacterCallback( int key, int action );
	static void glfwMousePosCallback( int x, int y );
	static void glfwMouseWheelPosCallback( int pos );
	static void glfwMouseButtonCallback( int button, int action );
	static int glfwWindowCloseCallback();

};

CE_NAMESPACE_END

