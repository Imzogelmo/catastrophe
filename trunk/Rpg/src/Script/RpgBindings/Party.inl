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

#include "Party.h"
#include "Script/MonoUtils.h"
#include "Script/MonoRpgBinding.h"



bool MonoRpgBinding::Party_AddMember( Party* party, Actor* actor )
{
	SAFE_CALL_RETURN(party, AddMember(actor), false);
}


bool MonoRpgBinding::Party_InsertMemberInSlot( Party* party, int slot, Actor* actor )
{
	SAFE_CALL_RETURN(party, InsertMemberInSlot(slot, actor), false);
}


void MonoRpgBinding::Party_RemoveMember( Party* party, Actor* actor )
{
	SAFE_CALL(party, RemoveMember(actor));
}


void MonoRpgBinding::Party_RemoveMemberInSlot( Party* party, int slot )
{
	SAFE_CALL(party, RemoveMemberInSlot(slot));
}


void MonoRpgBinding::Party_RemoveAllMembers( Party* party )
{
	SAFE_CALL(party, RemoveAllMembers());
}


int MonoRpgBinding::Party_GetFirstEmptySlot( Party* party, int startSlot )
{
	SAFE_CALL_RETURN(party, GetFirstEmptySlot(startSlot), 0);
}


bool MonoRpgBinding::Party_Contains( Party* party, Actor* actor )
{
	SAFE_CALL_RETURN(party, Contains(actor), false);
}


Actor* MonoRpgBinding::Party_GetMemberInSlot( Party* party, int slot )
{
	SAFE_CALL_RETURN(party, GetMember(slot), 0);
}


void MonoRpgBinding::Party_SetMemberInSlot( Party* party, int slot, Actor* actor )
{
	SAFE_CALL(party, SetMember(slot, actor));
}


u32 MonoRpgBinding::Party_GetPartySize( Party* party )
{
	SAFE_CALL_RETURN(party, GetPartySize(), 0);
}


u32 MonoRpgBinding::Party_GetMaxPartySize( Party* party )
{
	SAFE_CALL_RETURN(party, GetMaxPartySize(), 0);
}


int MonoRpgBinding::Party_GetGold( Party* party )
{
	SAFE_CALL_RETURN(party, GetGold(), 0);
}


void MonoRpgBinding::Party_SetGold( Party* party, int val )
{
	SAFE_CALL(party, SetGold(val));
}


void MonoRpgBinding::Party_SwapMembers( Party* party, u32 firstSlot, u32 secondSlot)
{
	SAFE_CALL(party, SwapMembers(firstSlot, secondSlot));
}


void MonoRpgBinding::Party_SetMaxPartySize( Party* party, u32 size )
{
	SAFE_CALL(party, SetMaxPartySize(size));
}


int MonoRpgBinding::Party_GetAverageExperienceLevel( Party* party )
{
	SAFE_CALL_RETURN(party, GetAverageExperienceLevel(), 0);
}


Inventory* MonoRpgBinding::Party_GetInventory( Party* party )
{
	SAFE_CALL_RETURN(&party, GetInventory(), 0);
}


void MonoRpgBinding::BindParty()
{
	SetNamespace("CatastropheEngine.Rpg.Party::");

	//AddInternalCall("Create", Party_Create);
	AddInternalCall("AddMember", Party_AddMember);
	AddInternalCall("InsertMemberInSlot", Party_InsertMemberInSlot);
	AddInternalCall("RemoveMember", Party_RemoveMember);
	AddInternalCall("RemoveAllMembers", Party_RemoveAllMembers);
	AddInternalCall("GetFirstEmptySlot", Party_GetFirstEmptySlot);
	AddInternalCall("Contains", Party_Contains);
	AddInternalCall("GetMemberInSlot", Party_GetMemberInSlot);
	AddInternalCall("SetMemberInSlot", Party_SetMemberInSlot);
	AddInternalCall("GetPartySize", Party_GetPartySize);
	AddInternalCall("GetMaxPartySize", Party_GetMaxPartySize);
	AddInternalCall("GetGold", Party_GetGold);
	AddInternalCall("SetGold", Party_SetGold);
	AddInternalCall("SwapMembers", Party_SwapMembers);
	AddInternalCall("SetMaxPartySize", Party_SetMaxPartySize);
	AddInternalCall("GetAverageExperienceLevel", Party_GetAverageExperienceLevel);
	AddInternalCall("GetInventory", Party_GetInventory);
}
