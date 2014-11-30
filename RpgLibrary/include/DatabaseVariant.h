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

#include "RpgCommon.h"


struct RPG_API DatabaseVariant
{
	enum Type : u8
	{
		Type_Invalid,
		Type_Item,
		Type_Weapon,
		Type_Armor,
		Type_Accessory,
		Type_Monster,
		Type_MonsterTroop,
		Type_MonsterFormation,
		Type_Character,
		Type_CharacterClass,
		Type_Race,
		Type_MiscIconSprite,
		Type_CharacterPortraitSprite,
		Type_CharacterMapSprite,
		Type_CharacterBattleSprite,
		Type_MonsterMapSprite,
		Type_MonsterBattleSprite,
		Type_Shader
	};

	u16	id;
	u16	type;
	//u8	unused;
	static Database* db;

	DatabaseVariant() : id(0), type(Type_Invalid) {}
	DatabaseVariant( Type dataType, u16 id ) : id(id), type((u16)dataType) {}


	Item*					GetItem();
	Item*					GetWeapon();
	Item*					GetArmor();
	Item*					GetAccessory();
	MonsterData*			GetMonster();
	MonsterTroop*			GetMonsterTroop();
	MonsterFormation*		GetMonsterFormation();
	CharacterData*			GetCharacter();
	CharacterClass*			GetCharacterClass();
	Race*					GetRace();
	SpriteAsset*			GetMiscIconSpriteAsset();
	SpriteAsset*			GetCharacterPortraitSpriteAsset();
	AnimatedSpriteSetAsset*	GetCharacterMapSpriteSetAsset();
	AnimatedSpriteSetAsset*	GetCharacterBattleSpriteSetAsset();
	AnimatedSpriteSetAsset*	GetMonsterMapSpriteSetAsset();
	AnimatedSpriteSetAsset*	GetMonsterBattleSpriteSetAsset();
	ShaderAsset*			GetShaderAsset();

};


