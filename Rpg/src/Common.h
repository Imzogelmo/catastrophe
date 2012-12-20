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

// Common.h
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


// forward declarations
class Tile;
class Tileset;
class TilesetManager;
class Map;
class MapLayer;

struct AttributeData;
struct ItemData;
struct SpellData;
struct MonsterData;
struct MonsterGroupData;
struct EncounterData;
struct CharacterClass;
struct MonsterGroupData;

class MonsterPartyData;
class EncounterGroupData;

class ItemList;
class SpellList;
class MonsterList;
class MonsterPartyList;
class EncounterGroupList;
class EncounterGroupList;
class CharacterClassList;
class Database;


class Item;
class InventoryItem;
class Inventory;
class Equipment;

class Screen;
class ScreenManager;
class Game;


class Resource;
class ResourceCache;
class ResourceManager;


//utility macros (normally only for testing)
#define foreachv(vec_type, it, container) \
	for( vec_type::iterator it = container.begin(); it != container.end(); ++it )

#define foreacha(v, array_decl) \
	const size_t size_##array_decl = array_decl.size(); \
	for( size_t v(0); v < size_##array_decl; ++v )

#define foreachi(i, loops) \
	for( int i(0); i < loops; ++i )

