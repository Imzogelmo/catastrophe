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

#include "Inventory.h"
#include "Script/MonoUtils.h"
#include "Script/MonoRpgBinding.h"


void MonoRpgBinding::Inventory_SetCapacity( Inventory* inventory, u32 maxItems )
{
	SAFE_CALL(inventory, SetCapacity(maxItems));
}


u32 MonoRpgBinding::Inventory_GetCapacity( Inventory* inventory )
{
	SAFE_CALL_RETURN(inventory, GetCapacity(), 0);
}


void MonoRpgBinding::Inventory_Clear( Inventory* inventory )
{
	SAFE_CALL(inventory, Clear());
}


int MonoRpgBinding::Inventory_FindFirstFreeSlot( Inventory* inventory, int startSlot )
{
	SAFE_CALL_RETURN(inventory, FindFirstFreeSlot(startSlot), 0);
}


int MonoRpgBinding::Inventory_FindFirstUsedSlot( Inventory* inventory, int startSlot )
{
	SAFE_CALL_RETURN(inventory, FindFirstUsedSlot(startSlot), 0);
}


void MonoRpgBinding::Inventory_AddSlot( Inventory* inventory, InventorySlot inventorySlot )
{
	SAFE_CALL(inventory, Add(inventorySlot));
}


void MonoRpgBinding::Inventory_AddItem( Inventory* inventory, Item* item, u8 amount )
{
	SAFE_CALL(inventory, Add(item, amount));
}


void MonoRpgBinding::Inventory_RemoveItem( Inventory* inventory, Item* item, u8 amount )
{
	SAFE_CALL(inventory, RemoveItem(item, amount));
}


void MonoRpgBinding::Inventory_RemoveSlot( Inventory* inventory, int slot )
{
	SAFE_CALL(inventory, RemoveSlot(slot));
}


u8 MonoRpgBinding::Inventory_AddItemsToSlot( Inventory* inventory, int slot, u8 amount )
{
	SAFE_CALL_RETURN(inventory, AddItemsToSlot(slot, amount), 0);
}


u8 MonoRpgBinding::Inventory_RemoveItemsFromSlot( Inventory* inventory, int slot, u8 amount )
{
	SAFE_CALL_RETURN(inventory, RemoveItemsFromSlot(slot, amount), 0);
}


void MonoRpgBinding::Inventory_Compress( Inventory* inventory )
{
	SAFE_CALL(inventory, Compress());
}


void MonoRpgBinding::Inventory_SwapSlots( Inventory* inventory, int firstSlot, int secondSlot )
{
	SAFE_CALL(inventory, SwapSlots(firstSlot, secondSlot));
}


void MonoRpgBinding::Inventory_Splice( Inventory* inventory, Inventory other )
{
	SAFE_CALL(inventory, Splice(other));
}


void MonoRpgBinding::Inventory_SpliceSlot( Inventory* inventory, Inventory other, int index )
{
	SAFE_CALL(inventory, Splice(other, index));
}


bool MonoRpgBinding::Inventory_Contains( Inventory* inventory, Item* item )
{
	SAFE_CALL_RETURN(inventory, Contains(item), 0);
}


int MonoRpgBinding::Inventory_FindFirstOf( Inventory* inventory, Item* item, int startSlot )
{
	SAFE_CALL_RETURN(inventory, FindFirstOf(item, startSlot), 0);
}


int MonoRpgBinding::Inventory_FindLastOf( Inventory* inventory, Item* item )
{
	SAFE_CALL_RETURN(inventory, FindLastOf(item), 0);
}


u32 MonoRpgBinding::Inventory_Size( Inventory* inventory )
{
	SAFE_CALL_RETURN(inventory, Size(), 0);
}


bool MonoRpgBinding::Inventory_IsEmpty( Inventory* inventory )
{
	SAFE_CALL_RETURN(inventory, IsEmpty(), 0);
}


bool MonoRpgBinding::Inventory_IsFull( Inventory* inventory )
{
	SAFE_CALL_RETURN(inventory, IsFull(), 0);
}


InventorySlot MonoRpgBinding::Inventory_GetSlot( Inventory* inventory, int slot )
{
	SAFE_CALL_RETURN(inventory, GetSlot(slot), InventorySlot());
}


void MonoRpgBinding::Inventory_SetSlot( Inventory* inventory, int slot, InventorySlot inventorySlot )
{
	SAFE_CALL(inventory, SetSlot(slot, inventorySlot));
}


bool MonoRpgBinding::Inventory_GetAllowDuplicateItems( Inventory* inventory )
{
	SAFE_CALL_RETURN(inventory, GetAllowDuplicateItems(), 0);
}


void MonoRpgBinding::Inventory_SetAllowDuplicateItems( Inventory* inventory, bool value )
{
	SAFE_CALL(inventory, SetAllowDuplicateItems(value));
}


bool MonoRpgBinding::Inventory_GetIsFixedSize( Inventory* inventory )
{
	SAFE_CALL_RETURN(inventory, GetIsFixedSize(), 0);
}


void MonoRpgBinding::Inventory_SetIsFixedSize( Inventory* inventory, bool value )
{
	SAFE_CALL(inventory, SetIsFixedSize(value));
}



void MonoRpgBinding::BindInventory()
{
	SetNamespace("CatastropheEngine.Rpg.Inventory::");

	AddInternalCall("SetCapacity", Inventory_SetCapacity);
	AddInternalCall("GetCapacity", Inventory_GetCapacity);
	AddInternalCall("Clear", Inventory_Clear);
	AddInternalCall("FindFirstFreeSlot", Inventory_FindFirstFreeSlot);
	AddInternalCall("FindFirstUsedSlot", Inventory_FindFirstUsedSlot);
	AddInternalCall("AddSlot", Inventory_AddSlot);
	AddInternalCall("AddItem", Inventory_AddItem);
	AddInternalCall("RemoveItem", Inventory_RemoveItem);
	AddInternalCall("RemoveSlot", Inventory_RemoveSlot);
	AddInternalCall("AddItemsToSlot", Inventory_AddItemsToSlot);
	AddInternalCall("RemoveItemsFromSlot", Inventory_RemoveItemsFromSlot);
	AddInternalCall("Compress", Inventory_Compress);
	AddInternalCall("SwapSlots", Inventory_SwapSlots);
	AddInternalCall("Splice", Inventory_Splice);
	AddInternalCall("SpliceSlot", Inventory_SpliceSlot);
	AddInternalCall("Contains", Inventory_Contains);
	AddInternalCall("FindFirstOf", Inventory_FindFirstOf);
	AddInternalCall("FindLastOf", Inventory_FindLastOf);
	AddInternalCall("Size", Inventory_Size);
	AddInternalCall("Empty", Inventory_IsEmpty);
	AddInternalCall("Full", Inventory_IsFull);
	AddInternalCall("GetSlot", Inventory_GetSlot);
	AddInternalCall("SetSlot", Inventory_SetSlot);
	AddInternalCall("GetAllowDuplicateItems", Inventory_GetAllowDuplicateItems);
	AddInternalCall("SetAllowDuplicateItems", Inventory_SetAllowDuplicateItems);
	AddInternalCall("GetIsFixedSize", Inventory_GetIsFixedSize);
	AddInternalCall("SetIsFixedSize", Inventory_SetIsFixedSize);
}

