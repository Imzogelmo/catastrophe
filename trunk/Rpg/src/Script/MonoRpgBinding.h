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

	// Database
	static Item* Database_GetItem( int id );
	static MonsterData* Database_GetMonster( int id );
	static MonsterTroop* Database_GetMonsterTroop( int id );
	static u32 Database_GetCount( int type );

	// Item
	static const char* Item_GetName( Item* item );
	static const char* Item_GetScript( Item* item );
	static const char* Item_GetDescription( Item* item );
	static void Item_SetName( Item* item, const char* str );
	static void Item_SetScript( Item* item, const char* str );
	static void Item_SetDescription( Item* item, const char* str );
	static int Item_GetIntValue( Item* item, int type );
	static void Item_SetIntValue( Item* item, int type, int value );

	// Actor
	static const char* Actor_GetName( Actor* actor );
	static void Actor_SetName( Actor* actor, const char* name );
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


	// Inventory
	static void Inventory_SetCapacity( Inventory* inventory, u32 maxItems );
	static u32 Inventory_GetCapacity( Inventory* inventory );
	static void Inventory_Clear( Inventory* inventory );
	static int Inventory_FindFirstFreeSlot( Inventory* inventory, int startSlot );
	static int Inventory_FindFirstUsedSlot( Inventory* inventory, int startSlot );
	static void Inventory_AddSlot( Inventory* inventory, InventorySlot inventorySlot );
	static void Inventory_AddItem( Inventory* inventory, Item* item, u8 amount );
	static void Inventory_RemoveItem( Inventory* inventory, Item* item, u8 amount );
	static void Inventory_RemoveSlot( Inventory* inventory, int slot );
	static u8 Inventory_AddItemsToSlot( Inventory* inventory, int slot, u8 amount );
	static u8 Inventory_RemoveItemsFromSlot( Inventory* inventory, int slot, u8 amount );
	static void Inventory_Compress( Inventory* inventory );
	static void Inventory_SwapSlots( Inventory* inventory, int firstSlot, int secondSlot );
	static void Inventory_Splice( Inventory* inventory, Inventory other );
	static void Inventory_SpliceSlot( Inventory* inventory, Inventory other, int index );
	static bool Inventory_Contains( Inventory* inventory, Item* item );
	static int Inventory_FindFirstOf( Inventory* inventory, Item* item, int startSlot );
	static int Inventory_FindLastOf( Inventory* inventory, Item* item );
	static u32 Inventory_Size( Inventory* inventory );
	static bool Inventory_IsEmpty( Inventory* inventory );
	static bool Inventory_IsFull( Inventory* inventory );
	static InventorySlot Inventory_GetSlot( Inventory* inventory, int slot );
	static void Inventory_SetSlot( Inventory* inventory, int slot, InventorySlot inventorySlot );
	static bool Inventory_GetAllowDuplicateItems( Inventory* inventory );
	static void Inventory_SetAllowDuplicateItems( Inventory* inventory, bool value );
	static bool Inventory_GetIsFixedSize( Inventory* inventory );
	static void Inventory_SetIsFixedSize( Inventory* inventory, bool value );


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


	// BattleGroup
	static void BattleGroup_InsertCombatant( BattleGroup* battleGroup, Combatant* combatant, u32 position );
	static bool BattleGroup_ContainsCombatant( BattleGroup* battleGroup, Combatant* combatant );
	static MonoObject* BattleGroup_GetCombatant( BattleGroup* battleGroup, int index );

	static MonoArray* BattleGroup_CallFuncRetArrayParam0( BattleGroup* battleGroup, int functionType );
	static MonoObject* BattleGroup_CallFuncRetCombatantParam0( BattleGroup* battleGroup, int functionType );
	static int BattleGroup_CallFuncRetIntParam0( BattleGroup* battleGroup, int functionType );
	static bool BattleGroup_CallFuncRetBoolParam0( BattleGroup* battleGroup, int functionType );
	static void BattleGroup_CallFuncRetVoidParam0( BattleGroup* battleGroup, int functionType );
	static void BattleGroup_CallFuncRetVoidParam1( BattleGroup* battleGroup, int functionType, void* param );


	// BattleFaction
	static BattleGroup* BattleFaction_CreateBattleGroup( BattleFaction* battleFaction );
	static void BattleFaction_RemoveBattleGroup( BattleFaction* battleFaction, BattleGroup* battleGroup );
	static bool BattleFaction_ContainsCombatant( BattleFaction* battleFaction, Combatant* combatant );
	static BattleGroup* BattleFaction_GetBattleGroup( BattleFaction* battleFaction, u32 groupNumber );
	static MonoObject* BattleFaction_GetClosestCombatantTo( BattleFaction* battleFaction, Combatant* combatant );
	static MonoObject* BattleFaction_GetClosestCombatantInDirection( BattleFaction* battleFaction, Combatant* combatant, int direction );

	static MonoArray* BattleFaction_CallFuncRetArrayParam0( BattleFaction* battleFaction, int functionType );
	static MonoObject* BattleFaction_CallFuncRetCombatantParam0( BattleFaction* battleFaction, int functionType );
	static int BattleFaction_CallFuncRetIntParam0( BattleFaction* battleFaction, int functionType );
	static bool BattleFaction_CallFuncRetBoolParam0( BattleFaction* battleFaction, int functionType );
	static void BattleFaction_CallFuncRetVoidParam0( BattleFaction* battleFaction, int functionType );
	static void BattleFaction_CallFuncRetVoidParam1( BattleFaction* battleFaction, int functionType, void* param );


	// Database
	static void BindItem();
	static void BindDatabase();

	// Rpg
	static void BindActor();
	static void BindInventorySlot();
	static void BindInventory();
	static void BindEquipment();
	static void BindParty();
	static void BindBattleGroup();
	static void BindBattleFaction();

};

