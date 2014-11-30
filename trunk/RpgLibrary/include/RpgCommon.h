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

// RpgCommon.h
// this file is kept as small as possible to prevent bloat.
// by forward declaring all classes we can prevent having to
// include them in header files.

//includes mostly forward declarations and common macros.
#include <Catastrophe/Common.h>

//It's safe to use this globally withouth causing pollution.
USING_NAMESPACE_CE

#define FORCE_INLINE	FC_FORCE_INLINE
#define NO_INLINE		FC_NO_INLINE
#define ASSERT			CE_ASSERT

#if defined (CE_DEBUG) && !defined (NDEBUG)
	#define TRACE(cond, message) { if(cond) { Log(message); } }
#else
	#define TRACE(cond, message)
#endif
#define Trace TRACE
#define SAFE_DELETE(p) { delete p; p = 0; }

//RPG_API
#if defined RPG_EXPORT
	#define RPG_API __declspec(dllexport)
#elif defined RPG_IMPORT
	#define RPG_API __declspec(dllimport)
#else
	#define RPG_API
#endif

// forward declarations
class Tile;
class TileProperties;
class Tileset;
class TileMap;
class TileMapLayer;
struct TileMapLayerCell;

template <class T> struct AttributeArray;
template <class T, u32 N> struct FixedAttributeArray;

struct Attributes;
struct AttributeFlags;
//struct Buff;
struct Modifier;
struct Item;
struct Skill;
struct Spell;
struct Race;
struct CharacterData;
struct CharacterClass;
struct MonsterData;
struct MonsterGroup;
struct MonsterTroop;
struct MonsterFormation;
struct Encounter;
struct EncounterData;
struct EncounterGroup;
struct FactorSet;
struct ExperienceTable;
struct ExpCurve;

class ItemDrop;
class ItemDropSet;

template <class T> class DataArray;

//resource
class TextureAsset;
class FontAsset;
class SpriteAsset;
class AnimatedSpriteAsset;
class AnimatedSpriteSetAsset;
class ShaderAsset;

class Database;
class Resource;
class ResourceDirectory;
class ResourceCache;
class ResourceManagerTypeBase;
class TextureManager;
class FontManager;
class TilesetManager;
class MapManager;
class ShaderObjectManager;



class RpgStrings;

#define DEFAULT_TILE_SIZE	16


#define MAX_LEVEL		255
#define MAX_PARAMS		4
#define MAX_STATS		16
#define MAX_ELEMENTS	8
#define MAX_STATUS		32
#define MAX_MISC		0

//this must be the sum of all other attribute types
#define MAX_ATTRIBUTES	60

#define MAX_ITEM_FACTORS	4

#define MAX_CLASS_FLAGS		32
#define MAX_FAMILY_FLAGS	32
#define MAX_ITEM_FLAGS		32

#define MAX_SKILL_LV		10



#define MAX_ITEM_DROPS		8
#define MAX_LV				9999
#define MAX_EXP				999999999
#define MAX_GOLD			999999999

#define MAX_PARAM_VALUE		999999999
#define MAX_STAT_VALUE		9999
#define MAX_ELEMENT_VALUE	100
#define MAX_STATUS_VALUE	100

#define MAX_FACTORSET_SIZE	4

//global
extern ResourceDirectory*	g_resourceDirectory;
extern TextureManager*		g_textureManager;
extern FontManager*			g_fontManager;
extern TilesetManager*		g_tilesetManager;
extern MapManager*			g_mapManager;
extern ShaderObjectManager*	g_shaderObjectManager;


void RpgLibInit();
void RpgLibShutdown();

