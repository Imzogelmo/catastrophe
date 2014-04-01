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

#include "Item.h"
#include "Inventory.h"
#include "Database.h"


Inventory::Inventory() :
	m_items(),
	m_maxSize(size_t(-1))
{
}


void Inventory::Reserve( size_t maxItems )
{
	m_items.reserve(maxItems);
}


void Inventory::Resize( size_t maxItems )
{
	m_items.resize( maxItems, InventoryItem() );
}


void Inventory::Clear()
{
	m_items.clear();
}


int Inventory::FindFirstFreeSlot() const
{
	int i(0);
	int size = (int)m_items.size();
	for( ; i < size; ++i )
	{
		if( m_items[i].IsEmpty() )
			return i;
	}

	return -1;
}


void Inventory::Add( const InventoryItem& inventoryItem )
{
	Add( inventoryItem.GetItem(), inventoryItem.GetAmount() );
}


void Inventory::Add( int id, int count )
{
	Item* item = GetDatabase()->GetItem(id);
	Add( item, count );
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
		m_items.push_back(InventoryItem(item, count));
	}
}


void Inventory::Add( const InventoryItem& inventoryItem )
{
	if( inventoryItem.IsEmpty() )
		return;

	Item* item = inventoryItem.GetItem();
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
		m_items.push_back(InventoryItem(item, count));
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
		i.RemoveAmount(count);
		if( i.IsEmpty() )
		{
			RemoveFromInventory(index);
		}
	}
}


void Remove( int id, int count )
{
}


void Inventory::RemoveFromInventory( int index )
{
	if( (size_t)index >= m_items.size() )
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
	// If we can't have duplicates then there is nothing to do.
	if( !GetPolicyCanContainDuplicates() )
		return;

	for( vec_type::iterator it = m_items.begin(); it < m_items.end(); ++it )
	{
		if( !it->IsValid() )
			continue;

		vec_type::iterator next = it + 1;
		for( ; next != m_items.end(); ++next )
		{
			if( it->GetItem() == next->GetItem() )
			{
				// Simply combine the two as best as possible.
				it->Combine(*next);

				// If they were successfully combined then check if we should compact the array.
				if( next->IsEmpty() && GetPolicyEraseOnRemove() )
				{
					RemoveFromInventory( int(next - m_items.begin()) );
					--next;
				}
			}
		}
	}
}


void Inventory::Swap( int first, int second )
{
	const int size = (int)m_items.size();
	if( first < size && second < size )
	{
		fc::swap( m_items[first], m_items[second] );
	}
}


void Inventory::Splice( Inventory& other )
{
	for( vec_type::iterator it = other.m_items.begin(); it != other.m_items.end(); ++it )
	{
		if( it->IsValid() )
			Add(*it);
	}

	other.Clear();
}


void Inventory::Splice( Inventory& other, int index )
{
	if( index < other.Size() )
	{
		Add( other.m_items[index] );
		other.RemoveFromInventory(index);
	}
}


bool Inventory::Contains( const Item* item ) const
{
	return Find(item) != -1;
}


int Inventory::Find( const Item* item ) const
{
	if( item )
	{
		for( vec_type::const_iterator it = m_items.begin(); it < m_items.end(); ++it )
		{
			if( it->GetItem() == item )
				return int(it - m_items.begin());
		}
	}

	return -1;
}


Item* Inventory::GetItem( int index ) const
{
	if( (size_t)index < m_items.size() )
		return m_items[index].GetItem();

	return 0;
}


Item* Inventory::GetItem( const fc::string& name ) const
{
	for( vec_type::const_iterator it = m_items.begin(); it != m_items.end(); ++it )
	{
		Item* item = it->GetItem();
		if( item && item->name == name )
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


InventoryItem& Inventory::operator []( int index )
{
	ASSERT((size_t)index < m_items.size());
	return m_items[index];
}


const InventoryItem& Inventory::operator []( int index ) const
{
	ASSERT((size_t)index < m_items.size());
	return m_items[index];
}
