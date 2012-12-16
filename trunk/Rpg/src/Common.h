
#pragma once

// Common.h
// this file is kept as small as possible to prevent bloat.
// by forward declaring all classes we can prevent having to
// include them in header files.

//includes mostly forward declarations and common macros.
#include <Catastrophe/Common.h>

//It's safe to use this globally withouth causing pollution.
USING_NAMESPACE_CE


#define ASSERT CE_ASSERT

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

struct ItemData;
struct MonsterData;
struct MonsterGroupData;
struct EncounterData;

class MonsterPartyData;
class EncounterGroupData;

class ItemList;
class MonsterList;
class MonsterPartyList;
class EncounterGroupList;
class Database;


class Item;
class InventoryItem;
class Inventory;
class Equipment;

class Screen;
class ScreenManager;
class Game;


// angelscript forward declarations
class asIScriptEngine;
class asIScriptModule;
class asIScriptContext;
class asIScriptGeneric;
class asIScriptObject;
class asIObjectType;
class asIScriptFunction;
class asIBinaryStream;
class asIJITCompiler;
struct asSMessageInfo;


//utility macros (normally only for testing)
#define foreachv(vec_type, it, container) \
	for( vec_type::iterator it = container.begin(); it != container.end(); ++it )

#define foreacha(v, array_decl) \
	const size_t size_##array_decl = array_decl.size(); \
	for( size_t v(0); v < size_##array_decl; ++v )

#define foreachi(i, loops) \
	for( int i(0); i < loops; ++i )

