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

#include <fc/dynamic_array.h>

#include "Common.h"
#include "Attributes.h"

//
//struct EquipmentSlot
//{
//	Item* item;
//
//	EquipmentSlot() : item(0) {}
//};
//

class RPG_API Equipment
{
public:
	typedef fc::dynamic_array<Item*> array_type;

	Equipment();

	void Resize( u32 maxSlots );

	u32 GetNumSlots() const { return m_items.size(); }
	u32 GetMaxSlots() const { return 8; } //magic number for now

	/// Equips an item in the given slot.
	void Equip( int slot, Item* item );

	/// Unequips an item in the given slot.
	void Unequip( int slot );

	/// Forcibly removes all eqipped items.
	void UnequipAll();

	/// Unequips the item contained in 'slot' and transfers it to inventory.
	void TransferToInventory( int slot, Inventory* destinationInventory );

	/// Unequips all items and transfers them to inventory.
	void TransferAllToInventory( Inventory* destinationInventory );

	/// Replaces the equipped item in a given slot with the new item, and transfers old item to inventory.
	void ReplaceSlot( int slot, Item* item, Inventory* destinationInventory );

	/// Returns true if item is equipped.
	bool Contains( Item* item ) const;

	/// Returns the first slot that contains item, or -1 if not found.
	int Find( Item* item ) const;

	/// Gets the item stored in a slot.
	Item* GetSlot( int slot ) const;

	array_type& GetEquippedItems() { return m_items; }
	const array_type& GetEquippedItems() const { return m_items; }

	/// Recalculates the attributes bonus malus values from all equipped items.
	/// *NOTE* You are required to invoke this method after any equipment alterations are performed.
	void RecalculateCombinedAttributes();

	/// Gets the combined attribute values from all equipped items.
	const Attributes& GetCombinedAttributes() const { return m_combinedAttributes; }

protected:
	array_type		m_items;
	Attributes		m_combinedAttributes;

};



