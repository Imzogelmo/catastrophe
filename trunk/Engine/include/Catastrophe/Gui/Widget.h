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

#include <fc/fixed_vector.h>

#include "../Common.h"
#include "../Math/Point.h"
#include "../Math/Vector2.h"
#include "../Math/Color.h"

CE_NAMESPACE_BEGIN


class Widget // todo: should be ref counted?? ..
{
public:
	typedef fc::fixed_vector<Widget*, 8>		child_vec_type; //todo: use memory pools instead.

	Widget( Point pos = Point::Zero, Point size = Point::Zero ); //zero...?

	virtual ~Widget();
	virtual void Update();
	virtual void Render( SpriteBatch* spritebatch );

	virtual void UpdateChildren();
	virtual void RenderChildren( SpriteBatch* spritebatch );

	//virtual void OnInput( InputStates i ); //not easy to do right now...
	//bool SerializeXml();
	//bool DeserializeXml();

	void SetPosition( const Point& position );
	void SetPosition( int x, int y ) { SetPosition( Point(x, y) ); }
	void SetX( int x ) { SetPosition( Point( x, m_pos.y ) ); }
	void SetY( int y ) { SetPosition( Point( m_pos.x, y ) ); }
	void SetSize( const Point& size );
	void SetSize( int width, int height ) { SetSize( Point(width, height) ); }
	void SetWidth( int width ) { SetSize( Point( width, m_size.y ) ); }
	void SetHeight( int height ) { SetSize( Point( m_size.x, height ) ); }
	void SetDimensions( const Rect& rect );
	void SetColor( const Color& color );
	void SetActive( bool enable );
	void SetFocus( bool enable );
	void SetSelected( bool enable );
	void SetVisible( bool enable );
	void SetFocusable( bool enable );

	//void BringToFront();
	//bool IsFront(); 

	void AddChild( Widget* element );
	void InsertChild( size_t index, Widget* element );
	void RemoveChild( Widget* element );
	void RemoveAllChildren();
	void Remove();
	void SetParent( Widget* parent );

	const Point& GetPosition() const { return m_pos; }
	const Point& GetSize() const { return m_size; }
	int GetWidth() const { return m_size.x; }
	int GetHeight() const { return m_size.y; }
	Rect GetDimensions() const;
	Point GetScreenPosition() const;
	Vector2 GetScreenPositionAsVector2() const;
	Vector2 GetSizeAsVector2() const;

	const Color& GetColor() const { return m_color; }

	bool HasFocus() const;
	bool IsRoot() const;
	bool IsActive() const { return m_active; }
	bool IsSelected() const { return m_selected; }
	bool IsVisible() const { return m_visible; }
	bool IsFocusable() const { return m_focusable; }

	size_t GetNumChildren( bool recurse = false ) const;
	Widget* GetChild( size_t index ) const;

	const child_vec_type& GetChildren() const { return m_children; }
	void GetChildren( child_vec_type& dest, bool recurse = false ) const;

	Widget* GetParent() const { return m_parent; }
	Widget* GetRoot();
	Rect GetBoundingRect() const;

	template <class Compare>
	void SortChildren( Compare comp );

protected:
	Widget*			m_parent;
	child_vec_type	m_children;

	Point			m_pos;
	Point			m_size;
	Color			m_color; //move me: ...

	bool			m_active;
	bool			m_selected;
	bool			m_visible;
	bool			m_focusable;


};





CE_NAMESPACE_END