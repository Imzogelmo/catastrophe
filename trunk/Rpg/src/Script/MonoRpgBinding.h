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

#include <Catastrophe/Common.h>
#include "Common.h"
#include "MonoBinding.h"


class MonoRpgBinding : public MonoBinding
{
public:

	// Actor
	static int Actor_GetParam( Actor* actor, int param );
	static int Actor_GetMaxParam( Actor* actor, int param );
	static int Actor_GetUnmodifiedMaxParam( Actor* actor, int param );
	static int Actor_GetBaseStat( Actor* actor, int stat );
	static int Actor_GetUnmodifiedBaseStat( Actor* actor, int stat );
	static int Actor_GetDerivedStat( Actor* actor, int stat );
	static int Actor_GetUnmodifiedDerivedStat( Actor* actor, int stat );

	static int Actor_CalculateModifiedMaxParameterValue( Actor* actor, int param );
	static int Actor_CalculateModifiedBaseStatValue( Actor* actor, int stat );
	static int Actor_CalculateModifiedDerivedStatValue( Actor* actor, int stat );

	static void Actor_SetParam( Actor* actor, int param, int value );
	static void Actor_SetMaxParam( Actor* actor, int param, int value );
	static void Actor_SetBaseStat( Actor* actor, int stat, int value );
	static void Actor_SetDerivedStat( Actor* actor, int stat, int value );


	// InventorySlot
	static u8 InventorySlot_AddAmount( InventorySlot* self, u8 amount );
	static u8 InventorySlot_RemoveAmount( InventorySlot* self, u8 amount );
	static void InventorySlot_Combine( InventorySlot* self, InventorySlot* inventorySlot );


	// Equipment
	static Equipment* Equipment_Create();
	static void Equipment_Destroy( Equipment* equipment );
	static void Equipment_Resize( Equipment* equipment, u32 maxSlots );
	static u32 Equipment_GetNumSlots( Equipment* equipment );
	static u32 Equipment_GetMaxSlots( Equipment* equipment );
	static void Equipment_Equip( Equipment* equipment, int slot, Item* item );
	static void Equipment_Unequip( Equipment* equipment, int slot );
	static void Equipment_UnequipAll( Equipment* equipment );
	static void Equipment_TransferToInventory( Equipment* equipment, int slot, Inventory* destinationInventory );
	static void Equipment_TransferAllToInventory( Equipment* equipment, Inventory* destinationInventory );
	static void Equipment_ReplaceSlot( Equipment* equipment, int slot, Item* item, Inventory* destinationInventory );
	static bool Equipment_Contains( Equipment* equipment, Item* item );
	static int Equipment_Find( Equipment* equipment, Item* item );
	static Item* Equipment_GetSlot( Equipment* equipment, int slot );
	static void Equipment_RecalculateCombinedAttributes( Equipment* equipment );
	static Attributes Equipment_GetCombinedAttributes( Equipment* equipment );


	// Party
	static bool Party_AddMember( Party* party, Actor* actor );
	static bool Party_InsertMemberInSlot( Party* party, int slot, Actor* actor );
	static void Party_RemoveMember( Party* party, Actor* actor );
	static void Party_RemoveMemberInSlot( Party* party, int slot );
	static void Party_RemoveAllMembers( Party* party );
	static int Party_GetFirstEmptySlot( Party* party, int startSlot );
	static bool Party_Contains( Party* party, Actor* actor );
	static Actor* Party_GetMemberInSlot( Party* party, int slot );
	static void Party_SetMemberInSlot( Party* party, int slot, Actor* actor );
	static u32 Party_GetPartySize( Party* party );
	static u32 Party_GetMaxPartySize( Party* party );
	static int Party_GetGold( Party* party );
	static void Party_SetGold( Party* party, int val );
	static void Party_SwapMembers( Party* party, u32 firstSlot, u32 secondSlot );
	static void Party_SetMaxPartySize( Party* party, u32 size );
	static int Party_GetAverageExperienceLevel( Party* party );
	static Inventory* Party_GetInventory( Party* party );


	static void BindActor();
	static void BindEquipment();
	static void BindParty();

};

