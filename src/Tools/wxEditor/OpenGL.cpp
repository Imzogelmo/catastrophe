//////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify //
// it under the terms of the GNU General Public License as published by //
// the Free Software Foundation, either version 3 of the License, or    //
// (at your option) any later version.                                  //
//                                                                      //
// This program is distributed in the hope that it will be useful,      //
// but WITHOUT ANY WARRANTY; without even the implied warranty of       //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        //
// GNU General Public License for more details.                         //
//////////////////////////////////////////////////////////////////////////

#include "Precompiled.h"
#include "OpenGL.h"

#include <wx/wx.h>
#include <wx/defs.h>
#include <wx/glcanvas.h>


namespace OpenGL
{

//Global OpenGL state vars
bool _is_opengl_init		= false;


bool IsOpenGLInitialized()
{
	return _is_opengl_init;
}


void InitOpenGL()
{
	if( !_is_opengl_init )
	{
		//This should never happen
		if( glBot.Init( 0x11 ) < 0 )
			throw(-1);
	}

	_is_opengl_init = true;

	// Just a few sensible defaults for now.

	glBot.Blender.Alpha();
	glEnable( GL_BLEND );
	glDepthFunc( GL_LEQUAL );
	glDisable( GL_DEPTH_TEST );
	glEnable( GL_ALPHA_TEST );
	glAlphaFunc( GL_GREATER, 0.01f );
	glDisable( GL_TEXTURE_2D );

	glShadeModel( GL_SMOOTH );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glHint( GL_POINT_SMOOTH_HINT,GL_NICEST );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );

	glEnable( GL_POINT_SMOOTH );
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_POLYGON_SMOOTH );

	//glLineWidth( 1.1f );
	//glPointSize( 1.1f );
}


void SetOrtho( const wxRect& rect )
{
	int x = rect.x;
	int y = rect.y;
	int w = rect.width;
	int h = rect.height;
	glViewport( x, y, w, h );
	Matrix ortho = Matrix::CreateOrthographic( (float)x, (float)w, (float)h, (float)y );
	glMatrixMode( GL_PROJECTION );
	glLoadMatrixf( &ortho[0] );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}


void ClearFrameBuffer( const Colorf& backColor )
{
	glDepthMask( GL_TRUE );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor( backColor.r, backColor.g, backColor.b, backColor.a );
	glClearDepth( 1.0 );
	glDepthMask( GL_FALSE );
}


void DisableBatchRendering()
{
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );
}


void EnableBatchRendering()
{
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );
}

void DrawThickOutlineRect( Primitive* primitive, wxRect rect, const Color& color, const Color& frame )
{
	Rectf bRect( Vector2(rect.x, rect.y), Vector2(rect.width, rect.height) );
	Rectf r2(bRect), r3(bRect);
	r2.Deflate(0.5f);
	r3.Deflate(1.0f);

	glDisable( GL_TEXTURE_2D );

	primitive->Begin( GL_LINE_STRIP );
	primitive->CreateRectangle( r2, color );
	primitive->Render();

	primitive->Begin( GL_LINE_STRIP );
	primitive->CreateRectangle( r3, frame );
	primitive->Render();

	//primitive->CreateRectangle( Rectf::Inflate( bRect, Vector2::One ), frame );
	//primitive->Render();
}



} //namespace OpenGL


