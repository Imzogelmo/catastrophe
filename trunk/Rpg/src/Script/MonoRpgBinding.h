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



	static void BindActor();

};

