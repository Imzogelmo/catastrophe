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

#include <fc/vector.h>

#include "Forward.h"
#include "../Common.h"
#include "../Math/Vector2.h"
#include "../Math/Vector2.h"
#include "../Math/Color.h"

CE_NAMESPACE_BEGIN


class CE_API Widget
{
public:
	typedef fc::vector<Widget*>		child_vec_type;

	Widget( const Vector2 pos = Vector2::Zero, Vector2 size = Vector2::Zero );

	virtual ~Widget();
	virtual void Update();
	virtual void Render( SpriteBatch* spritebatch );

	virtual void UpdateChildren();
	virtual void RenderChildren( SpriteBatch* spritebatch );

	void SetPosition( const Vector2& position );
	void SetPosition( float x, float y ) { SetPosition( Vector2(x, y) ); }
	void SetX( float x ) { SetPosition( Vector2( x, m_pos.y ) ); }
	void SetY( float y ) { SetPosition( Vector2( m_pos.x, y ) ); }
	void SetSize( const Vector2& size );
	void SetSize( float width, float height ) { SetSize( Vector2(width, height) ); }
	void SetWidth( float width ) { SetSize( Vector2( width, m_size.y ) ); }
	void SetHeight( float height ) { SetSize( Vector2( m_size.x, height ) ); }
	void SetDimensions( const Rectf& rect );
	void SetActive( bool enable );
	void SetSelected( bool enable );
	void SetVisible( bool enable );
	void SetEnabled( bool enable );

	void AddChild( Widget* element );
	void InsertChild( size_t index, Widget* element );
	void RemoveChild( Widget* element );
	void RemoveAllChildren();
	void Remove();
	void SetParent( Widget* parent );

	const Vector2& GetPosition() const { return m_pos; }
	const Vector2& GetSize() const { return m_size; }
	float GetWidth() const { return m_size.x; }
	float GetHeight() const { return m_size.y; }
	Rectf GetDimensions() const;
	Vector2 GetScreenPosition() const;

	bool IsRoot() const;
	bool IsActive() const { return m_active; }
	bool IsSelected() const { return m_selected; }
	bool IsVisible() const { return m_visible; }
	bool IsLocked() const { return m_locked; }
	bool IsEnabled() const { return m_enabled; }

	size_t GetNumChildren( bool recurse = false ) const;
	Widget* GetChild( size_t index ) const;
	bool HasChild( Widget* element, size_t* index = 0 ) const;

	const child_vec_type& GetChildren() const { return m_children; }
	void GetChildren( child_vec_type& dest, bool recurse = false ) const;

	Widget* GetParent() const { return m_parent; }
	Widget* GetRoot();
	Rectf GetBoundingRect( bool recurse = false ) const;

	template <class Compare>
	void SortChildren( Compare comp );

	void AddRef() { ++m_ref_count; }
	void ReleaseRef() { --m_ref_count; }

protected:
	Widget*			m_parent;
	child_vec_type	m_children;

	Vector2			m_pos;
	Vector2			m_size;

	int				m_ref_count;
	bool			m_active;
	bool			m_selected;
	bool			m_visible;
	bool			m_enabled;
	bool			m_locked;

};




CE_NAMESPACE_END