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

#include "Actor.h"
#include "Script/MonoRpgBinding.h"



const char* MonoRpgBinding::Actor_GetName( Actor* actor )
{
	SAFE_CALL_RETURN(actor, GetName(), "");
}


void MonoRpgBinding::Actor_SetName( Actor* actor, const char* name )
{
	SAFE_CALL(actor, SetName(name ? name : ""));
}


int MonoRpgBinding::Actor_GetParam( Actor* actor, int param )
{
	if( actor )
		return actor->GetParam(param);
}


int MonoRpgBinding::Actor_GetMaxParam( Actor* actor, int param )
{
	if( actor )
		return actor->GetMaxParam(param);
}


int MonoRpgBinding::Actor_GetUnmodifiedMaxParam( Actor* actor, int param )
{
	if( actor )
		return actor->GetBaseMaxParam(param);
}


int MonoRpgBinding::Actor_GetBaseStat( Actor* actor, int stat )
{
	if( actor )
		return actor->GetBaseStat(stat);
}


int MonoRpgBinding::Actor_GetUnmodifiedBaseStat( Actor* actor, int stat )
{
	if( actor )
		return actor->GetBaseStat(stat);
}


int MonoRpgBinding::Actor_GetDerivedStat( Actor* actor, int stat )
{
	if( actor )
		return actor->GetStat(stat);
}


int MonoRpgBinding::Actor_GetUnmodifiedDerivedStat( Actor* actor, int stat )
{
	if( actor )
		return actor->GetStat(stat);
}


int MonoRpgBinding::Actor_CalculateModifiedMaxParameterValue( Actor* actor, int param )
{
	if( actor )
		return actor->GetStat(param);
}


int MonoRpgBinding::Actor_CalculateModifiedBaseStatValue( Actor* actor, int stat )
{
	if( actor )
		return actor->CalculateModifiedStatValue(stat);
}


int MonoRpgBinding::Actor_CalculateModifiedDerivedStatValue( Actor* actor, int stat )
{
	if( actor )
		return actor->CalculateModifiedStatValue(stat);
}


void MonoRpgBinding::Actor_SetParam( Actor* actor, int param, int value )
{
	if( actor )
		return actor->SetParam(param, value);
}


void MonoRpgBinding::Actor_SetMaxParam( Actor* actor, int param, int value )
{
	if( actor )
		return actor->SetMaxParam(param, value);
}


void MonoRpgBinding::Actor_SetBaseStat( Actor* actor, int stat, int value )
{
	if( actor )
		return actor->GetStat(stat, value);
}


void MonoRpgBinding::Actor_SetDerivedStat( Actor* actor, int stat, int value )
{
	if( actor )
		return actor->GetStat(stat, value);
}



void MonoRpgBinding::BindActor()
{
	SetNamespace("CatastropheEngine.Rpg.ActorBase::");

	// Getters
	AddInternalCall("GetName", Actor_GetName);
	AddInternalCall("SetName", Actor_SetName);
	AddInternalCall("GetParameter", Actor_GetParam);
	AddInternalCall("GetMaxParameter", Actor_GetMaxParam);
	AddInternalCall("GetUnmodifiedMaxParameter", Actor_GetUnmodifiedMaxParam);
	AddInternalCall("GetBaseStat", Actor_GetBaseStat);
	AddInternalCall("GetUnmodifiedBaseStat", Actor_GetUnmodifiedBaseStat);
	AddInternalCall("GetDerivedStat", Actor_GetDerivedStat);
	AddInternalCall("GetUnmodifiedDerivedStat", Actor_GetUnmodifiedDerivedStat);
	AddInternalCall("CalculateModifiedMaxParameterValue", Actor_CalculateModifiedMaxParameterValue);
	AddInternalCall("CalculateModifiedBaseStatValue", Actor_CalculateModifiedBaseStatValue);
	AddInternalCall("CalculateModifiedDerivedStatValue", Actor_CalculateModifiedDerivedStatValue);

	// Setters
	AddInternalCall("SetParameter", Actor_SetParam);
	AddInternalCall("SetMaxParameter", Actor_SetMaxParam);
	AddInternalCall("SetBaseStat", Actor_SetBaseStat);
	AddInternalCall("SetDerivedStat", Actor_SetDerivedStat);


}

