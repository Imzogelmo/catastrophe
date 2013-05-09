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
class Map;
class MapLayer;

template <class T> struct AttributeArray;
template <class T, size_t N> struct FixedAttributeArray;

struct Attributes;
struct AttributeFlags;
struct Item;
struct Skill;
struct Spell;
struct Race;
//struct Character;
struct CharacterClass;
struct Monster;
struct MonsterGroup;
struct MonsterTroop;
struct Encounter;
struct EncounterGroup;
struct ExpTable;
struct ExpCurve;

template <class T> class DataArray;

//resource
class Database;
class Resource;
class ResourceDirectory;
class ResourceCache;
class ResourceManagerTypeBase;
class TextureManager;
class TilesetManager;
class MapManager;



class RpgStrings;



#define MAX_ATTRIBS		4
#define MAX_STATS		16
#define MAX_ELEMENTS	32
#define MAX_STATUS		32
#define MAX_MISC		8

#define MAX_CLASS_FLAGS		32
#define MAX_FAMILY_FLAGS	32
#define MAX_ITEM_FLAGS		32




#define MAX_ITEM_DROPS	8



//global
extern ResourceDirectory*	g_resourceDirectory;
extern TextureManager*		g_textureManager;
extern TilesetManager*		g_tilesetManager;
extern MapManager*			g_mapManager;


void RpgLibInit();
void RpgLibShutdown();

