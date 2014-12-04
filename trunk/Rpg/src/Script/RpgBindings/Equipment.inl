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

#include "Equipment.h"
#include "Script/MonoUtils.h"
#include "Script/MonoRpgBinding.h"



Equipment* MonoRpgBinding::Equipment_Create()
{
	Equipment* equipment = new Equipment();
	return equipment;
}


void MonoRpgBinding::Equipment_Resize( Equipment* equipment, u32 maxSlots )
{
	SAFE_CALL(equipment, Resize(maxSlots));
}


u32 MonoRpgBinding::Equipment_GetNumSlots( Equipment* equipment )
{
	SAFE_CALL_RETURN(equipment, GetNumSlots(), 0);
}


u32 MonoRpgBinding::Equipment_GetMaxSlots( Equipment* equipment )
{
	SAFE_CALL_RETURN(equipment, GetMaxSlots(), 0);
}


void MonoRpgBinding::Equipment_Equip( Equipment* equipment, int slot, Item* item )
{
	SAFE_CALL(equipment, Equip(slot, item));
}


void MonoRpgBinding::Equipment_Unequip( Equipment* equipment, int slot )
{
	SAFE_CALL(equipment, Unequip(slot));
}


void MonoRpgBinding::Equipment_UnequipAll( Equipment* equipment )
{
	SAFE_CALL(equipment, UnequipAll());
}


void MonoRpgBinding::Equipment_TransferToInventory( Equipment* equipment, int slot, Inventory* destinationInventory )
{
	SAFE_CALL(equipment, TransferToInventory(slot, destinationInventory));
}


void MonoRpgBinding::Equipment_TransferAllToInventory( Equipment* equipment, Inventory* destinationInventory )
{
	SAFE_CALL(equipment, TransferAllToInventory(destinationInventory));
}


void MonoRpgBinding::Equipment_ReplaceSlot( Equipment* equipment, int slot, Item* item, Inventory* destinationInventory )
{
	SAFE_CALL(equipment, ReplaceSlot(slot, item, destinationInventory));
}


bool MonoRpgBinding::Equipment_Contains( Equipment* equipment, Item* item )
{
	SAFE_CALL_RETURN(equipment, Contains(item), false);
}


int MonoRpgBinding::Equipment_Find( Equipment* equipment, Item* item )
{
	SAFE_CALL_RETURN(equipment, Find(item), -1);
}


Item* MonoRpgBinding::Equipment_GetSlot( Equipment* equipment, int slot )
{
	SAFE_CALL_RETURN(equipment, GetSlot(slot), 0);
}


void MonoRpgBinding::Equipment_RecalculateCombinedAttributes( Equipment* equipment )
{
	SAFE_CALL(equipment, RecalculateCombinedAttributes());
}


Attributes MonoRpgBinding::Equipment_GetCombinedAttributes( Equipment* equipment )
{
	SAFE_CALL_RETURN(equipment, GetCombinedAttributes(), Attributes());
}




void MonoRpgBinding::BindEquipment()
{
	AddInternalCall("Create", Equipment_Create);
	AddInternalCall("Resize", Equipment_Resize);
	AddInternalCall("GetNumSlots", Equipment_GetNumSlots);
	AddInternalCall("GetMaxSlots", Equipment_GetMaxSlots);
	AddInternalCall("Equip", Equipment_Equip);
	AddInternalCall("Unequip", Equipment_Unequip);
	AddInternalCall("UnequipAll", Equipment_UnequipAll);
	AddInternalCall("TransferToInventory", Equipment_TransferToInventory);
	AddInternalCall("TransferAllToInventory", Equipment_TransferAllToInventory);
	AddInternalCall("ReplaceSlot", Equipment_ReplaceSlot);
	AddInternalCall("Contains", Equipment_Contains);
	AddInternalCall("Find", Equipment_Find);
	AddInternalCall("GetSlot", Equipment_GetSlot);
	//AddInternalCall("GetEquippedItems", Equipment_GetEquippedItems);
	AddInternalCall("RecalculateCombinedAttributes", Equipment_RecalculateCombinedAttributes);
	AddInternalCall("GetCombinedAttributes", Equipment_GetCombinedAttributes);
}
