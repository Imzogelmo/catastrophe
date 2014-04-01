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


/**
 * @InventoryItem
 * class that holds an item pointer and an amount.
 * *note* - Item* is allowed to be null.
 * (for example, inventories with blank spots.)
 */
class RPG_API InventoryItem
{
public:
	InventoryItem( Item* item = 0, int amount = 0, int maxAmount = m_defaultMax );

	/// Adds an amount. Returns the amount that could be successfully added.
	int AddAmount( int amount = 1 );

	/// Removes an amount. Returns the amount that could be successfully removed.
	int RemoveAmount( int amount = 1 );

	/// Adds an amount to this item equal to the amount of the secondary item.
	void Combine( const InventoryItem& inventoryItem );

	/// Get the pointer to the item.
	Item* GetItem() const { return m_item; }

	int GetAmount() const { return m_amount; }
	int GetMaxAmount() const { return m_maxAmount; }
	int GetUnusedAmount() const { return m_maxAmount - m_amount; }

	int GetItemType() const;
	int GetItemSubType() const;
	int GetItemId() const;

	bool IsNull() const { return m_item == 0; } 
	bool IsEmpty() const { return m_amount == 0; } 
	void SetEmpty() { m_amount = 0; }

	void SetItem( Item* item );
	void SetAmount( int amount );
	void SetMaxAmount( int maxAmount );


	// sets the default max amount used to initialize an InventoryItem.
	static void SetGlobalDefaultMaxAmount( int amount ); //todo: this is depricated

protected:
	Item*	m_item;
	int		m_amount;
	int		m_maxAmount;

	static int m_defaultMax;

};
