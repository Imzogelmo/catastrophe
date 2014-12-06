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

#include "InventorySlot.h"
#include "Script/MonoUtils.h"
#include "Script/MonoRpgBinding.h"



u8 MonoEngineBinding::InventorySlot_AddAmount(InventorySlot* self, u8 amount )
{
	SAFE_CALL_RETURN(self, AddAmount(amount), 0);
}


u8 MonoEngineBinding::InventorySlot_RemoveAmount(InventorySlot* self, u8 amount )
{
	SAFE_CALL_RETURN(self, RemoveAmount(amount), 0);
}


void MonoEngineBinding::InventorySlot_Combine(InventorySlot* self, InventorySlot* inventorySlot )
{
	SAFE_CALL(self, Combine(*inventorySlot));
}



void MonoEngineBinding::BindInventorySlot()
{
	AddInternalCall("AddAmount", InventorySlot_AddAmount);
	AddInternalCall("RemoveAmount", InventorySlot_RemoveAmount);
	AddInternalCall("Combine", InventorySlot_Combine);
}
