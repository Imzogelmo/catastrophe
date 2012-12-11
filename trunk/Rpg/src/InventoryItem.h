
#pragma once

#include "Common.h"
#include "Item.h"


/**
 * @InventoryItem
 * class that holds an item pointer and an amount.
 * *note* - Item* is allowed to be null.
 * (for Inventories with blank spots for example)
 */
class InventoryItem
{
public:
	InventoryItem( Item* item = 0, int amount = 0, int maxAmount = 99 );

	// Add, Remove - returns the amount that could be successfully added or removed.
	int Add( int amount = 1 );
	int Remove( int amount = 1 );

	Item* GetItem() { return m_item; }
	const Item* GetItem() const { return m_item; }

	int GetAmount() const { return m_amount; }
	int GetMaxAmount() const { return m_maxAmount; }
	int GetUnusedAmount() const { return m_maxAmount - m_amount; }

	bool IsItem() const { return m_item != 0; } 
	bool IsEmpty() const { return m_item && m_amount == 0; } 
	void SetEmpty() { m_amount = 0; }

	void SetItem( Item* item );
	void SetAmount( int amount );
	void SetMaxAmount( int maxAmount );

protected:
	Item*	m_item; //should be const / mutable ??
	int		m_amount;
	int		m_maxAmount; //should this be universal??

};
