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

#include "BattleFaction.h"
#include "Script/MonoUtils.h"
#include "Script/MonoRpgBinding.h"


BattleGroup* MonoRpgBinding::BattleFaction_CreateBattleGroup( BattleFaction* battleFaction )
{
	SAFE_CALL_RETURN(battleFaction, CreateBattleGroup(), null);
}


BattleGroup* MonoRpgBinding::BattleFaction_GetBattleGroup( BattleFaction* battleFaction, u32 groupNumber )
{
	SAFE_CALL_RETURN(battleFaction, GetBattleGroup(groupNumber), null);
}


bool MonoRpgBinding::BattleFaction_ContainsCombatant( BattleFaction* battleFaction, Combatant* combatant )
{
	SAFE_CALL_RETURN(battleFaction, ContainsCombatant(combatant), false);
}


MonoObject* MonoRpgBinding::BattleFaction_GetClosestCombatantTo( BattleFaction* battleFaction, Combatant* combatant )
{
	MonoObject* object = null;
	Combatant* closestCombatant = battleFaction->GetClosestCombatantTo(combatant);
	if( closestCombatant != null )
		object = combatant->GetScriptObject()->GetMonoObjectPtr();

	return object;
}


MonoObject* MonoRpgBinding::BattleFaction_GetClosestCombatantInDirection( BattleFaction* battleFaction, Combatant* combatant, int direction )
{
	MonoObject* object = null;
	Combatant* closestCombatant = battleFaction->GetClosestCombatantInDirection(combatant, direction);
	if( closestCombatant != null )
		object = combatant->GetScriptObject()->GetMonoObjectPtr();

	return object;
}



enum bfRetArrayParam0
{
	bfRetArrayParam0_GetActiveCombatants,
	bfRetArrayParam0_GetIncapacitatedCombatants,
	bfRetArrayParam0_GetCombatants
};

MonoArray* MonoRpgBinding::BattleFaction_CallFuncRetArrayParam0( BattleFaction* battleFaction, int functionType )
{
	if( battleFaction == null )
		return 0;

	BattleGroup::vec_type combatants;

	switch(functionType)
	{
		case bfRetArrayParam0_GetActiveCombatants:
			battleFaction->GetActiveCombatants(combatants);
			break;
		case bfRetArrayParam0_GetIncapacitatedCombatants:
			battleFaction->GetIncapacitatedCombatants(combatants);
			break;
		case bfRetArrayParam0_GetCombatants:
			battleFaction->GetCombatants(combatants);
			break;
		default:
			LogDebug("BattleFaction_GetCombatantArray: Invalid functionType! (%i) ", functionType);
			break;
	}

	const u32 size = combatants.size();
	MonoArray* array = mono_array_new(mono_domain_get(), mono_get_object_class(), size);
	for( u32 i(0); i < size; ++i )
	{
		MonoObject** p = (MonoObject**)mono_array_addr_with_size(array, sizeof(MonoObject*), i);
		*p = combatants[i]->GetScriptObject()->GetMonoObjectPtr();
	}

	return array;
}



enum bfRetCombatantParam0
{
	bfRetCombatantParam0_SelectRandomActiveCombatant,
	bfRetCombatantParam0_SelectRandomIncapacitatedCombatant,
	bfRetCombatantParam0_SelectRandomCombatant
};

MonoObject* MonoRpgBinding::BattleFaction_CallFuncRetCombatantParam0( BattleFaction* battleFaction, int functionType )
{
	Combatant* combatant = null;

	if( battleFaction != null )
	{
		switch(functionType)
		{
			case bfRetCombatantParam0_SelectRandomActiveCombatant:
				combatant = battleFaction->SelectRandomActiveCombatant();
				break;
			case bfRetCombatantParam0_SelectRandomIncapacitatedCombatant:
				combatant = battleFaction->SelectRandomIncapacitatedCombatant();
				break;
			case bfRetCombatantParam0_SelectRandomCombatant:
				combatant = battleFaction->SelectRandomCombatant();
				break;
			default:
				LogDebug("BattleFaction_GetBoolValue: Invalid functionType! (%i) ", functionType);
				break;
		}
	}

	MonoObject* object = null;
	if( combatant != null )
		object = combatant->GetScriptObject()->GetMonoObjectPtr();

	return object;
}



enum bfRetIntParam0
{
	bfRetIntParam0_GetNumActiveCombatants,
	bfRetIntParam0_GetNumIncapacitatedCombatants,
	bfRetIntParam0_GetNumCombatants,
	bfRetIntParam0_GetCombinedExp,
	bfRetIntParam0_GetCombinedGold,
};

int MonoRpgBinding::BattleFaction_CallFuncRetIntParam0( BattleFaction* battleFaction, int functionType )
{
	int value = 0;

	if( battleFaction != null )
	{
		switch(functionType)
		{
			case bfRetIntParam0_GetNumActiveCombatants:
				value = battleFaction->GetNumActiveCombatants();
				break;
			case bfRetIntParam0_GetNumIncapacitatedCombatants:
				value = battleFaction->GetNumIncapacitatedCombatants();
				break;
			case bfRetIntParam0_GetNumCombatants:
				value = battleFaction->GetNumCombatants();
				break;
			case bfRetIntParam0_GetCombinedExp:
				value = battleFaction->GetCombinedExp();
				break;
			case bfRetIntParam0_GetCombinedGold:
				value = battleFaction->GetCombinedGold();
				break;
		}
	}

	return value;
}



enum bfRetBoolParam0
{
	bfRetBoolParam0_IsDefeated
};

bool MonoRpgBinding::BattleFaction_CallFuncRetBoolParam0( BattleFaction* battleFaction, int functionType )
{
	bool value = false;

	if( battleFaction != null )
	{
		switch(functionType)
		{
			case bfRetBoolParam0_IsDefeated:
				value = battleFaction->IsDefeated();
				break;
		}
	}

	return value;
}



enum bfRetVoidParam0
{
	bfRetVoidParam0_RemoveAllCombatants,
	bfRetVoidParam0_RemoveIncapacitatedCombatants,
	bfRetVoidParam0_RemoveEmptyBattleGroups
};

void MonoRpgBinding::BattleFaction_CallFuncRetVoidParam0( BattleFaction* battleFaction, int functionType )
{
	switch(functionType)
	{
		case bfRetVoidParam0_RemoveAllCombatants:
			battleFaction->RemoveAllCombatants();
			break;
		case bfRetVoidParam0_RemoveIncapacitatedCombatants:
			battleFaction->RemoveIncapacitatedCombatants();
			break;
		case bfRetVoidParam0_RemoveEmptyBattleGroups:
			battleFaction->RemoveEmptyBattleGroups();
			break;
	}
}



enum bfRetVoidParam1
{
	bfRetVoidParam1_RemoveBattleGroup,
	bfRetVoidParam1_RemoveCombatant
};

void MonoRpgBinding::BattleFaction_CallFuncRetVoidParam1( BattleFaction* battleFaction, int functionType, void* param )
{
	switch(functionType)
	{
		case bfRetVoidParam1_RemoveBattleGroup:
			battleFaction->RemoveBattleGroup((BattleGroup*)param);
			break;
		case bfRetVoidParam1_RemoveCombatant:
			battleFaction->RemoveCombatant((Combatant*)param);
			break;
	}
}


void MonoRpgBinding::BindBattleFaction()
{
	SetNamespace("CatastropheEngine.Rpg.BattleFaction::");

	AddInternalCall("CreateBattleGroup", BattleFaction_CreateBattleGroup);
	AddInternalCall("ContainsCombatant", BattleFaction_ContainsCombatant);
	AddInternalCall("GetBattleGroup", BattleFaction_GetBattleGroup);
	AddInternalCall("GetClosestCombatantTo", BattleFaction_GetClosestCombatantTo);
	AddInternalCall("GetClosestCombatantInDirection", BattleFaction_GetClosestCombatantInDirection);

	AddInternalCall("BattleFaction_CallFuncRetArrayParam0", BattleFaction_CallFuncRetArrayParam0);
	AddInternalCall("BattleFaction_CallFuncRetCombatantParam0", BattleFaction_CallFuncRetCombatantParam0);
	AddInternalCall("BattleFaction_CallFuncRetIntParam0", BattleFaction_CallFuncRetIntParam0);
	AddInternalCall("BattleFaction_CallFuncRetBoolParam0", BattleFaction_CallFuncRetBoolParam0);
	AddInternalCall("BattleFaction_CallFuncRetVoidParam0", BattleFaction_CallFuncRetVoidParam0);
	AddInternalCall("BattleFaction_CallFuncRetVoidParam1", BattleFaction_CallFuncRetVoidParam1);

}

