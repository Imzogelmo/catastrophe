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
#include "InventorySlot.h"
#include "Item.h"


InventorySlot::InventorySlot() :
	m_item(null),
	m_amount(0),
	m_maxAmount(99),
	m_flags(0)
{
}


InventorySlot::InventorySlot( Item* item, u8 amount ) :
	m_item(item),
	m_amount(amount),
	m_maxAmount(99),
	m_flags(0)
{
	if( m_amount > m_maxAmount )
		m_amount = m_maxAmount;
}


InventorySlot::InventorySlot( Item* item, u8 amount, u8 maxAmount, u8 flags ) :
	m_item(item),
	m_amount(amount > maxAmount ? maxAmount : amount),
	m_maxAmount(maxAmount),
	m_flags(flags)
{
}


u8 InventorySlot::AddAmount( u8 amount )
{
	const u8 unused = GetUnusedAmount();
	if( unused < amount )
		amount -= (amount - unused);

	m_amount += amount;
	return amount;
}


u8 InventorySlot::RemoveAmount( u8 amount )
{
	u8 amountRemoved = (m_amount < amount ? m_amount : amount);
	m_amount -= amountRemoved;

	return amountRemoved;
}


void InventorySlot::Combine( InventorySlot& inventorySlot )
{
	u8 amountAdded = AddAmount(inventorySlot.m_amount);
	inventorySlot.RemoveAmount(amountAdded);
}


void InventorySlot::SetItem( Item* item )
{
	m_item = item;
}


void InventorySlot::SetAmount( u8 amount )
{
	m_amount = (amount < m_maxAmount ? amount : m_maxAmount);
}


void InventorySlot::SetMaxAmount( u8 maxAmount )
{
	if( m_amount > maxAmount )
		m_amount = maxAmount;

	m_maxAmount = maxAmount;
}

