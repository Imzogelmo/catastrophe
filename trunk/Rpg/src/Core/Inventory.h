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

#include <fc/vector.h>
#include <fc/string.h>

#include "Common.h"
#include "InventorySlot.h"


class RPG_API Inventory
{
public:
	typedef fc::vector<InventorySlot> vec_type;

	Inventory();

	/// Sets the maximum number ot item slots this inventory can hold.
	void SetCapacity( u32 maxItems );

	/// Gets the maximum number ot item slots this inventory can hold.
	u32 GetCapacity() const;

	/// Clears the contents of this inventory.
	void Clear();

	/// Gets the index of the first unused slot, or -1 if none are found.
	int FindFirstFreeSlot( int startSlot = 0 ) const;

	/// Gets the index of the first valid slot, or -1 if none are found.
	int FindFirstUsedSlot( int startSlot = 0 ) const;

	/// Adds an InventorySlot into the first unused slot.
	void Add( InventorySlot inventorySlot );

	/// Adds an Item into the first unused slot.
	void Add( Item* item, u8 amount = 1 );

	/// Removes an amount from the last slot that contains item.
	void RemoveItem( Item* item, u8 amount = 1 );

	/// Empties the slot of any items if size is fixed, otherwise removes it.
	void RemoveSlot( int slot );

	/// Adds an amount to a slot and returns the amount that could be added.
	u8 AddItemsToSlot( int slot, u8 amount = 1 );

	/// Removes an amount to a slot and returns the amount that could be removed.
	u8 RemoveItemsFromSlot( int slot, u8 amount = 1 );

	/// Compresses any unused slots, while combining any duplicates.
	void Compress();

	/// Swaps the two inventory slots.
	void SwapSlots( int firstSlot, int secondSlot );

	/// Add the contents of another Inventory to this one.
	void Splice( Inventory& other );

	/// Add the contents of a slot in another Inventory at to this one.
	void Splice( Inventory& other, int index );

	/// Returns true if any slots contain item.
	bool Contains( Item* item ) const;

	/// Returns the first slot which contains item, or -1 if none exist.
	int FindFirstOf( Item* item, int startSlot = 0 ) const;

	/// Returns the last slot which contains item, or -1 if none exist.
	int FindLastOf( Item* item ) const;

	/// Returns the number of items in this inventory.
	u32 Size() const;

	/// Returns true if there are no items in this inventory.
	bool IsEmpty() const;

	/// Returns true if no more slots can be added.
	bool IsFull() const;

	/// Returns the first slot which contains an item that matches name, or -1 if none exist.
	int GetItemSlotByItemName( const fc::string& itemName ) const;

	//template <class Compare> void Sort( Compare comp = Compare() );


	InventorySlot& operator []( int slot );
	const InventorySlot& operator []( int slot ) const;

	InventorySlot& GetSlot( int slot ) { return operator[](slot); }
	const InventorySlot& GetSlot( int slot ) const { return operator[](slot); }

	/// Sets the conents of an InventorySlot at a given slot.
	void SetSlot( int slot, const InventorySlot& inventorySlot ) { GetSlot(slot) = inventorySlot; }

	/// Whether or not this inventory is allowed to have duplicate item slots.
	bool GetAllowDuplicateItems() const { return m_allowDuplicateItems; }
	void SetAllowDuplicateItems( bool value );

	/// Whether or not this inventory is allowed to manage its own size.
	bool GetIsFixedSize() const { return m_isFixedSize; }
	void SetIsFixedSize( bool value );


protected:
	vec_type	m_itemSlots;
	u32			m_maxSize;

	bool		m_allowDuplicateItems;
	bool		m_isFixedSize;

};



