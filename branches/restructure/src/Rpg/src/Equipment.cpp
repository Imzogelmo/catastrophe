// catastrophe rpg engine
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include "Item.h"
#include "Inventory.h"
#include "Equipment.h"



Equipment::Equipment()
{
}


void Equipment::Equip( Item* item, Inventory* source )
{
	m_items.push_back(item);
	m_combinedAttributes += item->GetAttributes();

	if(source != 0)
	{
		source->Remove( item, 1 );
	}
}


void Equipment::Unequip( const Item* item, Inventory* dest )
{
	size_t index = 0;
	if( Find(item, index) )
	{
		Unequip(index, dest);
	}
}


void Equipment::Unequip( size_t index, Inventory* dest )
{
	if( index >= m_items.size() )
		return;

	Item* item = m_items[index];
	if(dest != 0)
	{
		dest->Add( item, 1 );
	}

	m_items.erase_at(index);
	m_combinedAttributes -= item->GetAttributes();
}


void Equipment::UnequipAll( Inventory* dest )
{
	if(dest != 0)
	{
		for( vec_type::iterator it = m_items.begin(); it != m_items.end(); ++it )
		{
			dest->Add(*it);
		}
	}

	m_items.clear();
	RecalculateCombinedAttributes();
}


bool Equipment::IsEquipped( const Item* item ) const
{
	size_t item_index;
	return Find(item, item_index);
}


bool Equipment::Find( const Item* item, size_t &item_index ) const
{
	vec_type::const_iterator it = fc::find( m_items.begin(), m_items.end(), item );
	if( it != m_items.end() )
	{
		item_index = size_t(it - m_items.begin());
		return true;
	}

	return false;
}


Item* Equipment::GetItem( size_t index )
{
	if( index < m_items.size() )
		return m_items[index];

	return 0;
}


const Item* Equipment::GetItem( size_t index ) const
{
	if( index < m_items.size() )
		return m_items[index];

	return 0;
}


void Equipment::RecalculateCombinedAttributes()
{
	m_combinedAttributes = Attributes();
	for( vec_type::iterator it = m_items.begin(); it != m_items.end(); ++it )
	{
		m_combinedAttributes += (*it)->GetAttributes();
	}
}



