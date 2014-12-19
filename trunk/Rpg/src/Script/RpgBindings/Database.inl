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

#include "Database.h"
#include "Script/MonoRpgBinding.h"



Item* MonoRpgBinding::Database_GetItem( int id )
{
	return GetDatabase()->GetItem(id);
}


MonsterData* MonoRpgBinding::Database_GetMonster( int id )
{
	return GetDatabase()->GetMonster(id);
}


MonsterTroop* MonoRpgBinding::Database_GetMonsterTroop( int id )
{
	return GetDatabase()->GetMonsterTroop(id);
}


enum DatabasePropertyArrayType
{
	DatabasePropertyArrayType_Item,
	DatabasePropertyArrayType_Monster,
	DatabasePropertyArrayType_Troop

};

u32 MonoRpgBinding::Database_GetCount( int type )
{
	const Database* database = GetDatabase();
	switch(type)
	{
		case DatabasePropertyArrayType_Item: return database->items.size();
		case DatabasePropertyArrayType_Monster: return database->monsters.size();
		case DatabasePropertyArrayType_Troop: return database->monsterTroops.size();
	}

	return 0;
}

/*
void MonoRpgBinding::Database_SetCount( int type, u32 count )
{
	const Database* database = GetDatabase();
	switch(type)
	{
		case DatabasePropertyArrayType_Item:
			database->items.size();
		case DatabasePropertyArrayType_Monster: return database->monsters.size();
		case DatabasePropertyArrayType_Troop: return database->troops.size();
	}

	return 0;
}
*/




void MonoRpgBinding::BindDatabase()
{
	SetNamespace("CatastropheEngine.Rpg.Database::");

	//AddInternalCall("GetSkill", Database_GetSkill);
	//AddInternalCall("GetPassiveSkill", Database_GetPassiveSkill);
	//AddInternalCall("GetSpell", Database_GetSpell);
	AddInternalCall("GetItem", Database_GetItem);
	AddInternalCall("GetCount", Database_GetCount);
	//AddInternalCall("GetWeapon", Database_GetWeapon);
	//AddInternalCall("GetArmor", Database_GetArmor);
	//AddInternalCall("GetAccessory", Database_GetAccessory);
	AddInternalCall("GetMonster", Database_GetMonster);
	AddInternalCall("GetMonsterTroop", Database_GetMonsterTroop);
	//AddInternalCall("GetMonsterFormation", Database_GetMonsterFormation);
	//AddInternalCall("GetCharacter", Database_GetCharacter);
	//AddInternalCall("GetCharacterClass", Database_GetCharacterClass);
	//AddInternalCall("GetRace", Database_GetRace);
	//AddInternalCall("GetExperienceTable", Database_GetExperienceTable);
	//AddInternalCall("GetBattleBackgroundSpritesAsset", Database_GetBattleBackgroundSpritesAsset);
	//AddInternalCall("GetMiscIconSpriteAsset", Database_GetMiscIconSpriteAsset);
	//AddInternalCall("GetCharacterPortraitSpriteAsset", Database_GetCharacterPortraitSpriteAsset);
	//AddInternalCall("GetCharacterMapSpriteSetAsset", Database_GetCharacterMapSpriteSetAsset);
	//AddInternalCall("GetCharacterBattleSpriteSetAsset", Database_GetCharacterBattleSpriteSetAsset);
	//AddInternalCall("GetMonsterMapSpriteSetAsset", Database_GetMonsterMapSpriteSetAsset);
	//AddInternalCall("GetMonsterBattleSpriteSetAsset", Database_GetMonsterBattleSpriteSetAsset);
	//AddInternalCall("GetShaderAsset", Database_GetShaderAsset);

}

