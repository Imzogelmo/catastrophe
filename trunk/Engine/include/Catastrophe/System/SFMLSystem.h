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


class sf::Window;


class SFMLSystem
{
public:
	virtual ~SFMLSystem()
	{}

	//virtual bool CreateWindow(const Point& size = Point(640, 480), bool fullscreen = false, bool resizable = true) = 0;
	bool CreateWindow(const Point& size = Point(640, 480), bool fullscreen = false, bool resizable = true,
		int depth_buffer_bits = 8, int stencil_bits = 0);

	void CloseWindow();
	double GetTime();

	void SetVSync(bool vsync = true);
	void SetWindowTitle(const char* title);
	void SetWindowSize(const Point& size);
	Point GetWindowSize();

	void Sleep(int milliseconds);
	void Iconify();
	void Restore();
	void SetCursorVisible(bool visible = true);

	void Update();
	void SwapBuffers();

	bool HasFocus() const;

protected:
	void sfmlProcessEvents();

	sf::Window* m_window;

};


