
#pragma once

#include <fc/vector.h>
#include "Common.h"
#include "Attributes.h"


class Equipment
{
public:
	typedef fc::vector<Item*> vec_type;

	Equipment();

	void Equip( Item* item, Inventory* source = 0 );
	void Unequip( const Item* item, Inventory* dest = 0 );
	void Unequip( size_t index, Inventory* dest = 0 );
	void UnequipAll( Inventory* dest = 0 );

	bool IsEquipped( const Item* item ) const;
	bool Find( const Item* item, size_t &item_index ) const;

	Item* GetItem( size_t index );
	const Item* GetItem( size_t index ) const;

	vec_type& GetEquippedItems() { return m_items; }
	const vec_type& GetEquippedItems() const { return m_items; }

	void RecalculateCombinedAttributes();
	Attributes GetCombinedAttributes() { return m_combinedAttributes; }

protected:
	vec_type		m_items;
	Attributes		m_combinedAttributes;

};



