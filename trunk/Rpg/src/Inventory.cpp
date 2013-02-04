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

#include <fc/vector.h>
#include <fc/sort.h>

#include "Inventory.h"


Inventory::Inventory() :
	m_items(),
	m_maxSize(size_t(-1))
{
}


void Inventory::Reserve( size_t max_items )
{
	m_items.reserve(max_items);
}


void Inventory::Clear()
{
	m_items.clear();
}


void Inventory::Add( const InventoryItem& inventoryItem )
{
	Add( inventoryItem.GetItem(), inventoryItem.GetAmount() );
}


void Inventory::Add( Item* item, int count )
{
	if( !item )
		return;

	size_t index = 0;
	if( Find(item, index) )
	{
		if( GetPolicyCanContainDuplicates() )
		{
			m_items.push_back(InventoryItem(item, count));
		}
		else
		{
			m_items[index].Add(count);
		}
	}
	else if( !IsFull() )
	{
		m_items.push_back(item);
	}
}


void Inventory::Remove( Item* item, int count )
{
	if( !item )
		return;

	size_t index = 0;
	if( Find(item, index) )
	{
		InventoryItem & i = m_items[index];
		i.Remove(count);
		if( i.IsEmpty() )
		{
			RemoveFromInventory(index);
		}
	}
}


void Remove( int id, int count )
{
}


void Inventory::RemoveFromInventory( size_t index )
{
	if( index >= m_items.size() )
		return;

	if( GetPolicyEraseOnRemove() )
	{
		m_items.erase_at(index);
	}
	else
	{
		m_items[index].SetEmpty();
	}
}


void Inventory::RemoveFromInventory( Item* item )
{
	if( !item )
		return;

	for( size_t i(0); i < m_items.size(); ++i )
	{
		if( m_items[i].GetItem() == item )
		{
			RemoveFromInventory(i);
			if( GetPolicyEraseOnRemove() )
				--i;
		}
	}
}


void Inventory::Unique()
{
	for( vec_type::iterator it = m_items.begin(); it < m_items.end(); ++it )
	{
		vec_type::iterator next = it + 1;
		for( ; next != m_items.end(); ++next )
		{
			if( it->GetItem() == next->GetItem() )
			{
				it->Add( next->GetAmount() );
				RemoveFromInventory( size_t(next - m_items.begin()) );
				if( GetPolicyEraseOnRemove() )
					--next;
			}
		}
	}
}


void Inventory::Swap( size_t first, size_t second )
{
	const size_t size = m_items.size();
	if( first < size && second < size )
	{
		fc::swap( m_items[first], m_items[second] );
	}
}


void Inventory::Splice( Inventory& other )
{
	for( vec_type::iterator it = other.m_items.begin(); it != other.m_items.end(); ++it )
	{
		Add(*it);
	}

	other.Clear();
}


void Inventory::Splice( Inventory& other, size_t index )
{
	if( index < other.Size() )
	{
		Add( other.m_items.at(index) );
		other.RemoveFromInventory(index);
	}
}


bool Inventory::Contains( const Item* item ) const
{
	if( item )
	{
		for( vec_type::const_iterator it = m_items.begin(); it < m_items.end(); ++it )
		{
			if( it->GetItem() == item )
				return true;
		}
	}

	return false;
}


bool Inventory::Find( const Item* item, size_t &item_index ) const
{
	if( item )
	{
		for( vec_type::const_iterator it = m_items.begin(); it < m_items.end(); ++it )
		{
			if( it->GetItem() == item )
			{
				item_index = size_t(it - m_items.begin());
				return true;
			}
		}
	}

	return false;
}


Item* Inventory::GetItem( size_t index ) const
{
	if( index < m_items.size() )
		return m_items[index].GetItem();

	return 0;
}


Item* Inventory::GetItem( const fc::string& name ) const
{
	for( vec_type::const_iterator it = m_items.begin(); it != m_items.end(); ++it )
	{
		Item* item = it->GetItem();
		if( item && item->GetName() == name )
		{
			return item;
		}
	}

	return 0;
}


template <class Compare>
void Inventory::Sort( Compare comp )
{
	fc::sort( m_items.begin(), m_items.end(), comp );
}


InventoryItem& Inventory::operator []( size_t index )
{
	ASSERT(index < m_items.size());
	return m_items[index];
}


const InventoryItem& Inventory::operator []( size_t index ) const
{
	ASSERT(index < m_items.size());
	return m_items[index];
}
