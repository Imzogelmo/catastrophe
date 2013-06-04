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

#include <fc/string.h>

#include "../Common.h"
#include "../Math/Point.h"
#include "../Math/Rect.h"
#include "../Math/Color.h"
#include "../Math/Colorf.h"

CE_NAMESPACE_BEGIN


class CE_API Window
{
public:
	friend class System;

	Window();
	virtual ~Window() {}

	virtual bool Open(int w = 640, int h = 480, bool fullscreen = false, bool resizable = true,
		int depth_buffer_bits = 8, int stencil_bits = 0, int multisample_level = 0) = 0;

	virtual void Close() = 0;
	virtual double GetTime() const = 0;

	virtual void SetTitle( const fc::string& title ) = 0;
	virtual void SetSize( int w, int h ) = 0;
	virtual void SetSize( const Point& size ) { SetSize(size.x, size.y); }
	virtual void SetPosition( const Point& pos ) = 0;

	virtual void SetVSync( bool vsync = true ) = 0;

	virtual fc::string GetTitle() const { return m_title; }
	virtual Point GetSize() const = 0;
	virtual Point GetDesktopSize() const = 0;
	virtual Point GetPosition() const = 0;

	virtual void Iconify() = 0;
	virtual void Restore() = 0;
	virtual void SetCursorVisible( bool visible = true ) = 0;
	virtual void SetRequestClose( bool request = true ) { m_requestClose = request; }

	virtual void Update() = 0;
	virtual void SwapBuffers() = 0;

	virtual bool HasFocus() const { return m_hasFocus; }
	virtual bool IsOpen() const { return m_isOpen; }
	virtual bool RequestClose() const { return m_requestClose; }
	virtual bool IsActive() const { return true; }

	virtual bool IsKeepAspectRatio() { return m_keepAspect; }
	virtual bool HasAntialiasing() { return m_hasAntialias; }
	virtual Rect GetViewport() const { return m_viewport; }


	float GetAspectRatio() const;
	void SetDefaultOpenGLState();
	void KeepAspectRatio( bool enable = true );
	void EnableAntiAliasing( bool enable = true );
	void ClearColor( const Colorf& color = Colorf::Black() );

	void SetViewport( const Rect& view );
	void SetOrthographicProjection();
	void SetOrthographicProjection( float left, float right, float bottom, float top, float zNear = -1.f, float zFar = 1.f );
	void SetPerspectiveProjection( float fov, float aspect, float up, float zNear, float zFar );

protected:
	void InternalResize( const Point& windowSize );
	void InternalResize( const Rect& windowRect );

	fc::string	m_title;
	Point		m_position;
	Point		m_size;

	bool		m_requestClose;
	bool		m_isOpen;
	bool		m_hasFocus;

	//opengl state
	Rect		m_viewport;
	Point		m_pixelResolution;
	int			m_depth_bits;
	bool		m_hasAntialias;
	bool		m_keepAspect;

};


CE_NAMESPACE_END

