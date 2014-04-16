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


void Equipment::Equip( Item* item, Inventory* sourceInventory )
{
	if( !item )
		return;

	m_items.push_back(item);
	m_combinedAttributes += item->GetAttributes();

	if(sourceInventory != 0)
	{
		sourceInventory->Remove( item, 1 );
	}
}


void Equipment::Unequip( Item* item, Inventory* destinationInventory )
{
	if( !item )
		return;

	int index = Find(item);
	if( index >= 0 )
	{
		Unequip(index, destinationInventory);
	}
}


void Equipment::Unequip( int index, Inventory* destinationInventory )
{
	if( index >= m_items.size() )
		return;

	Item* item = m_items[index];
	if(destinationInventory != 0)
	{
		destinationInventory->Add( item, 1 );
	}

	m_items.erase_at(index);
	RecalculateCombinedAttributes();
}


void Equipment::UnequipAll( Inventory* destinationInventory )
{
	if(destinationInventory != 0)
	{
		for( vec_type::iterator it = m_items.begin(); it != m_items.end(); ++it )
		{
			destinationInventory->Add(*it);
		}
	}

	m_items.clear();
	RecalculateCombinedAttributes();
}


bool Equipment::IsEquipped( Item* item ) const
{
	return Find(item) >= 0;
}


int Equipment::Find( Item* item ) const
{
	vec_type::const_iterator it = fc::find( m_items.begin(), m_items.end(), item );
	if( it != m_items.end() )
		return (int)(it - m_items.begin());

	return -1;
}


bool Equipment::IsItemOfTypeEquipped( int itemType ) const
{
	return (GetItemIndexOfTypeEquipped(itemType) != -1);
}


int Equipment::GetItemIndexOfTypeEquipped( int itemType ) const
{
	for( vec_type::const_iterator it = m_items.begin(); it != m_items.end(); ++it )
	{
		if( (*it)->type == itemType )
			return int(it - m_items.begin());
	}

	return -1;
}


Item* Equipment::GetItemOfTypeEquipped( int itemType ) const
{
	int i = GetItemIndexOfTypeEquipped(itemType);
	return ( i != -1 ? m_items[i] : 0);
}


Item* Equipment::GetItem( int index ) const
{
	if( index < m_items.size() )
		return const_cast<Item*>(m_items[index]);

	return 0;
}


void Equipment::RecalculateCombinedAttributes()
{
	m_combinedAttributes = Attributes();
	for( vec_type::iterator it = m_items.begin(); it != m_items.end(); ++it )
	{
		Item* item = *it;
		if( item && item->HasAttributes() )
			m_combinedAttributes += item->GetAttributes();
	}
}



