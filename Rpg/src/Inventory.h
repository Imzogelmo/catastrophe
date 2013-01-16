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
#include "InventoryItem.h"


class RPG_API Inventory
{
public:
	typedef fc::vector<InventoryItem> vec_type;

	Inventory();

	void Reserve( size_t max_items );
	void Clear();

	void Add( const InventoryItem& inventoryItem );
	void Add( Item* item, int count = 1 );
	void Remove( Item* item, int count = 1 );
	void RemoveFromInventory( size_t index );
	void RemoveFromInventory( Item* item );

	void Unique();
	void Swap( size_t first, size_t second );
	void Splice( Inventory& other );
	void Splice( Inventory& other, size_t index );

	bool Contains( const Item* item ) const;
	bool Find( const Item* item, size_t &item_index ) const;

	size_t Size() const { return m_items.size(); }
	bool IsFull() const { return m_items.size() == m_maxSize; }

	Item* GetItem( size_t index ) const;
	Item* GetItem( const fc::string& name ) const;

	InventoryItem& operator []( size_t index );
	const InventoryItem& operator []( size_t index ) const;
	InventoryItem& GetInventoryItem( size_t index ) { return operator[](index); }
	const InventoryItem& GetInventoryItem( size_t index ) const { return operator[](index); }


	//internal management policy queries.
	bool GetPolicyCanContainDuplicates() const { return m_canContainDuplicates; }
	bool GetPolicyEraseOnRemove() const { return m_policyEraseOnRemove; }

private:
	vec_type	m_items;
	size_t		m_maxSize;

	bool		m_canContainDuplicates;
	bool		m_policyEraseOnRemove;

};



