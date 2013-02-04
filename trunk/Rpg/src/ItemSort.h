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
#include "Item.h"
#include "InventoryItem.h"


class ItemSort
{
public:

	// sort by type and subtype
	struct ByType
	{
		bool operator () ( const Item* a, const Item* b ) const
		{
			if(a && b)
			{
				if( a->type == b->type )
					return a->subtype < b->subtype;

				return a->type < b->type;
			}

			// the null pointer is greater.
			return ((a) ? (b < a) : (a < b));
		}

		bool operator () ( const InventoryItem& a, const InventoryItem& b ) const
		{
			return operator ()(a.GetItem(), b.GetItem());
		}
	};

	// sort by amount
	struct ByAmount
	{
		bool operator () ( const Item* a, const Item* b ) const { return a < b; }
		bool operator () ( const InventoryItem& a, const InventoryItem& b ) const
		{
			return a.GetAmount() < b.GetAmount();
		}
	};

	// sort by name
	struct ByName
	{
		bool operator () ( const Item* a, const Item* b ) const
		{
			if(a && b)
				return a->GetName() < b->GetName();

			return ((a) ? (b < a) : (a < b));
		}

		bool operator () ( const InventoryItem& a, const InventoryItem& b ) const
		{
			return operator ()(a.GetItem(), b.GetItem());
		}
	};

	// sort by item statistic (ex; optimize equipment)
	struct ByStat
	{
		int id;

		ByName( int id = 0 ) : id(id) 
		{}

		bool operator () ( const Item* a, const Item* b ) const
		{
			if(a && b)
				return a->attributes.stat[id] < a->attributes.stat[id];

			return ((a) ? (b < a) : (a < b));
		}

		bool operator () ( const InventoryItem& a, const InventoryItem& b ) const
		{
			return operator ()(a.GetItem(), b.GetItem());
		}
	};

	attributes
};

