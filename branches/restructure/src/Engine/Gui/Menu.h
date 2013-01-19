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

#include "Widget.h"

CE_NAMESPACE_BEGIN


class CE_API Menu : public Widget
{
public:
	Menu();

	void Update();
	void Render( SpriteBatch* spritebatch );

	void AddItem( Widget* item );
	void InsertItem( size_t index, Widget* item );
	void RemoveItem( Widget* item );
	void RemoveItem( size_t index );
	void RemoveAllItems();

	void SetDefaultItemSize( const Point& size );
	void SetAutoItemLayout( bool enable = true );

	void SetSelection( int index );
	int GetSelection() const;

	size_t GetNumItems() const;
	Widget* GetItem( size_t index );
	Widget* GetSelectedItem();

	bool IsSelected( size_t index ) const; //base already has this name...

protected:
	Widget			m_itemContent;
	int				m_selectedItem;

	Point			m_defaultItemSize;

	bool			m_autoItemLayout;

};


CE_NAMESPACE_END

