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

#include "BattleGroup.h"
#include "Script/MonoUtils.h"
#include "Script/MonoRpgBinding.h"


void MonoRpgBinding::BattleGroup_InsertCombatant( BattleGroup* battleGroup, Combatant* combatant, u32 position )
{
	SAFE_CALL(battleGroup, InsertCombatant(combatant, position));
}


bool MonoRpgBinding::BattleGroup_ContainsCombatant( BattleGroup* battleGroup, Combatant* combatant )
{
	SAFE_CALL_RETURN(battleGroup, ContainsCombatant(combatant), false);
}


MonoObject* MonoRpgBinding::BattleGroup_GetCombatant( BattleGroup* battleGroup, int index )
{
	MonoObject* object = null;
	if( battleGroup != null )
	{
		Combatant* combatant = battleGroup->GetCombatant(index);
		object = combatant->GetScriptObject()->GetMonoObjectPtr();
	}

	return object;
}



enum bgRetArrayParam0
{
	bgRetArrayParam0_GetActiveCombatants,
	bgRetArrayParam0_GetIncapacitatedCombatants,
	bgRetArrayParam0_GetCombatants
};

MonoArray* MonoRpgBinding::BattleGroup_CallFuncRetArrayParam0( BattleGroup* battleGroup, int functionType )
{
	if( battleGroup == null )
		return 0;

	BattleGroup::vec_type combatants;

	switch(functionType)
	{
		case bgRetArrayParam0_GetActiveCombatants:
			battleGroup->GetActiveCombatants(combatants);
			break;
		case bgRetArrayParam0_GetIncapacitatedCombatants:
			battleGroup->GetIncapacitatedCombatants(combatants);
			break;
		case bgRetArrayParam0_GetCombatants:
			combatants = battleGroup->GetCombatants();
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



enum bgRetCombatantParam0
{
	bgRetCombatantParam0_SelectRandomActiveCombatant,
	bgRetCombatantParam0_SelectRandomIncapacitatedCombatant,
	bgRetCombatantParam0_SelectRandomCombatant
};

MonoObject* MonoRpgBinding::BattleGroup_CallFuncRetCombatantParam0( BattleGroup* battleGroup, int functionType )
{
	Combatant* combatant = null;

	if( battleGroup != null )
	{
		switch(functionType)
		{
			case bgRetCombatantParam0_SelectRandomActiveCombatant:
				combatant = battleGroup->SelectRandomActiveCombatant();
				break;
			case bgRetCombatantParam0_SelectRandomIncapacitatedCombatant:
				combatant = battleGroup->SelectRandomIncapacitatedCombatant();
				break;
			case bgRetCombatantParam0_SelectRandomCombatant:
				combatant = battleGroup->SelectRandomCombatant();
				break;
		}
	}

	MonoObject* object = null;
	if( combatant != null )
		object = combatant->GetScriptObject()->GetMonoObjectPtr();

	return object;
}



enum bgRetIntParam0
{
	bgRetIntParam0_GetNumActiveCombatants,
	bgRetIntParam0_GetNumIncapacitatedCombatants,
	bgRetIntParam0_GetNumCombatants,
	bgRetIntParam0_GetCombinedExp,
	bgRetIntParam0_GetCombinedGold,
};

int MonoRpgBinding::BattleGroup_CallFuncRetIntParam0( BattleGroup* battleGroup, int functionType )
{
	int value = 0;

	if( battleGroup != null )
	{
		switch(functionType)
		{
			case bgRetIntParam0_GetNumActiveCombatants:
				value = battleGroup->GetNumActiveCombatants();
				break;
			case bgRetIntParam0_GetNumIncapacitatedCombatants:
				value = battleGroup->GetNumIncapacitatedCombatants();
				break;
			case bgRetIntParam0_GetNumCombatants:
				value = battleGroup->GetNumCombatants();
				break;
			case bgRetIntParam0_GetCombinedExp:
				value = battleGroup->GetCombinedExp();
				break;
			case bgRetIntParam0_GetCombinedGold:
				value = battleGroup->GetCombinedGold();
				break;
		}
	}

	return value;
}



enum bgRetBoolParam0
{
	bgRetBoolParam0_IsDefeated
};

bool MonoRpgBinding::BattleGroup_CallFuncRetBoolParam0( BattleGroup* battleGroup, int functionType )
{
	bool value = false;

	if( battleGroup != null )
	{
		switch(functionType)
		{
			case bgRetBoolParam0_IsDefeated:
				value = battleGroup->IsDefeated();
				break;
		}
	}

	return value;
}



enum bgRetVoidParam0
{
	bgRetVoidParam0_RemoveAllCombatants,
	bgRetVoidParam0_RemoveIncapacitatedCombatants
};

void MonoRpgBinding::BattleGroup_CallFuncRetVoidParam0( BattleGroup* battleGroup, int functionType )
{
	switch(functionType)
	{
		case bgRetVoidParam0_RemoveAllCombatants:
			battleGroup->RemoveAllCombatants();
			break;
		case bgRetVoidParam0_RemoveIncapacitatedCombatants:
			battleGroup->RemoveIncapacitatedCombatants();
			break;
	}
}


enum bgRetVoidParam1
{
	bgRetVoidParam1_AddCombatant,
	bgRetVoidParam1_RemoveCombatant
};

void MonoRpgBinding::BattleGroup_CallFuncRetVoidParam1( BattleGroup* battleGroup, int functionType, void* param )
{
	switch(functionType)
	{
		case bgRetVoidParam1_AddCombatant:
			battleGroup->AddCombatant((Combatant*)param);
			break;
		case bgRetVoidParam1_RemoveCombatant:
			battleGroup->RemoveCombatant((Combatant*)param);
			break;
	}
}



void MonoRpgBinding::BindBattleGroup()
{
	SetNamespace("CatastropheEngine.Rpg.BattleGroup::");

	AddInternalCall("InsertCombatant", BattleGroup_InsertCombatant);
	AddInternalCall("ContainsCombatant", BattleGroup_ContainsCombatant);
	AddInternalCall("GetCombatant", BattleGroup_GetCombatant);

	AddInternalCall("CallFuncRetArrayParam0", BattleGroup_CallFuncRetArrayParam0);
	AddInternalCall("CallFuncRetCombatantParam0", BattleGroup_CallFuncRetCombatantParam0);
	AddInternalCall("CallFuncRetIntParam0", BattleGroup_CallFuncRetIntParam0);
	AddInternalCall("CallFuncRetBoolParam0", BattleGroup_CallFuncRetBoolParam0);
	AddInternalCall("CallFuncRetVoidParam0", BattleGroup_CallFuncRetVoidParam0);
	AddInternalCall("CallFuncRetVoidParam1", BattleGroup_CallFuncRetVoidParam1);

}

