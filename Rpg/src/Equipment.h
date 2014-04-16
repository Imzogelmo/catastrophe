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
#include "Common.h"
#include "Attributes.h"


class RPG_API Equipment
{
public:
	typedef fc::vector<Item*> vec_type;

	Equipment();

	void Equip( Item* item, Inventory* sourceInventory = 0 );
	void Unequip( Item* item, Inventory* destinationInventory = 0 );
	void Unequip( int index, Inventory* destinationInventory = 0 );
	void UnequipAll( Inventory* destinationInventory = 0 );

	bool IsEquipped( Item* item ) const;
	bool IsItemOfTypeEquipped( int itemType ) const;

	int Find( Item* item ) const;
	int GetItemIndexOfTypeEquipped( int itemType ) const;
	Item* GetItemOfTypeEquipped( int itemType ) const;

	Item* GetItem( int index ) const;
	vec_type& GetEquippedItems() { return m_items; }
	const vec_type& GetEquippedItems() const { return m_items; }

	void RecalculateCombinedAttributes();
	const Attributes& GetCombinedAttributes() const { return m_combinedAttributes; }

protected:
	vec_type		m_items;
	Attributes		m_combinedAttributes;

};



