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


#include <fc/math.h>
#include "InventoryItem.h"


InventoryItem::InventoryItem( Item* item, int amount, int maxAmount ) :
	m_item(item),
	m_amount(amount),
	m_maxAmount(maxAmount)
{
}


int InventoryItem::Add( int amount )
{
	if(amount < 0)
		return Remove( fc::abs(amount) );

	int num_added = amount;
	if( m_amount + amount > m_maxAmount )
	{
		num_added = m_maxAmount - m_amount;
	}

	m_amount += num_added;
	return num_added;
}


int InventoryItem::Remove( int amount )
{
	if(amount < 0)
		return Add( fc::abs(amount) );

	int num_removed = amount;
	if( m_amount - amount < 0 )
	{
		num_removed = m_maxAmount - m_amount;
	}

	m_amount -= num_removed;
	return num_removed;
}


void InventoryItem::SetItem( Item* item )
{
	m_item = item;
	if(!m_item)
		m_amount = 0;
}


void InventoryItem::SetAmount( int amount )
{
	if(amount < 0)
		amount = 0;
	m_amount = (amount < m_maxAmount ? amount : m_maxAmount);
}


void InventoryItem::SetMaxAmount( int maxAmount )
{
	if(maxAmount < 0)
		maxAmount = 0;
	if(m_amount > maxAmount)
		m_amount = maxAmount;

	m_maxAmount = maxAmount;
}

