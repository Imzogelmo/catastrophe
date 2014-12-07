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

#include <fc/sort.h>

#include "Item.h"
#include "Inventory.h"


Inventory::Inventory() :
	m_itemSlots(),
	m_maxSize(u32(-1))
{
}


void Inventory::SetCapacity( u32 maxItems )
{
	if( m_isFixedSize )
	{
		// If the inventory shrinks then compress it to avoid possible loss of items.
		if( maxItems < m_itemSlots.size() )
			Compress();

		m_itemSlots.resize(maxItems, InventorySlot());
	}
	else
	{
		// If we are already auto-sized there's nothing to do
		// except make sure that we have enough capacity to hold all the items.
		if( m_itemSlots.capacity() < maxItems )
			m_itemSlots.reserve(maxItems);
	}
}


u32 Inventory::GetCapacity() const
{
	if( m_isFixedSize )
		return m_itemSlots.size();
	
	return m_itemSlots.capacity();
}


void Inventory::Clear()
{
	if( m_isFixedSize )
		fc::fill(m_itemSlots.begin(), m_itemSlots.end(), InventorySlot());
	else
		m_itemSlots.clear();
}


int Inventory::FindFirstFreeSlot( int startSlot ) const
{
	if( (u32)startSlot < m_itemSlots.size() )
	{
		for( vec_type::const_iterator it = m_itemSlots.begin() + startSlot; it < m_itemSlots.end(); ++it )
			if( it->IsEmpty() )
				return (it - m_itemSlots.begin());
	}

	return -1;
}


int Inventory::FindFirstUsedSlot( int startSlot ) const
{
	if( (u32)startSlot < m_itemSlots.size() )
	{
		for( vec_type::const_iterator it = m_itemSlots.begin() + startSlot; it < m_itemSlots.end(); ++it )
			if( it->IsEmpty() )
				return (it - m_itemSlots.begin());
	}

	return -1;
}


void Inventory::Add( Item* item, u8 amount )
{
	Add(InventorySlot(item, amount));
}


void Inventory::Add( InventorySlot inventorySlot )
{
	if( inventorySlot.IsEmpty() )
		return;

	int currentSlot = 0;
	do
	{
		currentSlot = FindFirstOf(inventorySlot.GetItem(), currentSlot);
		if( currentSlot != -1 )
		{
			m_itemSlots[currentSlot].Combine(inventorySlot);
		}

		else // Item not found, add a new slot
		{
			if( !m_isFixedSize )
			{
				m_itemSlots.push_back(inventorySlot);
				break;
			}
			else
			{
				// The inventory is static, so we insert into the first free slot
				int freeSlot = FindFirstFreeSlot();
				if( freeSlot != -1 )
					m_itemSlots[freeSlot] = inventorySlot;

				break;
			}
		}
	}
	while( m_allowDuplicateItems && inventorySlot.GetAmount() != 0 );

}


void Inventory::RemoveItem( Item* item, u8 amount )
{
	if( item == null )
		return;

	int lastSlot = FindLastOf(item);
	if( lastSlot != -1 )
	{
		InventorySlot & inventorySlot = m_itemSlots[lastSlot];
		inventorySlot.RemoveAmount(amount);

		if( inventorySlot.IsEmpty() )
			RemoveSlot(lastSlot);
	}
}


void Inventory::RemoveSlot( int slot )
{
	if( (u32)slot < m_itemSlots.size() )
	{
		if( m_isFixedSize )
			m_itemSlots[slot] = InventorySlot();

		else
			m_itemSlots.erase_at(slot);
	}
}


u8 Inventory::AddItemsToSlot( int slot, u8 amount )
{
	if( (u32)slot < m_itemSlots.size() )
		return m_itemSlots[slot].AddAmount(amount);

	return 0;
}


u8 Inventory::RemoveItemsFromSlot( int slot, u8 amount )
{
	if( (u32)slot < m_itemSlots.size() )
		return m_itemSlots[slot].RemoveAmount(amount);

	return 0;
}


void Inventory::Compress()
{
	vec_type::iterator lastValidPosition = m_itemSlots.begin();
	for( vec_type::iterator it = m_itemSlots.begin(); it < m_itemSlots.end(); ++it )
	{
		vec_type::iterator next = it + 1;
		if( it->IsEmpty() )
		{
			for( ; next != m_itemSlots.end(); ++next )
			{
				if( !next->IsEmpty() )
				{
					fc::swap(*it, *next);
					++lastValidPosition;
					break;
				}
			}
		}
		else
		{
			++lastValidPosition;
		}

		// Try and combine any duplicates.
		for( ; next != m_itemSlots.end(); ++next )
		{
			if( it->GetItem() == next->GetItem() )
			{
				// Simply combine the two as best as possible.
				it->Combine(*next);
			}
		}
	}

	if( !m_isFixedSize )
	{
		if( lastValidPosition < m_itemSlots.end() )
			m_itemSlots.erase( lastValidPosition, m_itemSlots.end());
	}
}


void Inventory::SwapSlots( int firstSlot, int secondSlot )
{
	const u32 size = m_itemSlots.size();
	if( (u32)firstSlot < size && (u32)secondSlot < size )
		fc::swap( m_itemSlots[firstSlot], m_itemSlots[secondSlot] );
}


void Inventory::Splice( Inventory& other )
{
	if( this != &other )
	{
		for( vec_type::iterator it = other.m_itemSlots.begin(); it != other.m_itemSlots.end(); ++it )
			if( !it->IsEmpty() )
				Add(*it);

		other.Clear();
	}
}


void Inventory::Splice( Inventory& other, int slot )
{
	if( this != &other )
	{
		if( (u32)slot < other.Size() )
		{
			Add( other.m_itemSlots[slot] );
			other.RemoveSlot(slot);
		}
	}
}


bool Inventory::Contains( Item* item ) const
{
	return FindFirstOf(item) != -1;
}


int Inventory::FindFirstOf( Item* item, int startSlot ) const
{
	if( (u32)startSlot < m_itemSlots.size() )
	{
		for( vec_type::const_iterator it = m_itemSlots.begin() + startSlot; it != m_itemSlots.end(); ++it )
			if( it->GetItem() == item )
				return int(it - m_itemSlots.begin());
	}

	return -1;
}


int Inventory::FindLastOf( Item* item ) const
{
	for( vec_type::const_iterator it = m_itemSlots.end(); it != m_itemSlots.begin(); )
		if( (--it)->GetItem() == item )
			return int(it - m_itemSlots.begin());

	return -1;
}


int Inventory::GetItemSlotByItemName( const fc::string& itemName ) const
{
	for( vec_type::const_iterator it = m_itemSlots.begin(); it != m_itemSlots.end(); ++it )
	{
		Item* item = it->GetItem();
		if( item && item->name == itemName )
		{
			return (it - m_itemSlots.begin());
		}
	}

	return -1;
}


u32 Inventory::Size() const
{
	//todo: figure out a way to cache this...
	if( m_isFixedSize )
	{
		u32 itemCount = 0;
		for( vec_type::const_iterator it = m_itemSlots.begin(); it != m_itemSlots.end(); ++it )
			if( !it->IsEmpty() )
				++itemCount;

		return itemCount;
	}

	return m_itemSlots.size();
}


bool Inventory::IsEmpty() const
{
	//todo: figure out a way to cache this...
	if( m_isFixedSize )
	{
		for( vec_type::const_iterator it = m_itemSlots.begin(); it != m_itemSlots.end(); ++it )
			if( !it->IsEmpty() )
				return false;

		return true;
	}

	return m_itemSlots.empty();
}


bool Inventory::IsFull() const
{
	//todo: figure out a way to cache this...
	return (m_isFixedSize ? (FindFirstFreeSlot() == -1) : false);
}

/*
template <class Compare>
void Inventory::Sort( Compare comp )
{
	fc::stable_sort( m_itemSlots.begin(), m_itemSlots.end(), comp );
}
*/

InventorySlot& Inventory::operator []( int slot )
{
	ASSERT((u32)slot < m_itemSlots.size());
	return m_itemSlots[slot];
}


const InventorySlot& Inventory::operator []( int slot ) const
{
	ASSERT((u32)slot < m_itemSlots.size());
	return m_itemSlots[slot];
}


void Inventory::SetAllowDuplicateItems( bool value )
{
	if( m_allowDuplicateItems == value )
		return;

	m_allowDuplicateItems = value;
	if( value == false )
		Compress();
}


void Inventory::SetIsFixedSize( bool value )
{
	m_isFixedSize = value;
}

