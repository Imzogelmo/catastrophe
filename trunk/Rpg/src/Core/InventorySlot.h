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

#pragma once

#include "Common.h"


enum InventorySlotFlags
{
	/// Flag checking if the item was newly acquired in the inventory.
	InventorySlotFlag_NewItem = 1
};


/**
 * @InventorySlot
 * class that holds an item pointer and an amount.
 * *note* - Item* is allowed to be null.
 * (for example, inventories with blank spots.)
 */

class RPG_API InventorySlot
{
public:

	InventorySlot();
	InventorySlot( Item* item, u8 amount );
	InventorySlot( Item* item, u8 amount, u8 maxAmount, u8 flags = 0 );

	/// Adds an amount. Returns the amount that could be successfully added.
	u8 AddAmount( u8 amount );

	/// Removes an amount. Returns the amount that could be successfully removed.
	u8 RemoveAmount( u8 amount );

	/// Adds an amount to this item equal to the amount of the secondary item.
	void Combine( InventorySlot& inventorySlot );

	/// Gets the item pointed to by this slot. (The pointer can be null)
	Item* GetItem() const { return m_item; }

	/// Sets the item used by this slot.
	void SetItem( Item* item );

	/// Gets the amount of items stored.
	u8 GetAmount() const { return m_amount; }

	/// Sets the amount of items in this slot.
	void SetAmount( u8 amount );

	/// Gets the maximum amount of items this slot can hold
	u8 GetMaxAmount() const { return m_maxAmount; }

	/// Set the maximum amount of items this slot can hold
	void SetMaxAmount( u8 maxAmount );

	/// Returns the amount of items that can be added to this slot before it is full.
	u8 GetUnusedAmount() const { return m_maxAmount - m_amount; }

	u8 GetFlags() const { return m_flags; }
	bool IsNull() const { return m_item == 0; }
	bool IsEmpty() const { return m_amount == 0; }
	bool IsFull() const { return m_amount == m_maxAmount; }
	void SetEmpty() { m_amount = 0; }

protected:
	Item*	m_item;
	u8		m_amount;
	u8		m_maxAmount;
	u8		m_flags;
	//u8		m_unused;

};

