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

#include "MinimapWindow.h"
#include "OpenGL.h"
#include "Editor.h"
#include "MapHelper.h"


BEGIN_EVENT_TABLE(MinimapWindow, wxGLCanvas)
    EVT_SIZE				(MinimapWindow::OnSize)
    EVT_PAINT				(MinimapWindow::OnPaint)
	EVT_ERASE_BACKGROUND	(MinimapWindow::OnEraseBackground)
END_EVENT_TABLE()


MinimapWindow::MinimapWindow(wxWindow* parent, wxGLContext* glContext) :
	wxGLCanvas(parent, 
		wxID_ANY, 
		wxDefaultPosition, 
		wxDefaultSize,
		0,
		_T("MinimapWindow"), 
		0,
		wxNullPalette
	),
	m_ptrGLContext(glContext)
{
	this->Show(true);
	m_stopwatch.Start();
	m_swDuration = (long)(1000 / 3); //max render frames-per-second.
	m_forceUpdate = true;
}


MinimapWindow::~MinimapWindow()
{
}


void MinimapWindow::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	long time = m_stopwatch.Time();
	if( m_forceUpdate || time > m_swDuration )
	{
		m_forceUpdate = false;
		m_stopwatch.Start();
	}
	else
	{
		return;
	}

	wxPaintDC dc(this);
	OpenGL::PrepareRenderingContext(this, m_ptrGLContext);
	OpenGL::ClearFrameBuffer(Colorf::Black(0.f));

	const wxRect windowRect = GetSize();

	Map* map = Editor->GetActiveMap();
	if(map)
	{
		wxRect mapRect;
		mapRect.width = (int)map->Width() * Tile::TileSize;
		mapRect.height = (int)map->Height() * Tile::TileSize;

		//set viewport to client size, and projection matrix to cover virtual size.
		glViewport( windowRect.x, windowRect.y, windowRect.width, windowRect.height );
		OpenGL::OrthographicProjection( 0.f, (float)mapRect.width, (float)mapRect.height, 0.f );

		m_spritebatch.Begin();

		map->Render( &m_spritebatch, mapRect, Tile::TileSize );

		m_spritebatch.Render();
		m_spritebatch.End();
	}

	SwapBuffers();

}


void MinimapWindow::OnSize( wxSizeEvent& event )
{
    // this is also necessary to update the context on some platforms
    wxGLCanvas::OnSize(event);

	wxSize size = event.GetSize();
	SetSize(size);

	m_forceUpdate = true;
}


