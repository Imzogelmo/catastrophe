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



Equipment::Equipment() :
	m_items(),
	m_combinedAttributes()
{
}


void Equipment::Resize( u32 maxSlots )
{
	maxSlots = fc::min(maxSlots, GetMaxSlots());
	m_items.resize(maxSlots, null);
}


void Equipment::Equip( int slot, Item* item )
{
	if( (u32)slot < m_items.size() )
		m_items[slot] = item;
}


void Equipment::Unequip( int slot )
{
	if( (u32)slot < m_items.size() )
		m_items[slot] = null;
}


void Equipment::TransferToInventory( int slot, Inventory* destinationInventory )
{
	if( destinationInventory )
		destinationInventory->Add(GetSlot(slot));

	Unequip(slot);
}


void Equipment::UnequipAll()
{
	m_items.fill(null);
}


void Equipment::TransferAllToInventory( Inventory* destinationInventory )
{
	if( destinationInventory )
		for( array_type::iterator it = m_items.begin(); it != m_items.end(); ++it )
			destinationInventory->Add(*it);

	UnequipAll();
}


void Equipment::ReplaceSlot( int slot, Item* item, Inventory* destinationInventory )
{
	if( (u32)slot < m_items.size() )
	{
		if( destinationInventory )
			destinationInventory->Add(m_items[slot]);

		m_items[slot] = item;
	}
}


bool Equipment::Contains( Item* item ) const
{
	return Find(item) >= 0;
}


int Equipment::Find( Item* item ) const
{
	array_type::const_iterator it = fc::find( m_items.begin(), m_items.end(), item );
	if( it != m_items.end() )
		return (int)(it - m_items.begin());

	return -1;
}


Item* Equipment::GetSlot( int slot ) const
{
	if( (u32)slot < m_items.size() )
		return const_cast<Item*>(m_items[slot]);

	return null;
}


void Equipment::RecalculateCombinedAttributes()
{
	m_combinedAttributes = Attributes();

	for( array_type::iterator it = m_items.begin(); it != m_items.end(); ++it )
	{
		Item* item = *it;
		if( item && item->HasAttributes() )
			m_combinedAttributes += item->GetAttributes();
	}
}



