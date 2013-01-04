// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files ( the "Software" ), to deal
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


#include "Math/Rect.h"

#include "Gui/Widget.h"

#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4706 ) //assignment within a conditional expression
#endif

CE_NAMESPACE_BEGIN


Widget::Widget( Point pos, Point size ) :
	m_parent(0),
	m_pos(pos),
	m_size(size),
	m_color(Color::White()),
	m_ref_count(1),
	m_active(false),
	m_selected(false),
	m_visible(true),
	m_focusable(false)
{
}


Widget::~Widget()
{
	RemoveAllChildren();
}


void Widget::Update()
{
	UpdateChildren();
}


void Widget::UpdateChildren()
{
	if( IsActive() )
	{
		for( child_vec_type::iterator it = m_children.begin(); it != m_children.end(); ++it )
		{
			(*it)->Update();
		}
	}
}


void Widget::Render( SpriteBatch* spritebatch )
{
	RenderChildren(spritebatch);
}


void Widget::RenderChildren( SpriteBatch* spritebatch )
{
	if( IsVisible() )
	{
		for( child_vec_type::iterator it = m_children.begin(); it != m_children.end(); ++it )
		{
			(*it)->Render(spritebatch);
		}
	}
}


void Widget::SetPosition( const Point& position )
{
	m_pos = position;
}


void Widget::SetSize( const Point& size )
{
	m_size = size;
}


void Widget::SetDimensions( const Rect& rect )
{
	SetPosition( rect.pos );
	SetSize( rect.size );
}


void Widget::SetColor( const Color& color )
{
	m_color = color;
}


void Widget::SetActive( bool enable )
{
	m_active = enable;
}


void Widget::SetFocusable( bool enable )
{
	m_focusable = enable;
}


void Widget::SetFocus( bool enable )
{
	if( m_focusable )
	{
		(void*)enable;
	}
}


void Widget::SetSelected( bool enable )
{
	m_selected = enable;
}


void Widget::SetVisible( bool enable )
{
	m_visible = enable;
}


void Widget::AddChild( Widget* element )
{
	InsertChild( m_children.size(), element );
}


void Widget::InsertChild( size_t index, Widget* element )
{
	if( index >= m_children.size() )
		index = m_children.size();

	if( !element || element == this || element->m_parent == this )
		return;

	for( Widget* parent = m_parent; parent != 0; parent = parent->m_parent )
	{
		if( parent == element )
			return;
	}

	m_children.insert_at( index, element );

	if( element->m_parent )
		element->m_parent->RemoveChild( element );

	element->m_parent = this;
}


void Widget::RemoveChild( Widget* element )
{
	for( child_vec_type::iterator it = m_children.begin(); it != m_children.end(); ++it )
	{
		if( *it == element )
		{
			element->m_parent = 0;
			m_children.erase( it );
			return;
		}
	}
}


void Widget::RemoveAllChildren()
{
	while( !m_children.empty() )
	{
		Widget* element = m_children.back();
		//element->Remove();
		element->m_parent = 0; //notify element.?..

		m_children.pop_back();
	}
}


void Widget::Remove()
{
	if( m_parent )
		m_parent->RemoveChild(this);
}


void Widget::SetParent( Widget* parent )
{
	if( parent )
		parent->AddChild(this);
}


bool Widget::HasFocus() const
{
	//return m_selected; //...not good
	return false;
}


void Widget::GetChildren( child_vec_type& dest, bool recurse ) const
{
	dest.clear();
	if( recurse )
	{
		for( child_vec_type::const_iterator it = m_children.begin(); it != m_children.end(); ++it )
		{
			Widget* child = *it;
			dest.push_back(child);
			if( !child->m_children.empty() )
			{
				child->GetChildren(dest, recurse);
			}
		}
	}
	else
	{
		dest = m_children;
	}
}


size_t Widget::GetNumChildren( bool recurse ) const
{
	size_t size = m_children.size();
	if( recurse )
	{
		for( child_vec_type::const_iterator it = m_children.begin(); it != m_children.end(); ++it )
			size += (*it)->GetNumChildren( true );
	}

	return size;
}


Widget* Widget::GetChild( size_t index ) const
{
	if( index < m_children.size() )
		return m_children[index];

	return 0;
}


Point Widget::GetScreenPosition() const
{
	Point screenPosition = m_pos;
	if( !IsRoot() )
	{
		screenPosition += m_parent->GetScreenPosition();
	}

	return screenPosition;
}


Rect Widget::GetDimensions() const
{
	return Rect(GetPosition(), GetSize());
}


bool Widget::IsRoot() const
{
	return GetParent() == 0;
}


Widget* Widget::GetRoot()
{
	Widget* parent = 0, *root = this;
	while( parent = root->GetParent() )
		root = parent;

	return root;
}


Rect Widget::GetBoundingRect() const
{
	Rect rect = Rect( GetScreenPosition(), GetSize() );

	for( child_vec_type::const_iterator it = m_children.begin(); it != m_children.end(); ++it )
	{
		Rect childRect = (*it)->GetBoundingRect();
		rect.Merge(childRect);
	}

	return rect;
}


template <class Compare>
void SortChildren( Compare comp )
{
	fc::sort( m_children.begin(), m_children.end(), comp );
}


CE_NAMESPACE_END

#ifdef _MSC_VER
	#pragma warning ( pop )
#endif

