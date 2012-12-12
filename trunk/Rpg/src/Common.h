
#pragma once

#include <Catastrophe/Common.h>

//It's safe to use this globally withouth causing pollution.
USING_NAMESPACE_CE
//using namespace Math;

#define ASSERT CE_ASSERT


class Tile;
class Tileset;
class TilesetManager;
class Map;
class MapLayer;


struct MonsterData;
struct MonsterGroupData;
class MonsterPartyData;


class Item;
class InventoryItem;
class Inventory;
class Equipment;



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

