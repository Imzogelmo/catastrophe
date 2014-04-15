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
#include "Item.h"

int InventoryItem::m_defaultMax = 99;


InventoryItem::InventoryItem( Item* item, int amount, int maxAmount ) :
	m_item(item),
	m_amount(amount),
	m_maxAmount(maxAmount)
{
}


int InventoryItem::AddAmount( int amount )
{
	if( amount < 0 )
		return RemoveAmount( -amount );

	int numAdded = amount;
	if( m_amount + amount > m_maxAmount )
	{
		numAdded = m_maxAmount - m_amount;
	}

	m_amount += numAdded;
	return numAdded;
}


int InventoryItem::RemoveAmount( int amount )
{
	if( amount < 0 )
		return AddAmount( -amount );

	int numRemoved = amount;
	if( m_amount - amount < 0 )
	{
		numRemoved = m_maxAmount - m_amount;
	}

	m_amount -= numRemoved;
	return numRemoved;
}


void InventoryItem::Combine( InventoryItem& inventoryItem )
{
	int amountAdded = AddAmount(inventoryItem.m_amount);
	inventoryItem.RemoveAmount(amountAdded);
}


int InventoryItem::GetItemType() const
{
	return m_item ? m_item->type : -1;
}


int InventoryItem::GetItemSubType() const
{
	return m_item ? m_item->type : -1;
}


int InventoryItem::GetItemId() const
{
	return m_item ? m_item->id : -1;
}


void InventoryItem::SetItem( Item* item )
{
	m_item = item;
	if(!m_item)
		m_amount = 0;
}


void InventoryItem::SetAmount( int amount )
{
	if( amount < 0 )
		amount = 0;

	m_amount = (amount < m_maxAmount ? amount : m_maxAmount);
}


void InventoryItem::SetMaxAmount( int maxAmount )
{
	if( maxAmount < 0 )
		maxAmount = 0;

	if( m_amount > maxAmount )
		m_amount = maxAmount;

	m_maxAmount = maxAmount;
}


void InventoryItem::SetGlobalDefaultMaxAmount( int amount )
{
	m_defaultMax = amount;
}

