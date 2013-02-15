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

#include "GLMapCanvas.h"
#include "OpenGL.h"
#include "Editor.h"
#include "MapHelper.h"
#include "Map.h"


SpriteBatch GLMapCanvas::m_spritebatch;
PrimitiveBatch GLMapCanvas::m_primbatch;
Primitive GLMapCanvas::m_prim;


//Template declaration
BEGIN_GLSCROLLEDWINDOW_EVENT_TABLE_TEMPLATE(GLMapCanvas)


BEGIN_EVENT_TABLE(GLMapCanvas, wxGLCanvas)
    EVT_SIZE				(GLMapCanvas::OnSize)
    EVT_PAINT				(GLMapCanvas::OnPaint)
	EVT_ERASE_BACKGROUND	(GLMapCanvas::OnEraseBackground)

	EVT_LEFT_DOWN			(GLMapCanvas::OnLeftClickPress)
	EVT_LEFT_UP				(GLMapCanvas::OnLeftClickRelease)
	EVT_RIGHT_DOWN			(GLMapCanvas::OnRightClickPress)
	EVT_RIGHT_UP			(GLMapCanvas::OnRightClickRelease)
	EVT_MOTION				(GLMapCanvas::OnMouseMove)
	EVT_LEAVE_WINDOW		(GLMapCanvas::OnMouseLeaveWindow)
	EVT_ENTER_WINDOW		(GLMapCanvas::OnMouseEnterWindow)
	EVT_MOUSEWHEEL			(GLMapCanvas::OnMouseWheel)


	EVT_KEY_DOWN			(GLMapCanvas::OnKeyDown)
	EVT_KEY_UP				(GLMapCanvas::OnKeyUp)

END_EVENT_TABLE()


GLMapCanvas::GLMapCanvas(GLScrolledWindow<GLMapCanvas>* parent, wxGLContext* glContext) :
	wxGLCanvas(parent, glContext,
		wxID_ANY, 
		wxDefaultPosition, 
		parent->GetSize(),//wxDefaultSize, 
		0,				//style
		_T("GLCanvas"), 
		0,				//attribList
		wxNullPalette
	),
	m_ptrGLContext(glContext),
	m_parent(parent)
{
	this->Show(true);
}


GLMapCanvas::~GLMapCanvas()
{
}


GLScrolledWindow<GLMapCanvas>* GLMapCanvas::CreateInstance(wxWindow* parent, wxGLContext* glContext)
{
	return new GLScrolledWindow<GLMapCanvas>(parent, glContext);
}


void GLMapCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);
	OpenGL::PrepareRenderingContext(this, m_ptrGLContext);

	const wxRect windowRect = GetSize();

	OpenGL::ClearFrameBuffer(Colorf::Black(0.f));
	OpenGL::SetOrtho( windowRect );

	m_spritebatch.Begin();

	// draw map (with offset)
	wxPoint mapOffset = m_parent->GetScrollbarPixelPositions();
	wxRect offsetRect = windowRect;
	offsetRect.x += mapOffset.x;
	offsetRect.y += mapOffset.y;
	Editor->GetActiveMap()->Render( &m_spritebatch, offsetRect, Tile::TileSize );

	// draw the selected tiles
	if( m_mouse.inWindow )
	{
		wxPoint mousePos = MapHelper::SnapToGrid( m_mouse.pos, Tile::TileSize );
		Vector2 vecPos = Vector2( float(mousePos.x), float(mousePos.y) );

		Editor->GetTileSelection().DrawTransparent( &m_spritebatch, vecPos, Tile::TileSize );
	}

	m_spritebatch.Render();
	m_spritebatch.End();
	SwapBuffers();
}


void GLMapCanvas::OnTimer()
{
	wxClientDC dc(this);
	OpenGL::PrepareRenderingContext(this, m_ptrGLContext);

	Render();
}


void GLMapCanvas::Update()
{
}


void GLMapCanvas::Render()
{
}


void GLMapCanvas::OnSize( wxSizeEvent& event )
{
    // this is also necessary to update the context on some platforms
    wxGLCanvas::OnSize(event);

	wxSize size = event.GetSize();
	printf("MapCanvas::OnSize: %d, %d\n", size.x, size.y );

	this->SetSize(size);
	OpenGL::SetOrtho( wxRect(size) ); //fix; add 1 tile to this

	Map* map = Editor->GetActiveMap();
	if(map)
	{
		m_parent->SetScrollbarUnits( map->Width(), map->Height() );
	}
	else
	{
		m_parent->SetScrollbarUnits( 0, 0 );
	}
}


//Key events
void GLMapCanvas::OnKeyDown(wxKeyEvent& event)
{
	(void*)&event;
}


void GLMapCanvas::OnKeyUp(wxKeyEvent& event)
{
	(void*)&event;
}


void GLMapCanvas::HandleMouseEvents( int middlePos, bool leftRelease, bool rightRelease )
{

	Refresh(true);
}



/////////////////////
//  Mouse events   //
/////////////////////

void GLMapCanvas::OnLeftClickPress(wxMouseEvent& event)
{
	m_mouse.left = true;
	m_mouse.clicked = MapHelper::SnapToGrid( m_mouse.pos, Tile::TileSize );

	wxPoint offsetGridPos = m_parent->GetScrollbarPixelPositions() + m_mouse.pos;
	Editor->GetActiveMapLayer()->AddTileSelection( MapHelper::SnapToIndexGrid( offsetGridPos, Tile::TileSize ) );
	printf("%d\n", m_mouse.left);
}


void GLMapCanvas::OnLeftClickRelease(wxMouseEvent& event)
{
	m_mouse.left = false;

	HandleMouseEvents(0, true, false);
}


void GLMapCanvas::OnRightClickPress(wxMouseEvent& event)
{
	m_mouse.right = true;
}


void GLMapCanvas::OnRightClickRelease(wxMouseEvent& event)
{
	m_mouse.right = false;
	HandleMouseEvents(0, false, true);
}


void GLMapCanvas::OnMouseMove(wxMouseEvent& event)
{
	m_mouse.previous = m_mouse.pos;
	m_mouse.pos = event.GetPosition();


	if( m_mouse.left )
	{
		wxPoint gridPrevious = MapHelper::SnapToIndexGrid( m_mouse.previous, Tile::TileSize );
		wxPoint gridPosition = MapHelper::SnapToIndexGrid( m_mouse.pos, Tile::TileSize );

		//Check if mouse changed to new grid location
		if( gridPrevious != gridPosition )
		{
			wxPoint offsetGridPos = MapHelper::SnapToIndexGrid( m_parent->GetScrollbarPixelPositions(), Tile::TileSize )
				+ gridPosition;

			Editor->GetActiveMapLayer()->AddTileSelection( offsetGridPos );
		}
	}


	HandleMouseEvents(0, false, false);
	printf("%d, %d\n", m_mouse.pos.x, m_mouse.pos.y);
}


void GLMapCanvas::OnMouseLeaveWindow(wxMouseEvent& event)
{
	m_mouse.inWindow = false;
	m_mouse.left = false;
	m_mouse.right = false;

	Refresh(true);
}


void GLMapCanvas::OnMouseEnterWindow(wxMouseEvent& event)
{
	printf("dfgkhbhfbl\n");
	m_mouse.inWindow = true;
}


void GLMapCanvas::OnMouseWheel(wxMouseEvent& event)
{
}




