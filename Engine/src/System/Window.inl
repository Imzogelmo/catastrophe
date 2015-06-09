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

#include "System/Window.h"
#include "Graphics/OpenGL.h"
#include "Graphics/BlendMode.h"

#include "Catastrophe/Core/Math/Rect.h"
#include "Catastrophe/Core/Math/Matrix.h"

CE_NAMESPACE_BEGIN


Window::Window() :
	m_title(),
	m_position(Point::Zero),
	m_size(Point::Zero),
	m_requestClose(false),
	m_isOpen(false),
	m_hasFocus(false),

	m_viewport(Rect::Zero),
	m_pixelResolution(Point::Zero),
	m_depth_bits(0),
	m_hasAntialias(false),
	m_keepAspect(false)
{
}

float Window::GetAspectRatio() const
{
	return (float(m_size.x) / float(m_size.y));
}

void Window::ClearColor( const Colorf& color )
{
	if(m_depth_bits != 0)
	{
		glDepthMask( GL_TRUE );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glClearColor( color.r, color.g, color.b, color.a );
		glClearDepth( 1.0 );
		glDepthMask( GL_FALSE );
	}
	else
	{
		glClear( GL_COLOR_BUFFER_BIT );
		glClearColor( color.r, color.g, color.b, color.a );
	}
}


void Window::SetDefaultOpenGLState()
{
	// enable alpha blending
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );

	// disable depth testing (2D optimization)
	glDepthFunc( GL_LEQUAL );
	glDisable( GL_DEPTH_TEST );

	// enable batched rendering
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );

	EnableAntiAliasing( HasAntialiasing() );
}


void Window::EnableAntiAliasing( bool enable )
{
	m_hasAntialias = enable;
	if( enable )
	{
		glShadeModel( GL_SMOOTH );
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
		glHint( GL_POINT_SMOOTH_HINT,GL_NICEST );
		glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
		glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );

		glEnable( GL_POINT_SMOOTH );
		glEnable( GL_LINE_SMOOTH );
		glEnable( GL_POLYGON_SMOOTH );
	}
	else
	{
		glDisable( GL_POINT_SMOOTH );
		glDisable( GL_LINE_SMOOTH );
		glDisable( GL_POLYGON_SMOOTH );
	}
}


void Window::KeepAspectRatio( bool enable )
{
	if(m_keepAspect != enable)
	{
		m_keepAspect = enable;
		InternalResize( Rect(Point(0, 0), m_size) );
	}
}


void Window::SetViewport( const Rect& view )
{
	if(IsOpen())
	{
		m_viewport = view;
		glViewport( view.position.x, view.position.y, view.size.x, view.size.y );
	}
	else //defer until window creation.
	{
		m_viewport = view;
	}
}


void Window::SetOrthographicProjection()
{
	SetOrthographicProjection( 0.f, (float)m_pixelResolution.x, (float)m_pixelResolution.y, 0.f );
}


void Window::SetOrthographicProjection( float left, float right, float bottom, float top, float zNear, float zFar )
{
	Matrix ortho = Matrix::CreateOrthographic( left, right, bottom, top, zNear, zFar );
	glMatrixMode( GL_PROJECTION );
	glLoadMatrixf( &ortho[0] );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}


void Window::SetPerspectiveProjection( float fov, float aspect, float up, float zNear, float zFar )
{
	Matrix perspective = Matrix::CreatePerspective( fov, aspect, up, zNear, zFar );
	glMatrixMode( GL_PROJECTION );
	glLoadMatrixf( &perspective[0] );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}


void Window::InternalResize( const Point& windowSize )
{
	InternalResize( Rect(Point::Zero, windowSize) );
}


void Window::InternalResize( const Rect& windowRect )
{
	CE_ASSERT(IsOpen());
	Rect view( windowRect );

	float point_size(1.f);
	const Point resolution = m_pixelResolution;
	if( m_keepAspect )
	{
		const Point size_offset( windowRect.size - resolution );
		const Point pos_offset( size_offset / Point(2, 2) );

		//if( g_settings.scale > 1 )
		{
			//TODO:
			//scale x2, x3, x4
		}

		Rect viewportOffset = Rect::Zero;
		if( size_offset.x > 0 ) viewportOffset.position.x = pos_offset.x, viewportOffset.size.x = size_offset.x;
		if( size_offset.y > 0 ) viewportOffset.position.y = pos_offset.y, viewportOffset.size.y = size_offset.y;

		view.position += viewportOffset.position;
		view.size -= viewportOffset.size;
	}
	else
	{
		// calculate minimum stretch precentage
		const float dx = windowRect.size.x / (float)resolution.x;
		const float dy = windowRect.size.y / (float)resolution.y;
		point_size = Math::Min( dx, dy );
	}

	if( m_hasAntialias )
		point_size *= 1.1f;

	glLineWidth( point_size );
	glPointSize( point_size );

	m_viewport = view;
	glViewport( view.position.x, view.position.y, view.size.x, view.size.y );
}


CE_NAMESPACE_END

