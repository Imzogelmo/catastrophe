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


#include "Gui/MenuElement.h"


CE_NAMESPACE_BEGIN



MenuElement::MenuElement() :
	Widget(),
	m_selectedItem(0)
{
	m_itemContent.SetParent(this);
}


void MenuElement::Update()
{
	this->Widget::Update();
	if( IsActive() )
	{
		m_itemContent.Update();
	}
}


void MenuElement::Render( SpriteBatch* spritebatch )
{
	this->Widget::Render(spritebatch);
	if( IsVisible() )
	{
		m_itemContent.Render(spritebatch);
	}
}


void MenuElement::AddItem( Widget* item )
{
	m_itemContent.AddChild( item );

	if( item && m_autoItemLayout ) //todo: ......
	{
		if( item->GetSize() == Point::Zero )
		{
			item->SetSize(m_defaultItemSize);
		}
		if( item->GetPosition() == Point::Zero )
		{
			Point pos = Point::Zero;
			pos.y = (int)GetNumItems() * m_defaultItemSize.y;
			item->SetPosition(m_defaultItemSize);
		}
	}
}


void MenuElement::InsertItem( size_t index, Widget* item )
{
	m_itemContent.InsertChild(index, item);
}


void MenuElement::RemoveItem( Widget* item )
{
	m_itemContent.RemoveChild( item );
}


void MenuElement::RemoveItem( size_t index )
{
	m_itemContent.RemoveChild( GetItem(index) );
}


void MenuElement::RemoveAllItems()
{
	m_itemContent.RemoveAllChildren();
}


void MenuElement::SetDefaultItemSize( const Point& size )
{
	m_defaultItemSize = size;
}


void MenuElement::SetAutoItemLayout( bool enable )
{
	m_autoItemLayout = enable;
}


void MenuElement::SetSelection( int index )
{
	m_selectedItem = index;
}


int MenuElement::GetSelection() const
{
	return m_selectedItem;
}


size_t MenuElement::GetNumItems() const
{
	return m_itemContent.GetNumChildren();
}


Widget* MenuElement::GetItem( size_t index )
{
	return m_itemContent.GetChild(index);
}


Widget* MenuElement::GetSelectedItem()
{
	return GetItem( (size_t)m_selectedItem );
}


bool MenuElement::IsSelected( size_t index ) const
{
	return m_selectedItem == index;
}



CE_NAMESPACE_END




