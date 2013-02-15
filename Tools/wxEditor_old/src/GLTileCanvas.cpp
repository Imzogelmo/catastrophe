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

#include "GLTileCanvas.h"
#include "OpenGL.h"
#include "Editor.h"
#include "TileHelper.h"


SpriteBatch GLTileCanvas::m_spritebatch;
PrimitiveBatch GLTileCanvas::m_primbatch;
Primitive GLTileCanvas::m_prim;

//Template declaration
BEGIN_GLSCROLLEDWINDOW_EVENT_TABLE_TEMPLATE(GLTileCanvas)


BEGIN_EVENT_TABLE(GLTileCanvas, wxGLCanvas)
    EVT_SIZE				(GLTileCanvas::OnSize)
    EVT_PAINT				(GLTileCanvas::OnPaint)
	EVT_ERASE_BACKGROUND	(GLTileCanvas::OnEraseBackground)

	EVT_LEFT_DOWN			(GLTileCanvas::OnLeftClickPress)
	EVT_LEFT_UP				(GLTileCanvas::OnLeftClickRelease)
	EVT_RIGHT_DOWN			(GLTileCanvas::OnRightClickPress)
	EVT_RIGHT_UP			(GLTileCanvas::OnRightClickRelease)
	EVT_MOTION				(GLTileCanvas::OnMouseMove)
	EVT_LEAVE_WINDOW		(GLTileCanvas::OnMouseLeaveWindow)
	EVT_ENTER_WINDOW		(GLTileCanvas::OnMouseEnterWindow)
	EVT_MOUSEWHEEL			(GLTileCanvas::OnMouseWheel)

	EVT_KEY_DOWN			(GLTileCanvas::OnKeyDown)
	EVT_KEY_UP				(GLTileCanvas::OnKeyUp)
END_EVENT_TABLE()


GLTileCanvas::GLTileCanvas(GLScrolledWindow<GLTileCanvas>* parent, wxGLContext* glContext) :
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


GLTileCanvas::~GLTileCanvas()
{
}


GLScrolledWindow<GLTileCanvas>* GLTileCanvas::CreateInstance(wxWindow* parent, wxGLContext* glContext)
{
	return new GLScrolledWindow<GLTileCanvas>(parent, glContext);
}


void GLTileCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);
	OpenGL::PrepareRenderingContext(this, m_ptrGLContext);

	OpenGL::ClearFrameBuffer(Colorf::Black(0.f));
	OpenGL::SetOrtho( wxRect(GetSize()) );

	//OpenGL::EnableBatchRendering();
	//.....

	Tileset *tileset = Editor->GetActiveTileset();
	if(!tileset)
	{
		SwapBuffers();
		return;
	}

	m_spritebatch.Begin();
	m_primbatch.Begin();

	const uint tilesetWidth = tileset->Width();
	const uint tilesetHeight = tileset->Height();
	for(uint y(0); y < tilesetHeight; ++y)
	{
		for(uint x(0); x < tilesetWidth; ++x)
		{
			const Tile *tile = tileset->GetTile(x,y);
			if( tile )
			{
				wxPoint offsetGridPos = TileHelper::SnapToIndexGrid( m_parent->GetScrollbarPixelPositions(), Tile::TileSize );

				tile->Draw( &m_spritebatch,
					Vector2(x * 16, y * 16) - Vector2( offsetGridPos.x * 16, offsetGridPos.y * 16)
					);
			}
		}
	}

	m_spritebatch.Render();
	m_spritebatch.End();

	//Draw selected tiles
	wxRect sRect = TileHelper::SnapToGrid( m_selectedTileRect, Tile::TileSize );

	m_prim.Clear();
	OpenGL::DrawThickOutlineRect( &m_prim, sRect );

	//m_primbatch.DrawPrimitive( m_prim );
	//m_primbatch.Render();

	SwapBuffers();
}


void GLTileCanvas::Update()
{
}


void GLTileCanvas::Render()
{
}


void GLTileCanvas::OnSize( wxSizeEvent& event )
{
    // this is also necessary to update the context on some platforms
    wxGLCanvas::OnSize(event);

	wxSize size = event.GetSize();
	printf("TileCanvas::OnSize: %d, %d\n", size.x, size.y );

	this->SetSize(size);
	OpenGL::SetOrtho( wxRect(size) );
}


//Key events
void GLTileCanvas::OnKeyDown(wxKeyEvent& event)
{
	(void*)&event;
}


void GLTileCanvas::OnKeyUp(wxKeyEvent& event)
{
	(void*)&event;
}


void GLTileCanvas::HandleMouseEvents( int middlePos, bool leftRelease, bool rightRelease )
{
	if( m_mouse.left || leftRelease )
	{
		//m_selectedTileRect = m_mouse.GetHighlightedRect();
		m_selectedTileRect = TileHelper::SnapToGrid( m_mouse.GetHighlightedRect(), Tile::TileSize );
		Editor->GetTileSelection().Set( m_selectedTileRect, Tile::TileSize );
	}

	Refresh(true);
}



/////////////////////
//  Mouse events   //
/////////////////////

void GLTileCanvas::OnLeftClickPress(wxMouseEvent& event)
{
	m_mouse.left = true;
	m_mouse.clicked = TileHelper::SnapToGrid( m_mouse.pos, Tile::TileSize );

	printf("%d\n", m_mouse.left);
}


void GLTileCanvas::OnLeftClickRelease(wxMouseEvent& event)
{
	m_mouse.left = false;

	HandleMouseEvents(0, true, false);
}


void GLTileCanvas::OnRightClickPress(wxMouseEvent& event)
{
	m_mouse.right = true;
}


void GLTileCanvas::OnRightClickRelease(wxMouseEvent& event)
{
	m_mouse.right = false;
	HandleMouseEvents(0, false, true);
}


void GLTileCanvas::OnMouseMove(wxMouseEvent& event)
{
	m_mouse.previous = m_mouse.pos;
	m_mouse.pos = event.GetPosition();

	HandleMouseEvents(0, false, false);

	printf("%d, %d\n", m_mouse.pos.x, m_mouse.pos.y);
}


void GLTileCanvas::OnMouseLeaveWindow(wxMouseEvent& event)
{
	m_mouse.inWindow = false;
	m_mouse.left = false;
	m_mouse.right = false;
}


void GLTileCanvas::OnMouseEnterWindow(wxMouseEvent& event)
{
	m_mouse.inWindow = true;
}


void GLTileCanvas::OnMouseWheel(wxMouseEvent& event)
{
}

